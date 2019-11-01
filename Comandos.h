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

using namespace std;

#define SUCCESS 0
#define FINISH_PROGRAM 1
// FFFFFFFF#FFFFFFFF#
#define MIN_SIZE 18
  
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
  void removeRegistrosUltimaBusca(string tabela, vector<int> vetor_busca);
  int criaIndice(string modifier, string tabela, string chave);
  void removeIndiceChave(string tabela, string chave);
  void geraNovoIndiceDeTabelaChave(string tabela, string chave);
  string retornaPalavraDeInput (string &input, char delimitador, bool removerEspacosAfrente = true);
  string* parseCampoCT(string input);
  string horaatual();
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
  pair<Comandos::Removido, Comandos::Removido> encontrarOndeInserir(string tabela, int tam_inserir);
private:
  vector<string> parseInsercao(string registro);
  pair<vector<string>, vector<string>> getVetorDeMetadados(string tabela, bool IR=false);
};

#endif
