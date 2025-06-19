#include "services/user_registration.h"
#include "core/log.h"

bool User_Registration::is_email_taken(const std::string& email)
{
    Log::log(Log_level::INFO, "Checking if email is taken: " + email);
    // if(!i_app->db().get_user_by_email(email).empty())
    // {
    //     return true;
    // }
    return false;
}

bool User_Registration::is_username_taken(const std::string& username)
{
    Log::log(Log_level::INFO, "Checking if username is taken: " + username);
    // if(!i_app->db().get_user_by_username(username).empty())
    // {
    //     return true;
    // }
    return false;
}

bool User_Registration::save_user_to_db(const std::string& email, const std::string& username, const std::string& password)
{
    Log::log(Log_level::INFO, "Saving user to database: " + username);
    // if(!i_app->db().save_user(email, username, password))
    // {
    //     Log::log(Log_level::ERROR, "Failed to save user to database.");
    //     return false;
    // }
    return true;
}

bool User_Registration::register_user(const std::string& email, const std::string& username, const std::string& password)
{
    Log::log(Log_level::INFO, "Starting user registration process for: " + username);

    if(!validate_email(email))
    {
        Log::log(Log_level::ERROR, "Invalid email format: " + email);
        return false;
    }
    if(!validate_username(username))
    {
        Log::log(Log_level::ERROR, "Invalid username format: " + username);
        return false;
    }
    if(!validate_password(password))
    {
        Log::log(Log_level::ERROR, "Invalid password format for user: " + username);
        return false;
    }
    if(is_email_taken(email))
    {
        Log::log(Log_level::ERROR, "Email already taken: " + email);
        return false;
    }
    if(is_username_taken(username))
    {
        Log::log(Log_level::ERROR, "Username already taken: " + username);
        return false;
    }
    if(!save_user_to_db(email, username, password))
    {
        Log::log(Log_level::ERROR, "Failed to save user to database for: " + username);
        return false;
    }

    Log::log(Log_level::INFO, "User registered successfully: " + username);
    return true;
}