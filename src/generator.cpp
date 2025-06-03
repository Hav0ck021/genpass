#include "../include/generator.h"
#include "../include/log.h"
#include <iostream>
#include <random>
#include <algorithm>

Logger Generator::generator_logger;

Generator::Generator()
{
    generator_logger.log(Log_level::INFO, "Generator has been instanced.");
}

Generator::~Generator()
{
    generator_logger.log(Log_level::INFO, "Generator has been removed.");
}

const int Generator::get_size_pass()
{
    return size_pass;
}

void Generator::set_size_pass(int &size)
{
    while(size < 4 || size > 50) {
        std::cout << "Invalid size!\n";
        std::cin >> size;
    }
    size_pass = size;
}

const std::string Generator::get_password()
{
    return password;
}

void Generator::set_password(const std::string pass)
{
    password = pass;
}

void Generator::generate_pass(int &size_pass)
{
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> dist_lower(0, lowercase.size() - 1);
    std::uniform_int_distribution<> dist_upper(0, uppercase.size() - 1);
    std::uniform_int_distribution<> dist_num(0, numbers.size() - 1);
    std::uniform_int_distribution<> dist_spec(0, special.size() - 1);
    std::uniform_int_distribution<> dist_type(0, 3);
    
    Generator::password.clear();
    
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
     
    std::cout << "Password: " << Generator::get_password() << '\n';
}