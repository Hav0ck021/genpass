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

int main()
{
    App app;

    // Testes para validate_username
    std::cout << "Teste validate_username:\n";
    std::cout << "Usuário válido: " << app.validate_username("usuario123") << "\n";
    // std::cout << "Usuário vazio: " << app.validate_username("") << "\n"; // Deve falhar
    // std::cout << "Usuário curto: " << app.validate_username("abc") << "\n"; // Deve falhar

    // Testes para validate_email
    std::cout << "\nTeste validate_email:\n";
    std::cout << "Email válido: " << app.validate_email("teste@email.com") << "\n";
    // std::cout << "Email vazio: " << app.validate_email("") << "\n"; // Deve falhar
    // std::cout << "Email inválido: " << app.validate_email("testeemail.com") << "\n"; // Deve falhar

    // Testes para validate_password_length
    std::cout << "\nTeste validate_password_length:\n";
    std::cout << "Senha longa: " << app.validate_password("12345678") << "\n";
    std::cout << "Senha curta: " << app.validate_password("123") << "\n";

    // Testes para validate_password_strength
    std::cout << "\nTeste validate_password_strength:\n";
    std::cout << "Senha forte: " << app.validate_password("Abcdef1!") << "\n";
    std::cout << "Senha fraca: " << app.validate_password("abcdefghi") << "\n";

    // Testes para validate_password
    std::cout << "\nTeste validate_password:\n";
    std::cout << "Senha válida: " << app.validate_password("Senha123!") << "\n";
    // std::cout << "Senha vazia: " << app.validate_password("") << "\n"; // Deve falhar

    return 0;
}