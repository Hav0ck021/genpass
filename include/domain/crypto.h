#ifndef CRYPTO_H
#define CRYPTO_H
#include "core/log.h"
#include "domain/user.h"
#include <bits/stdc++.h>
#include <iostream>
#include <string>

namespace Crypto
{
    const std::string BASE64_URL_ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_";
    std::string generate_salt();
    std::string generate_hash(const std::string& password, const std::string& salt);
    bool create_password(User user);
    bool reset_password(const std::string& pass);
    std::string encrypt_password(char *password, const unsigned char *otp);
    std::string decrypt_password(char *passwd, char *hashed_password, const unsigned char *otp);
};
#endif // CRYPTO_H