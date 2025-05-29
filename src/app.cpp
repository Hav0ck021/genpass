#include "../include/vault.h"
#include "../include/auth.h"
#include "../include/app.h"
#include "../include/log.h"
#include "../include/user.h"
#include "../include/config.h"
#include <iostream>
#include <regex>

Logger app_logger("logs/genpass.log");

App::App()
{
    app_logger.log(Log_level::INFO, "App constructor called.");
}

App::~App()
{
    app_logger.log(Log_level::INFO, "App destructor called.");
}

bool App::validate_username(const std::string& user)
{
    if(user.empty())
    {
        app_logger.log(Log_level::ERROR, "Username cannot be empty.");
        return false;
    }
    if(user.length() < 8)
    {
        app_logger.log(Log_level::ERROR, "Username is too short.");
        return false;
    }
    return true;
}

bool App::validate_email(const std::string& email)
{
    if(email.empty())
    {
        app_logger.log(Log_level::ERROR, "Email cannot be empty.");
        return false;
    }
    if(email.find('@') == std::string::npos)
    {
        app_logger.log(Log_level::ERROR, "Email is not valid.");
        return false;
    }
    if(email.find('.') == std::string::npos)
    {
        app_logger.log(Log_level::ERROR, "Email is not valid.");
        return false;
    }
    const std::regex pattern("([a-zA-Z0-9._%+-]+)@([a-zA-Z0-9.-]+)\\.([a-zA-Z]{2,})");
    return std::regex_match(email, pattern);
}

bool App::validate_password(const std::string& password)
{
    if(password.empty())
    {
        app_logger.log(Log_level::ERROR, "Password cannot be empty.");
        return false;
    }
    if(validate_password_length(password) != 0)
    {
        app_logger.log(Log_level::ERROR, "Password is too short.");
        return false;
    }
    if(validate_password_strength(password) != 0)
    {
        app_logger.log(Log_level::ERROR, "Password is not strong enough.");
        return false;
    }
    return true;
}

uint8_t App::validate_password_strength(const std::string& password)
{
    if(password.length() < 8)
    {
        return 1;
    }
    if(password.find_first_of("0123456789") == std::string::npos)
    {
        return 1;
    }
    if(password.find_first_of("!@#$%^&*()_+") == std::string::npos)
    {
        return 1;
    }
    return 0;
}

uint8_t App::validate_password_length(const std::string& password)
{
    if(password.length() < 8)
    {
        return 1;
    }
    return 0;
}

void App::run()
{
    User u;
    u.input_data();
    u.output_data();
}

bool App::init_session_vault(const std::string& username, const std::string& password)
{
    // Development of this function is in progress. Must be verify token session.
    if(!Auth::login(username, password))
    {
        app_logger.log(Log_level::ERROR, "Invalid credentials for user: " + username);
        return false;
    }
    app_logger.log(Log_level::INFO, "User: " + username + " logged in successfully in your vault.");
    return true;
}