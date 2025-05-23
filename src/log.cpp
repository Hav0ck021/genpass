#include "../include/log.h"
#include <iostream>
#include <ctime>
#include <thread>
#include <mutex>

Logger::Logger(const std::string& filename)
{
    log_file.open(filename, std::ios::app);
    if (!log_file.is_open()) {
        std::cerr << "Error opening log file: " << filename << '\n';
    }
}

Logger::~Logger()
{
    log_file.close();
}

std::string Logger::level_to_string(log_level level)
{
    switch (level)
    {
        case log_level::DEBUG: return "DEBUG";
        case log_level::INFO: return "INFO";
        case log_level::WARNING: return "WARNING";
        case log_level::ERROR: return "ERROR";
        case log_level::CRITICAL: return "CRITICAL";
        default: return "UNKNOWN";
    }
}

void Logger::log(log_level level, const std::string& message)
{
    if (!log_file.is_open())
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

    std::cout << log_message.str() << '\n';
    log_file << log_message.str() << '\n';
    log_file.flush();
}