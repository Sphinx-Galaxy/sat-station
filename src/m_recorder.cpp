#include "m_recorder.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

m_recorder::m_recorder(const std::string &audio_folder, int ppm_offset, int rtl_device)
{
    this->rtl_device = rtl_device;
    this->ppm_offset = ppm_offset;
    this->audio_folder = audio_folder;
}

m_recorder::~m_recorder()
{
    //dtor
}

std::string m_recorder::generate_filename(m_satellite sat) {
    filename.clear();

    filename = audio_folder + "/";
    filename += std::to_string(sat.get_los().Year());
    filename += (sat.get_los().Month() < 10 ? "0" : "") + std::to_string(sat.get_los().Month());
    filename += (sat.get_los().Day() < 10 ? "0" : "") + std::to_string(sat.get_los().Day());
    filename += (sat.get_los().Hour() < 10 ? "0" : "") + std::to_string(sat.get_los().Hour());
    filename += (sat.get_los().Minute() < 10 ? "0" : "") + std::to_string(sat.get_los().Minute());
    filename += "_";
    filename += sat.get_sat_config().name;
    filename += ".wav";

    std::cout << "Created audio filename: " << filename << std::endl;

    return filename;
}

bool m_recorder::record_sat(m_satellite sat) {
    std::string systemcall;

    systemcall.clear();
    systemcall = "timeout " + std::to_string(sat.get_los_seconds() - sat.get_aos_seconds());
    systemcall += " ./rtl_fm -d " + std::to_string(rtl_device);
    systemcall += " -M fm ";
    systemcall += " -f " + std::to_string(sat.get_sat_config().frequency);
    systemcall += " -s " + std::to_string(sat.get_sat_config().bandwidth);
    systemcall += " -p " + std::to_string(ppm_offset);
    systemcall += " -F 9 ";
    systemcall += " | ";
    systemcall += " sox -t raw ";
    systemcall += " -r " + std::to_string(sat.get_sat_config().bandwidth);
    systemcall += " -es -b16 -c1 -V1 ";
    systemcall += " - " + generate_filename(sat);
    systemcall += " rate 11025";

    std::cout << "Record systemcall: " << systemcall << std::endl;

    //systemcall = "touch " + generate_filename(sat);

    system(systemcall.c_str());
    return true;
}
