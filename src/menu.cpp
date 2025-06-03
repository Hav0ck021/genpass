#include "../include/generator.h"
#include "../include/vault.h"
#include "../include/menu.h"
#include "../include/log.h"
#include "../include/app.h"
#include "../include/user.h"
#include "../include/auth.h"
#include <iostream>

Logger Menu::menu_logger;

Menu::Menu()
{
    menu_logger.log(Log_level::INFO, "Menu constructor called.");
}

Menu::~Menu()
{
    menu_logger.log(Log_level::INFO, "Menu destructor called.");
}

void Menu::init_genpass()
{
    menu_logger.log(Log_level::INFO, "Initializing GenPass...");
}

void Menu::menu()
{
    menu_logger.log(Log_level::INFO, "Displaying menu...");
    std::cout << R"(
             Welcome to GenPass!

    |────────────────────────────────────|
    |    genpass: c++ password manager   |  
    |────────────────────────────────────|
    |                                    |
    |               v1.0.0               |
    |                                    |
    |            Caio Gabriel            |
    |                                    |
    |        github.com/Hav0ck021        |
    |                                    |
    |────────────────────────────────────|
    
    Please select an option:)"<< '\n';
    Menu::menu_options();
    
    int choice;
    std::cin >> choice;
    
    switch (choice)
    {
        case 1:
        {
            std::cout << "Generating password..." << '\n';
            Generator gen;
            int size_pass;
            std::cin >> size_pass;
            gen.generate_pass(size_pass);
            break;
        }
        case 2:
        {
            close_genpass();
            break;
        }
        case 3:
        {
            std::cout << "Accessing password vault..." << '\n';
            App gen_app;
            // Remake this logic
            gen_app.init_session_genpass("admin", "admin");
            break;
        }
        case 4:
        {
            std::cout << "Feature not implemented yet." << '\n';
            break;
        }
        case 5:
        {
            close_genpass();
            break;
        }
        default:
        {
            std::cout << "Invalid choice. Please try again." << '\n';
            menu();
            break;
        }
    }
}

void Menu::help()
{
    menu_logger.log(Log_level::INFO, "Displaying help...");
    
    std::cout << R"(
    Usage: genpass <command> [options] [arguments]
    genpass [ --help | -h | --version ]

    genpass is a simple and secure password manager.

    Global Options:
        -h, --help            Show this help message and exit.
        --version             Show genpass version and exit.

    Available Commands:
        init                  Initializes a new genpass password store.
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
    menu_logger.log(Log_level::INFO, "Displaying menu options...");
    std::cout << R"(
    [1]. Create new account
    [2]. Recovery account
    [3]. Access password vault
    [4]. Generate new password
    [5]. Exit)" << '\n';
}


void Menu::close_genpass()
{
    menu_logger.log(Log_level::INFO, "Closing GenPass...");
    std::cout << "Exiting genpass..." << '\n';
    exit(0);
}