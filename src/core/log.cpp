#include "core/log.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>
#include <ctime>
#include <thread>
#include <mutex>

std::mutex Log::log_mutex;

std::ofstream Log::log_file;

void Log::create_log_file()
{
    struct stat st{};
    if (stat(Log::LOG_DIR.c_str(), &st) == -1) {
        if (mkdir(Log::LOG_DIR.c_str(), 0755) != 0) {
            std::cerr << "Failed to create log directory: " << Log::LOG_DIR << '\n';
            perror("mkdir");
            return;
        }
    }
    Log::log_file.open(Log::LOG_FILE_PATH.c_str(), std::ios::app);
    if (!Log::log_file.is_open()) {
        std::cerr << "Error opening default log file: " << Log::LOG_FILE_PATH << '\n';
        return;
    }
}

std::string Log::level_to_string(Log_level level)
{
    switch(level)
    {
        case Log_level::DEBUG: return "DEBUG";
        case Log_level::INFO: return "INFO";
        case Log_level::WARNING: return "WARNING";
        case Log_level::ERROR: return "ERROR";
        case Log_level::CRITICAL: return "CRITICAL";
        default: return "UNKNOWN";
    }
}

void Log::log(Log_level level, const std::string& message)
{
    if(!Log::log_file.is_open())
    {
        std::cerr << "Log file is not open. Can't save log message.\n";
        return;
    }

    std::lock_guard<std::mutex> guard(Log::log_mutex);
    
    time_t now = std::time(nullptr);
    tm* local_time = std::localtime(&now);
    char time_buffer[24];
    std::strftime(time_buffer,
            sizeof(time_buffer),
            "%Y-%m-%d %H:%M:%S", local_time);

    std::ostringstream log_message;
    log_message << "[" <<  time_buffer << "] - "
                << level_to_string(level) << ": "
                << message; 
                
    Log::log_file << log_message.str() << '\n';
    Log::log_file.flush();
}