#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <mutex>
#include <thread>

enum class Log_level : uint8_t 
{
    DEBUG,
    INFO,
    WARNING,
    ERROR,
    CRITICAL,
};

class Logger
{
    protected:
        // Check problematic code to race condition resolution by using mutex.
        std::mutex log_mutex;
        const std::string LOG_DIR = "logs";
        const std::string LOG_FILE_PATH = LOG_DIR + "/genpass.log";
    public:
        Logger();
        ~Logger();
        void log(Log_level level, const std::string& message);
    private:
        std::ofstream log_file;
        std::string level_to_string(Log_level level);
};
#endif // LOG_H