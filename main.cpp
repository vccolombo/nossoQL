#include "Comandos.h"
#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

#define SUCCESS 0
#define FINISH_PROGRAM 1

// encontra o indice do delimitador na string input e retorna a palavra antes dele
// remove a palavra antes do delimitador da string input
string retornaPalavraDeInput (string &input, char delimitador) {
  string palavra;
  int i = 0;
  while (input[i] == delimitador)
    i++;
  input.erase(0, i);
  palavra = input.substr(0, input.find(delimitador));
  input.erase(0, palavra.length());
  return palavra;
}

int interpretadorDeComandos (Comandos &comando, string &input) {
  string palavra_chave;
  palavra_chave = retornaPalavraDeInput(input, ' ');
  // Transformar comando para UPPER (retirar case sensitiviness)
  transform(palavra_chave.begin(), palavra_chave.end(), palavra_chave.begin(), ::toupper);

  if (palavra_chave == "CT") {
    string tabela = retornaPalavraDeInput(input, ' ');
    string campos = retornaPalavraDeInput(input, ' ');
    comando.criarArquivoComNomeTabela(tabela, campos);
  }
  else if (palavra_chave == "RT") {
    string tabela = retornaPalavraDeInput(input, ' ');
    comando.apagaArquivoComNomeTabela(tabela);
  }
  else if (palavra_chave == "AT") {
    string tabela = retornaPalavraDeInput(input, ' ');
    comando.resumoDaTabela(tabela);
  }
  else if (palavra_chave == "LT") {
    comando.listarTabelas();
  }
  else if (palavra_chave == "IR") {
    string tabela = retornaPalavraDeInput(input, ' ');
    string registro = retornaPalavraDeInput(input, ' ');
    comando.inserirRegistro(tabela, registro);
  }
  else if (palavra_chave == "BR") {
    string modifier = retornaPalavraDeInput(input, ' ');
    string tabela = retornaPalavraDeInput(input, ' ');
    string busca = retornaPalavraDeInput(input, ' ');
    comando.buscaEmTabela(modifier, tabela, busca);
  }
  else if (palavra_chave == "AR") {
    string tabela = retornaPalavraDeInput(input, ' ');
    comando.apresentarRegistrosUltimaBusca(tabela);
  }
  else if (palavra_chave == "RR") {
    string tabela = retornaPalavraDeInput(input, ' ');
    comando.removeRegistrosUltimaBusca(tabela);
  }
  else if (palavra_chave == "CI") {
    string modifier = retornaPalavraDeInput(input, ' ');
    string tabela = retornaPalavraDeInput(input, ' ');
    string chave = retornaPalavraDeInput(input, ' ');
    comando.criaIndice(modifier, tabela, chave);
  }
  else if (palavra_chave == "RI") {
    string tabela = retornaPalavraDeInput(input, ' ');
    string chave = retornaPalavraDeInput(input, ' ');
    comando.removeIndiceChave(tabela, chave);
  }
  else if (palavra_chave == "GI") {
    string tabela = retornaPalavraDeInput(input, ' ');
    string chave = retornaPalavraDeInput(input, ' ');
    comando.geraNovoIndiceDeTabelaChave(tabela, chave);
  }
  else if (palavra_chave == "EB") {
    cout << "Finalizando a execução... Tenha um ótimo dia." << '\n';
    return FINISH_PROGRAM;
  }
  else {
    cout << "Comando não reconhecido." << "\n"
          << "Aperte ENTER para nova entrada." << "\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }

  return SUCCESS;
}

int main() {
  Comandos comando;
  string input = "";
  int codeResult = SUCCESS;
  while (codeResult != FINISH_PROGRAM) {
    cout << ">>> ";
    getline(cin, input);
    codeResult = interpretadorDeComandos(comando, input);
  }

  return 0;
}
