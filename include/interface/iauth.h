#ifndef IAUTH_H
#define IAUTH_H
#include <string>

class IAuth
{
    public:
        virtual bool login(const std::string& username, const std::string& password) = 0;
        virtual bool is_logged_in(const std::string &token) = 0;
        virtual void logout(const std::string &token) = 0;
        virtual ~IAuth() = default;
};

#endif // IAUTH_H