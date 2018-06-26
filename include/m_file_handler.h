#ifndef M_FILE_HANDLER_H
#define M_FILE_HANDLER_H

#include <string>

class m_file_handler
{
    public:
        m_file_handler(const std::string &full_filename);
        virtual ~m_file_handler();

        void set_filename(const std::string &full_filename);

        std::string get_stripped_filename() const {return stripped_filename;}
        std::string get_full_filename() const {return full_filename;}
        std::string get_directory() const {return directory;}

        static std::string strip_filename(const std::string &full_filename);
        static std::string strip_directory(const std::string &full_filename);

        std::string get_latest_file(const std::string &directory);
        std::string get_next_file(const std::string &file);
        bool is_last_file(const std::string &file);

        unsigned long timestamp_to_seconds(const std::string &stripped_filename);
    protected:

    private:
        std::string full_filename, stripped_filename, directory;

};

#endif // M_FILE_HANDLER_H
