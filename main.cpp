<<<<<<< HEAD
#include <iostream>
#include <string>
using namespace std;

void criaArquivoComNomeTabela(string nome_tabela) {
    cout << "Criando tabela com nome" << nome_tabela;
}

void apagaArquivoComNomeTabela(string nome_tabela) {
    cout << "Apagando arquivo relativo a tabela: " << nome_tabela;
}

void interpretadorDeComandos(string comando) {
    if (comando == "CT") {
        cin >> comando;
        criaArquivoComNomeTabela(comando);
        return;
    }
    else if (comando == "RT") {
        cin >> comando;
        apagaArquivoComNomeTabela(comando);
    }

    else if (comando == "AT") {

    }

    else if (comando == "LT") {
        
    }

    else if (comando == "IR") {

    }

    else if (comando == "BR") {
        cin >> comando;
        if (comando == "N") {

        }
        else if (comando == "U") {

        }
    }

    else if (comando == "AR") {

    }

    else if (comando == "RR") {

    }

    else if (comando == "CI") {
        cin >> comando;
        if (comando == "A") {

        }
        else if (comando == "H") {
            
        }
    }

    else if (comando == "RI") {

    }

    else if (comando == "GI") {

    }

    else if (comando == "EB") {
        return;
    }
}

int main() {
    string comando;
    while (comando != "EB") {
        cin >> comando;
        interpretadorDeComandos(comando);
    }

    return 0;
}
=======
#include <cstdio>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <string>

int main(int argc, char const *argv[]) {
  char comando[200];
  while (fgets(comando, sizeof(comando), stdin) != NULL) {
    std::cout << comando << '\n';
  }

  return 0;
}
>>>>>>> upstream/master
