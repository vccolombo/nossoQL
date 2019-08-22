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
    cout << "Comando não reconhecido." << "\n"
		 << "Use o comando CT para criar um arquivo vazio associado à tabela indicada " << "\n"
		 << "Use o comando RT para apagar o arquivo relativo à tabela indicada." << "\n"
		 << "Use o comando AT para apresentar um resumo dos metadados da tabela indicada." << "\n"
		 << "Use o comando LT para listar o nome de todas as tabelas existentes." << "\n"
		 << "Use o comando IR para inserir o registro no arquivo da tabela indicada." << "\n"
		 << "Use o comando BR para buscar na tabela todos os registros que satisfaçam o critério da busca." << "\n"
		 << "Use o comando AR para apresentar na tela os valores dos registros retornado pela última busca." << "\n"
		 << "Use o comando RR para remover todos os registros da última busca realizada." << "\n"
		 << "Use o comando CI para criar um indice usando a chave indicada como chave de busca." << "\n"
		 << "Use o comando RI para remover o índice relativo à chave indicada." << "\n"
		 << "Use o comando GI para gerar novamente um novo índice de tabela referente à chave indicada." << "\n"
		 << "Use o comando EB para encerrar a execução do programa." << "\n"
		 << "Aperte ENTER para nova entrada." << "\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }
}

int main() {
  Comandos comando;
  string input = "";
  while (input != "EB") {
    cout << ">>> ";
    cin >> input;
    // Transformar comando para UPPER (retirar case sensitiviness)
    transform(input.begin(), input.end(), input.begin(), ::toupper);
    interpretadorDeComandos(comando, input);
  }

  return 0;
}
