#ifndef USER_H
#define USER_H
#include "../include/log.h"
#include <uuid/uuid.h>
#include <iostream>

class User
{
    private:
        static Logger user_logger;
        uuid_t uuid;
        std::string name;
        std::string username;
        std::string email;
        std::string pass;
    public:
        User();
        ~User();
        void input_data();
        void output_data();
        const std::string get_uuid();
        void set_uuid();
        const std::string get_name();
        void set_name(const std::string& name);
        const std::string get_username();
        void set_username(const std::string& username);
        const std::string get_email();
        void set_email(const std::string& email);
        const std::string get_pass();
        void set_pass(const std::string& password);
};

#endif // USER_H