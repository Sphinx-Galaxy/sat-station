#ifndef M_RECORDER_H
#define M_RECORDER_H

#include "m_file_handler.h"
#include "m_tle.h"

class m_recorder
{
    public:
        m_recorder(struct m_sat sat, const char * audio_directory);
        virtual ~m_recorder();

        const bool record_sat();
        const char * get_audiofile_name() {return filename;}

    protected:

    private:
        struct m_sat sat;
        char filename[MAX_FILENAME_SIZE];
        char audio_directory[MAX_FILENAME_SIZE];

        const char * generate_filename();
        const bool save_audio_to_file();
};

#endif // M_RECORDER_H
