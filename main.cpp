#include "Comandos.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#define SUCCESS 0
#define FINISH_PROGRAM 1

int interpretadorDeComandos (Comandos &comando, string &input) {
  string palavra_chave;
  palavra_chave = comando.retornaPalavraDeInput(input, ' ');
  // Transformar comando para UPPER (retirar case sensitiviness)
  transform(palavra_chave.begin(), palavra_chave.end(), palavra_chave.begin(), ::toupper);

  if (palavra_chave == "CT") {
    string tabela = comando.retornaPalavraDeInput(input, ' ');
    string *campos = comando.parseCampoCT(input);
    if (campos != NULL){
      comando.criarArquivoComNomeTabela(tabela, campos);
    }
    else
      cout << "Campos Invalidos, tente novamente!" << endl;
    
    
  }
  else if (palavra_chave == "RT") {
    string tabela = comando.retornaPalavraDeInput(input, ' ');
    comando.apagaArquivoComNomeTabela(tabela);
  }
  else if (palavra_chave == "AT") {
    string tabela = comando.retornaPalavraDeInput(input, ' ');
    comando.resumoDaTabela(tabela);
  }
  else if (palavra_chave == "LT") {
    comando.listarTabelas();
  }
  else if (palavra_chave == "IR") {
    string tabela = comando.retornaPalavraDeInput(input, ' ');
    string registro = comando.retornaPalavraDeInput(input, '\n');
    comando.inserirRegistro(tabela, registro);
  }
  else if (palavra_chave == "BR") {
    string modifier = comando.retornaPalavraDeInput(input, ' ');
    transform(modifier.begin(), modifier.end(), modifier.begin(), ::toupper);
    string tabela = comando.retornaPalavraDeInput(input, ' ');
    string busca = comando.retornaPalavraDeInput(input, ' ');
    comando.buscaEmTabela(modifier, tabela, busca);
  }
  else if (palavra_chave == "AR") {
    string tabela = comando.retornaPalavraDeInput(input, ' ');
    comando.apresentarRegistrosUltimaBusca(tabela);
  }
  else if (palavra_chave == "RR") {
    string tabela = comando.retornaPalavraDeInput(input, ' ');
    comando.removeRegistrosUltimaBusca(tabela);
  }
  else if (palavra_chave == "CI") {
    string modifier = comando.retornaPalavraDeInput(input, ' ');
    transform(modifier.begin(), modifier.end(), modifier.begin(), ::toupper);
    string tabela = comando.retornaPalavraDeInput(input, ' ');
    string chave = comando.retornaPalavraDeInput(input, ' ');
    comando.criaIndice(modifier, tabela, chave);
  }
  else if (palavra_chave == "RI") {
    string tabela = comando.retornaPalavraDeInput(input, ' ');
    string chave = comando.retornaPalavraDeInput(input, ' ');
    comando.removeIndiceChave(tabela, chave);
  }
  else if (palavra_chave == "GI") {
    string tabela = comando.retornaPalavraDeInput(input, ' ');
    string chave = comando.retornaPalavraDeInput(input, ' ');
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

int main(int argc, char *argv[]) {
  Comandos comando;
  string input = "";
  int codeResult = SUCCESS;

  if(argv[1] != NULL){
    cout << "Modo arquivo, trabalhando com: " << argv[1] << endl;

    ifstream myfile(argv[1]);

    if(myfile.is_open()){
      while(getline(myfile, input) && codeResult != FINISH_PROGRAM){
        codeResult = interpretadorDeComandos(comando, input);
      }
    }
    else{
      cout << "Erro ao abrir arquivo.\n Finalizando Execução.\n"; 
    }
  }
  else{
    while (codeResult != FINISH_PROGRAM) {
      cout << ">>> ";
      getline(cin, input);
      codeResult = interpretadorDeComandos(comando, input);
    }
  }

  return 0;
}
