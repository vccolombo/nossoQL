#include <iostream> 
#include <utility> 
#include <vector> 
#include <math.h>

#define TAM_BLOCO 13

typedef struct{
    int num_elem; // quantidade de elementos presente no bloco
    std::pair<int,int> elemento[TAM_BLOCO]; // <chave,ponteiro da tabela>
    long int prox; // ponteiro para proximo bloco caso o primeiro fique cheio
}bloco;


/* Essa biblioteca gera um hash dinâmico, isto é, uma hash que pode crescer, uma hash de blocos.

iniciaHash - cria o arquivo contendo respectivamente 
     [tam, hash[tam], bloco, bloco, bloco ..... ]
     tam - o tamanho do vetor hash 
     hash[tam] - uma sequencia de long ints, indicando a posicao de cada um dos tam primeiro blocos
     bloco - blocos vao guardar os indices, podem ser criados mais blocos do que os originais,
     caso eles fiquei cheios, no entanto, esses novos blocos serao apontados pelos blocos originais, atraves do bloco.prox

buscaHash - com a chave dada, aplica a funcao hash para obter a posicao do bloco do qual esta chave é associada

insereHash - apos executar a busca, obtendo a posicao do bloco, é feita a inserção nesse bloco caso ele nao esteja cheio
    se o bloco estiver cheio, ira verificar o bloco.prox, se for igual a -1, ira criar um novo bloco no arq, e inserir nesse novo
    se bloco.prox != -1, entao existe um novo bloco, a função insere é chamada de novo recursivamente para esse bloco

leHash - apos executar a busca, obtendo a posicao do bloco, é retornado este bloco e todos blocos sequencialmente conectados a ele, (a partir do bloco.prox)

removeHash - apaga o arquivo da hash
*/

void iniciaHash(int quant_reg, std::string tabela, std::string campo);
long int buscaHash(std::string tabela, std::string campo, int chave);
void insereHash(std::string tabela, std::string campo, std::pair<int,int> el, long int pos_bloco );
std::vector<bloco> leHash(std::string tabela, std::string campo, int chave);
void removeHash(std::string tabela, std::string campo);

/* 
Mesma coisa mas com uns print pra debug (TO DO)

void iniciaHash_d(int quant_reg, std::string tabela, std::string campo);
long int buscaHash_d(std::string tabela, std::string campo, int chave);
void insereHash_d(std::string tabela, std::string campo, std::pair<int,int> el, long int pos_bloco );
std::vector<bloco> leHash_d(std::string tabela, std::string campo, int chave);
*/