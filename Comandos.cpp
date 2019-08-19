#include "Comandos.h"

Comandos::Comandos() {}

void Comandos::criarArquivoComNomeTabela(string _tabela, string _campos) {
  cout << "Criando tabela com nome: " << _tabela << "\n";
}

void Comandos::apagaArquivoComNomeTabela(string _tabela) {
  cout << "Apagando tabela " << _tabela << "\n";
}

void Comandos::resumoDaTabela(string tabela) {}

void Comandos::listarTabelas() {}

void Comandos::inserirRegistro(string tabela, string registro) {}

void Comandos::buscaEmTabela(string modifier, string tabela, string busca) {}

void Comandos::apresentarRegistrosUltimaBusca(string tabela) {}

void Comandos::removeRegistrosUltimaBusca(string tabela) {}

void Comandos::criaIndice(string modifier, string tabela, string chave) {}

void Comandos::removeIndiceChave(string tabela, string chave) {}

void Comandos::geraNovoIndiceDeTabelaChave(string tabela, string chave) {}
