#ifndef COMANDOS_H
#define COMANDOS_H

#include <iostream>
#include <string>
using namespace std;

class Comandos {
public:
  Comandos();
  void criarArquivoComNomeTabela(string tabela, string* campos);
  void apagaArquivoComNomeTabela(string tabela);
  void resumoDaTabela(string tabela);
  void listarTabelas();
  void inserirRegistro(string tabela, string registro);
  void buscaEmTabela(string modifier, string tabela, string busca);
  void apresentarRegistrosUltimaBusca(string tabela);
  void removeRegistrosUltimaBusca(string tabela);
  void criaIndice(string modifier, string tabela, string chave);
  void removeIndiceChave(string tabela, string chave);
  void geraNovoIndiceDeTabelaChave(string tabela, string chave);
  string retornaPalavraDeInput (string &input, char delimitador, bool removerEspacosAfrente = true);
  string* parseCampoCT(string input);

private:
  void parseInsercao(string registro);
};

#endif
