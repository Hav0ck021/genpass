#include "core/menu.h"
#include "core/app.h"
#include "core/log.h"
#include "domain/auth.h"
#include "domain/generator.h"
#include "domain/user.h"
#include "repository/db.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char* argv[]) {
    Menu menu;

    // Converte argumentos para vetor de strings para facilitar busca
    std::vector<std::string> args(argv + 1, argv + argc);

    if (args.empty()) {
        menu.menu();
        return 0;
    }

    // Opções simples
    if (std::find(args.begin(), args.end(), "-h") != args.end() ||
        std::find(args.begin(), args.end(), "--help") != args.end()) {
        menu.help();
        return 0;
    }

    if (std::find(args.begin(), args.end(), "-i") != args.end() ||
        std::find(args.begin(), args.end(), "--init") != args.end()) {
        menu.init_genpass();
        return 0;
    }

    if (std::find(args.begin(), args.end(), "-v") != args.end() ||
        std::find(args.begin(), args.end(), "--version") != args.end()) {
        std::cout << "GenPass version 1.0.0\n";
        return 0;
    }

    if (std::find(args.begin(), args.end(), "-n") != args.end() ||
        std::find(args.begin(), args.end(), "--new-pass") != args.end()) {
        std::cout << "Generating new password...\n";
        // Aqui você pode chamar o método apropriado do Generator
        return 0;
    }

    if (std::find(args.begin(), args.end(), "-c") != args.end() ||
        std::find(args.begin(), args.end(), "--create-account") != args.end()) {
        std::cout << "Creating new account...\n";
        // Chame o método apropriado para criar conta
        return 0;
    }

    if (std::find(args.begin(), args.end(), "-r") != args.end() ||
        std::find(args.begin(), args.end(), "--recovery-account") != args.end()) {
        std::cout << "Recovering account...\n";
        // Chame o método apropriado para recuperar conta
        return 0;
    }

    // Opções de login
    std::string username, password, otp;
    for (size_t i = 0; i < args.size(); ++i) {
        if ((args[i] == "-u" || args[i] == "--username") && i + 1 < args.size()) {
            username = args[i + 1];
        }
        if ((args[i] == "-p" || args[i] == "--password") && i + 1 < args.size()) {
            password = args[i + 1];
        }
        if ((args[i] == "-o" || args[i] == "--otp") && i + 1 < args.size()) {
            otp = args[i + 1];
        }
    }
    if (!username.empty() && !password.empty()) {
        std::cout << "Signing in with username: " << username << "\n";
        // Chame o método de autenticação aqui, usando username, password e otp
        return 0;
    }

    // Se nenhuma opção reconhecida, mostra o menu padrão
    menu.menu();
    return 0;
}