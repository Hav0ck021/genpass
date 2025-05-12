#pragma once
#ifndef GENPASS_GENERATOR_H
#define GENPASS_GENERATOR_H
#include <vector>
#include <cstring>

#define TAM_ALFA 26

class UserGen{
    private:
        uint32_t id = 0;
        char name[32]{};
        char nick[32]{};
        int sizePass = 0;
        char password[32]{};
    public:
        UserGen();
        ~UserGen();
        void setName(const char *nome){
            int tam = sizeof(name) - 1;
            strncpy(name, nome, tam);
            name[tam] = '\0';
        };
        const char *getName(){
            return name;
        };

        void setNick(const char *apelido){
            int tam = sizeof(nick) - 1;
            strncpy(nick, apelido, tam);
            name[tam] = '\0';
        };

        const char *getNick(){
            return nick;
        };

        void setSizePass(int tamanho){
            sizePass = tamanho;
        };
        int getSizePass() const{
            return sizePass;
        };

        void setPassword(const char *senha){
            int tam = sizeof(password) - 1;
            strncpy(password, senha, tam);
            name[tam] = '\0';
        };
        const char *getPassword(){
            return password;
        };

        void entradaDados();
        void saidaDadosUsuario();
        int entrarTamanhoSenha();
        static int verificarTamanhoSenha(int &num);
        void gerarSenha();

};
UserGen::UserGen() {
    std::cout << "O usuario foi criado com sucesso" << std::endl;
}

UserGen::~UserGen() {
    std::cout << "O usuario foi removido com sucesso" << std::endl;
}

void UserGen::entradaDados(){
    char nome[32], apelido[32];

    std::cout << "Insira o seu nome -> ";
    std::cin >> nome;
    setName(nome);

    std::cout << "Insira o seu nickname - > ";
    std::cin >> apelido;
    setNick(apelido);

    //id++;
}

void UserGen::saidaDadosUsuario(){
    std::cout << "Nome -> " << getName() <<std::endl;
    std::cout << "Apelido -> " << getNick() << std::endl;
    std::cout << "Senha gerada -> " << getPassword() << std::endl;
    std::cout << "Tamanho da senha - > " << getSizePass() << std::endl;
}

int UserGen::verificarTamanhoSenha(int &num) {
    while(num < 4 || num > 32) {
        std::cout << "\nInsira uma quantidade valida!";
        std::cin >> num;
    }
    return num;
}

int UserGen::entrarTamanhoSenha(){
    int k;
    std::cout << "\nInsira a quantidade de caracteres que a senha deve ter, sendo de 8 a 32 -> ";
    std::cin >> k;
    setSizePass(k);
    return verificarTamanhoSenha(sizePass);
}


void UserGen::gerarSenha(){
    srand(time(nullptr));

    int k = 0;

    while(k < sizePass) {
        password[k] = ((char)(97 + rand() % TAM_ALFA));
        k++;
    }
    setPassword(password);
    std::cout << "\nA senha gerada eh -> " << getPassword() << "\n";
    // Inserir funcionalidade de salvar a senha no BD, antes da alocacao ser excluida.
}


#endif //GENPASS_GENERATOR_H
