#include <iostream>
#include <stdlib.h>
#include "m_file_handler.h"
#include "m_wxxer.h"
#include "m_satellite.h"
#include "m_recorder.h"

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
/*    CoordGeodetic geo(52.637, 9.223, 10); //Change here if you want different longitude, latitude, altitude
    m_satellite gen_sat(geo, 40); //Change here if you want a different degree of elevation

	bool firstrun = true;
    time_t local_time;
    char * forecast_folder = "/home/mattis/weather/forecast"; //Change here if you want it to store things in different folders
    char * map_folder = "/home/mattis/weather/map";
    char * audio_folder = "/home/mattis/weather/audio";

    //Better change nothing here...
    while(true) {
	if(!firstrun)
		sleep(90);

        gen_sat.set_next_sat();
        printf("* Next rising time: %ld UTC seconds\n", gen_sat.get_next_sat_time());

        time(&local_time);
        printf("* Sleep for: %d seconds\n", gen_sat.get_next_sat_time() - local_time);
        sleep(gen_sat.get_next_sat_time() - local_time);

	//System call to kill all sdr
	system("ps -ef | grep 'rtl_sdr' | grep -v grep | awk '{print $2}' | xargs -r kill -9");
	sleep(3);

        //Record Audio
        m_recorder m_rec(gen_sat.get_next_sat(), audio_folder);
        m_rec.record_sat();

        //Make weather forecast
        m_wxxer m_forecaster(m_rec.get_audiofile_name(), map_folder, forecast_folder);
        m_forecaster.create_forecast();

	firstrun=false;
}


    cout << endl << "Successfull end!" << endl;
    return 0;*/
}
