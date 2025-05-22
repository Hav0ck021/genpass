#include "../include/config.h"
#include "../include/log.h"
#include <iostream>
#include <fstream>
#include <algorithm>

Logger config_logger("../logs/genpass.log");

Config::Config()
{
    config_logger.log(log_level::INFO, "Config constructor called.");
}

Config::~Config()
{
    config_logger.log(log_level::INFO, "Config destructor called.");
}

void Config::load(const std::string& filename)
{
    if(filename.empty())
    {
        config_logger.log(log_level::INFO, "Creating a new config file: " + filename + '.');
        std::ofstream config_file(filename);
        config_logger.log(log_level::INFO, "Config file created.");
    }

    std::ifstream config_file(filename);
    if(!config_file.is_open())
    {
        config_logger.log(log_level::ERROR, "Error opening config file: " + filename);
        exit(1);
    }

    std::string line;
    while(std::getline(config_file, line))
    {
        line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
        
        if (line.empty() || line[0] == '#') continue;
        std::string buffer[64];
        // Continue development (unfinished)
    }
}