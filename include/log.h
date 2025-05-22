#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <mutex>
#include <thread>

enum class log_level : uint8_t 
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
    public:
        Logger(const std::string& filename);
        ~Logger();
        void log(log_level level, const std::string& message);
    private:
        std::ofstream log_file;
        std::string level_to_string(log_level level);
};
#endif // LOG_H