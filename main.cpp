#include "Comandos.h"
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;


void interpretadorDeComandos (Comandos &comando) {
    if (comando.keyword == "CT") {
        cin >> comando.keyword;
        comando.criarArquivoComNomeTabela();
    }

    else if (comando.keyword == "RT") {
        cin >> comando.keyword;
        comando.apagaArquivoComNomeTabela();
    }

    else if (comando.keyword == "AT") {

    }

    else if (comando.keyword == "LT") {
        
    }

    else if (comando.keyword == "IR") {

    }

    else if (comando.keyword == "BR") {
        cin >> comando.keyword;
        if (comando.keyword == "N") {

        }
        else if (comando.keyword == "U") {

        }
    }

    else if (comando.keyword == "AR") {

    }

    else if (comando.keyword == "RR") {

    }

    else if (comando.keyword == "CI") {
        cin >> comando.keyword;
        if (comando.keyword == "A") {

        }
        else if (comando.keyword == "H") {
            
        }
    }

    else if (comando.keyword == "RI") {

    }

    else if (comando.keyword == "GI") {

    }

    else if (comando.keyword == "EB") {
        return;
    }
}

int main() {
    Comandos comando;
    while (comando.keyword != "EB") {
        cin >> comando.keyword;
		transform(comando.keyword.begin(), comando.keyword.end(), comando.keyword.begin(), ::toupper);
        interpretadorDeComandos(comando);
    }

    return 0;
}
