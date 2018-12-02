#include "m_satellite.h"

#include "Observer.h"
#include "Util.h"
#include "SGP4.h"
#include "CoordTopocentric.h"
#include "CoordGeodetic.h"
#include <float.h>

#define PI 3.1415926

#include <cmath>
#include <list>

m_satellite::m_satellite(CoordGeodetic geo, double minimum_elevation, const struct sat_config &sat_cfg) {
    this->user_geo = geo;
    this->minimum_elevation = minimum_elevation*PI/180;
    this->sat_cfg = sat_cfg;
}

m_satellite::~m_satellite() {
    //dtor
}

void m_satellite::update() {
    std::cout << "Update sat: " << sat_cfg.name << std::endl;
    std::cout << "TLE: \n" << sat_cfg.tle->Line1() << std::endl << sat_cfg.tle->Line2() << std::endl;

    start_time = DateTime::Now();

    if(!calc_sat_rising_time())
        aos = time(NULL);
    else {
        SGP4 sgp4(*(sat_cfg.tle));
        max_elevation = find_max_elevation(sgp4, aos, los);
    }

    //Erase 10% of time after LOS and AOS to save space, because the sat isn't directly available
    DateTime signal(0.1*(los.Ticks() - aos.Ticks()));
    aos.AddTicks(signal.Ticks());
    los.AddTicks(-signal.Ticks());

    std::cout << "aos: " << get_aos_seconds() << " los: " << get_los_seconds() << std::endl;
}

unsigned long m_satellite::datetime_to_seconds(const DateTime &date) {
    struct tm *tm_now;
    time_t rawtime;
    tm_now = gmtime(&rawtime);

    tm_now->tm_year = date.Year()-1900;
    tm_now->tm_mon = date.Month()-1;
    tm_now->tm_mday = date.Day();
    tm_now->tm_hour = date.Hour();
    tm_now->tm_min = date.Minute();
    tm_now->tm_sec = date.Second();

    return mktime(tm_now);
}

DateTime m_satellite::seconds_to_datetime(const unsigned long seconds) {
/*    DateTime date;
    struct tm *tm_now;
    time_t rawtime = seconds;
    tm_now = gmtime(&rawtime);

    date.Year() = tm_now->tm_year+1900;
    tm_now->tm_year = date.Year()-1900;
    tm_now->tm_mon = date.Month()-1;
    tm_now->tm_mday = date.Day();
    tm_now->tm_hour = date.Hour();
    tm_now->tm_min = date.Minute();
    tm_now->tm_sec = date.Second();

    return mktime(tm_now);*/
}

double m_satellite::find_max_elevation(SGP4& sgp4, const DateTime& aos, const DateTime& los) {
    Observer obs(user_geo);
    bool running = true;
    double time_step = (los - aos).TotalSeconds() / 9.0;
    DateTime current_time(aos); //! current time
    DateTime time1(aos); //! start time of search period
    DateTime time2(los); //! end time of search period
    double max_elevation; //! max elevation

    do
    {
        running = true;
        max_elevation = -99999999999999.0;
        while (running && current_time < time2)
        {
            Eci eci = sgp4.FindPosition(current_time);
            CoordTopocentric topo = obs.GetLookAngle(eci);

            if (topo.elevation > max_elevation)
            {
                //rising
                max_elevation = topo.elevation;
                //move time along
                current_time = current_time.AddSeconds(time_step);
                if (current_time > time2)
                    current_time = time2;
            }
            else
                running = false;
        }

        //Take timestep back
        time1 = current_time.AddSeconds(-2.0 * time_step);
        time2 = current_time;
        current_time = time1;

        //Recalc timestep
        time_step = (time2 - time1).TotalSeconds() / 9.0;
    }
    while (time_step > 1.0);

//    printf("* Maximum elevation: %lf\n", max_elevation);

    return max_elevation;
}

bool m_satellite::calc_sat_rising_time() {
//    printf("* Calc sat %s rising time\n", sat.name);
    DateTime end_time = start_time.AddDays(3);
    SGP4 sgp4(*(sat_cfg.tle));
    Observer obs(user_geo);

    DateTime aos_time;
    DateTime los_time;

    bool found_aos = false;

    DateTime previous_time(start_time);
    DateTime current_time(start_time);

//    printf("* Starttime: Y: %d M: %d D: %d HH: %d MM: %d\n", start_time.Year(), start_time.Month(), start_time.Day(), start_time.Hour(), start_time.Minute());
//    printf("* Endtime: Y: %d M: %d D: %d HH: %d MM: %d\n", end_time.Year(), end_time.Month(), end_time.Day(), end_time.Hour(), end_time.Minute());

    while (current_time < end_time) {
        bool end_of_pass = false;

        //calculate satellite position
        Eci eci = sgp4.FindPosition(current_time);
        CoordTopocentric topo = obs.GetLookAngle(eci);

        if (!found_aos && topo.elevation > 0.0) {
            //aos hasnt occured yet, but the satellite is now above horizon
            //this must have occured within the last time_step
            if (start_time == current_time) {
                //satellite was already above the horizon at the start,
                //so use the start time
//                printf("* Satellite already above the horizion\n");
                aos_time = start_time;
            }
            else {
                //find the point at which the satellite crossed the horizon
                aos_time = find_crossing_point(
                        sgp4,
                        previous_time,
                        current_time,
                        true);
            }
            found_aos = true;
        }
        else if (found_aos && topo.elevation < 0.0) {
            found_aos = false;
            //end of pass, so move along more than time_step
            end_of_pass = true;
            // already have the aos, but now the satellite is below the horizon,
            // so find the los
            los_time = find_crossing_point(
                    sgp4,
                    previous_time,
                    current_time,
                    false);

            if(find_max_elevation(sgp4, aos_time, los_time) >= minimum_elevation) {
                aos = aos_time;
                los = los_time;
                return true;
            }
        }

        //save current time
        previous_time = current_time;

        if (end_of_pass) {
            //at the end of the pass move the time along by 30mins
            current_time = current_time + TimeSpan(0, 30, 0);
        }
        else {
            //move the time along by the time step value
            current_time = current_time + TimeSpan(0, 0, time_step);
        }

        if (current_time > end_time) {
            //dont go past end time
            current_time = end_time;
        }
    }
    return false;
}

DateTime m_satellite::find_crossing_point(SGP4& sgp4, const DateTime& initial_time1, const DateTime& initial_time2, bool finding_aos)
{
    Observer obs(user_geo);

    bool running;
    int cnt;

    DateTime time1(initial_time1);
    DateTime time2(initial_time2);
    DateTime middle_time;

    running = true;
    cnt = 0;
    while (running && cnt++ < 16) {
        middle_time = time1.AddSeconds((time2 - time1).TotalSeconds() / 2.0);
        //calculate satellite position
        Eci eci = sgp4.FindPosition(middle_time);
        CoordTopocentric topo = obs.GetLookAngle(eci);

        if (topo.elevation > 0.0) {
            //satellite above horizon
            if (finding_aos)
                time2 = middle_time;
            else
                time1 = middle_time;
        }
        else {
            if (finding_aos)
                time1 = middle_time;
            else
                time2 = middle_time;
        }

        if ((time2 - time1).TotalSeconds() < 1.0) {
            //two times are within a second, stop
            running = false;
            //remove microseconds
            int us = middle_time.Microsecond();
            middle_time = middle_time.AddMicroseconds(-us);
            //step back into the pass by 1 second
            middle_time = middle_time.AddSeconds(finding_aos ? 1 : -1);
        }
    }


    //go back/forward 1second until below the horizon
    running = true;
    cnt = 0;
    while (running && cnt++ < 6) {
        Eci eci = sgp4.FindPosition(middle_time);
        CoordTopocentric topo = obs.GetLookAngle(eci);
        if (topo.elevation > 0)
            middle_time = middle_time.AddSeconds(finding_aos ? -1 : 1);
        else
            running = false;
    }
    return middle_time;
}
