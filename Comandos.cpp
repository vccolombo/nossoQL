#include "Comandos.h"

using namespace std;

Comandos::Comandos() {}

string Comandos::horaatual(){
  time_t rawtime;
  struct tm * timeinfo;
  time (&rawtime);
  timeinfo = localtime (&rawtime);
  mktime (timeinfo);
  return string(asctime(timeinfo));
}

int Comandos::criarArquivoComNomeTabela(string tabela, string* campos) {
  // verificar se existe tabela com nome igual
  ifstream arquivo_base;
  arquivo_base.open("./tabelas/base.txt");
  if (arquivo_base.is_open()) {
    // verificar se ja existe uma tabela com o mesmo nome
    string linha;
    while (getline(arquivo_base, linha)) {
      if (linha == tabela) {
        cout << "Tabela já existe. Terminando execução.\n";
        return FINISH_PROGRAM;
      }
    }
  } else {
    cout << "Erro ao criar arquivo base.txt\n";
  }
  ofstream base;
  base.open("./tabelas/base.txt", ios_base::app);
  if (base.is_open()) {
    base << tabela << endl;
    base.close();
  }

  string tab = "tabelas/", meta = "tabelas/";
  tab.append(tabela + "_TAB.txt");
  meta.append(tabela + "_META.txt");
  ofstream(tab.c_str());
  ofstream(meta.c_str());

  ofstream arquivo_meta;
  arquivo_meta.open(meta, ios_base::app);

  int j = 1;
  cout << "Criando tabela com nome: " << tabela << "\n";
  arquivo_meta << tabela << ";" << "tabelas/_META.txt" << ";" << int(campos[0][0]) << ";";
  cout << "Campos:" << " " << int(campos[0][0]) << ";" ;
  for(int i = 0; i < int(campos[0][0]); i++){
    cout << "TIPO: "   << campos[j] << ", NOME: " << campos[j + 1] << endl;
    arquivo_meta << campos[j] << ":" << campos[j + 1] << ";";
    j += 2;
  }
  arquivo_meta << Comandos::horaatual() << ";" << endl;
  arquivo_meta.close();
  return SUCCESS;
}

void Comandos::apagaArquivoComNomeTabela(string tabela) {
  string base = "./tabelas/base.txt";
  ifstream arquivo_base;
  ofstream temp;
  arquivo_base.open(base);
  temp.open("./tabelas/temp.txt");
  // tenta abrir arquivo base e temp
  if (!arquivo_base.is_open() || !temp.is_open()) {
    cout << "Erro ao abrir arquivo base.txt\n";
    return;
  }
  // tenta remover arquivo com tabela e metadados
  string arquivo_tabela = "./tabelas/" + tabela + "_TAB.txt";
  string arquivo_meta = "./tabelas/" + tabela + "_META.txt";
  if (remove(arquivo_tabela.c_str()) != 0) {
    cout << "Erro ao tentar remover arquivo: " << arquivo_tabela << "\n";
    return;
  }
  if (remove(arquivo_meta.c_str()) != 0) {
    cout << "Erro ao tentar remover arquivo: " << arquivo_meta << "\n";
    return;
  } else {
    // copia e remocao de dados da tabela para novo arquivo temp
    cout << "Apagando tabela " << tabela << "\n";
    string input;
    while (getline(arquivo_base, input)) {
      if (input != tabela)
        temp << input << endl;
    }
    arquivo_base.close();
    temp.close();
    if (remove(base.c_str()) != 0) {
      cout << "Erro ao tentar remover arquivo.\n";
    }
    rename("./tabelas/temp.txt", "./tabelas/base.txt");
  }
}

void Comandos::resumoDaTabela(string tabela) {
  cout << "Resumo da tabela " << tabela << endl;
  string meta = "tabelas/";
  meta.append(tabela);
  meta.append("_META.txt");

  string linha;
  ifstream arquivo;
  arquivo.open(meta);
  if (arquivo.is_open()) {
    while (!arquivo.eof() ) {
      getline(arquivo,linha);
      cout << linha << endl;
    }
    arquivo.close();
  }
  else{
    cout << "Erro ao tentar ler resumo de tabela" << endl;
  }
}

void Comandos::listarTabelas() {
  ifstream base;
  base.open("./tabelas/base.txt");
  if (base.is_open()) {
    string linha;
    while (getline(base, linha)) {
      cout << linha << "\n";
    }
  }
  else{
    cout << "Erro ao tentar ler lista de tabelas" << endl;
  }
}

void Comandos::inserirRegistro(string tabela, string registro) {
  vector<string> metadados = getVetorDeMetadados(tabela);
  size_t quantidade_de_campos = stoi(metadados[2]);

  cout << "Inserir registro " << registro << " na tabela " << tabela << '\n';
  // vetor em que cada entrada é um campo da inserção
  vector<string> inserir = parseInsercao(registro);

  if (quantidade_de_campos != inserir.size())
  {
    cout << "ERRO IMPOSSÍVEL INSERIR NA TABELA: Quantidade incorreta de campos para inserir\n";
    return;
  }
  
  

  ofstream file;
  file.open("tabelas/" + tabela + "_TAB.txt", ios_base::app);
  if (file.fail()) {
    // TODO o arquivo não existe (a tabela não foi criada)
    std::cout << "ERRO" << '\n';
    return;
  }
  // escrever no arquivo cada entrada do vetor inserir
  for (auto reg : inserir) {
    file << reg << ';';
  }
  file << '\n';
  file.close();
}

void Comandos::buscaEmTabela(string modifier, string tabela, string busca) {

  ifstream file; //Leitura do arquivo
  file.open("tabelas/" + tabela + "_TAB.txt");
  if (file.fail()) {
    // TODO o arquivo não existe (a tabela não foi criada)
    std::cout << "Não foi possível encontrar a Tabela." << '\n';
    return;
  }

  vector<string> linha_meta_dados = getVetorDeMetadados(tabela);
  // Retira o tipo dos campo, mantendo somente o nome do campo
  vector<string> nomes_campos;

  //parse do campo selecionado para busca
  size_t pos_dois_pontos = busca.find(":"); //Posição dos ":"
  string campo_b = busca.substr(0,pos_dois_pontos); //Separa o início da string até ":"
  string elemento_b = busca.substr(pos_dois_pontos+1); //Separa o ":" até o fim

  bool existe_campo = false; // Verificador da existência do campo
  int i = 0;
  int indice_campo; // Armazena a posição do campo que foi encontrado na busca


  //Percorre todos os campos presentes no meta, e ao encontrar o campo necessário pra busca, armazena sua posição em indice_campo
  while (i < stoi(linha_meta_dados[2])){
    size_t pos_dois_pontos = linha_meta_dados[3+i].find(":");
    string tipo = linha_meta_dados[3+i].substr(0,pos_dois_pontos);
    string campo = linha_meta_dados[3+i].substr(pos_dois_pontos+1);
    nomes_campos.push_back(campo); //Insere o nome do campo no vetor
    // Se o campo for igual ao campo da busca, armazena a posição
    if (campo == campo_b){
      indice_campo = i;
      existe_campo = true;
    }
    i++;
  };
  if(!existe_campo){
    cout << "Não foi possível encontrar o campo" << endl;
    return;
  }

  // Linha busca = 1;2;3;4;
  // Vetor = [1, 2, 3, 4]
  string linha_busca;
  vector<string> vetor_linha_busca;
  bool encontrou = false;
  if (modifier == "N") {
    cout << "Busca em " << tabela << " todos com critério " << busca
              << '\n';
    do{
      getline(file, linha_busca); //Armazena a linha em linha_busca
      vetor_linha_busca = parseBuscaMetaDados(linha_busca); //Armazena os campos da linha atual
      //Evita segmentation fault quando pega uma linha vazia.
      if (linha_busca != ""){
        if (vetor_linha_busca[indice_campo] == elemento_b){ //Compara o conteúdo do campo com o conteúdo da busca
          encontrou = true;
          for(int j = 0; j < nomes_campos.size(); j++){ //Imprime o conteúdo do registro da busca
            cout << nomes_campos[j] << ": " << vetor_linha_busca[j] << " ";
          }
          cout << endl;
        }
      }
    }while(!file.eof());
    if (!encontrou){
      cout << "Elemento não encontrado!" << endl;
    }
  } else if (modifier == "U") {
    cout << "Busca em " << tabela << " primeiro com critério " << busca
              << '\n';

    // Busca até encontrar o primeiro campo igual ao conteúdo da busca
    do{
      getline(file, linha_busca);
      vetor_linha_busca = parseBuscaMetaDados(linha_busca);
      //Evita segmentation fault quando pega uma linha vazia.
      if (linha_busca != ""){
        if (vetor_linha_busca[indice_campo] == elemento_b){
          encontrou = true;
          for(int j = 0; j < nomes_campos.size(); j++){
            cout << nomes_campos[j] << ": " << vetor_linha_busca[j] << " ";
          }
          cout << endl;
        }
      }
    }while(!file.eof() && !encontrou);
    if (!encontrou){
      cout << "Elemento não encontrado!" << endl;
    }


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
  string palavra;
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
    palavra = input.substr(idx_ini, idx_fim - idx_ini);
    if (strlen(palavra.c_str()) <= 0)
      return NULL;
    campo[i++] = palavra;
    idx_ini = idx_fim + 1;
  }
  return campo;
}

vector<string> Comandos::parseInsercao(string registro) {
  vector<string> insercoes;
  cout << "Registros a serem inseridos: " << '\n';
  int campo = 0;
  bool var = false;
  while (registro.length() > 0) {
    cout << "Campo " << ++campo << ": ";
    string palavra = retornaPalavraDeInput(registro, ';', var);
    cout << palavra << "<\n";
    insercoes.push_back(palavra);
    var = true;
  }
  cout << '\n';
  return insercoes;
}

//Retorna em um vetor todo o conteúdo entre ;
vector<string> Comandos::parseBuscaMetaDados(string dados_meta){
  vector<string> resposta;
  while(dados_meta.length() > 0){
    string palavra = retornaPalavraDeInput(dados_meta, ';');
    resposta.push_back(palavra);
  }

  return resposta;
}

vector<string> Comandos::getVetorDeMetadados(string tabela) {
  ifstream file_meta; //Leitura do arquivo
  file_meta.open("tabelas/" + tabela + "_META.txt");
  if (file_meta.fail()) {
    // TODO o arquivo não existe (a tabela não foi criada)
    std::cout << "Não foi possível encontrar a o Metadados da Tabela." << '\n';
    vector<string> empty;
    return empty;
  }

  string dados_file_meta;
  file_meta >> dados_file_meta; //recebe como string todo o conteudo do arquivo meta da tabela

  //0  = Nome Tabela / 1 = path txt meta / 2 = qtd de campos / 3 até 3+qtd de campos = campos / ultimo = data
  vector<string> linha_meta_dados = parseBuscaMetaDados(dados_file_meta);

  return linha_meta_dados;

} 
