#include "Comandos.h"
#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

void interpretadorDeComandos(Comandos &comando, string input) {

  if (input == "CT") {
    string tabela, campos;
    cin >> tabela >> campos;
    comando.criarArquivoComNomeTabela(tabela, campos);
  }

  else if (input == "RT") {
    string tabela;
    cin >> tabela;
    comando.apagaArquivoComNomeTabela(tabela);
  }

  else if (input == "AT") {
    string tabela;
    cin >> tabela;
    comando.resumoDaTabela(tabela);

  }

  else if (input == "LT") {
    comando.listarTabelas();

  }

  else if (input == "IR") {
    string tabela, registro;
    cin >> tabela >> registro;
    comando.inserirRegistro(tabela, registro);
  }

  else if (input == "BR") {
    string modifier, tabela, busca;
    cin >> modifier >> tabela >> busca;
    comando.buscaEmTabela(modifier, tabela, busca);
  }

  else if (input == "AR") {
    string tabela;
    cin >> tabela;
    comando.apresentarRegistrosUltimaBusca(tabela);
  }

  else if (input == "RR") {
    string tabela;
    cin >> tabela;
    comando.removeRegistrosUltimaBusca(tabela);

  }

  else if (input == "CI") {
    string modifier, tabela, chave;
    cin >> modifier >> tabela >> chave;
    comando.criaIndice(modifier, tabela, chave);
  }

  else if (input == "RI") {
    string tabela, chave;
    cin >> tabela >> chave;

    comando.removeIndiceChave(tabela, chave);

  }

  else if (input == "GI") {
    string tabela, chave;
    cin >> tabela >> chave;

    comando.geraNovoIndiceDeTabelaChave(tabela, chave);

  }

  else if (input == "EB") {
    cout << "Finalizando a execução... Tenha um ótimo dia." << '\n';
  }

  else {
    cout << "Comando não reconhecido."
         << "\n";
  }
}

int main() {
  Comandos comando;
  string input = "";
  while (input != "EB") {
    cout << ">>> ";
    cin >> input;
    transform(input.begin(), input.end(), input.begin(), ::toupper);
    interpretadorDeComandos(comando, input);
  }

  return 0;
}
