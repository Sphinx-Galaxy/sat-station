#include "m_file_handler.h"

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <stdint.h>
#include <sys/stat.h>
#include <time.h>

m_file_handler::m_file_handler(const char filename[MAX_FILENAME_SIZE]) {
    strcpy(this->filename, filename);

    strip_filename();
    strip_directory();
}

m_file_handler::~m_file_handler() {

}

const bool m_file_handler::strip_filename(const char * filename, char * cb) {
    uint8_t character_counter = 0, name_counter = 0;

    while(filename[character_counter] != '.') {
        if(filename[character_counter] == '/')
            name_counter = 0;
        else
            name_counter++;
        character_counter++;
    }

    cb[name_counter] = '\0';
    while(filename[character_counter] != '/') {
        cb[--name_counter] = filename[--character_counter];
    }

    return true;
}

const char * m_file_handler::get_next_file() {
    printf("* m_file_handler::get_next_file() : Check if this works!\n");
    DIR *dir;
    struct dirent *entry;
    struct stat current_file, next_file;
    long long time_current_file, time_next_file = 0, time_tmp_file;

//    stat(filename, &current_file);
    time_current_file = crude_time(stripped_filename); //in seconds please

    if((dir = opendir (file_directory)) == NULL)
        return NULL;

    else {
      while ((entry = readdir(dir)) != NULL) {

//        stat(entry->d_name, &next_file);
        time_tmp_file = crude_time(entry->d_name);
//        printf("* Getting file: %s Time: %d\n", entry->d_name, time_tmp_file);

        if((time_next_file > time_tmp_file || time_next_file == 0) && time_tmp_file > time_current_file && entry->d_name[0] != '.') {
            time_next_file = time_tmp_file;
            sprintf(filename, "%s/%s", file_directory, entry->d_name);
            }
        }
      closedir (dir);
    }

    printf("* New file: %s\n", filename);

    strip_directory();
    strip_filename();

    return filename;
}

const long m_file_handler::crude_time(const char * file) {
    printf("* m_file_handler::crude_time(const char * file) : i dont like this method\n");
    long year = 0, mon = 0, day = 0, hour = 0, mins = 0;
    time_t rawtime;
    struct tm * timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    year += (file[7] - '0')*1000;
    year += (file[8] - '0')*100;
    year += (file[9] - '0')*10;
    year += (file[10] - '0');

    mon += (file[11] - '0')*10;
    mon += (file[12] - '0');

    day += (file[13] - '0')*10;
    day += (file[14] - '0');

    hour += (file[16] - '0')*10;
    hour += (file[17] - '0');

    mins += (file[18] - '0')*10;
    mins += (file[19] - '0');

    timeinfo->tm_year =  2000 - 1900;
    timeinfo->tm_mon = mon - 1;
    timeinfo->tm_mday = day;
    timeinfo->tm_hour = hour;
    timeinfo->tm_min = mins;

  /* call mktime: timeinfo->tm_wday will be set */
    long time = mktime ( timeinfo );

    return time;
}



const bool m_file_handler::is_last_file(const char * file) {
    std::string str1 = file;
    std::string str2 = filename;

    if(str1.compare(str2) == true)
        return true;
    else
        return false;
}

const char * m_file_handler::get_latest_file() {
    printf("* GET_LATEST_FILE : Not implemented\n");
}

bool m_file_handler::set_filename(const char filename[MAX_FILENAME_SIZE]) {
    strcpy(this->filename, filename);

    return strip_filename() && strip_directory();
}

bool m_file_handler::strip_filename() {
    m_file_handler::strip_filename(filename, stripped_filename);

    return true;
}

bool m_file_handler::strip_directory() {
    uint8_t character_counter = 0, name_counter = 0;

    while(filename[character_counter] != '.') {
        if(filename[character_counter] == '/')
            name_counter = character_counter;
        character_counter++;
    }

    character_counter = 0;

    while(character_counter < name_counter) {
        file_directory[character_counter] = filename[character_counter];
        character_counter++;
    }
    file_directory[character_counter] = '\0';

    return true;
}
