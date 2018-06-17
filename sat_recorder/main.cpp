#include <iostream>
#include <stdlib.h>
#include "m_file_handler.h"
#include "m_wxxer.h"
#include "m_satellite.h"
#include "m_recorder.h"
#include "m_station.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "Observer.h"
#include "SGP4.h"
#include "Util.h"
#include "CoordTopocentric.h"
#include "CoordGeodetic.h"

using namespace std;

int main(int argc, char * argv[])
{
    CoordGeodetic geo(52.637, 9.223, 10); //Change here if you want different longitude, latitude, altitude
    m_station station(geo, 40);
    m_satellite *sat;

	bool firstrun = true;
    time_t local_time;
    std::string forecast_folder = "/home/mattis/weather/forecast";
    std::string map_folder =  "/home/mattis/weather/map";//Change here if you want it to store things in different folders
    std::string audio_folder = "/home/mattis/weather/audio";

    //Better change nothing here...
    while(true) {
        if(!firstrun)
            sleep(90);

        sat = station.get_next_sat();
        std::cout << "Setting next sat:\nAOS: " << sat->get_aos_seconds() << " LOS: " << sat->get_los_seconds() << std::endl;

        time(&local_time);
        std::cout << "Waiting now: " << (sat->get_aos_seconds()-local_time) << " seconds" << std::endl;
        sleep(sat->get_aos_seconds() - local_time);

        //System call to kill all sdr
        //system("ps -ef | grep 'rtl_sdr' | grep -v grep | awk '{print $2}' | xargs -r kill -9");

        //Record Audio
        m_recorder rec(audio_folder, 72, 1);
        rec.record_sat(*sat);

        //Make weather forecas
        m_wxxer wxxer(rec.get_audiofile_name(), map_folder, forecast_folder, {"MCIR"});
        wxxer.create_forecast();

	firstrun=false;
}


    cout << endl << "Successfull end!" << endl;
    return 0;
}
