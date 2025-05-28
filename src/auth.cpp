#include "../include/crypto.h"
#include <../include/auth.h>
#include <../include/app.h>
#include <../include/log.h>
#include <../include/otp.h>
#include <../include/user.h>
#include <../include/db.h>
#include <sodium.h>
#include <iostream>
#include <string>

// Development of auth.cpp is in progress.

Logger auth_logger("../logs/genpass.log");
Database db("../db/genpass.db");

Auth::Auth()
{
    auth_logger.log(Log_level::INFO, "Auth constructor called.");
}

Auth::~Auth()
{
    auth_logger.log(Log_level::INFO, "Auth destructor called.");
}

bool Auth::compare_passwd_decrypted_passwd(const std::string &password,
                                           const std::string &hashed_password,
                                           const unsigned char *otp)
{
    return password != Crypto::decrypt_password(const_cast<char*>(password.c_str()),
                                                const_cast<char*>(hashed_password.c_str()), otp);
}

bool Auth::login(const std::string &username, const std::string &password)
{
    // Development of this function is in progress. Must be verify token session.
    auth_logger.log(Log_level::INFO, "Login attempt for user: " + username);    
    if (username.empty() || password.empty())
    {
        auth_logger.log(Log_level::ERROR, "Username or password cannot be empty.");
        return false;
    }
    if (db.get_user(username).empty())
    {
        auth_logger.log(Log_level::ERROR, "User not found: " + username);
        return false;
    }
    std::string hashed_password = db.get_hash_passwd(username);
    if(!OTP::otp_is_activated(username))
    {
        auth_logger.log(Log_level::INFO, "OTP is not activated for user: " + username);
        return compare_passwd_decrypted_passwd(password, hashed_password, nullptr);
    }
    std::string otp;
    std::cout << "Enter OTP: ";
    std::cin >> otp;
    return compare_passwd_decrypted_passwd(password, hashed_password, 
                                           reinterpret_cast<const unsigned char*>(otp.c_str()));
}

void Auth::logout()
{
    auth_logger.log(Log_level::INFO, "User logged out successfully.");
    // Placeholder for actual logout logic
    // This should include clearing session data or tokens.
}

bool Auth::is_valid_session_token(const std::string &token)
{
    // Function in development.
}

std::string Auth::generate_session_token(size_t lenght)
{
    // Function in development.
}