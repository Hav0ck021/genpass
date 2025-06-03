#include "../include/user.h"
#include "../include/app.h"
#include "../include/log.h"
#include <uuid/uuid.h>
#include <iostream>

Logger User::user_logger;

User::User()
{
    user_logger.log(Log_level::INFO, "New user has been created.");
}

User::~User()
{
    user_logger.log(Log_level::INFO, "New user has been removed.");
}

const std::string User::get_uuid()
{
    char uuid_str[37];
    uuid_unparse(uuid, uuid_str);
    return std::string(uuid_str);
}

void User::set_uuid()
{
    uuid_generate(uuid);
}

const std::string User::get_name()
{
    return name;
}

void User::set_name(const std::string& n)
{
    name = n;
}

const std::string User::get_username()
{
    return username;
}

void User::set_username(const std::string& n)
{
    if(n.empty())
    {
        user_logger.log(Log_level::ERROR, "Username cannot be empty.");
        exit(1);
    }
    username = n;
}

void User::set_email(const std::string& e)
{
    if(!App::validate_email(e))
    {
        user_logger.log(Log_level::ERROR, "Email is not valid.");
        exit(1);
    }
    email = e;
}

const std::string User::get_email()
{
    return email;
}

const std::string User::get_pass()
{
    return pass;
}

void User::set_pass(const std::string& p)
{
    if(!App::validate_password(p))
    {
        user_logger.log(Log_level::ERROR, "Password is not valid.");
        exit(1);
    }
    pass = p;
}

void User::input_data()
{
    std::cout << "Insert you name: ";
    std::cin >> name;
    User::set_name(name);

    std::cout << "Insert your username: ";
    std::cin >> username;
    User::set_username(username);

    std::cout << "Insert your email: ";
    std::cin >> email;
    User::set_email(email);
    
    std::cout << "Insert your password: ";
    std::cin >> pass;
    User::set_pass(pass);

    set_uuid();
    user_logger.log(Log_level::INFO, "UUID generated: " + get_uuid() + " from user: " + username + '.');
    user_logger.log(Log_level::INFO, "User: " + User::get_username() + " data has been set.");
}

void User::output_data()
{
    std::cout << "UUID: " << User::get_uuid() << '\n';
    std::cout << "Name: " << User::get_name() << '\n';
    std::cout << "Username: " << User::get_username() << '\n';
    std::cout << "Email: " << User::get_email() << '\n';
    std::cout << "Password: " << User::get_pass() << '\n';
}