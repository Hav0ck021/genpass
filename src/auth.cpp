#include "../include/crypto.h"
#include "../include/auth.h"
#include "../include/app.h"
#include "../include/log.h"
#include "../include/otp.h"
#include "../include/user.h"
#include "../include/db.h"
#include <sodium.h>
#include <iostream>
#include <string>

const std::string BASE64_URL_ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_";

Database db("../db/genpass.db");

Logger Auth::auth_logger;

Auth::Auth()
{
    auth_logger.log(Log_level::INFO, "Auth constructor called.");
}

Auth::~Auth()
{
    auth_logger.log(Log_level::INFO, "Auth destructor called.");
}

bool Auth::is_valid_token_session(const std::string &token)
{
    auth_logger.log(Log_level::INFO, "Validating token session: " + token);
    return false;
}

bool Auth::is_active_session(Session &user_session)
{
    auth_logger.log(Log_level::INFO, "Checking if session is active for user: " + user_session.username);
    return user_session.is_active && !is_session_expired(user_session);
}

bool Auth::is_session_expired(Session &user_session)
{
    auth_logger.log(Log_level::INFO, "Checking if session is expired for user: " + user_session.username);
    std::time_t current_time = std::time(nullptr);
    return (current_time - user_session.last_activity) > SESSION_TIMEOUT;
}

void Auth::update_session_activity(Session &user_session)
{
    auth_logger.log(Log_level::INFO, "Updating session activity for user: " + user_session.username);
    user_session.last_activity = std::time(nullptr);
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

    if(otp.empty())
    {
        auth_logger.log(Log_level::ERROR, "OTP cannot be empty.");
        return false;
    }
    if(compare_passwd_decrypted_passwd(password,
                                       hashed_password,
                                       reinterpret_cast<const unsigned char*>(otp.c_str())) != true)
    {
        auth_logger.log(Log_level::ERROR, "Password or OTP is incorrect for user: " + username);
        return false;
    }
    auth_logger.log(Log_level::INFO, "User " + username + " logged in successfully.");
    Auth::create_session(username);
    return true;
}

void Auth::logout()
{
    auth_logger.log(Log_level::INFO, "User logged out successfully.");
    // Placeholder for actual logout logic
    // This should include clearing session data or tokens.
}
    
bool Auth::compare_passwd_decrypted_passwd(const std::string &password,
                                            const std::string &hashed_password,
                                            const unsigned char *otp)
{
    return password != Crypto::decrypt_password(const_cast<char*>(password.c_str()),
                                                const_cast<char*>(hashed_password.c_str()), otp);
}

void Auth::create_session(const std::string &username)
{
    std::cout << "Creating session for user: " << username << std::endl;
}


void Auth::delete_session(const std::string &username)
{
    std::cout << "Deleting session for user: " << username << std::endl;
}

std::string Auth::generate_session_token(size_t lenght)
{
    if(lenght == 0)
    {
        auth_logger.log(Log_level::ERROR, "Token length must be greater than 0.");
        return "";
    }
    
    std::string new_token;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, BASE64_URL_ALPHABET.size() - 1);

    while(lenght > 0)
    {
        new_token += BASE64_URL_ALPHABET[dis(gen)];
        lenght--;
    }
    return new_token;
}