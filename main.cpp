#include "Comandos.h"
#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

#define SUCCESS 0
#define FINISH_PROGRAM 1

// encontra o indice do delimitador na string input e retorna a palavra antes dele
// remove a palavra antes do delimitador da string input
string retornaPalavraDeInput (string &input, string delimitador) {
  string palavra;
  int i = 0;
  while (input[i] == ' ')
    i++;
  input.erase(0, i);
  palavra = input.substr(0, input.find(delimitador));
  input.erase(0, palavra.length());
  return palavra;
}

//separa o tipo e o nome de cada um dos campos da tabela
string * parserCampoCT(string input) {
  
  int i = 0, campo_correto = 0, quant_campo = 0;
  int idx_ini = 0,idx_fim;
  string palavra, *campo;
  input.erase(0, 1);

  //varredura para encontrar problemas na string como
  //Existencia de ' ' e separção incorreta de campos 
  //contagem de campos
  while(input[i] != '\0'){
    if (input[i] == ' ')
      return NULL;
    if (input[i] == ':')
      campo_correto++;
    if (input[i] == ';'){
      quant_campo++;
      campo_correto--;  
    }
    if (campo_correto > 1 || campo_correto < 0){
      return NULL;
    }
    i++;
  }
  if (campo_correto != 0){
    return NULL;
  }
  campo = new string[1+quant_campo*2];
  campo[0] = quant_campo;
  i=1;

  //separação de TIPO e NOME de cada campo
  for(int j=0;j<quant_campo;j++){

    idx_fim = input.find(':',idx_ini);
    palavra = input.substr(idx_ini, idx_fim-idx_ini);
    transform(palavra.begin(), palavra.end(), palavra.begin(), ::toupper);

  
    if (palavra.compare("INT") == 0 || palavra.compare("STR") == 0)
      campo[i++] = palavra;
    else if (palavra.compare("FLT") == 0 || palavra.compare("BIN") == 0)
      campo[i++] = palavra;
    else{
      delete[] campo;  
      return NULL;
    }


    idx_ini = idx_fim+1;
    idx_fim = input.find(';',idx_ini);
    palavra = input.substr(idx_ini, idx_fim-idx_ini);
    campo[i++] = palavra;
    idx_ini = idx_fim+1;
  }
  return campo;
}

int interpretadorDeComandos (Comandos &comando, string &input) {
  string delimitador = "\n";
  string palavra_chave;
  palavra_chave = retornaPalavraDeInput(input, " ");
  // Transformar comando para UPPER (retirar case sensitiviness)
  transform(palavra_chave.begin(), palavra_chave.end(), palavra_chave.begin(), ::toupper);

  if (palavra_chave == "CT") {
    string tabela = retornaPalavraDeInput(input, " ");
    string *campos = parserCampoCT(input);
    if (campos != NULL)
      comando.criarArquivoComNomeTabela(tabela, campos);
    else
      cout << "Campo Invalido" << endl;
  }
  else if (palavra_chave == "RT") {
    string tabela = retornaPalavraDeInput(input, delimitador);
    comando.apagaArquivoComNomeTabela(tabela);
  }
  else if (palavra_chave == "AT") {
    string tabela = retornaPalavraDeInput(input, delimitador);
    comando.resumoDaTabela(tabela);
  }
  else if (palavra_chave == "LT") {
    comando.listarTabelas();
  }
  else if (palavra_chave == "IR") {
    string tabela = retornaPalavraDeInput(input, " ");
    string registro = retornaPalavraDeInput(input, delimitador);
    comando.inserirRegistro(tabela, registro);
  }
  else if (palavra_chave == "BR") {
    string modifier = retornaPalavraDeInput(input, " ");
    string tabela = retornaPalavraDeInput(input, " ");
    string busca = retornaPalavraDeInput(input, delimitador);
    comando.buscaEmTabela(modifier, tabela, busca);
  }
  else if (palavra_chave == "AR") {
    string tabela = retornaPalavraDeInput(input, delimitador);
    comando.apresentarRegistrosUltimaBusca(tabela);
  }
  else if (palavra_chave == "RR") {
    string tabela = retornaPalavraDeInput(input, delimitador);
    comando.removeRegistrosUltimaBusca(tabela);
  }
  else if (palavra_chave == "CI") {
    string modifier = retornaPalavraDeInput(input, " ");
    string tabela = retornaPalavraDeInput(input, " ");
    string chave = retornaPalavraDeInput(input, delimitador);
    comando.criaIndice(modifier, tabela, chave);
  }
  else if (palavra_chave == "RI") {
    string tabela = retornaPalavraDeInput(input, " ");
    string chave = retornaPalavraDeInput(input, delimitador);
    comando.removeIndiceChave(tabela, chave);
  }
  else if (palavra_chave == "GI") {
    string tabela = retornaPalavraDeInput(input, " ");
    string chave = retornaPalavraDeInput(input, delimitador);
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
