#ifndef M_SATELLITE_H
#define M_SATELLITE_H

#include "m_tle.h"

#include <string>
#include <time.h>

struct sat_config {
    std::string name;
    Tle *tle;

    unsigned long frequency;
    unsigned long bandwidth;
    std::string modulation;
};

class m_satellite
{
    public:
        m_satellite(CoordGeodetic geo, double minimum_elevation, const struct sat_config &sat_cfg);
        virtual ~m_satellite();


        unsigned long get_aos_seconds() {return datetime_to_seconds(aos);}
        unsigned long get_los_seconds() {return datetime_to_seconds(los);}
        DateTime get_aos() {return aos;}
        DateTime get_los() {return los;}
        double get_max_elevation() const {return max_elevation;}
        struct sat_config get_sat_config() const {return sat_cfg;};

        void update();

    protected:
    private:
        struct sat_config sat_cfg;
        double minimum_elevation;
        CoordGeodetic user_geo;

        DateTime aos;
        DateTime los;
        double max_elevation;

        const int time_step = 180;
        DateTime start_time;

        double find_max_elevation(SGP4& sgp4, const DateTime& aos, const DateTime& los);
        bool calc_sat_rising_time();
        DateTime find_crossing_point(SGP4& sgp4, const DateTime& initial_time1, const DateTime& initial_time2, bool finding_aos);
        unsigned long datetime_to_seconds(const DateTime &date);
        DateTime seconds_to_datetime(const unsigned long seconds);
};

#endif // M_SATELLITE_H
