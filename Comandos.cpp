#include "Comandos.h"

Comandos::Comandos() {}

void Comandos::criarArquivoComNomeTabela(string tabela, string campos) {
  cout << "Criando tabela com nome: " << tabela << "\n";
  std::cout << "Campos: " << campos << '\n';
}

void Comandos::apagaArquivoComNomeTabela(string tabela) {
  cout << "Apagando tabela " << tabela << "\n";
}

void Comandos::resumoDaTabela(string tabela) {
  cout << "Resumo da tabela " << tabela << '\n';
}

void Comandos::listarTabelas() { cout << "Listar tabelas" << '\n'; }

void Comandos::inserirRegistro(string tabela, string registro) {
  cout << "Inserir registro " << registro << " na tabela " << tabela << '\n';
}

void Comandos::buscaEmTabela(string modifier, string tabela, string busca) {
  if (modifier == "N") {
    std::cout << "Busca em " << tabela << " todos com critério " << busca
              << '\n';
  } else if (modifier == "U") {
    std::cout << "Busca em " << tabela << " primeiro com critério " << busca
              << '\n';
  } else {
    std::cout << "Modificador não reconhecido: " << modifier << '\n';
  }
}

void Comandos::apresentarRegistrosUltimaBusca(string tabela) {
  std::cout << "Apresentar registro da última busca em " << tabela << '\n';
}

void Comandos::removeRegistrosUltimaBusca(string tabela) {
  std::cout << "Remove registro da última busca em " << tabela << '\n';
}

void Comandos::criaIndice(string modifier, string tabela, string chave) {
  if (modifier == "A") {
    std::cout << "Cria um índice estruturado para " << tabela
              << " usando a chave " << chave << '\n';
  } else if (modifier == "H") {
    std::cout << "Cria um índice usando hash para " << tabela
              << " usando a chave " << chave << '\n';
  } else {
    std::cout << "Modificador não reconhecido: " << modifier << '\n';
  }
}

void Comandos::removeIndiceChave(string tabela, string chave) {
  std::cout << "Remove o indice relativo a " << chave << " de " << tabela
            << '\n';
}

void Comandos::geraNovoIndiceDeTabelaChave(string tabela, string chave) {
  std::cout << "Gera novamente o indice de " << tabela << " referente a chave "
            << chave << '\n';
}
