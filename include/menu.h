#ifndef MENU_H
#define MENU_H
#include "../src/generator.cpp"
#include "../src/auth.cpp"
#include "../src/app.cpp"
#include "../src/log.cpp"
#include "../src/user.cpp"
#include <iostream>

class Menu
{
    public:
        Menu();
        ~Menu();
        void init_genpass();
        void menu_options();
        void close_genpass();
};
#endif // MENU_H