#include "Comandos.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <time.h>       /* time_t, struct tm, time, localtime */

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
      vet_busca = comando.buscaEmTabela(modifier, tabela, busca);
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
      comando.criaIndice(modifier, tabela, chave);
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

int main() {
  Comandos comando;
  string input = "";
  string modo;
  string tab_ultima_busca;
  vector<int> vet_busca;
  // Opcao de selecionar modo interativo ou ler um arquivo
  cout << "Digite I para modo interativo ou F para leitura de arquivo:\t";
  cin >> modo;
  transform(modo.begin(), modo.end(), modo.begin(), ::toupper);
  // se modo == F, abrir arquivo
  if (modo == "F") {
    cout << "Digite o nome do arquivo:\t";
    cin >> input;
    cout << "\n\n";
    ifstream arquivo(input);
    if (arquivo.is_open()) {
      int code_result = SUCCESS;
      while (getline(arquivo, input) && code_result != FINISH_PROGRAM) {
        code_result = interpretadorDeComandos(comando, input, 0,tab_ultima_busca,vet_busca);
      }
    } else {
      cout << "Erro ao abrir arquivo.\nFinalizando execução.\n";
    }
  }
  // se modo == I, utilize o terminal do interpretador
  else if (modo == "I") {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    int code_result = SUCCESS;
    while (code_result != FINISH_PROGRAM) {
      cout << ">>> ";
      getline(cin, input);
      code_result = interpretadorDeComandos(comando, input,1,tab_ultima_busca,vet_busca);
    }
  } else {
    cout << "Comando Invalido.\nFinalizando execução.\n";
  }
  cout << "Execução finalizada.\n";
  return 0;
}
