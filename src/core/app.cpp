#include "core/app.h"
#include "core/log.h"
#include <unistd.h>
#include <iostream>
#include <regex>

App::App(){}

App::~App()
{
    Log::log(Log_level::INFO, "App destructor called.");
}

bool App::validate_password_strength(const std::string& password)
{
    if(password.find_first_of(lowercase) == std::string::npos)
    {
        return false;
    }
    if(password.find_first_of(uppercase) == std::string::npos)
    {
        return false;
    }
    if(password.find_first_of(numbers) == std::string::npos)
    {
        return false;
    }
    if(password.find_first_of(special) == std::string::npos)
    {
        return false;
    }
    return true;
}

bool App::validate_password_length(const std::string& password)
{
    if(password.length() < 8 || password.length() > 64)
    {
        return false;
    }
    return true;
}

bool App::validate_email(const std::string& email)
{
    if(email.empty())
    {
        Log::log(Log_level::ERROR, "Email cannot be empty.");
        return false;
    }
    if(email.find('@') == std::string::npos)
    {
        Log::log(Log_level::ERROR, "Email is not valid.");
        return false;
    }
    if(email.find('.') == std::string::npos)
    {
        Log::log(Log_level::ERROR, "Email is not valid.");
        return false;
    }
    const std::regex pattern("([a-zA-Z0-9._%+-]+)@([a-zA-Z0-9.-]+)\\.([a-zA-Z]{2,})");
    return std::regex_match(email, pattern);
}

bool App::validate_username(const std::string& user)
{
    if(user.empty())
    {
        Log::log(Log_level::ERROR, "Username cannot be empty.");
        return false;
    }
    if(user.length() < 8)
    {
        Log::log(Log_level::ERROR, "Username is too short.");
        return false;
    }
    return true;
}


bool App::validate_password(const std::string& password)
{
    if(password.empty())
    {
        Log::log(Log_level::ERROR, "Password cannot be empty.");
        return false;
    }
    if(!validate_password_length(password))
    {
        Log::log(Log_level::ERROR, "Password is too short.");
        return false;
    }
    if(!validate_password_strength(password))
    {
        Log::log(Log_level::ERROR, "Password is not strong enough.");
        return false;
    }
    return true;
}

std::string App::get_password_input()
{
    termios oldt;
    if(!isatty(STDIN_FILENO))
    {
        Log::log(Log_level::ERROR, "Standard input is not a terminal.");
        return "";
    }
    if(tcgetattr(STDIN_FILENO, &oldt) != 0)
    {
        Log::log(Log_level::ERROR, "Failed to get terminal attributes.");
        return "";
    }
    termios newt = oldt;
    newt.c_lflag &= ~ECHO;
    if(tcsetattr(STDIN_FILENO, TCSANOW, &newt) != 0)
    {
        Log::log(Log_level::ERROR, "Failed to set terminal attributes.");
        return "";
    }
    std::string password;
    std::cout.flush();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    int ch;
    while((ch = getchar()) != '\n' && ch != EOF)
    {
        if(ch == 127 || ch == 8)
        {
            if(!password.empty()) 
            {
                std::cout << "\b \b";
                password.pop_back();
            }
        } 
        else if(isprint(ch))
        {
            password += static_cast<char>(ch);
            std::cout << '*';
        }
    }
    std::cout << '\n';
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return password;
}


bool App::init_session_vault(const std::string& username, const std::string& password)
{
    // Development of this function is in progress. Must be verify token session.
    // if(!auth.login(username, password))
    // {
    //     Log::log(Log_level::ERROR, "Invalid credentials for user: " + username);
    //     return false;
    // }
    Log::log(Log_level::INFO, "User: " + username + " logged in successfully in vault.");
    return true;
}

bool App::close_session_genpass()
{
    Log::log(Log_level::INFO, "Session closed for user: " + /*username*/);
    return true;
}

bool App::init_session_genpass(const std::string& username, const std::string& password)
{
    if(!init_session_vault(username, password))
    {
        Log::log(Log_level::ERROR, "Failed to initialize session for user: " + username);
        return false;
    }
    Log::log(Log_level::INFO, "Session initialized successfully for user: " + username);
    // auth.create_session(username);
    
    Log::log(Log_level::INFO, "Session created for user: " + username);
    return true;
}

bool App::close_session_genpass()
{
    // auth.delete_session(username);

    Log::log(Log_level::INFO, "Session closed for user: " + /*username*/);
    return true;
}
