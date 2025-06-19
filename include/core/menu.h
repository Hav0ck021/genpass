#ifndef MENU_H
#define MENU_H

class Menu
{
    private:
        void create_account();
        void recover_account();
        void access_vault();
        void generate_password();
        void exit_program();
    public:
        Menu();
        ~Menu();
        void draw();
        void menu();
        void help();
        void menu_options();
        void close_genpass();
};
#endif // MENU_H