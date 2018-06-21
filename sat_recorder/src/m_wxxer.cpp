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
        systemcall += " -c ";

/*        if(std::compare(options.at(i), "A") == 0)
            systemcall += " -a";
        if(std::compare(options.at(i), "B") == 0)
            systemcall += " -b";*/

        systemcall += " -e";
        systemcall += " " + options.at(i);

        systemcall += " -m " + map_file;
        systemcall += " " + audio_file;
        systemcall += " " + forecast_file;

        system(systemcall.c_str());
    }
}

void m_wxxer::create_map() {
    std::string systemcall;

    set_utc();
    set_map_file();

    systemcall = "wxmap";
    systemcall += " -T " + get_sat_name();
    systemcall += " " + get_utc();
    systemcall += " " + get_map_file();

    std::cout << "Create map with systemcall: " << systemcall << std::endl;

    system(systemcall.c_str());
}

void m_wxxer::set_utc() {
    size_t utc_pos = 0;

    for(size_t i = 0; i < 1; i++) { //To skip the first '_' position
        for(; utc_pos < stripped_filename.size(); utc_pos++) {
            if(stripped_filename[utc_pos] == '_')
                break;
        }
    }

    for(size_t i = 0; i < stripped_filename.size();)
        UTC.push_back(stripped_filename[utc_pos+i]);

    std::cout << "Extract utc from: " << stripped_filename << " : " << UTC << std::endl;
}

void m_wxxer::set_sat_name() {

    for(size_t i = 0; i < stripped_filename.size(); i++) {
        if(stripped_filename[i] == '_')
            break;
        sat_name.push_back(stripped_filename[i]);
    }

    std::cout << "Extract sat name from: " << stripped_filename << " : " << sat_name << std::endl;
}
