#ifndef GENPASS_GENERATOR_H
#define GENPASS_GENERATOR_H
#include "core/log.h"
#include <iostream>
#include <vector>
#include <cstring>

#define ALFA_SIZE 26

namespace Generator
{
    uint8_t size_pass = 12;    
    std::string password;
    const std::string uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const std::string lowercase = "abcdefghijklmnopqrstuvwxyz";
    const std::string numbers = "0123456789";
    const std::string special = "!@#$%^&*()_+";
    std::string generate_pass(uint8_t &size);
};
#endif //GENPASS_GENERATOR_H
