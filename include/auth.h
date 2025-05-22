#ifndef AUTH_H
#define AUTH_H
#include <../include/log.h>
#include <../include/user.h>
#include <../include/app.h>
#include <bits/stdc++.h>
#include <iostream>
#include <string>

class Auth
{
    private:
        std::string encrypt_password(char *password, const unsigned char *otp);
        std::string decrypt_password(char *passwd, char *hashed_password, const unsigned char *otp);
        static std::string generate_salt();
        static std::string generate_otp();
        static std::string generate_hash(const std::string& password, const std::string& salt);
    public:
        Auth();
        ~Auth();
        static bool create_password(User new_user, const std::string& new_passwd);
        static std::string reset_password(const std::string& pass);
};
#endif // AUTH_H