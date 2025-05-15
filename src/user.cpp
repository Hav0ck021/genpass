#include "../include/user.h"
#include "../include/log.h"
#include <iostream>

logger user_logger("user.log");

user::user()
{
    user_logger.log(log_level::INFO, "Usuario has been created.\n");
}

user::~user()
{
    user_logger.log(log_level::INFO, "Usuario has been removed.\n");
}

const std::string user::get_name()
{
    return name;
}

void user::set_name(const char *n)
{
    int tam = sizeof(name) - 1;
    strncpy(name, n, tam);
    name[tam] = '\0';
}

const std::string user::get_nick()
{
    return nick;
}

void user::set_nick(const char *n)
{
    int tam = sizeof(nick) - 1;
    strncpy(nick, n, tam);
    name[tam] = '\0';
}

void user::input_data()
{
    char name[32], nick[32];

    std::cout << "Insert you name: ";
    std::cin >> name;
    user::set_name(name);

    std::cout << "Insira o seu nickname - > ";
    std::cin >> nick;
    user::set_nick(nick);

    user::id++;
}

void user::output_data()
{
    std::cout << "Name -> " << user::get_name() <<std::endl;
    std::cout << "Nickname -> " << user::get_nick() << std::endl;
}