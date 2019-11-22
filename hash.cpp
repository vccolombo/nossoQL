#include "hash.h"


bool compare(const std::pair<int, int>&i, const std::pair<int, int>&j)
{
    return i.first < j.first;
}


void iniciaHash(int quant_reg, std::string tabela, std::string campo){
    FILE* arquivo;  //ponteiro para arquivo
    int tam = ceil((quant_reg / TAM_BLOCO)/0.6);                    //quant de bloco
    long int pos_bloco = 0;                                         //auxiliar para preencher o arquivo
    long int hash[tam];                                             //ira guardar o endereco de cada bloco do arquivo
    
    std::string nome_arq = (tabela + "_" + campo +  "_HASH.bin");   //nome do arquivo - "tabela_campo_HASH.bin"
    bloco block;                                                    //bloco auxliar pra preencher arquivo com os blocos iniciais
    block.prox = -1;                                                //-1 indicando a inexistencia de um bloco adicional
    block.num_elem = 0;                                             //0 pois os blocos começam vazios


    //escreve tam e escreve um long int = 0 tam vezes
    arquivo = fopen(nome_arq.c_str(), "wb+");
    fseek(arquivo,0,SEEK_SET);
    fwrite(&tam,sizeof(int),1,arquivo);                              //escreve quantos blocos tem na hash
    for(int i=0; i<tam;i++)
        fwrite(&pos_bloco,sizeof(long int), 1, arquivo);             //escreve tam vezes um long que int que ira...
    fclose(arquivo);                                                 //...ira indicar a posicao de cada bloco no arquivoo    


    //escreve os blocos no arquivo e atualiza o vetor hash com a posicao no arquivo de cada bloco
    arquivo = fopen(nome_arq.c_str(), "ab");                     //abre o arquivo com append binario
    for (int i=0; i<tam;i++){                                    //itera tam vezes:
        hash[i] = ftell(arquivo);                                //escrevendo em hash[i] a posicao que o bloco sera escrito no arquivo
        fwrite(&block,sizeof(bloco),1,arquivo);                  //escreve bloco aux no arquivo tam vezes
    }
    fclose(arquivo);                                             //fecha o arquivo


    // atualiza os long int com a posicao de cada bloco escrito anteriormente (que esta guardado em hash[i])
    arquivo = fopen(nome_arq.c_str(), "rb+");                       //abre o arquivo
    for (int i=0; i<tam;i++){                                       //itera tam vezes:
        fseek(arquivo,sizeof(int) + i*sizeof(long int),SEEK_SET);   //com o offset do primeiro int escrito (linha 19) anda passos de tamanho long int
        fwrite(&hash[i],sizeof(long int),1,arquivo);                //escrevendo no arquivo a posicao que os blocos foram escritos no arquivo
    }
    fclose(arquivo);                                                //fecha o arquivo
    //*/

}
        
long int buscaHash(std::string tabela, std::string campo, int chave){
    FILE* arquivo;
    std::string nome_arq = (tabela + "_" + campo +  "_HASH.bin"); //nome do arquivo
    int tam_hash; //tamanho da hash, necessario para usar no modulo da funcao hash
    int pos_hash; //indica qual posicao a funcao hash retornou
    long int pos_bloco; //indica qual posicao a hash aponta

    arquivo = fopen(nome_arq.c_str(),"rb"); //abre o arquivo para leitura binaria
    fseek(arquivo,0,SEEK_SET);
    fread(&tam_hash,sizeof(int),1,arquivo); //le tamanho da hash
    fclose(arquivo);
    pos_hash = (chave * 127) % tam_hash;      //executa a func. hash obtendo a pos do vetor hash 
    
    //std::cout << "POS_HASH - " << pos_hash;

    arquivo = fopen(nome_arq.c_str(),"rb");
    fseek(arquivo,sizeof(int) + pos_hash*sizeof(long int),SEEK_SET);    //vai até o endereco pos_ash
    fread(&pos_bloco,sizeof(long int),1,arquivo);                       //pega o endereco do bloco apontado por pos_hash
    fclose(arquivo);

    return pos_bloco;
    
}


void insereHash(std::string tabela, std::string campo, std::pair<int,int> el, long int pos_bloco ){
    FILE* arquivo;
    bloco prim_bloco;
    std::string nome_arq = (tabela + "_" + campo +  "_HASH.bin"); //nome do arquivo
    //std::cout << " POS_BLOCO - " << pos_bloco << std::endl;
    
    arquivo = fopen(nome_arq.c_str(),"rb+"); //abre pra leitura e escrita sem sobrescrever o arquivo
    fseek(arquivo,pos_bloco,SEEK_SET);
    fread(&prim_bloco,sizeof(bloco),1,arquivo); //le o bloco apontado por pos_bloco
    
    if (prim_bloco.num_elem < TAM_BLOCO){               //se o bloco nao estiver cheio
        prim_bloco.elemento[prim_bloco.num_elem] = el;      //insere o par no vetor
        prim_bloco.num_elem++;                              //atualiza o preenchimento do vetor
        fseek(arquivo,pos_bloco,SEEK_SET);                  //como houve um fread que após a leitura anda com o ponteiro, é preciso voltar novamente ao pos_bloco
        fwrite(&prim_bloco,sizeof(bloco),1,arquivo);        //sobrescreve o bloco com as infos atualizadas
        fclose(arquivo);
    }
    else if(prim_bloco.prox == -1){                     //se nao tiver um proximo bloco
        bloco novo_bloco;                                   //cria um novo bloco
        fseek(arquivo,0,SEEK_END);                          //vai para o final do arquivo
        prim_bloco.prox = ftell(arquivo);                   //atualiza o bloco.prox do primeiro para apontar para final do arquivo (onde ira ser inserido o proximo bloco)
        novo_bloco.prox = -1;                               //novo bloco aponta pra nenhum bloco
        novo_bloco.elemento[0] = el;                        //ja insere o el no novo bloco
        novo_bloco.num_elem = 1;                            //e atualiza o numero de elementos em 1
        fwrite(&novo_bloco,sizeof(bloco),1,arquivo);        //escreve o novo bloco no final do arquivo
        fseek(arquivo,pos_bloco,SEEK_SET);                  //volta para a posicao do primeiro bloco
        fwrite(&prim_bloco,sizeof(bloco),1,arquivo);        //sobrescreve o primeiro bloco com o novo bloco.prox
        fclose(arquivo);
    }
    else{                                               //se o bloco esta cheio, e existe um proximo bloco
        insereHash(tabela,campo,el,prim_bloco.prox);        //chamamos a insercao nesse novo bloco
    }

    

}


std::vector<bloco> leHash(std::string tabela, std::string campo, int chave){
    FILE* arquivo;
    std::vector<bloco> block;
    bloco aux;
    std::string nome_arq = (tabela + "_" + campo+  "_HASH.bin"); //nome do arquivo
    
    long int pos_bloco = buscaHash(tabela,campo,chave); //pega a pos_bloco referente a chave
    
    arquivo = fopen(nome_arq.c_str(),"rb"); //abre o arquivo para leitura
    fseek(arquivo,pos_bloco,SEEK_SET);      //move o ponteiro para pos_bloco
    fread(&aux,sizeof(bloco),1,arquivo);    // le o bloco para um auxiliar...
    block.push_back(aux);                   //e o insere no vector de blocos
    
    while(aux.prox != -1){                  //enquanto aux.prox apontar para um novo bloco
        fseek(arquivo,aux.prox,SEEK_SET);           //iremos ate aux.prox
        fread(&aux,sizeof(bloco),1,arquivo);        //atualizaremos aux com esse novo bloco
        block.push_back(aux);                       //o inserimos para o vector de blocos
    }

    return block;
    
    
}


void removeHash(std::string tabela, std::string campo){
    std::string nome_arq = (tabela + "_" + campo+  "_HASH.bin"); //nome do arquivo
    int status = remove(nome_arq.c_str());

    if (status == 0)
        std::cout << "o arquivo: \"" << nome_arq << "\" foi deletado com sucesso." << std::endl;
    else
    {
       std::cout << "Nao foi possivel deletar o arquivo" << std::endl;
    }
}



/*
int main(){
    std::string tab = "tabela";
    std::string camp = "campo";
    std::vector<bloco> bl;

    iniciaHash(20,tab,camp);
    for(int i = 0; i<20;i++){
        std::pair<int, int > a;
        a.first = (i+1)*10;
        a.second = 99-i;
        //std::cout << a.first << " ";
        insereHash("tabela","campo",a, buscaHash(tab,camp,a.first));
    }
    std::cout << "pos insercao > " << std::endl << std::endl;
    
    for(int i=0; i<20; i++){
        std::vector<bloco> blocos;
        blocos = leHash(tab,camp,(i+1)*10);
        for(int j = 0; j<blocos.size();j++){
            //std::cout << " [CHAVE  " << i << ", BLOCO " << j << "] - ";
            for(int k = 0; k<blocos[j].num_elem;k++){
                //std::cout << "[" << blocos[j].elemento[k].first << "," << blocos[j].elemento[k].second << "], ";
            }
            std::cout << std::endl;
        }

    }
    removeHash(tab,camp);
    return 0;
}

*/