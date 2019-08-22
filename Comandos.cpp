#include "Comandos.h"

Comandos::Comandos() {}

void Comandos::criarArquivoComNomeTabela(string tabela, string campos) {
  cout << "Criando tabela com nome: " << tabela << "\n";
  cout << "Campos: " << campos << '\n';
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
  parseInsercao(registro);
}

void Comandos::buscaEmTabela(string modifier, string tabela, string busca) {
  if (modifier == "N") {
    cout << "Busca em " << tabela << " todos com critério " << busca
              << '\n';
  } else if (modifier == "U") {
    cout << "Busca em " << tabela << " primeiro com critério " << busca
              << '\n';
  } else {
    cout << "Modificador não reconhecido: " << modifier << '\n';
  }
}

void Comandos::apresentarRegistrosUltimaBusca(string tabela) {
  cout << "Apresentar registro da última busca em " << tabela << '\n';
}

void Comandos::removeRegistrosUltimaBusca(string tabela) {
  cout << "Remove registro da última busca em " << tabela << '\n';
}

void Comandos::criaIndice(string modifier, string tabela, string chave) {
  if (modifier == "A") {
    cout << "Cria um índice estruturado para " << tabela
              << " usando a chave " << chave << '\n';
  } else if (modifier == "H") {
    cout << "Cria um índice usando hash para " << tabela
              << " usando a chave " << chave << '\n';
  } else {
    cout << "Modificador não reconhecido: " << modifier << '\n';
  }
}

void Comandos::removeIndiceChave(string tabela, string chave) {
  cout << "Remove o indice relativo a " << chave << " de " << tabela
            << '\n';
}

void Comandos::geraNovoIndiceDeTabelaChave(string tabela, string chave) {
  cout << "Gera novamente o indice de " << tabela << " referente a chave "
            << chave << '\n';
}

// encontra o indice do delimitador na string input e retorna a palavra antes dele
// remove a palavra antes do delimitador da string input
string Comandos::retornaPalavraDeInput (string &input, char delimitador, bool removerEspacosAfrente) {
  string palavra;

  if (removerEspacosAfrente) {
    int i = 0;
    while (input[i] == ' ')
      i++;
    input.erase(0, i);
  }

  int i = 0;
  while (input[i] == delimitador)
    i++;
  input.erase(0, i);
  palavra = input.substr(0, input.find(delimitador));
  input.erase(0, palavra.length());
  return palavra;
}

void Comandos::parseInsercao(string registro) {
  std::cout << "Registros a serem inseridos: " << '\n';
  int campo = 0;
  while (registro.length() > 0) {
    std::cout << "Campo " << ++campo << ": ";
    std::cout << retornaPalavraDeInput(registro, ';') << '\n';
  }
  std::cout << '\n';

}
