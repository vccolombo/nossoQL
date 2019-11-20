#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;

static const char alphanum[] =
"0123456789"
"$%&"
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz";
int stringLength = sizeof(alphanum) - 1;


char genRandom(){
    return alphanum[rand() % stringLength];

}
string genSTR(int tam){
    string str;
    for(unsigned int i = 0; i < tam; ++i){
        str += genRandom();
    }
    return str;
}


//rodar com 0 argumentos -> ./g                     : ira gerar uma tabela com um campo STR e um campo INT de 50 registros
//rodar com 1 argumento  -> ./g num_regs            : ira gerar uma tabela com um campo STR e um campo INT de num_reg registros
//rodar com 2 argumentos -> ./g num_regs  num_campo : ira gerar uma tabela num_campo+2 campos, o primeiro STR e todos seguintes sendo INT, com num_reg registros

//ira gerar o tab.txt, que dps e so rodar a main colocando esse .txt como argumento

//  ./main.exe tab.txt



int main(int argc, char** argv){
    long int num_reg = 50;
    int num_campo = 2;
    ofstream file;
    srand (time(NULL));


    if(argv[1] != NULL)
        num_reg = strtol(argv[1], NULL, 10);
    if(argv[2] != NULL)
        num_campo += strtol(argv[2], NULL, 10);


    file.open("tab.txt",ios::out); 
    file << "ct tab STR:nome;INT:idade";
    for(int i = 0; i<num_campo-2;i++){
        if (i==0)
            file << ";";
         if(i == num_campo-3)
            file << "INT:"<< genSTR(4);
         else
            file << "INT:"<< genSTR(4) << ";";
    }
    file << endl;

    for(int i = 0; i < num_reg; i++){
        file << "ir tab " << genSTR(5) << ";" << rand() % 98 + 1;
        for(int j = 0; j<num_campo-2;j++){
         if(j == 0)
            file << ";";
         if(j == num_campo-3)
            file << rand() % 98 + 1;
         else
            file << rand() % 98 + 1 << ";";
        }
        file << endl;
    }
    file.close();
    return 0;

}