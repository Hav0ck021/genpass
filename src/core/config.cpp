#include "core/config.h"
#include "core/log.h"
#include <iostream>
#include <fstream>
#include <algorithm>

void Config::set(const std::string& key, const std::string& value)
{
    settings[key] = value;
    Log::log(Log_level::INFO, "Config key set: " + key + " = " + value);
}

void Config::load(const std::string& filename)
{
    if(filename.empty())
    {
        Log::log(Log_level::INFO, "Creating a new config file: " + filename + '.');
        std::ofstream config_file(filename);
        Log::log(Log_level::INFO, "Config file created.");
    }
    std::ifstream config_file(filename);
    if(!config_file.is_open())
    {
        Log::log(Log_level::ERROR, "Error opening config file: " + filename);
    }
    std::string line;
    while(std::getline(config_file, line))
    {
        line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
        if(line.empty() || line[0] == '#') 
        {
            continue;
        }
        std::string buffer[64];
        // Continue development (unfinished)
    }
}

void Config::save(const std::string& filename, const std::string& key, const std::string& value)
{
    // if(filename.empty())
    // {
    //     Log::log(Log_level::ERROR, "Filename cannot be empty.");
    //     return;
    // }
    // std::ofstream config_file(filename, std::ios::app);
    // if(!config_file.is_open())
    // {
    //     Log::log(Log_level::ERROR, "Error opening config file for writing: " + filename);
    //     return;
    // }
    // config_file << key << "=" << value << '\n';
    // Log::log(Log_level::INFO, "Config saved: " + key + " = " + value);
}

// int get_max_login_attempts()
// {
//     return max_login_attempts;
// }

// void set_max_login_attempts(int attempts)
// {
//     if(attempts <= 0)
//     {
//         Log::log(Log_level::ERROR, "Max login attempts cannot be negative or 0.");
//         return;
//     }
//     max_login_attempts = attempts;
//     Log::log(Log_level::INFO, "Max login attempts set to: " + std::to_string(max_login_attempts));
// }
