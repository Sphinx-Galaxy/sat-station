#ifndef M_SATELLITE_H
#define M_SATELLITE_H

#include "m_tle.h"


#include <time.h>

class m_satellite
{
    public:
        m_satellite(CoordGeodetic geo, const double minimum_elevation);
        virtual ~m_satellite();

        const unsigned long get_next_sat_time() {return sat_now.next_rising_time_utc;}
        const unsigned long get_next_sat_frequency() {return sat_now.frequency;}
        const char * get_next_sat_name() {return sat_now.name;}
        const m_sat get_next_sat() {return sat_now;}

        const bool set_next_sat();

    protected:
    private:
        double minimum_elevation;
        const int time_step = 180;
        CoordGeodetic user_geo;
        DateTime start_time;
        struct m_sat sat_now;
        const struct m_sat sat_list[NUMBER_OF_SATS] = {noaa15, noaa18, noaa19, meteor};


        const DateTime calc_sat_rising_time(struct m_sat sat);
        const double FindMaxElevation(SGP4& sgp4, const DateTime& aos, const DateTime& los);
        const DateTime FindCrossingPoint(SGP4& sgp4, const DateTime& initial_time1, const DateTime& initial_time2, bool finding_aos);
};

#endif // M_SATELLITE_H
