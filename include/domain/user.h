#ifndef USER_H
#define USER_H

#include "core/log.h"
#include "interface/iapp.h"
#include <uuid/uuid.h>
#include <iostream>
#include <memory>
#include <string>

class User
{
    private:
        std::shared_ptr<IApp> i_app;

        uuid_t uuid;
        std::string name;
        std::string username;
        std::string email;
        std::string pass;
        bool otp_is_enabled = false;
    public:
        User(std::shared_ptr<IApp> i_app) : i_app(i_app) {};
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
        const bool get_otp_is_enabled();
        void set_otp_is_enabled(bool otp_enabled);
};
#endif // USER_H