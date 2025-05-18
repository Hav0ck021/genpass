#include "../include/user.h"
#include "../include/app.h"
#include "../include/log.h"
#include <uuid/uuid.h>
#include <iostream>

logger user_logger("../logs/genpass.log");

user::user()
{
    user_logger.log(log_level::INFO, "New user has been created.\n");
}

user::~user()
{
    user_logger.log(log_level::INFO, "New user has been removed.\n");
}

const std::string user::get_uuid()
{
    char uuid_str[37];
    uuid_unparse(uuid, uuid_str);
    return std::string(uuid_str);
}

void user::set_uuid()
{
    uuid_generate(uuid);
}

const std::string user::get_name()
{
    return name;
}

void user::set_name(const std::string& n)
{
    name = n;
}

const std::string user::get_username()
{
    return username;
}

void user::set_username(const std::string& n)
{
    if(n.empty())
    {
        user_logger.log(log_level::ERROR, "Username cannot be empty.\n");
        exit(1);
    }
    username = n;
}

void user::set_email(const std::string& e)
{
    if(!app::validate_email(e))
    {
        user_logger.log(log_level::ERROR, "Email is not valid.\n");
        exit(1);
    }
    email = e;
}

const std::string user::get_email()
{
    return email;
}

const std::string user::get_pass()
{
    return pass;
}

void user::set_pass(const std::string& p)
{
    if(!app::validate_password(p))
    {
        user_logger.log(log_level::ERROR, "Password is not valid.\n");
        exit(1);
    }
    pass = p;
}

void user::input_data()
{
    std::cout << "Insert you name: ";
    std::cin >> name;
    user::set_name(name);

    std::cout << "Insert your username: ";
    std::cin >> username;
    user::set_username(username);

    std::cout << "Insert your email: ";
    std::cin >> email;
    user::set_email(email);
    
    std::cout << "Insert your password: ";
    std::cin >> pass;
    user::set_pass(pass);

    set_uuid();
    user_logger.log(log_level::INFO, "UUID generated: " + get_uuid() + " from user: " + username + '\n');
    user_logger.log(log_level::INFO, "User: " + user::get_username() + " data has been set.\n");
}

void user::output_data()
{
    std::cout << "UUID: " << user::get_uuid() << '\n';
    std::cout << "Name: " << user::get_name() << '\n';
    std::cout << "Username: " << user::get_username() << '\n';
    std::cout << "Email: " << user::get_email() << '\n';
    std::cout << "Password: " << user::get_pass() << '\n';
}

int main()
{
    user u;
    u.input_data();
    u.output_data();
    return 0;
}