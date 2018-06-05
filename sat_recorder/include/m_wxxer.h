#ifndef M_WXXER_H
#define M_WXXER_H

#include "m_file_handler.h"

class m_wxxer
{
    public:
        m_wxxer(const char * audio_file, const char * map_folder, const char * forecast_folder);
        virtual ~m_wxxer();

        const bool create_forecast();
        const bool create_map();
        const char * get_utc();

    protected:
    private:
        const char * get_sat_name();
        const bool set_map_file();
        const bool set_forecast_file();

        enum options {MCIR};

        char stripped_filename[MAX_FILENAME_SIZE];
        char audio_file[MAX_FILENAME_SIZE];
        char map_file[MAX_FILENAME_SIZE];
        char forecast_file[MAX_FILENAME_SIZE];

        char forecast_folder[MAX_FILENAME_SIZE];
        char map_folder[MAX_FILENAME_SIZE];
        char UTC[MAX_FILENAME_SIZE];
        char sat_name[MAX_FILENAME_SIZE];
};

#endif // M_WXXER_H
