#ifndef COMANDOS_H
#define COMANDOS_H

#include <iostream>
#include <algorithm>
#include <fstream>
#include <string.h>
#include <cstdio>
#include <time.h>       /* time_t, struct tm, time, localtime */
#include <stdio.h>
#include <vector>
#include <limits>
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
#include <cstring>
#include <string>
#include <tuple>
#ifdef WINDOWS
   #include <direct.h>
   #define Define_CurrentDir _getcwd
#else
   #include <unistd.h>
   #define Define_CurrentDir getcwd
 #endif



using namespace std;

#define SUCCESS 0
#define FINISH_PROGRAM 1
// FFFFFFFF#FFFFFFFF#
#define MIN_SIZE 18
#define PONTEIRO_HEAD_SIZE 10
  
typedef struct busca{
    string nome_tabela;
    vector<int> linhas;
}busca;

class Comandos {
public:
  Comandos();
  int criarArquivoComNomeTabela(string tabela, string* campos);
  int apagaArquivoComNomeTabela(string tabela);
  void resumoDaTabela(string tabela);
  void listarTabelas();
  void inserirRegistro(string tabela, string registro);
  void buscaEmTabela(string modifier, string tabela, string busca);
  void apresentarRegistrosUltimaBusca(string tabela);
  void removeRegistrosUltimaBusca(string tabela);
  int criaIndice(string modifier, string tabela, string chave);
  void removeIndiceChave(string tabela, string chave);
  void geraNovoIndiceDeTabelaChave(string tabela, string chave);
  string retornaPalavraDeInput (string &input, char delimitador, bool removerEspacosAfrente = true);
  string* parseCampoCT(string input);
  string horaatual();
  int existearquivoindice(string tabela, string tipoindice, string chave);
  vector<string> parseBuscaMetaDados(string dados_meta);
  int ponteiroProximo(string &linha);
  pair<int, int> bestFit(string tabela, vector<string>inserir);
  typedef struct Removido{
    int pos;
    int prox;
    int tamanho;
    string buffer;
    string conteudo;
  } posicoes;
  vector<busca> buscas;
private:
  vector<string> parseInsercao(string registro);
  pair<vector<string>, vector<string>> getVetorDeMetadados(string tabela, bool IR=false);
  void alterarPonteiroHead(string tabela, int ponteiro_head);
  tuple<Comandos::Removido, Comandos::Removido, int> encontrarOndeInserir(string tabela, int tam_inserir);
  bool possuiHash(string tabela, string indice);
  bool possuiArvore(string tabela, string indice);
};

#endif
