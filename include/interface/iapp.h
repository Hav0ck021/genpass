#ifndef IAPP_H
#define IAPP_H
#include <string>

class IApp
{
    public:
        virtual ~IApp() {};
        virtual bool validate_email(const std::string& email) = 0;
        virtual bool validate_username(const std::string& user) = 0;
        virtual bool validate_password(const std::string& password) = 0;
        virtual std::string get_password_input() = 0;
        virtual bool init_session_vault(const std::string& username, const std::string& password) = 0;
        virtual bool init_session_genpass(const std::string& username, const std::string& password) = 0;
        virtual void run() = 0;
};

#endif // IAPP_H