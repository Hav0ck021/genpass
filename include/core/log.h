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

namespace Log
{
    // Check problematic code to race condition resolution by using mutex.
    extern std::mutex log_mutex;
    extern std::ofstream log_file;
    const std::string LOG_DIR = "logs";
    const std::string LOG_FILE_PATH = LOG_DIR + "/genpass.log";

    void create_log_file();
    std::string level_to_string(Log_level level);
    void log(Log_level level, const std::string& message);
};

#endif // LOG_H