#include <bits/stdc++.h>
#include <iostream>

void criarSenha(){

}

/** Função responsável pela encriptação da senha inserida
 * pelo usuário. **/
void EncryptPassword(){

}

/** Função responsável pela decriptação da senha inserida
 * pelo usuário, revelando a mensagem original. **/
void DecryptPassword(){

}

bool verificarSenha(const char *pass) {
    char realPass[] = "admin";
    if (strcmp(pass, realPass) == 0){
        return true;
    }
    return false;
}

int tentativaSenha(){
    char pass[17];
    int i = 3;
    std::cout << "\nSenha Incorreta!\nVoce tem " << i << "tentativas para inserir a senha correta.\n\n";

    while (i > 0) {
        std::cin >> pass;

        if (verificarSenha(pass)) {
            return iniciarGenPass();
        }
        i--;
        std::cout << "\nSenha Incorreta!\nVoce tem " << i << " tentativas para inserir a senha correta.\n\n";
    }
    return fecharGenPass();
}