#ifndef M_STATION_H
#define M_STATION_H

#include "m_satellite.h"

#include <vector>

class m_station
{
    public:
        m_station();
        virtual ~m_station();

        m_satellite get_next_sat();

        void setup();

    private:
        std::vector<m_satellite*> sat_list;
};

#endif // M_STATION_H
