#include "../include/config.h"
#include <iostream>
#include <fstream>

config::config()
{
    std::cout << "Config constructor called.\n";
}

config::~config()
{
    std::cout << "Config destructor called.\n";
}

void config::load(const std::string& filename)
{
    if(!filename.empty())
    {
        std::cout << "Creating a new config file.\n";
        std::ofstream config_file(filename);
        std::cout << "Config file created.\n";
    }

    std::ifstream config_file(filename);
    if(!config_file.is_open())
    {
        
    }
}