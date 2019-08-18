#include "Comandos.h"

Comandos::Comandos() {

}

void Comandos::criarArquivoComNomeTabela(string campos) {
    cout << "Criando tabela com nome: " << Comandos::keyword << "\n";
}

void Comandos::apagaArquivoComNomeTabela() {
    cout << "Apagando tabela " << Comandos::keyword << "\n";
}
