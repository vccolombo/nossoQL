#include "Comandos.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

#define SUCCESS 0
#define FINISH_PROGRAM 1

int interpretadorDeComandos (Comandos &comando, string &input, int modo_interativo, string &tab_ultima_busca, vector<int> &vet_busca) {
  string palavra_chave;
  palavra_chave = comando.retornaPalavraDeInput(input, ' ');
  // Transformar comando para UPPER (retirar case sensitiviness)
  transform(palavra_chave.begin(), palavra_chave.end(), palavra_chave.begin(), ::toupper);

  if (palavra_chave == "CT") {
    string tabela = comando.retornaPalavraDeInput(input, ' ');
    string *campos = comando.parseCampoCT(input);
    if (campos != NULL){
      return comando.criarArquivoComNomeTabela(tabela, campos);
    }
    else
      cout << "Campos Invalidos, tente novamente!" << endl;
  }
  else if (palavra_chave == "RT") {
    string tabela = comando.retornaPalavraDeInput(input, ' ');
    if (tabela.length() > 0) {
      return comando.apagaArquivoComNomeTabela(tabela);
    } else {
      cout << "Erro: entrada incompleta." << "\n";
    }
  }
  else if (palavra_chave == "AT") {
    string tabela = comando.retornaPalavraDeInput(input, ' ');
    if (tabela.length() > 0) {
      comando.resumoDaTabela(tabela);
    } else {
      cout << "Erro: entrada incompleta." << "\n";
    }
  }
  else if (palavra_chave == "LT") {
    comando.listarTabelas();
  }
  else if (palavra_chave == "IR") {
    string tabela = comando.retornaPalavraDeInput(input, ' ');
    input.erase(0, 1);
    string registro = comando.retornaPalavraDeInput(input, '\n', false);
    if (tabela.length() > 0 && registro.length() > 0) {
      comando.inserirRegistro(tabela, registro);
    } else {
      cout << "Erro: entrada incompleta." << "\n";
    }
  }
  else if (palavra_chave == "BR") {
    string modifier = comando.retornaPalavraDeInput(input, ' ');
    transform(modifier.begin(), modifier.end(), modifier.begin(), ::toupper);
    string tabela = comando.retornaPalavraDeInput(input, ' ');
    string busca = comando.retornaPalavraDeInput(input, ';');
    if (tabela.length() > 0 && modifier.length() > 0 && busca.length() > 0) {
      tab_ultima_busca = tabela;
      comando.buscaEmTabela(modifier, tabela, busca);
      for (int i = 0; i < vet_busca.size(); i++)
		    cout << vet_busca.at(i) << ' ';
      cout << "<" << endl;
    } else
      cout << "Erro: entrada incompleta." << "\n";
  }
  else if (palavra_chave == "AR") {
    string tabela = comando.retornaPalavraDeInput(input, ' ');
    if (tabela.length() > 0) {
      comando.apresentarRegistrosUltimaBusca(tabela);
    } else {
      cout << "Erro: entrada incompleta." << "\n";
    }
  }
  else if (palavra_chave == "RR") {
    string tabela = comando.retornaPalavraDeInput(input, ' ');


    if (tabela.length() > 0) {
      if (tab_ultima_busca == tabela)
       comando.removeRegistrosUltimaBusca(tabela, vet_busca);
      else
        cout << "Erro: a ultima busca nao corresponde a tabela:" << tabela << endl;
    } else {
      cout << "Erro: entrada incompleta." << "\n";
    }
  }
  else if (palavra_chave == "CI") {
    string modifier = comando.retornaPalavraDeInput(input, ' ');
    transform(modifier.begin(), modifier.end(), modifier.begin(), ::toupper);
    string tabela = comando.retornaPalavraDeInput(input, ' ');
    string chave = comando.retornaPalavraDeInput(input, ' ');
    if (tabela.length() > 0 && modifier.length() > 0 && chave.length() > 0) {
      return comando.criaIndice(modifier, tabela, chave);
    } else {
      cout << "Erro: entrada incompleta." << "\n";
    }
  }
  else if (palavra_chave == "RI") {
    string tabela = comando.retornaPalavraDeInput(input, ' ');
    string chave = comando.retornaPalavraDeInput(input, ' ');
    if (tabela.length() > 0 && chave.length() > 0) {
      comando.removeIndiceChave(tabela, chave);
    } else {
      cout << "Erro: entrada incompleta." << "\n";
    }
  }
  else if (palavra_chave == "GI") {
    string tabela = comando.retornaPalavraDeInput(input, ' ');
    string chave = comando.retornaPalavraDeInput(input, ' ');
    if (tabela.length() > 0 && chave.length() > 0) {
      comando.geraNovoIndiceDeTabelaChave(tabela, chave);
    } else {
      cout << "Erro: entrada incompleta." << "\n";
    }
  }
  else if (palavra_chave == "EB") {
    cout << "Finalizando a execução... Tenha um ótimo dia." << '\n';
    return FINISH_PROGRAM;
  }
  else if (palavra_chave == "" && modo_interativo) {
    cout << "Finalizando execução.\n\n";
    return FINISH_PROGRAM;
  }
  else {
    cout << "Comando não reconhecido." << "\n";
    if (modo_interativo) {
      cout << "Use o comando CT para criar um arquivo vazio associado à tabela indicada " << "\n"
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
      << "Use o comando EB para encerrar a execução do programa." << "\n";
    }
  }
  return SUCCESS;
}

int main(int argc, char *argv[]) {
  Comandos comando;
  string input = "";
  string tab_ultima_busca;
  vector<int> vet_busca;
  int code_result = SUCCESS;

  if(argv[1] != NULL){
    cout << "Modo arquivo, trabalhando com: " << argv[1] << endl;
    ifstream myfile(argv[1]);

    if(myfile.is_open()){
      while(getline(myfile, input) && code_result != FINISH_PROGRAM){
        code_result = interpretadorDeComandos(comando, input, 0,tab_ultima_busca,vet_busca);
      }
    }
    else{
      cout << "Erro ao abrir arquivo.\n Finalizando Execução.\n";
    }
  }
  else{
    while (code_result != FINISH_PROGRAM) {
      cout << ">>> ";
      getline(cin, input);
      code_result = interpretadorDeComandos(comando, input,1,tab_ultima_busca,vet_busca);

    }
  }

  return 0;
}
