#ifndef M_WXXER_H
#define M_WXXER_H

#include "m_file_handler.h"

#include <vector>

class m_wxxer
{
    public:
        m_wxxer(const std::string &audio_file, const std::string &map_folder,
                const std::string &forecast_folder, const std::vector<std::string> &options);
        virtual ~m_wxxer();

        void create_forecast();
        void create_map();

        std::string get_map_file() const {return map_file;}
        std::string get_utc() const {return UTC;}
        std::string get_sat_name() const {return sat_name;}

    protected:
    private:
        std::vector<std::string> options;
        std::string audio_file;
        std::string forecast_folder;
        std::string map_folder;

        std::string stripped_filename;
        std::string map_file;
        std::string forecast_file;

        std::string UTC;
        std::string sat_name;

        void set_utc();
        void set_map_file();
        void set_sat_name();
        void set_forecast_file(const std::string &option);
};

inline void m_wxxer::set_map_file() {
    map_file = map_folder + "/" + stripped_filename + "_map.png";
}

inline void m_wxxer::set_forecast_file(const std::string &option) {
    forecast_file = forecast_folder + "/" + stripped_filename + "-" + option + ".png";
}

#endif // M_WXXER_H
