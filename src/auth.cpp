#include <../include/auth.h>
#include <../include/app.h>
#include <../include/log.h>
#include <../include/user.h>
#include <sodium.h>
#include <iostream>
#include <string>

Logger auth_logger("../logs/genpass.log");

Auth::Auth()
{
    auth_logger.log(log_level::INFO, "Auth constructor called.");
}

Auth::~Auth()
{
    auth_logger.log(log_level::INFO, "Auth destructor called.");
}

std::string Auth::encrypt_password(char *passwd, const unsigned char *otp)
{
    if (sodium_init() < 0)
    {
        auth_logger.log(log_level::ERROR, "Sodium library initialization failed.");
        return "";
    }
    char *hash_pass;
    if(crypto_pwhash_str(hash_pass, passwd, strlen(passwd),
                         crypto_pwhash_OPSLIMIT_INTERACTIVE,
                         crypto_pwhash_MEMLIMIT_INTERACTIVE) != 0)
    {
                             
        return "";
    }
    unsigned char hash_pass_with_otp[crypto_pwhash_STRBYTES];
    if(crypto_pwhash(hash_pass_with_otp, strlen(hash_pass), passwd, strlen(passwd), otp,
                    crypto_pwhash_OPSLIMIT_INTERACTIVE,
                    crypto_pwhash_MEMLIMIT_INTERACTIVE,
                    crypto_pwhash_ALG_ARGON2ID13) != 0)
    {
        auth_logger.log(log_level::ERROR, "Password verification failed.");
        return "";
    }
    std::string encrypted_password = std::string(reinterpret_cast<char*>(hash_pass_with_otp));
    return encrypted_password;
}

std::string Auth::decrypt_password(char *passwd, char *hash_passwd, const unsigned char *otp)
{
    if (sodium_init() < 0)
    {
        auth_logger.log(log_level::ERROR, "Sodium library initialization failed.");
        return "";
    }
    if(crypto_pwhash_str_verify(hash_passwd, passwd, strlen(passwd)) != 0)
    {
        auth_logger.log(log_level::ERROR, "Password verification failed.");
        return "";
    }
    unsigned char pass[crypto_pwhash_STRBYTES];
    if(crypto_pwhash(pass, strlen(hash_passwd), hash_passwd, strlen(hash_passwd), otp,
                    crypto_pwhash_OPSLIMIT_INTERACTIVE,
                    crypto_pwhash_MEMLIMIT_INTERACTIVE,
                    crypto_pwhash_ALG_ARGON2ID13) != 0)
    {
        auth_logger.log(log_level::ERROR, "Password decryption failed.");
        return "";
    }
    std::string decrypted_password = std::string(reinterpret_cast<char*>(pass));
    return decrypted_password;
}

bool Auth::create_password(User new_user, const std::string& new_passwd)
{
    if(new_passwd.length() < 8)
    {
        auth_logger.log(log_level::ERROR, "Password must be at least 8 characters long.");
        return false;
    }
    new_user.set_pass(new_passwd);
    return true;
}

std::string Auth::reset_password(const std::string& pass)
{

}

std::string Auth::generate_salt()
{
    
}

std::string Auth::generate_otp()
{
    
}

std::string Auth::generate_hash(const std::string& password, const std::string& salt)
{
    
}