#include "Comandos.h"
#include <vector>
#include <iostream>
#include <cstdlib>
#define MAXVETOR 100

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
  }
  ofstream base;
  base.open("./tabelas/base.txt", ios_base::app);
  if (base.is_open()) {
    base << tabela << endl;
    base.close();
  } else {
    cout << "Erro ao criar arquivo base.txt\n";
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
  // -1|||||||| é o ponteiro para a primeira ocorrencia de um registro removido (-1 pq nao existe)
  arquivo_meta << tabela << ";" << "-1||||||||" << ";" << int(campos[0][0]) << ";";
  cout << "Campos:" << " " << int(campos[0][0]) << ";" ;
  for(int i = 0; i < int(campos[0][0]); i++){
    cout << "TIPO: "   << campos[j] << ", NOME: " << campos[j + 1] << endl;
    arquivo_meta << campos[j] << ":" << campos[j + 1] << ";";
    j += 2;
  }
  arquivo_meta << Comandos::horaatual();
  arquivo_meta.close();
  return SUCCESS;
}

int Comandos::apagaArquivoComNomeTabela(string tabela) {
  string base = "./tabelas/base.txt";
  ifstream arquivo_base;
  arquivo_base.open(base);
  // tenta abrir arquivo base e temp
  if (!arquivo_base.is_open()) {
    cout << "Erro ao abrir arquivo base.txt\n";
    return FINISH_PROGRAM;
  }
  // verificar se tabela existe
  string linha;
  bool existe = false;
  while (getline(arquivo_base, linha) && !existe) {
    if (linha == tabela)
      existe = true;
  }
  if (!existe) {
    cout << "Tabela: " + tabela + " não existe!" << endl
         << "Finalizando execução." << endl;
    return FINISH_PROGRAM;
  }
  // tenta remover arquivo com tabela e metadados
  string arquivo_tabela = "./tabelas/" + tabela + "_TAB.txt";
  string arquivo_meta = "./tabelas/" + tabela + "_META.txt";
  if (remove(arquivo_tabela.c_str()) != 0) {
    cout << "Erro ao tentar remover arquivo: " << arquivo_tabela << "\n";
    return FINISH_PROGRAM;
  }
  if (remove(arquivo_meta.c_str()) != 0) {
    cout << "Erro ao tentar remover arquivo: " << arquivo_meta << "\n";
    return FINISH_PROGRAM;
  } else {
    ofstream temp;
    temp.open("./tabelas/temp.txt");
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

//Retirado de https://pt.stackoverflow.com/questions/47130/como-obter-o-diret%C3%B3rio-que-o-programa-est%C3%A1-sendo-executado
//Recupera onde o programa está sendo executado, parecido com getpwd()
 char LOCAL_DIR[FILENAME_MAX];
  if (!Define_CurrentDir(LOCAL_DIR, sizeof(LOCAL_DIR))) {
    string erro = "Erro ao tentar encontrar o local de instalação do programa";
    cout << erro;
    return 0;
    }

//Adaptado junto com o codigo que le os arquivos de dentro da pasta
//https://www.hardware.com.br/comunidade/arquivos-varrer/1103524/
  DIR *dir;
  struct dirent *lsdir;
  string diretoriolocal = LOCAL_DIR, apagando;
  int i = 0, controleqt = 0;

  //Adapta para o diretorio onde esta as tabelas
  diretoriolocal = diretoriolocal + "/tabelas/";

  dir = opendir(diretoriolocal.c_str());
  /* Imprime e apaga os arquivos referente a tabela do diretorio tabelas */
  while ( ( lsdir = readdir(dir) ) != NULL ) { 
      i = 0;
      controleqt = 0;
      while(controleqt++ != int(tabela.length()+1)){
        if(tabela[i] == lsdir->d_name[i]){
          if((i+1) == int(tabela.length())){
            apagando = diretoriolocal;
            apagando = apagando + lsdir->d_name;

            remove(apagando.c_str());
          }
        }
        else{
          break;
        }
      i++;
      }   
  }
  closedir(dir);
  return SUCCESS;
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

// retirado de https://stackoverflow.com/questions/4654636/how-to-determine-if-a-string-is-a-number-with-c
bool is_number(const std::string& s) {
    return !s.empty() && std::find_if(s.begin(), 
        s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
}

void Comandos::inserirRegistro(string tabela, string registro) {
  auto par_meta = getVetorDeMetadados(tabela, true);
  vector<string> metadados = par_meta.first;
  vector<string> indices_meta = par_meta.second;
  size_t quantidade_de_campos = stoi(metadados[2]);
  cout << "Inserir registro " << registro << " na tabela " << tabela << '\n';
  // vetor em que cada entrada é um campo da inserção
  vector<string> inserir = parseInsercao(registro);

  if (quantidade_de_campos != inserir.size())
  {
    cout << "ERRO IMPOSSÍVEL INSERIR NA TABELA: Quantidade incorreta de campos para inserir\n";
    return;
  }

  // vetor com indices (se houver)
  vector<string> indices;
  // vetor com tipos de indices (se houver)
  vector<string> tipos;
  // vetor com indice (literalmente) do registro a ser inserido (se houver indice)
  vector<int> index;
  for (size_t i = 0; i < quantidade_de_campos; i++)
  {
    string campo = metadados[3+i]; // 3 é a posição do primeiro campo
    string tipo = retornaPalavraDeInput(campo, ':');
    if (tipo == "INT")
    {
      if(is_number(inserir[i]) == false) {
        cout << "ERRO TIPO INCORRETO: TIPO INCORRETO DE DADOS NO CAMPO " << i << '\n';
        return;
      }
    }

    // transforma campo no nome do campo removendo o ':'
    campo = campo.erase(0, 1);
    // verificar se existe indice para o campo
    for (int j = 0; j < indices_meta.size(); j++) {
      string indice_campo = indices_meta[j].substr(0, indices_meta[j].find(' '));
      string indices_tipos = indices_meta[j].substr(indices_meta[j].find(' ') + 1, indices_meta[j].size());
      // adiciona no vetor se indice existir
      if (campo == indice_campo) {
        indices.push_back(indice_campo);
        tipos.push_back(indices_tipos);
        index.push_back(i);
      }
    }
  }
  // bestFit retorna (0, ponteiro) caso nao exista espacos marcados como invalido
  // neste caso, a insercao ocorre no fim do arquivo (onde ponteiro marca),
  // ou (1, ponteiro) caso bestFit tenha funcionado e o ponteiro onde foi inserido
  auto par = bestFit(tabela, inserir);
  int sucesso = par.first;
  int ponteiro = par.second;
 
  if (sucesso == 0) {
    ofstream file;
    file.open("tabelas/" + tabela + "_TAB.txt", ios_base::app);
    if (file.fail()) {
      // TODO o arquivo não existe (a tabela não foi criada)
      std::cout << "ERRO" << '\n';
      return;
    }
    // escrever no arquivo cada entrada do vetor inserir
    int tamanho_insercao = 0;
    for (auto reg : inserir) {
      tamanho_insercao += reg.size();
      file << reg << ';';
    }
    tamanho_insercao = MIN_SIZE - ++tamanho_insercao;
    for (int i = 0; i < tamanho_insercao; i++) {
      file << '|';
    }
    file << '\n';
    file.close();
  }

  // inserir nas tabelas de indice
  cout << "INDICES" << endl;
  for (int i = 0; i < indices.size(); i++) {
    if (tipos[i] == "A") {
      // inserir em arvore
      cout << "Arvore" << endl;
      cout << "Inserindo: " << inserir[index[i]] << "  na arvore de " << indices[i] << " com ponteiro " << ponteiro << endl; 
    }
    else if (tipos[i] == "H") {
      // inserir em hash
      cout << "Hash" << endl;
      cout << "Inserindo: " << inserir[index[i]] << "  na hash de " << indices[i] << " com ponteiro " << ponteiro << endl; 
    }
  }
}

bool linhaInvalida(string linha) {
  return linha.find('#') != string::npos;
  
}

// Função para verificar se um indice em uma dada tabela possui função hash
// retorna true se possui, false caso contrário
bool Comandos::possuiHash(string tabela, string indice) {
  vector<string> indices = getVetorDeMetadados(tabela, true).second;
  for (auto &ind: indices) {
    if (ind.find(indice) != string::npos && ind.find(" H") != string::npos) return true;
  }
  return false;
}

// Função para verificar se um indice uma dada tabela possui arvore
// retorna true se possui, false caso contrário
bool Comandos::possuiArvore(string tabela, string indice) {
  vector<string> indices = getVetorDeMetadados(tabela, true).second;
  for (auto &ind: indices) {
    if (ind.find(indice) != string::npos && ind.find(" A") != string::npos) return true;
  }
  return false;
}

void Comandos::buscaEmTabela(string modifier, string tabela, string busca) {
  ifstream file; //Leitura do arquivo
  struct busca busca_aux;
  vector<int> vet_buscas;
  file.open("tabelas/" + tabela + "_TAB.txt");
  if (file.fail()) {
    // TODO o arquivo não existe (a tabela não foi criada)
    std::cout << "Não foi possível encontrar a Tabela." << '\n';
    return;
  }

  auto par = getVetorDeMetadados(tabela);
  vector<string> linha_meta_dados = par.first;
  // Retira o tipo dos campo, mantendo somente o nome do campo
  vector<string> nomes_campos;
  unsigned int quantidade_de_campos = stoi(linha_meta_dados[2]);

  //parse do campo selecionado para busca
  size_t pos_dois_pontos = busca.find(":");              //Posição dos ":"
  string campo_b = busca.substr(0, pos_dois_pontos);     //Separa o início da string até ":"
  string elemento_b = busca.substr(pos_dois_pontos + 1); //Separa o ":" até o fim

  bool existe_campo = false; // Verificador da existência do campo
  unsigned int i = 0;
  int indice_campo; // Armazena a posição do campo que foi encontrado na busca

  // checa se o indice campo_b possui hash. A verificação da hash acontece primeiro pois
  // é mais eficiente, e decidimos por ser preferencial em relação à árvore.
  if (possuiHash(tabela, campo_b)) {
    cout << "possui hash do indice: " << campo_b << endl;
    return;
  }
  // checa se o indice campo_b possui arvore
  else if (possuiArvore(tabela, campo_b)) {
    cout << "possui arvore do indice: " << campo_b << endl;
    return;
  }

  // caso não tenha hash nem arvore, faz a busca sequencial

  //Percorre todos os campos presentes no meta, e ao encontrar o campo necessário pra busca, armazena sua posição em indice_campo
  while (i < quantidade_de_campos) {
    size_t pos_dois_pontos = linha_meta_dados[3 + i].find(":");
    string campo = linha_meta_dados[3 + i].substr(pos_dois_pontos + 1);
    nomes_campos.push_back(campo); //Insere o nome do campo no vetor
    // Se o campo for igual ao campo da busca, armazena a posição
    if (campo == campo_b) {
      indice_campo = i;
      existe_campo = true;
    }
    i++;
  }
  if (!existe_campo) {
    cout << "Não foi possível encontrar o campo" << endl;
    return;
  }

  // Linha busca = 1;2;3;4;
  // Vetor = [1, 2, 3, 4]
  string linha_busca;
  vector<string> vetor_linha_busca;
  
  int pos_do_char = 0; // posição do ponteiro pro fseek
  bool encontrou = false;
  bool existe_nas_buscas = false;

  if (modifier == "N") {
    cout << "Busca em " << tabela << " todos com critério " << busca
         << '\n';
    do {
      getline(file, linha_busca); //Armazena a linha em linha_busca
      int tamanho_da_linha = linha_busca.length();
      // Ignora linha inválida
      if (linhaInvalida(linha_busca)) { 
        cout << "ignorado" << '\n';
        pos_do_char += tamanho_da_linha + 1;
        continue;
      } 

      vetor_linha_busca = parseBuscaMetaDados(linha_busca); //Armazena os campos da linha atual
      //Evita segmentation fault quando pega uma linha vazia.
      if (linha_busca != "") {
        if (vetor_linha_busca[indice_campo] == elemento_b) { 
          //Compara o conteúdo do campo com o conteúdo da busca
          encontrou = true;
          busca_aux.linhas.push_back(pos_do_char);
        }
      }
      pos_do_char += tamanho_da_linha + 1;
    } while (!file.eof());
  }
  else if (modifier == "U") {
    cout << "Busca em " << tabela << " primeiro com critério " << busca
          << '\n';

    // Busca até encontrar o primeiro campo igual ao conteúdo da busca
    do {
      getline(file, linha_busca); //Armazena a linha em linha_busca
      int tamanho_da_linha = linha_busca.length();
      // Ignora linha inválida
      if (linhaInvalida(linha_busca)) { 
        cout << "ignorado" << '\n';
        pos_do_char += tamanho_da_linha + 1;
        continue;
      } 

      vetor_linha_busca = parseBuscaMetaDados(linha_busca); //Armazena os campos da linha atual
      //Evita segmentation fault quando pega uma linha vazia.
      if (linha_busca != "") {
        if (vetor_linha_busca[indice_campo] == elemento_b) { 
          //Compara o conteúdo do campo com o conteúdo da busca
          encontrou = true;
          busca_aux.linhas.push_back(pos_do_char);
        }
      }
      pos_do_char += tamanho_da_linha + 1;
    } while (!file.eof() && !encontrou);
  }
  else { // Modificador incorreto
      cout << "Modificador não reconhecido: " << modifier << ". Utilize N para fazer a busca, na tabela, de todos os registros que satisfaçam o critério de busca e U para fazer a busca, na tabela, do primeiro registro que satisfaça o critério. \n";
      return;
  }
  if (encontrou) {
    if(!buscas.size()){
      busca_aux.nome_tabela = tabela;
      buscas.push_back(busca_aux);
    }
    else{
      i = 0;
      while(i < buscas.size() && !existe_nas_buscas){
        if(buscas[i].nome_tabela == tabela){
          buscas[i].linhas = busca_aux.linhas;
          existe_nas_buscas = true;
        }
        i++;
      }
      if(!existe_nas_buscas){
        busca_aux.nome_tabela = tabela;
        buscas.push_back(busca_aux);
      }
    }
    cout << "REGISTRO ENCONTRADO" << endl;
  }
  else {
    cout << "REGISTRO NÃO ENCONTRADO" << endl;
  }
  return ;
}

void Comandos::apresentarRegistrosUltimaBusca(string tabela) {
  
  // ifstream file; //Leitura do arquivo
  // file.open("tabelas/" + tabela + "_TAB.txt");
  FILE *fp;
  fp = fopen(("tabelas/" + tabela + "_TAB.txt").c_str(), "r");
  if (fp == NULL) {
    // TODO o arquivo não existe (a tabela não foi criada)
    std::cout << "Não foi possível encontrar a Tabela." << '\n';
    return;
  }

  //0  = Nome Tabela / 1 = path txt meta / 2 = qtd de campos / 3 até 3+qtd de campos = campos / ultimo = data
  auto par = getVetorDeMetadados(tabela);
  vector<string> linha_meta_dados = par.first;
  // Retira o tipo dos campo, mantendo somente o nome do campo
  vector<string> nomes_campos;
  unsigned int i = 0;
  unsigned int quantidade_de_campos = stoi(linha_meta_dados[2]);

  //Percorre todos os campos presentes no meta, e ao encontrar o campo necessário pra busca, armazena sua posição em indice_campo
  while (i < quantidade_de_campos){
    size_t pos_dois_pontos = linha_meta_dados[3+i].find(":");
    string campo = linha_meta_dados[3+i].substr(pos_dois_pontos+1);
    nomes_campos.push_back(campo); 
    i++;
  };

  bool existe_busca = false;
  vector<int> linhas;
  cout << "Apresentar registro da última busca em " << tabela << '\n';
  if(buscas.size()){
    for(i = 0; i < buscas.size(); i++){
      if(buscas[i].nome_tabela == tabela){
        existe_busca = true;
        linhas = buscas[i].linhas;
      }
    }
  }
  if(existe_busca){
    string resultado;
    i = 0;
    int linhas_restantes = linhas.size();
    while(linhas_restantes--) {
      fseek(fp, linhas[i], SEEK_SET);
      i++; // próximo elemento do vetor de linhas encontradas;

      char tmp[1000000] = {'\n'};
      fscanf(fp, "%[^\n^|]", tmp); // ler a linha atual até | ou \n
      resultado = tmp;
      for (int k = 0; k < nomes_campos.size(); k++){
        cout << nomes_campos[k] << ": " << retornaPalavraDeInput(resultado, ';') << " ";
      }
      cout << endl;
    }
    // while(getline(file, resultado) && j < linhas.size()){
    //   if(i == linhas[j]){
    //     for (k = 0; k < nomes_campos.size(); k++){
    //       cout << nomes_campos[k] << ": " << retornaPalavraDeInput(resultado, ';') << " ";
    //     }
    //     cout << endl;
    //     j++;
    //   }
    //   i++;
    // }
  }
  else{
    cout << "Nenhuma pesquisa referente a essa tabela foi encontrada." << endl;
  }


}

void Comandos::removeRegistrosUltimaBusca(string tabela){
  auto par_meta = getVetorDeMetadados(tabela, true); //retorna um par com <vetor com os metadados da tabela,indices existentes da tabela c/ o tipo>
  vector<string> metadados = par_meta.first;  
  vector<string> indices_meta = par_meta.second; //vector com cada linha sendo "nomeIndice tipoIndice"

  // ponteiro_head: ponteiro para o primeiro registro invalido (salvo nos metadados)
  int ponteiro_head = stoi(metadados[1].substr(0, metadados[1].find('|')));
  
  size_t qtd_campo = stoi(metadados[2]);
  vector<string> indices; //vector que guarda os indices
  vector<string> tipos;   //vector que guarda os tipos de cada indice
  
  vector<vector<string>> reg_removido; //guarda os registros que serao removidos dos indices
  vector<int> campo_indexado;              //indica o(s) campo(s) indexado(s) nessa tabela
  vector<int> ponteiro;

  int tab=0;
  while(tabela != buscas[tab].nome_tabela || tab == buscas.size())
      tab++;
  
  if(tab == buscas.size()){
    cout << "erro" << endl;
    return;
  }
  cout << "a tabela é a" << buscas[tab].nome_tabela << endl;

  string arquivo_tab = "tabelas/" + tabela + "_TAB.txt";

  for (size_t i = 0; i < buscas[tab].linhas.size(); i++) {
    ifstream arquivo;
    arquivo.open(arquivo_tab);
    arquivo.seekg(0, ios::beg);

    // anterior: registro que esteja antes do removido
    // atual: registro a ser removido
    // posterior: registro que esteja apros o removido
    int pos = 0;
    Comandos::Removido anterior;
    anterior.pos = -1;
    Comandos::Removido atual;
    Comandos::Removido posterior;
    posterior.pos = -1;

    int qtd_linha = -1;
    string linha;
    while (getline(arquivo, linha) && posterior.pos == -1) {
      qtd_linha++;
      if (qtd_linha == buscas[tab].linhas[i]) {
        atual.pos = pos + (2 * qtd_linha);
        atual.tamanho = linha.size();
        atual.conteudo = linha;

        reg_removido.push_back(parseInsercao(linha));
        ponteiro.push_back(pos + 1);
      } else {
        if (qtd_linha < buscas[tab].linhas[i] && linha.find('#') != string::npos) {
          anterior.pos = pos + (2 * qtd_linha);
          anterior.tamanho = linha.size();
          anterior.conteudo = linha;
        }
        else if (qtd_linha > buscas[tab].linhas[i] && linha.find('#') != string::npos) {
          posterior.pos = pos + (2 * qtd_linha);
          posterior.tamanho = linha.size();
          posterior.conteudo = linha;
        }
      }
      pos += linha.size(); 
    }
    arquivo.close();

    // se o registro removido veio antes do ponteiro_head entao atualize o ponteiro_head para o atual
    // atualize tmb os metadados assim que terminar o loop
    if (atual.pos < ponteiro_head || ponteiro_head == -1) 
      ponteiro_head = atual.pos;
  
    FILE *fp;
    fp = fopen(arquivo_tab.c_str(), "r+");
    // se existe um registro anterior (removido), altere o ponteiro do anterior para o atual
    // e o ponteiro do atual.prox para aquele que o anterior apontava
    // atual.prox -> anterior.prox  &  anterior.prox -> atual
    if (anterior.pos != -1) {
      retornaPalavraDeInput(anterior.conteudo, '#');
      anterior.conteudo.erase(0, 1);
      atual.prox = stoi(anterior.conteudo.substr(0, linha.find('#')));
      anterior.prox = atual.pos;
      anterior.buffer = to_string(anterior.tamanho) + "#" + to_string(anterior.prox) + '#';

      fseek(fp, anterior.pos, SEEK_SET);
      fprintf(fp, anterior.buffer.c_str());
    }

    atual.prox = posterior.pos;
    atual.buffer = to_string(atual.tamanho) + '#' + to_string(atual.prox) + '#';
    fseek(fp, atual.pos, SEEK_SET);
    fprintf(fp, atual.buffer.c_str());
    fclose(fp);
  }

  alterarPonteiroHead(tabela, ponteiro_head);

  // checar se exsite indice
  for (size_t i = 0; i < qtd_campo; i++){
    string campo = metadados[3+i]; // 3 é a posição do primeiro campo
    
    // transforma campo no nome do campo removendo o tipo seguido do ':'
    campo = campo.erase(0, 4);

    // verificar se existe indice para o campo
    for (size_t j = 0; j < indices_meta.size(); j++) {
      string indice_campo = indices_meta[j].substr(0, indices_meta[j].find(' '));
      string indices_tipos = indices_meta[j].substr(indices_meta[j].find(' ') + 1, indices_meta[j].size());
      // adiciona no vetor se indice existir
      if (campo == indice_campo) {
        indices.push_back(indice_campo);
        tipos.push_back(indices_tipos);
        campo_indexado.push_back(i);
      }
    }
  }

  for(size_t i = 0; i < reg_removido.size(); i++){
    for (size_t j = 0; j < indices.size(); j++) {
      if (tipos[j] == "A") {
        // remove na arvore
        cout << "Removendo: " << reg_removido[i][campo_indexado[j]] << " com ponteiro " << ponteiro[i] << " na ARVORE de " << indices[j] << "." << endl; 
      }
      else if (tipos[j] == "H") {
        // remove na hash
        cout << "Hash" << endl;
        cout << "Removendo: " << reg_removido[i][campo_indexado[j]] <<  " com ponteiro" << ponteiro[i] << "  na HASH de " << indices[j] << "." << endl; 
      }
    }
  }
}

int Comandos::criaIndice(string modifier, string tabela, string chave) {
  tabela = "./tabelas/" + tabela + "_META.txt";
  // verificar se a chave e valida
  ifstream arquivo;
  arquivo.open(tabela);
  
  // qtd de ";" ate os campos (ate o numero que indica a quantidade de campos)
  int qtd_ate_campos = 2;
  // qtd de campos
  int qtd_campos;
  string linha;
  getline(arquivo, linha);
  for (int i = 0; i < qtd_ate_campos; i++) {
    retornaPalavraDeInput(linha, ';');
  } linha.erase(0, 1);
  qtd_campos = stoi(linha.substr(0, linha.find(';')));
  // deixa a linha contendo apenas os campos em diante
  retornaPalavraDeInput(linha, ';');
  linha.erase(0, 1);

  // armazena o tipo de cada campo em uma posicao do vector
  string campos;
  string tipo;
  for (int i = 0; i < qtd_campos && campos != chave; i++) {
    tipo = retornaPalavraDeInput(linha, ':');
    linha.erase(0, 1);
    campos = retornaPalavraDeInput(linha, ';');
    linha.erase(0, 1);
  }
  
  if (campos != chave) {
    cout << "Erro: Campo invalido.\nTerminando execução." << endl;
    return FINISH_PROGRAM;
  }

  if (tipo != "INT") {
    cout << "Erro: Apenas campos inteiros (INT) podem ser indexados." << endl;
    return SUCCESS;
  }

  // verificar se o indice ja existe
  while (getline(arquivo, linha)) {
    string campo_encontrado;
    string tipo_encontrado;
    campo_encontrado = retornaPalavraDeInput(linha, ' ');
    linha.erase(0, 1);
    tipo_encontrado = linha;
    // se o indice ja existe && tipo do indice ja existe
    if (campo_encontrado == campos && tipo_encontrado == modifier) {
      cout << "Erro: Índice já existe. Comando ignorado." << endl;
      return SUCCESS;
    }
  }
  arquivo.close();
  
  // insere indice e tipo no arquivo de metadados
  ofstream arquivo_meta;
  arquivo_meta.open(tabela, ios::app);
  arquivo_meta << campos + ' ' + modifier << endl; 
  arquivo_meta.close();

  if (modifier == "A") {
    cout << "Cria um índice estruturado para " << tabela
              << " usando a chave " << chave << '\n';
  } else if (modifier == "H") {
    cout << "Cria um índice usando hash para " << tabela
              << " usando a chave " << chave << '\n';
  } else {
    cout << "Erro: Modificador não reconhecido: " << modifier << '\n'
		 << "Utilize A para criar um índice estruturado como árvore de múltiplos caminhos para a tabela, usando chave como chave de busca, atualizando os metadados e  H para criar um índice usando hashing para a tabela, usando chave como chave de busca, atualizando os metadados. \n";
  }
  return SUCCESS;
}

void Comandos::removeIndiceChave(string tabela, string chave) {
  string meta = "tabelas/";
  meta.append(tabela);
  meta.append("_META.txt");

  string linha;
  ifstream arquivo;
  arquivo.open(meta);

  ofstream temp;
  temp.open("tabelas/temp.txt");
  if (arquivo.is_open()) {
    getline(arquivo, linha);
    temp << linha << endl;
    while (!arquivo.eof()) {
      getline(arquivo,linha);
      if (linha.find(chave) != string::npos) {
        if (linha.find(" A") != string::npos) {
          cout << "REMOVER ARVORE" << endl;
        } else if (linha.find(" H") != string::npos) {
          cout << "REMOVER HASH" << endl;
        }
      } else {
        if (linha.size() != 0) {
          temp << linha << endl;
        }
      }
    }
    arquivo.close();
    temp.close();

    const char * p = meta.c_str();
    remove(p);
    rename("tabelas/temp.txt", meta.c_str());
  }
  else{
    cout << "Erro ao tentar ler metadados" << endl;
  }
}

void Comandos::geraNovoIndiceDeTabelaChave(string tabela, string chave) {
  cout << "Gera novamente o indice de " << tabela << " referente a chave "
            << chave << '\n';
}

// retorna um "ponteiro" para o proximo espaco disponivel
int Comandos::ponteiroProximo(string &linha) {
  retornaPalavraDeInput(linha, '#');
  linha.erase(0, 1);
  return stoi(linha.substr(0, linha.find('#')));
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

tuple<Comandos::Removido, Comandos::Removido, int> Comandos::encontrarOndeInserir(string tabela, int tam_inserir) {
  ifstream arquivo;
  string arquivo_tab = "./tabelas/" + tabela + "_TAB.txt";
  arquivo.open(arquivo_tab);
  if (!arquivo.is_open())
    cout << "Erro ao abrir arquivo" << arquivo_tab << endl;
  arquivo.seekg(0, ios::beg);
  string linha;
  int percorrido_pos = 0;
  int qtd_linha = 0;

  int tam_disponivel;
  int tam_atual;
  int melhor_tam = numeric_limits<int>::max();
  int pos = 0;
  int pos_prox;
  Comandos::Removido melhor;
  melhor.pos = -1;
  Comandos::Removido anterior_melhor;
  Comandos::Removido anterior;
  anterior.pos = 0;
  anterior.prox = 0;

  // ponteiro_head: ponteiro para o primeiro registro invalido (salvo nos metadados)
  auto par = getVetorDeMetadados(tabela);
  vector<string> metadados = par.first;
  int ponteiro_head = stoi(metadados[1].substr(0, metadados[1].find('|')));

  // se nao existir nenhum espaco removido: leia o arquivo e retorne a posicao do final do arquivo
  if (ponteiro_head == -1) {
    while (getline(arquivo, linha)) {
      percorrido_pos += linha.size();
      qtd_linha++;
    }

  }
  else {
    while (getline(arquivo, linha)) {
      cout << linha << endl;
      if (linha.find('#') != string::npos) { 
        tam_atual = linha.size();
        tam_disponivel = tam_atual - tam_inserir;

        pos = anterior.prox;
        string copia_linha = linha;
        pos_prox = ponteiroProximo(copia_linha);
        if (tam_disponivel >= 0 && tam_disponivel <= melhor_tam) {
          melhor_tam = tam_disponivel;
          anterior_melhor.tamanho = anterior.tamanho;
          anterior_melhor.pos = anterior.pos;

          melhor.pos = pos;
          melhor.tamanho = tam_atual;
          melhor.prox = pos_prox;
        }
        anterior.tamanho = tam_atual;
        anterior.pos = anterior.prox;
        anterior.prox = pos_prox;
        // mover para o proximo removido
        arquivo.seekg(pos_prox, ios::beg);
      }  else {
        pos += linha.size();
        qtd_linha++;
        anterior.prox = pos + (2 * qtd_linha);
        anterior.pos = anterior.prox;
      }
    }
  }
  // condicao de best fit falhar, retorne a posicao do final do arquivo
  if (melhor.pos == -1) {
    melhor.prox = percorrido_pos + (2 * qtd_linha);
  }

  arquivo.close();
  return make_tuple(anterior_melhor, melhor, ponteiro_head);
}

pair<int, int> Comandos::bestFit(string tabela, vector<string> inserir) {
  string arquivo_tab = "./tabelas/" + tabela + "_TAB.txt";
  // calcula o tamanho da nova insercao
  int tam_inserir = 0;
  for (auto reg : inserir)
    tam_inserir += reg.size() + 1;

  // le o arquivo e verifica se existe algum espaco valido para insercao
  auto par = encontrarOndeInserir(tabela, tam_inserir);
  Comandos::Removido melhor_anterior = get<0>(par);
  Comandos::Removido melhor = get<1>(par);
  int ponteiro_head = get<2>(par);
  // retorna se nao ha espacos validos
  if (melhor.pos == -1) {
    return make_pair(0, melhor.prox);
  }
  
  // insere no espaco disponivel
  FILE *arquivo;
  arquivo = fopen(arquivo_tab.c_str(), "r+");
  // mudar ponteiro da anterior
  fseek(arquivo, melhor_anterior.pos, SEEK_SET);
  melhor_anterior.buffer = to_string(melhor_anterior.tamanho) + '#' + to_string(melhor.prox) + '#';
  fprintf(arquivo, melhor_anterior.buffer.c_str());

  // se o registro inserido for igual ao ponteiro_head
  // atualize o ponteiro_head
  if (ponteiro_head == melhor.pos) {
    ponteiro_head = melhor.prox;
    alterarPonteiroHead(tabela, ponteiro_head);
  }

  // nova insercao no espaco disponivel
  fseek(arquivo, melhor.pos, SEEK_SET);
  for (auto reg : inserir) {
    fprintf(arquivo, reg.c_str());
    fprintf(arquivo, ";");
  }
  int remanescente = melhor.tamanho - tam_inserir;
  cout << remanescente;
  for (int i = 0; i < remanescente; i++) {
    fprintf(arquivo, "|");
  }
  fclose(arquivo);
  return make_pair(1, melhor.pos);
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

// Função para pegar as informações do arquivo de metadados
// Retorna um par em que o elemento first é a primeira linha do metadados (informações da tabela)
// o segundo elemento second é um vetor em que cada entrada é uma linha a partir da 2a linha, 
//  indicando quais indices existem na tabela.
// Para receber os indices, o argumento IR deve ser setado como true
pair<vector<string>, vector<string>> Comandos::getVetorDeMetadados(string tabela, bool IR) {
  ifstream file_meta; //Leitura do arquivo
  file_meta.open("tabelas/" + tabela + "_META.txt");

  if (file_meta.fail()) {
    // TODO o arquivo não existe (a tabela não foi criada)
    std::cout << "Não foi possível encontrar a o Metadados da Tabela." << '\n';
    vector<string> empty;
    return make_pair(empty, empty);
  }

  string dados_file_meta;
  //file_meta >> dados_file_meta; //recebe como string todo o conteudo do arquivo meta da tabela
  getline(file_meta, dados_file_meta);
  //0  = Nome Tabela / 1 = path txt meta / 2 = qtd de campos / 3 até 3+qtd de campos = campos / ultimo = data
  vector<string> linha_meta_dados = parseBuscaMetaDados(dados_file_meta);
  
  // recebe os indices (se existir)
  vector<string> linhas_indice;
  if (IR) {
    string buffer;
    while (getline(file_meta, buffer)) {
      linhas_indice.push_back(buffer);
    }
  }
  return make_pair(linha_meta_dados, linhas_indice);
} 

void Comandos::alterarPonteiroHead(string tabela, int ponteiro_head) {
  string arquivo_meta = "./tabelas/" + tabela + "_META.txt";

  string buffer = to_string(ponteiro_head);
  // se sobrar espaco no buffer: preencha com '|' pois deve possuir tamanho fixo
  for (int i = 0; i < (PONTEIRO_HEAD_SIZE - buffer.size()); i++) {
    buffer.push_back('|');
  }

  // a posicao do ponteiro_head sempre sera o tamanho do nome da tabela + 1 (;)
  int pos = tabela.size() + 1;
  FILE *fp;
  fp = fopen(arquivo_meta.c_str(), "r+");
  fseek(fp, pos, SEEK_SET);
  fprintf(fp, buffer.c_str());
  fclose(fp);
}