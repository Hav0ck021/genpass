#ifndef CRYPTO_H
#define CRYPTO_H
#include "../include/log.h"
#include "../include/user.h"
#include "../include/app.h"
#include <bits/stdc++.h>
#include <iostream>
#include <string>

class Crypto
{
    private:
        static Logger crypto_logger;
        static std::string generate_salt();
        static std::string generate_hash(const std::string& password, const std::string& salt);
    public:
        Crypto();
        ~Crypto();
        static bool create_password(User new_user, const std::string& new_passwd);
        static std::string reset_password(const std::string& pass);
        static std::string encrypt_password(char *password, const unsigned char *otp);
        static std::string decrypt_password(char *passwd, char *hashed_password, const unsigned char *otp);
        static std::string encode(size_t lenght);
        static std::string decode(size_t lenght);
};
#endif // CRYPTO_H