#ifndef APP_H
#define APP_H
#include "core/log.h"
#include "interface/iapp.h"
#include <termios.h>
#include <iostream>

class App : public IApp
{
    private:
        bool validate_password_strength(const std::string& password);
        bool validate_password_length(const std::string& password);
        std::string uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        std::string lowercase = "abcdefghijklmnopqrstuvwxyz";
        std::string numbers = "0123456789";
        std::string special = "!@#$%^&*()_+";
    public:
        App();
        ~App();
        bool validate_email(const std::string& email) override;
        bool validate_username(const std::string& user) override;
        bool validate_password(const std::string& password) override;
        std::string get_password_input() override;
        bool init_session_vault(const std::string& username, const std::string& password) override;
        bool close_session_vault();
        bool init_session_genpass(const std::string& username, const std::string& password) override;
        bool close_session_genpass();

};
#endif // APP_H