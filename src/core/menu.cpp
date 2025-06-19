#include "core/app.h"
#include "core/log.h"
#include "core/menu.h"
#include "domain/generator.h"
#include "services/user_registration.h"
#include "domain/vault.h"
#include <memory>
#include <iostream>

void Menu::create_account() {
    std::cout << "Creating new account..." << '\n';
    
    std::string email, username, password;
    std::cout << "Enter email: ";
    std::cin >> email;
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;

    std::shared_ptr<IApp> app = std::make_shared<App>();
    User_Registration user_reg(app);

    if (!user_reg.register_user(email, username, password)) {
        Log::log(Log_level::ERROR,"Failed to create account.");
        return;
    }
    Log::log(Log_level::INFO, "Account created successfully!");
}

void Menu::recover_account() {
    std::cout << "Recovering account..." << '\n';

    std::string username;
    std::cout << "Enter username for recovery: ";
    std::cin >> username;

    Auth auth;
    if (!auth.recover_account(username)) {
        Log::log(Log_level::ERROR, "Account not found or recovery failed.");
    }
    Log::log(Log_level::INFO, "Account recovery initiated.");
}


void Menu::access_vault() {
    std::cout << "Accessing password vault..." << '\n';

    std::string username, password;
    std::cout << "Username: ";
    std::cin >> username;
    std::cout << "Password: ";
    std::cin >> password;

    if(app.init_session_genpass(username, password)) {
        std::cout << "Access granted." << '\n';
        // Poderia continuar para navegação dentro do vault aqui
    } else {
        std::cout << "Access denied. Invalid credentials." << '\n';
    }
}


void Menu::generate_password() {
    std::cout << "Generating password..." << '\n';

    uint8_t size_pass;
    std::cout << "Enter desired password length: ";
    std::cin >> size_pass;


    if(size_pass < 8 || size_pass > 64)
    {
        Log::log(Log_level::ERROR, "Invalid size. Must be between 8 and 64.");
        return;
    }
    
    std::string password = Generator::generate_pass(size_pass);
    std::shared_ptr<IApp> i_app = std::make_shared<App>();

    if(!i_app->validate_password(password)) {
        Log::log(Log_level::ERROR, "Failed to generate a valid password.");
        return;
    }
    std::cout << "Generated password: " << password << '\n';
}


void Menu::exit_program() {
    close_genpass();
}


Menu::Menu(){}

Menu::~Menu()
{
    Log::log(Log_level::INFO, "Menu destructor called.");
}

void Menu::draw()
{
    Log::log(Log_level::INFO, "Drawing menu...");
    std::cout << R"(
    ┌────────────────────────────────────┐
    │                                    │
    │   genpass: c++ password manager    │
    │                                    │
    │        github.com/Hav0ck021        │
    │                                    │
    │               v1.0.0               │
    ├────────────────────────────────────┤
    │ 1. Create new account              │
    │ 2. Recovery account                │
    │ 3. Access password vault           │
    │ 4. Generate new password           │
    │ 5. Exit                            │
    └────────────────────────────────────┘)" << '\n';
}

void Menu::menu()
{
    Menu::draw();
    Menu::menu_options();
    
    int choice;
    if (!(std::cin >> choice)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter a number." << '\n';
        return;
    }
    
    switch (choice)
    {
        case 1: // create_account(); break;
        case 2: // recover_account(); break;
        case 3: // access_vault(); break;
        case 4: // generate_pass(); break;
        case 5: // close_genpass(); return;
        default:
            std::cout << "Invalid choice. Please try again." << '\n';
    }
}

void Menu::help()
{
    Log::log(Log_level::INFO, "Displaying help...");
    
    std::cout << R"(
    Usage: genpass <command> [options] [arguments]
    genpass [ --help | -h | --version ]

    genpass is a simple and secure password manager.

    Global Options:
        -h, --help               Show this help message and exit.
        -i, --init               Initialize the GenPass password store.
        -v, --version            Show genpass version and exit.
        -n, --new-pass           Generate a new password.
        -c, --create-account     Create a new account to the GenPass.
        -r, --recovery-account   Recover an existing account.
    Sign in to the password vault with the following options:
        -u, --username USERNAME  Specify the username for the password vault.
        -p, --password PASSWORD  Specify the password for the password vault.
        -o, --otp OTP            Specify the one-time password for the vault.

    Available Commands:
        init                  Initializes a new genpass password vault.
                              Creates the necessary directory structure and
                              configuration files in the default or specified location.

    Examples:
        genpass init
        genpass --help

    Use "genpass <command> --help" for more information on a specific command.
    (Future functionality: command-specific help))" << '\n';
}

void Menu::menu_options()
{
    Log::log(Log_level::INFO, "Displaying menu options...");
    std::cout << R"(
    [1]. Create new account
    [2]. Recovery account
    [3]. Access password vault
    [4]. Generate new password
    [5]. Exit)" << '\n';
}


void Menu::close_genpass()
{
    Log::log(Log_level::INFO, "Closing GenPass...");
    std::cout << "Exiting genpass..." << '\n';
    exit(0);
}