#include "m_wxxer.h"

#include "m_file_handler.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

m_wxxer::m_wxxer(const char * audio_file, const char * map_folder, const char * forecast_folder) {
    strcpy(this->audio_file , audio_file);
    strcpy(this->map_folder , map_folder);
    strcpy(this->forecast_folder , forecast_folder);
    m_file_handler::strip_filename(audio_file, stripped_filename);
}

m_wxxer::~m_wxxer()
{
    //dtor
}

const bool m_wxxer::create_forecast() {
    printf("* m_wxxer::create_forecast() : Add more options\n");
    char system_call[MAX_SYSTEM_CALL_SIZE];

    sprintf(map_file, "%s/%s-%s", map_folder, stripped_filename, "map.png");

    create_map();

    //TODO More Options

    //while(options) {
        //sprintf(system_call, "wxtoimg %s...");
        //system(system_call);

    set_forecast_file();
sprintf(system_call, "%s -c -a -m %s %s %s/%s-%s.png", "wxtoimg", map_file, audio_file, forecast_folder, stripped_filename, "A");
system(system_call);

sprintf(system_call, "%s -c -b -m %s %s %s/%s-%s.png", "wxtoimg", map_file, audio_file, forecast_folder, stripped_filename, "B");
	system(system_call);

sprintf(system_call, "%s -e %s -m %s %s %s/%s-%s.png", "wxtoimg", "MCIR", map_file, audio_file, forecast_folder, stripped_filename, "MCIR");
	system(system_call);

sprintf(system_call, "%s -e %s -m %s %s %s/%s-%s.png", "wxtoimg", "therm", map_file, audio_file, forecast_folder, stripped_filename, "Temp");
	system(system_call);

    return true;
}

const bool m_wxxer::set_map_file() {
    sprintf(map_file, "%s/%s-map.png", map_folder, stripped_filename);
    return map_file!=NULL;
}

const bool m_wxxer::set_forecast_file() {
    printf("* m_wxxer::set_forecast_file() : Add more options\n");
    sprintf(forecast_file, "%s/%s-%s.png", forecast_folder, stripped_filename, "MCIR");

    return forecast_file!=NULL;
}


const bool m_wxxer::create_map() {
    char system_call[MAX_SYSTEM_CALL_SIZE];

    set_map_file();
    sprintf(system_call, "%s -T %s %s %s", "wxmap", get_sat_name(), get_utc(), map_file);

	printf("* System call: \"%s\"\n", system_call);

    if(!system(system_call)) {
        printf("* System call: \"%s\" failed\n", system_call);
        return false;
    }

    return true;
}

const char * m_wxxer::get_utc() {
    printf("* m_wxxer::get_utc(const char * filename) : Change this later\n");
    sprintf(UTC, "\"%c%c %c%c %c%c%c%c %c%c:%c%c UTC\"",
        stripped_filename[13], stripped_filename[14], stripped_filename[11], stripped_filename[12],
        stripped_filename[7], stripped_filename[8], stripped_filename[9], stripped_filename[10],
        stripped_filename[16], stripped_filename[17], stripped_filename[18], stripped_filename[19]);

    return UTC;
}

const char * m_wxxer::get_sat_name() {
    printf("* m_wxxer::get_sat_name(const char * filename) : Please fix this\n");

    sprintf(sat_name, "\"NOAA %c%c\"\0", stripped_filename[4], stripped_filename[5]);

    return sat_name;
}
