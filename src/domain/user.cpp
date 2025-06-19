#include "core/log.h"
#include "domain/user.h"
#include "interface/iapp.h"
#include <uuid/uuid.h>
#include <iostream>

User::User(std::shared_ptr<IApp> app) : i_app(app) {}

User::~User()
{
    Log::log(Log_level::INFO, "New user has been removed.");
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
        Log::log(Log_level::ERROR, "Username cannot be empty.");
        exit(1);
    }
    username = n;
}

void User::set_email(const std::string& e)
{
    if(!i_app->validate_email(e))
    {
        Log::log(Log_level::ERROR, "Email is not valid.");
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
    if(!i_app->validate_password(p))
    {
        Log::log(Log_level::ERROR, "Password is not valid.");
        exit(1);
    }
    pass = p;
}

void User::input_data()
{
    std::cout << "Insert you name: ";
    std::cin >> name;
    set_name(name);

    std::cout << "Insert your username: ";
    std::cin >> username;
    set_username(username);

    std::cout << "Insert your email: ";
    std::cin >> email;
    set_email(email);
    
    std::cout << "Insert your password: ";
    std::string pass = i_app->get_password_input();
    set_pass(pass);

    set_uuid();
    Log::log(Log_level::INFO, "UUID generated: " + get_uuid() + " from user: " + username + '.');
    Log::log(Log_level::INFO, "User: " + get_username() + " data has been set.");
}

void User::output_data()
{
    std::cout << "UUID: " << get_uuid() << '\n';
    std::cout << "Name: " << get_name() << '\n';
    std::cout << "Username: " << get_username() << '\n';
    std::cout << "Email: " << get_email() << '\n';
    std::cout << "Password: " << get_pass() << '\n';
}