#ifndef M_FILE_HANDLER_H
#define M_FILE_HANDLER_H

#define MAX_FILENAME_SIZE 256
#define MAX_SYSTEM_CALL_SIZE 256

class m_file_handler
{
    public:
        m_file_handler(const char filename[MAX_FILENAME_SIZE]);
        virtual ~m_file_handler();

        bool set_filename(const char filename[MAX_FILENAME_SIZE]);

        const char * get_stripped_filename() {return stripped_filename;}
        const char * get_full_filename() {return filename;}
        const char * get_directory() {return file_directory;}

        static const bool strip_filename(const char * filename, char * cb);

        const char * get_next_file();
        const char * get_latest_file();

        const bool is_last_file(const char * file);

    protected:

    private:
        char filename[MAX_FILENAME_SIZE];
        char stripped_filename[MAX_FILENAME_SIZE];
        char file_directory[MAX_FILENAME_SIZE];
        const long crude_time(const char * file);

        bool strip_filename();
        bool strip_directory();
};

#endif // M_FILE_HANDLER_H
