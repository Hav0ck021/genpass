#include "../include/log.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>
#include <ctime>
#include <thread>
#include <mutex>

Logger::Logger()
{
    struct stat st{};
    if (stat(LOG_DIR.c_str(), &st) == -1) {
        if (mkdir(LOG_DIR.c_str(), 0755) != 0) {
            std::cerr << "Failed to create log directory: " << LOG_DIR << '\n';
            perror("mkdir");
        }
    }
    log_file.open(LOG_FILE_PATH.c_str(), std::ios::app);
    if (!log_file.is_open()) {
        std::cerr << "Error opening default log file: " << LOG_FILE_PATH << '\n';
    }
}

Logger::~Logger()
{
    std::lock_guard<std::mutex> lock(log_mutex);
    log_file.flush();
    log_file.close();
}

std::string Logger::level_to_string(Log_level level)
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

void Logger::log(Log_level level, const std::string& message)
{
    if(!log_file.is_open())
    {
        std::cerr << "Log file is not open. Can't save log message.\n";
        exit(1);
    }
    
    std::lock_guard<std::mutex> guard(log_mutex);
    
    time_t now = time(0);
    tm* local_time = localtime(&now);
    char time_buffer[24];
    strftime(time_buffer,
             sizeof(time_buffer),
             "%Y-%m-%d %H:%M:%S", local_time);

    std::ostringstream log_message;
    log_message << "[" <<  time_buffer << "] - "
                << level_to_string(level) << ": "
                << message; 
                
    log_file << log_message.str() << '\n';
    log_file.flush();
}