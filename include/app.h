#ifndef APP_H
#define APP_H
#include <uuid/uuid.h>
#include <iostream>

class App
{
    private:
        static uint8_t validate_password_strength(const std::string& password);
        static uint8_t validate_password_length(const std::string& password);
    public:
        App();
        ~App();
        void run();
        static bool validate_email(const std::string& email);
        static bool validate_username(const std::string& user);
        static bool validate_password(const std::string& password);
};

#endif // APP_H