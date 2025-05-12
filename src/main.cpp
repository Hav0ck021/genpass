#include <iostream>
#include <cstring>
//#include "bin/headers/app.h"
#include "bin/headers/menu.h"
#include "bin/headers/auth.h"

int main() {
    char senha[17];

    apresentacaoInicial();
    std::cin >> senha;

    if (verificarSenha(senha)) {
        iniciarGenPass();
    } else {
        tentativaSenha();
    }
}


