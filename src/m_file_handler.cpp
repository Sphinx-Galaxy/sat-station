#include "m_file_handler.h"

#include <algorithm>
#include <cassert>
#include <dirent.h>
#include <iostream>
#include <sys/stat.h>
#include <ctime>

m_file_handler::m_file_handler(const std::string &full_filename) {
    set_filename(full_filename);
}

m_file_handler::~m_file_handler() {

}

std::string m_file_handler::strip_filename(const std::string &full_filename) {
    size_t start = full_filename.find_last_of('/')+1;
    size_t stop = full_filename.find_last_of('.');

    std::string temp = full_filename.substr(start, stop-start);

    std::cout << "Stripping Filename: " << full_filename << " : " << temp << std::endl;

    return temp;
}

std::string m_file_handler::get_next_file(const std::string &file) {
    DIR *dir;
    struct dirent *entry;
    std::string next_file_str;
    struct stat current_file, next_file;
    unsigned long time_current_file, time_next_file = 0, time_tmp_file;

    time_current_file = timestamp_to_seconds(strip_filename(file)); //in seconds please

    dir = opendir(strip_directory(file).c_str());
    assert(dir);

    while ((entry = readdir(dir)) != NULL) {
        time_tmp_file = timestamp_to_seconds(entry->d_name);

        if((time_next_file > time_tmp_file || time_next_file == 0) && time_tmp_file > time_current_file && entry->d_name[0] != '.') {
            time_next_file = time_tmp_file;
            next_file_str = strip_directory(file) + "/" + std::string(entry->d_name);
        }
    }
    closedir (dir);

    std::cout << "Previous file: " << file << " Next file: " << next_file_str;

    return next_file_str;
}

unsigned long m_file_handler::timestamp_to_seconds(const std::string &stripped_filename) {
    long year = 0, mon = 0, day = 0, hour = 0, mins = 0;
    time_t rawtime;
    struct tm * timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    size_t pos;

    for(pos = 0; pos < stripped_filename.size(); pos++)
        if(stripped_filename[pos] == '_')
            break;

    year += (stripped_filename[pos++] - '0')*1000;
    year += (stripped_filename[pos++] - '0')*100;
    year += (stripped_filename[pos++] - '0')*10;
    year += (stripped_filename[pos++] - '0');

    mon += (stripped_filename[pos++] - '0')*10;
    mon += (stripped_filename[pos++] - '0');

    day += (stripped_filename[pos++] - '0')*10;
    day += (stripped_filename[pos++] - '0');

    hour += (stripped_filename[pos++] - '0')*10;
    hour += (stripped_filename[pos++] - '0');

    mins += (stripped_filename[pos++] - '0')*10;
    mins += (stripped_filename[pos++] - '0');

    timeinfo->tm_year =  year - 1900;
    timeinfo->tm_mon = mon - 1;
    timeinfo->tm_mday = day;
    timeinfo->tm_hour = hour;
    timeinfo->tm_min = mins;

  /* call mktime: timeinfo->tm_wday will be set */
    long time = mktime ( timeinfo );

    return time;
}



bool m_file_handler::is_last_file(const std::string &file) {
    std::string str1 = file;
    std::string str2 = full_filename;

    if(str1.compare(str2) == true)
        return true;
    else
        return false;
}

std::string m_file_handler::get_latest_file(const std::string &directory) {
    std::cout << "Not implemented yet" << std::endl;
    assert(false);
}

void m_file_handler::set_filename(const std::string &full_filename) {
    this->full_filename = full_filename;
    this->stripped_filename = strip_filename(full_filename);
    this->directory = strip_directory(full_filename);
}

std::string m_file_handler::strip_directory(const std::string &full_filename) {
    size_t character_counter = 0, name_counter = 0;
    std::string temp;

    while(full_filename[character_counter] != '.') {
        if(full_filename[character_counter] == '/')
            name_counter = character_counter;
        character_counter++;
        assert(character_counter <= full_filename.size());
    }

    character_counter = 0;

    while(character_counter < name_counter) {
        temp.push_back(full_filename[character_counter]);
        character_counter++;
        assert(character_counter <= full_filename.size());
    }

    std::cout << "Stripping Directory: " << full_filename << " : " << temp << std::endl;

    return temp;
}
