#ifndef M_RECORDER_H
#define M_RECORDER_H

#include "m_file_handler.h"
#include "m_satellite.h"
#include "m_tle.h"

#include <string>

class m_recorder
{
    public:
        m_recorder(const std::string &audio_folder, int ppm_offset=72, int rtl_device=0);
        virtual ~m_recorder();

        bool record_sat(m_satellite sat);
        std::string get_audiofile_name() {return filename;}

    protected:

    private:
        std::string filename;
        std::string audio_folder;
        int ppm_offset, rtl_device;

        std::string generate_filename(m_satellite sat);
        bool save_audio_to_file();
};

#endif // M_RECORDER_H
