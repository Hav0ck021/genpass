#include "core/log.h"
#include "domain/crypto.h"
#include "domain/user.h"
#include "domain/generator.h"
#include <sodium.h>
#include <iostream>
#include <string>

bool Crypto::create_password(User user)
{
    if(user.get_name().empty() && user.get_username().empty())
    {
        Log::log(Log_level::ERROR, "User not found.");
        return false;
    }
    std::cout << " User: " + user.get_username() + " Do you want a random password?\nY / N";
    std::string user_input;
    std::cin >> user_input;
    if(user_input.compare("Y") != 0 && user_input.compare("y") != 0)
    {
        std::string new_passwd;
        std::cout << "The password must contain at least one uppercase letter, one lowercase letter, one number, and one special character.\nEnter the new password: ";
        std::cin >> new_passwd;
        if(!app.validate_password(new_passwd))
        {
            Log::log(Log_level::ERROR, "Password validation failed. It must contain at least one uppercase letter, one lowercase letter, one number, and one special character.");
            return false;
        }
        std::string new_passwd_hash = encrypt_password(const_cast<char*>(new_passwd.c_str()), nullptr);
        user.set_pass(new_passwd_hash);
        return true;
    }
    std::string new_pass = Generator::generate_pass(Generator::size_pass);
    if(new_pass.empty())
    {
        Log::log(Log_level::ERROR, "Password generation failed.");
        return false;
    }
    std::string new_passwd_hash = encrypt_password(const_cast<char*>(generator.get_password().c_str()), nullptr);
    if(new_passwd_hash.empty())
    {
        Log::log(Log_level::ERROR, "Password encryption failed.");
        return false;
    }
    user.set_pass(new_passwd_hash);
    return true;
}

bool Crypto::reset_password(const std::string& pass)
{
    if(db.get_user(user.get_username()).empty())
    {
        Log::log(Log_level::ERROR, "User not found in the database.");
        return false;
    }
    if(!app.validate_password(pass))
    {
        Log::log(Log_level::ERROR, "Password validation failed. It must contain at least one uppercase letter, one lowercase letter, one number, and one special character.");
        return false;
    }
    if(db.get_otp_status(user.get_username()))
    {
        Log::log(Log_level::INFO, "OTP is enabled for user: " + user.get_username());
        std::string otp_stdin;
        std::cout << "Enter OTP: ";
        std::cin >> otp_stdin;
        if(otp_stdin.empty())
        {
            Log::log(Log_level::ERROR, "OTP cannot be empty.");
            return false;
        }
        if(!auth.compare_passwd_decrypted_passwd(pass, db.get_hash_passwd(user.get_username()), reinterpret_cast<const unsigned char*>(otp_stdin.c_str())))
        {
            Log::log(Log_level::ERROR, "Password or OTP is incorrect for user: " + user.get_username());
            return false;
        }
        std::string new_passwd_hash = encrypt_password(const_cast<char*>(pass.c_str()), reinterpret_cast<const unsigned char*>(otp_stdin.c_str()));
        user.set_pass(new_passwd_hash);
        return true;
    }
    std::string new_passwd_hash = encrypt_password(const_cast<char*>(pass.c_str()), nullptr);
    user.set_pass(new_passwd_hash);
    return true;
}

std::string Crypto::encrypt_password(char *passwd, const unsigned char *otp)
{
    if (sodium_init() < 0)
    {
        Log::log(Log_level::ERROR, "Sodium library initialization failed.");
        return "";
    }
    char hash_pass[crypto_pwhash_STRBYTES];
    if(crypto_pwhash_str(hash_pass, passwd, strlen(passwd),
                         crypto_pwhash_OPSLIMIT_INTERACTIVE,
                         crypto_pwhash_MEMLIMIT_INTERACTIVE) != 0)
    {
                             
        return "";
    }
    if(otp == nullptr)
    {
        return std::string(hash_pass);
    }
    unsigned char hash_pass_with_otp[crypto_pwhash_STRBYTES];
    if(crypto_pwhash(hash_pass_with_otp, strlen(hash_pass), passwd, strlen(passwd), otp,
                    crypto_pwhash_OPSLIMIT_INTERACTIVE,
                    crypto_pwhash_MEMLIMIT_INTERACTIVE,
                    crypto_pwhash_ALG_ARGON2ID13) != 0)
    {
        Log::log(Log_level::ERROR, "Password verification failed.");
        return "";
    }
    std::string encrypted_password = std::string(reinterpret_cast<char*>(hash_pass_with_otp));
    return encrypted_password;
}

std::string Crypto::decrypt_password(char *passwd, char *hash_passwd, const unsigned char *otp)
{
    if (sodium_init() < 0)
    {
        Log::log(Log_level::ERROR, "Sodium library initialization failed.");
        return "";
    }
    if(crypto_pwhash_str_verify(hash_passwd, passwd, strlen(passwd)) != 0)
    {
        Log::log(Log_level::ERROR, "Password verification failed.");
        return "";
    }
    unsigned char pass[crypto_pwhash_STRBYTES];
    if(crypto_pwhash(pass, strlen(hash_passwd), hash_passwd, strlen(hash_passwd), otp,
                    crypto_pwhash_OPSLIMIT_INTERACTIVE,
                    crypto_pwhash_MEMLIMIT_INTERACTIVE,
                    crypto_pwhash_ALG_ARGON2ID13) != 0)
    {
        Log::log(Log_level::ERROR, "Password decryption failed.");
        return "";
    }
    std::string decrypted_password = std::string(reinterpret_cast<char*>(pass));
    return decrypted_password;
}