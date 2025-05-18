#include "../include/app.h"
#include "../include/log.h"
#include "../include/user.h"
#include "../include/config.h"
#include <iostream>
#include <regex>

logger app_logger("../logs/genpass.log");

app::app()
{
    app_logger.log(log_level::INFO, "App constructor called.");
}

app::~app()
{
    app_logger.log(log_level::INFO, "App destructor called.");
}

bool app::validate_email(const std::string& email)
{
    if(email.empty())
    {
        app_logger.log(log_level::ERROR, "Email cannot be empty.\n");
        exit(1);
    }
    if(email.find('@') == std::string::npos)
    {
        app_logger.log(log_level::ERROR, "Email is not valid.\n");
        exit(1);
    }
    if(email.find('.') == std::string::npos)
    {
        app_logger.log(log_level::ERROR, "Email is not valid.\n");
        exit(1);
    }
    const std::regex pattern("([a-zA-Z0-9._%+-]+)@([a-zA-Z0-9.-]+)\\.([a-zA-Z]{2,})");
    return std::regex_match(email, pattern);
}

bool app::validate_username(const std::string& username)
{
    if(username.empty())
    {
        app_logger.log(log_level::ERROR, "Username cannot be empty.\n");
        exit(1);
    }
    if(username.length() < 3)
    {
        app_logger.log(log_level::ERROR, "Username is too short.\n");
        exit(1);
    }
    return true;
}

bool app::validate_password(const std::string& password)
{
    if(password.empty())
    {
        app_logger.log(log_level::ERROR, "Password cannot be empty.\n");
        exit(1);
    }
    if(validate_password_length(password) == 0)
    {
        app_logger.log(log_level::ERROR, "Password is too short.\n");
        exit(1);
    }
    if(validate_password_strength(password) == 0)
    {
        app_logger.log(log_level::ERROR, "Password is not strong enough.\n");
        exit(1);
    }
    return true;
}

uint8_t app::validate_password_strength(const std::string& password)
{
    if(password.length() < 8)
    {
        return 0;
    }
    if(password.find_first_of("0123456789") == std::string::npos)
    {
        return 0;
    }
    if(password.find_first_of("!@#$%^&*()_+") == std::string::npos)
    {
        return 0;
    }
    return 1;
}

uint8_t app::validate_password_length(const std::string& password)
{
    if(password.length() < 8)
    {
        return 0;
    }
    return 1;
}

void app::run()
{
    user u;
    u.input_data();
    u.output_data();
}