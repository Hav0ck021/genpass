#ifndef AUTH_H
#define AUTH_H
#include "../include/log.h"
#include "../include/user.h"
#include "../include/app.h"
#include <bits/stdc++.h>
#include <iostream>
#include <string>

class Auth
{
    // Development of this class is in progress.
    private:
        bool is_valid_session_token(const std::string &token);
    public:
        Auth();
        ~Auth();
        // Login
        static bool login(const std::string &username,
                   const std::string &password);
        void logout();
        static bool compare_passwd_decrypted_passwd(const std::string &password, const std::string &hashed_password, const unsigned char *otp);
        std::string generate_session_token(size_t lenght);
};
#endif // AUTH_H