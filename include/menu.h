#ifndef MENU_H
#define MENU_H
#include "../include/generator.h"
#include "../include/auth.h"
#include "../include/app.h"
#include "../include/log.h"
#include "../include/user.h"
#include <iostream>

class Menu
{
    private:
        static Logger menu_logger;
    public:
        Menu();
        ~Menu();
        void init_genpass();
        void menu();
        void help();
        void menu_options();
        void close_genpass();
};
#endif // MENU_H