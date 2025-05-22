#ifndef GENPASS_GENERATOR_H
#define GENPASS_GENERATOR_H
#include <iostream>
#include <vector>
#include <cstring>

#define ALFA_SIZE 26

class generator{
    private:
        uint8_t size_pass = 0;    
        std::string password;
        const std::string lowercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        const std::string uppercase = "abcdefghijklmnopqrstuvwxyz";
        const std::string numbers = "0123456789";
        const std::string special = "!@#$%^&*()_+";
    public:
        generator();
        ~generator();     
        const int get_size_pass();
        void set_size_pass(int &size);
        const std::string get_password();
        void set_password(const std::string pass);
        void generate_pass(int &size);
};

#endif //GENPASS_GENERATOR_H
