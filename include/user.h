#ifndef USER_H
#define USER_H
#include <iostream>
#include <uuid.h>

class user
{
    private:
        uint32_t id = 0;
        std::string name;
        std::string nick;
    public:
        user();
        ~user();
        void input_data();
        void output_data();
        const std::string get_name();
        void set_name(const char *name);
        const std::string get_nick();
        void set_nick(const char *nickname);
};


#endif // USER_H