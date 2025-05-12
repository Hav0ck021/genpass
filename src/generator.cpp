#include <iostream>
#include <ctime>
#include <cstdlib>
#include <thread>
#include <mutex>
#include "../headers/generator.h"

/**
using namespace std;

std::mutex pass_mtx;
std::vector<char> newPass(16,'');

void inserirMinuscula(){

}

void inserirMaiuscula(){

}
**/

int createUserAndPass(){
    UserGen usuario;

    usuario.entrarTamanhoSenha();
    usuario.gerarSenha();
    usuario.saidaDadosUsuario();

    return 0;
}