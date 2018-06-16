#include "m_station.h"

#include "m_tle.h"

#include <climits>

m_station::m_station(CoordGeodetic geo, double minimum_elevation)
{
    this->minimum_elevation = minimum_elevation;
    this->geo = geo;
    setup();
}

m_station::~m_station()
{
    //dtor
}

m_satellite* m_station::get_next_sat() {
    std::cout << "Getting next satellite" << std::endl;
    //Create time variable
    unsigned long time = ULONG_MAX;
    size_t sat_number;

    for(size_t i = 0; i < sat_list.size(); i++) {
        sat_list[i]->update();
        if(time > sat_list[i]->get_aos_seconds())
            sat_number = i;
    }
    return sat_list[sat_number];
}

void m_station::setup() {
    sat_list.push_back(new m_satellite(geo, minimum_elevation, {"NOAA15", &noaa15_tle, 1371000, 60000}));

    /*struct sat_config noaa18 = {"NOAA18", &noaa18_tle, 1371000, 60000};
    sat_list.push_back(new m_satellite(geo, minimum_elevation, noaa18));

    struct sat_config noaa19 = {"NOAA19", &noaa19_tle, 1371000, 60000};
    sat_list.push_back(new m_satellite(geo, minimum_elevation, noaa19));

    struct sat_config meteor = {"Meteor", &meteor_tle, 1371000, 60000};
    sat_list.push_back(new m_satellite(geo, minimum_elevation, meteor));
*/}