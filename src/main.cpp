#include "../include/generator.h"
#include "../include/auth.h"
#include "../include/menu.h"
#include "../include/user.h"
#include "../include/app.h"
#include "../include/log.h"
#include "../include/db.h"
#include <iostream>
#include <string>

int main(int argc, char **argv)
{
    Menu menu;
    if(argc > 1)
    { 
        if(std::string(argv[1]) == "--help" || std::string(argv[1]) == "-h")
        {
            menu.help();
            exit(0);
        }
        else if(std::string(argv[1]) == "--version" || std::string(argv[1]) == "-v")
        {
            std::cout << "GenPass v1.0.0" << '\n';
            exit(0);
        } 
        else if(std::string(argv[1]) == "init")
        {
            menu.init_genpass();
            menu.menu();
            exit(0);
        }
        else
        {
            std::cout << "Invalid command. Use --help for more information." << '\n';
            exit(1);
        }
    }
    return 0;
}