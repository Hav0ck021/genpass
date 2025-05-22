#ifndef MENU_H
#define MENU_H
#include <iostream>
#include "../src/generator.cpp"

/** Apresentação das opções que o programa pode oferecer
 * ao usuário. **/

void apresentacaoInicial(){
    char adminPass[32];
    std::cout << "Bem vindo ao GenPass!\nAdministrador, insira a sua senha -> ";
    std::cin >> adminPass;
}

int fecharGenPass(){
    std::cout << "\nSaindo do GenPass...\n";
    return 0;
}

void gerarSenhaAleatoria();

void escolhaOpcao(){
    std::cout << "\n1 - Gerar senha aleatoria\n2 - Alterar sua senha\n3 - Sair do GenPass\n";
    int num;
    std::cin >> num;
    switch(num) {
        case 1:
            // Função para alterar a senha do usuário
            break;
        case 2:
            gerarSenhaAleatoria();
            break;
        case 3:
            fecharGenPass();
            break;
    }
}

int iniciarGenPass(){
    std::cout << "\nBem vindo ao GenPass, Administrador!\nEscolha uma das seguintes funcionalidades para ser executada: \n";
    escolhaOpcao();
    return 0;
}

#endif // MENU_H