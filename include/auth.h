#ifndef AUTH_H
#define AUTH_H
#include <../include/log.h>
#include <../include/user.h>
#include <../include/app.h>
#include <bits/stdc++.h>
#include <iostream>
#include <string>

class auth
{
    private:
        static std::string encrypt_password(const std::string& password);
        static std::string decrypt_password(const std::string& password);
    public:
        auth();
        ~auth();
        static bool create_password(const std::string& pass);
        static std::string reset_password(const std::string& pass);
};
#endif // AUTH_H