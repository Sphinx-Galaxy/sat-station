#ifndef M_STATION_H
#define M_STATION_H

#include "m_satellite.h"

#include <vector>

class m_station
{
    public:
        m_station(CoordGeodetic geo, double minimum_elevation=10);
        virtual ~m_station();

        m_satellite* get_next_sat();

    private:
        std::vector<m_satellite*> sat_list;
        CoordGeodetic geo;
        double minimum_elevation;

        void setup();
};

#endif // M_STATION_H
