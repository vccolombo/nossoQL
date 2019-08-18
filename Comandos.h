#ifndef COMANDOS_H
#define COMANDOS_H

#include <iostream>
#include <string>
using namespace std;

class Comandos {
public: 
    Comandos();
    string keyword;
    void criarArquivoComNomeTabela();
    void apagaArquivoComNomeTabela();
};

#endif