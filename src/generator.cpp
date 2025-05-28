#include "../include/generator.h"
#include "../include/log.h"
#include <iostream>
#include <random>
#include <algorithm>

Logger generator_logger("logs/genpass.log");

generator::generator()
{
    generator_logger.log(Log_level::INFO, "Generator has been instanced.\n");
}

generator::~generator()
{
    generator_logger.log(Log_level::INFO, "Generator has been removed.\n");
}

const int generator::get_size_pass()
{
    return size_pass;
}

void generator::set_size_pass(int &size)
{
    while(size < 4 || size > 32) {
        std::cout << "Invalid size!\n";
        std::cin >> size;
    }
    size_pass = size;
}

const std::string generator::get_password()
{
    return password;
}

void generator::set_password(const std::string pass)
{
    password = pass;
}

void generator::generate_pass(int &size_pass)
{
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> dist_lower(0, lowercase.size() - 1);
    std::uniform_int_distribution<> dist_upper(0, uppercase.size() - 1);
    std::uniform_int_distribution<> dist_num(0, numbers.size() - 1);
    std::uniform_int_distribution<> dist_spec(0, special.size() - 1);
    std::uniform_int_distribution<> dist_type(0, 3);
    
    generator::password.clear();
    
    while(size_pass > 0)
    {
        int type = dist_type(gen);
        switch(type)
        {
            case 0:
                password += lowercase[dist_lower(gen)];
                break;
            case 1:
                password += uppercase[dist_upper(gen)];
                break;
            case 2:
                password += numbers[dist_num(gen)];
                break;
            case 3:
                password += special[dist_spec(gen)];
                break;
        }
        size_pass--;
    }
    std::shuffle(password.begin(), password.end(), gen);
     
    std::cout << "Password: " << generator::get_password() << '\n';
}