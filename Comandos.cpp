#include "Comandos.h"


Comandos::Comandos() {}

void Comandos::criarArquivoComNomeTabela(string tabela, string* campos) {
  int j=1;
  cout << "Criando tabela com nome: " << tabela << "\n";
  cout << "Campos:" << " " << int(campos[0][0]) << endl;
  for(int i = 0; i < int(campos[0][0]); i++){
    cout << "TIPO: "   << campos[j] << ", NOME: " << campos[j+1] << endl;
    j+=2;
  }
}

void Comandos::apagaArquivoComNomeTabela(string tabela) {
  cout << "Apagando tabela " << tabela << "\n";
}

void Comandos::resumoDaTabela(string tabela) {
  cout << "Resumo da tabela " << tabela << '\n';
}

void Comandos::listarTabelas() { cout << "Listar tabelas" << '\n'; }

void Comandos::inserirRegistro(string tabela, string registro) {
  cout << "Inserir registro " << registro << " na tabela " << tabela << '\n';
  parseInsercao(registro);
}

void Comandos::buscaEmTabela(string modifier, string tabela, string busca) {
  if (modifier == "N") {
    cout << "Busca em " << tabela << " todos com critério " << busca
              << '\n';
  } else if (modifier == "U") {
    cout << "Busca em " << tabela << " primeiro com critério " << busca
              << '\n';
  } else {
    cout << "Modificador não reconhecido: " << modifier << ". Utilize N para fazer a busca, na tabela, de todos os registros que satisfaçam o critério de busca e U para fazer a busca, na tabela, do primeiro registro que satisfaça o critério. \n";
  }
}

void Comandos::apresentarRegistrosUltimaBusca(string tabela) {
  cout << "Apresentar registro da última busca em " << tabela << '\n';
}

void Comandos::removeRegistrosUltimaBusca(string tabela) {
  cout << "Remove registro da última busca em " << tabela << '\n';
}

void Comandos::criaIndice(string modifier, string tabela, string chave) {
  if (modifier == "A") {
    cout << "Cria um índice estruturado para " << tabela
              << " usando a chave " << chave << '\n';
  } else if (modifier == "H") {
    cout << "Cria um índice usando hash para " << tabela
              << " usando a chave " << chave << '\n';
  } else {
    cout << "Modificador não reconhecido: " << modifier << '\n'
		 << "Utilize A para criar um índice estruturado como árvore de múltiplos caminhos para a tabela, usando chave como chave de busca, atualizando os metadados e  H para criar um índice usando hashing para a tabela, usando chave como chave de busca, atualizando os metadados. \n";
  }
}

void Comandos::removeIndiceChave(string tabela, string chave) {
  cout << "Remove o indice relativo a " << chave << " de " << tabela
            << '\n';
}

void Comandos::geraNovoIndiceDeTabelaChave(string tabela, string chave) {
  cout << "Gera novamente o indice de " << tabela << " referente a chave "
            << chave << '\n';
}

// encontra o indice do delimitador na string input e retorna a palavra antes dele
// remove a palavra antes do delimitador da string input
string Comandos::retornaPalavraDeInput (string &input, char delimitador, bool removerEspacosAfrente) {
  string palavra;
  if (removerEspacosAfrente) {
    int i = 0;
    while (input[i] == ' ')
      i++;
    input.erase(0, i);
  }

  int i = 0;
  while (input[i] == delimitador)
    i++;
  input.erase(0, i);
  palavra = input.substr(0, input.find(delimitador));
  input.erase(0, palavra.length());
  return palavra;
}

//separa o tipo e o nome de cada um dos campos da tabela
string* Comandos::parseCampoCT(string input) {
  int i = 0, quant_campo = 0;
  int ponto_virgula = 0, dois_pontos = 0;
  int idx_ini = 0, idx_fim;
  string palavra, *campo;
  input.erase(0, 1);
  //varredura para encontrar problemas na string como
  //Existencia de ' ' e separção incorreta de campos 
  //contagem de campos
  while(input[i] != '\0'){
    if (input[i] == ' ')
      return NULL;
    if (input[i] == ':'){
      dois_pontos++;
      quant_campo++;
    }
    if (input[i] == ';')
      ponto_virgula++;  
    i++;
  }
  if (dois_pontos-1 != ponto_virgula || dois_pontos == 0){
    return NULL;
  }
  campo = new string[1 + quant_campo * 2];
  campo[0] = quant_campo;
  i = 1;

  //separação de TIPO e NOME de cada campo
  for(int j = 0; j < quant_campo; j++){
    idx_fim = input.find(':', idx_ini);
    palavra = input.substr(idx_ini, idx_fim - idx_ini);
    transform(palavra.begin(), palavra.end(), palavra.begin(), ::toupper);
  
    if (palavra.compare("INT") == 0 || palavra.compare("STR") == 0)
      campo[i++] = palavra;
    else if (palavra.compare("FLT") == 0 || palavra.compare("BIN") == 0)
      campo[i++] = palavra;
    else{
      delete[] campo;  
      return NULL;
    }

    idx_ini = idx_fim + 1;
    idx_fim = input.find(";", idx_ini);
    cout << idx_fim << endl;
    palavra = input.substr(idx_ini, idx_fim - idx_ini);
    if (strlen(palavra.c_str()) <= 0)
      return NULL;
    campo[i++] = palavra;
    idx_ini = idx_fim + 1;
  }
  return campo;
}

void Comandos::parseInsercao(string registro) {
  cout << "Registros a serem inseridos: " << '\n';
  int campo = 0;
  while (registro.length() > 0) {
    cout << "Campo " << ++campo << ": ";
    cout << retornaPalavraDeInput(registro, ';') << '\n';
  }
  cout << '\n';
}
