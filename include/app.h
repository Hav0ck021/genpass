#ifndef APP_H
#define APP_H
#include "../include/log.h"
#include <uuid/uuid.h>
#include <termios.h>
#include <iostream>

class App
{
    private:
        static Logger app_logger;
    public:
        App();
        static uint8_t validate_password_strength(const std::string& password);
        static uint8_t validate_password_length(const std::string& password);
        ~App();
        static bool validate_email(const std::string& email);
        static bool validate_username(const std::string& user);
        static bool validate_password(const std::string& password);
        static std::string get_password_input(const std::string& prompt);
        static bool init_session_vault(const std::string& username, const std::string& password);
        static bool init_session_genpass(const std::string& username, const std::string& password);
    };

#endif // APP_H