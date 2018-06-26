#include "m_wxxer.h"

#include "m_file_handler.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

m_wxxer::m_wxxer(const std::string &audio_file, const std::string &map_folder,
                const std::string &forecast_folder, const std::vector<std::string> &options){
    this->audio_file = audio_file;
    this->map_folder = map_folder;
    this->forecast_folder = forecast_folder;
    this->stripped_filename = m_file_handler::strip_filename(audio_file);
    this->options = options;
}

m_wxxer::~m_wxxer(){}

void m_wxxer::create_forecast() {
    std::string systemcall;

    create_map();

    for(size_t i = 0; i < options.size(); i++) {
        set_forecast_file(options[i]);

        systemcall = "wxtoimg";
        systemcall += " -c";

/*        if(std::compare(options.at(i), "A") == 0)
            systemcall += " -a";
        if(std::compare(options.at(i), "B") == 0)
            systemcall += " -b";*/

        systemcall += " -e";
        systemcall += " " + options.at(i);

        systemcall += " -m " + map_file;
        systemcall += " " + audio_file;
        systemcall += " " + forecast_file;

        std::cout << "Create picture with systemcall: " << systemcall << std::endl;

        system(systemcall.c_str());
    }
}

void m_wxxer::create_map() {
    std::string systemcall;

    set_utc();
    set_map_file();
    set_sat_name();

    systemcall = "wxmap";
    //systemcall += " -T " + get_sat_name();
    systemcall += " " + get_utc();
    systemcall += " " + get_map_file();

    std::cout << "Create map with systemcall: " << systemcall << std::endl;

    system(systemcall.c_str());
}

void m_wxxer::set_utc() {
    size_t utc_start = stripped_filename.find('_')+1;
    size_t utc_stop = stripped_filename.find('.');

    UTC = stripped_filename.substr(utc_start, utc_stop-utc_start);

    std::cout << "Extract utc from: " << stripped_filename << " : " << UTC << std::endl;
}

//todo, wxmap needs "NOAA 19" but i use "NOAA19"
void m_wxxer::set_sat_name() {
    size_t name_start = 0;
    size_t name_stop = stripped_filename.find('_');

    sat_name = stripped_filename.substr(name_start, name_stop-name_start);

    std::cout << "Extract sat name from: " << stripped_filename << " : " << sat_name << std::endl;
}
