#include "../include/menu.h"
#include "../include/log.h"
#include "../include/app.h"
#include "../include/user.h"
#include "../include/auth.h"
#include <iostream>

Logger menu_logger("../logs/genpass.log");

Menu::Menu()
{
    menu_logger.log(log_level::INFO, "Menu constructor called.");
}

Menu::~Menu()
{
    menu_logger.log(log_level::INFO, "Menu destructor called.");
}

void Menu::init_genpass()
{
    menu_logger.log(log_level::INFO, "Initializing GenPass...");
    std::cout << "Password Generator Initialized." << std::endl;
}

void Menu::menu_options()
{
    menu_logger.log(log_level::INFO, "Displaying menu options...");
    std::cout << "1. Generate Password" << std::endl;
    std::cout << "2. Exit" << std::endl;
}

void Menu::close_genpass()
{
    menu_logger.log(log_level::INFO, "Closing GenPass...");
    std::cout << "Exiting GenPass..." << std::endl;
    exit(0);
}