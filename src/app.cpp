// #include "../include/config.h"
// #include "../include/vault.h"
#include "../include/auth.h"
#include "../include/app.h"
#include "../include/log.h"
#include "../include/user.h"
#include <unistd.h>
#include <iostream>
#include <regex>

Logger App::app_logger;

App::App()
{
    app_logger.log(Log_level::INFO, "App constructor called.");
}

App::~App()
{
    app_logger.log(Log_level::INFO, "App destructor called.");
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
    if(password.length() < 8 || password.length() > 50)
    {
        app_logger.log(Log_level::ERROR, "Password length must be between 8 and 50 characters.");
        return 1;
    }
    
    return 0;
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

std::string App::get_password_input(const std::string& prompt)
{
    std::string password;
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    
    newt.c_lflag &= ~static_cast<tcflag_t>(ECHO);
    newt.c_lflag &= ~static_cast<tcflag_t>(ECHONL);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    
    std::cout << prompt;
    std::getline(std::cin, password);
    
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    std::cout << '\n';
    return password;
}


bool App::init_session_vault(const std::string& username, const std::string& password)
{
    // Development of this function is in progress. Must be verify token session.
    if(!Auth::login(username, password))
    {
        app_logger.log(Log_level::ERROR, "Invalid credentials for user: " + username);
        return false;
    }
    app_logger.log(Log_level::INFO, "User: " + username + " logged in successfully in vault.");
    return true;
}

bool App::init_session_genpass(const std::string& username, const std::string& password)
{
    if(!init_session_vault(username, password))
    {
        app_logger.log(Log_level::ERROR, "Failed to initialize session for user: " + username);
        return false;
    }
    app_logger.log(Log_level::INFO, "Session initialized successfully for user: " + username);
    Auth::create_session(username);
    
    app_logger.log(Log_level::INFO, "Session created for user: " + username);
    init_session_vault(username, password);
    return true;
}

// int main() {
//     App app;

//     // Teste de validate_username
//     std::cout << "Teste validate_username:\n";
//     std::cout << "Vazio: " << app.validate_username("") << "\n";
//     std::cout << "Curto: " << app.validate_username("user") << "\n";
//     std::cout << "Válido: " << app.validate_username("usuario123") << "\n\n";

//     // Teste de validate_email
//     std::cout << "Teste validate_email:\n";
//     std::cout << "Vazio: " << app.validate_email("") << "\n";
//     std::cout << "Sem @: " << app.validate_email("email.com") << "\n";
//     std::cout << "Sem .: " << app.validate_email("email@email") << "\n";
//     std::cout << "Válido: " << app.validate_email("email@email.com") << "\n\n";

//     // Teste de validate_password_length
//     std::cout << "Teste validate_password_length:\n";
//     std::cout << "Curto: " << (int)app.validate_password_length("123") << "\n";
//     std::cout << "Longo: " << (int)app.validate_password_length(std::string(60, 'a')) << "\n";
//     std::cout << "Válido: " << (int)app.validate_password_length("12345678") << "\n\n";

//     // Teste de validate_password_strength
//     std::cout << "Teste validate_password_strength:\n";
//     std::cout << "Fraca: " << (int)app.validate_password_strength("abcdefgh") << "\n";
//     std::cout << "Sem número: " << (int)app.validate_password_strength("abcdefgh!") << "\n";
//     std::cout << "Sem símbolo: " << (int)app.validate_password_strength("abcd1234") << "\n";
//     std::cout << "Forte: " << (int)app.validate_password_strength("Abcd1234!") << "\n\n";

//     // Teste de validate_password
//     std::cout << "Teste validate_password:\n";
//     std::cout << "Vazia: " << app.validate_password("") << "\n";
//     std::cout << "Fraca: " << app.validate_password("abcdefgh") << "\n";
//     std::cout << "Forte: " << app.validate_password("Abcd1234!") << "\n\n";

//     // Teste de get_password_input (comentado para evitar bloqueio em testes automáticos)
//     // std::string pwd = app.get_password_input("Digite uma senha: ");
//     // std::cout << "Senha digitada: " << pwd << "\n";

//     // Teste de init_session_vault e init_session_genpass
//     std::cout << "Teste init_session_vault:\n";
//     std::cout << app.init_session_vault("usuario123", "Abcd1234!") << "\n";
//     std::cout << "Teste init_session_genpass:\n";
//     std::cout << app.init_session_genpass("usuario123", "Abcd1234!") << "\n";

//     return 0;
// }