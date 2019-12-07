#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <iomanip>
#include "PESSOA.h"

using namespace std;

//SUB-ROTINA PRINCIPAL DO PROGRAMA
int main(void)
{
    int OPCAO;
    fstream cadastro("pessoas.dat", ios_base::in | ios_base::binary);
    if (cadastro.fail())
        criarArquivo();
    do {
        menu();
        cin >> OPCAO;
        lbuffer();
        switch (OPCAO) {
        case 1:
            cadastrar();
            break;
        case 2:
            consultarNome();
            break;
        case 3:
            consultarDtNasc();
            break;
        case 4:
            remover();
            break;
        case 5:
            alterar();
            break;
        }
    } while (OPCAO != 6);

    return 0;
}
