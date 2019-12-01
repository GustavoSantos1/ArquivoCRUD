#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <iomanip>
#include "PESSOA.h"

using namespace std;

#if defined _WIN32 || defined _WIN64

// Limpar tela

void limpa(void) {
    HANDLE TELA;
    DWORD ESCRITA = 0;
    COORD POS;
    TELA = GetStdHandle(STD_OUTPUT_HANDLE);
    POS.X = 0;
    POS.Y = 0;
    FillConsoleOutputCharacter(TELA, 32, 100 * 100, POS, &ESCRITA);
}


// Posicionar cursor nos limites 80 x 24

void position(int LINHA, int COLUNA) {
    if (COLUNA >= 1 and COLUNA <= 80 and LINHA >= 1 and LINHA <= 24) {
        HANDLE TELA;
        COORD POS;
        TELA = GetStdHandle(STD_OUTPUT_HANDLE);
        POS.X = COLUNA - 1;
        POS.Y = LINHA - 1;
        SetConsoleCursorPosition(TELA, POS);
    }
}


// Limpar linha a partir da posicao do cursor
void clearline(void) {
    HANDLE TELA;
    COORD POS;
    CONSOLE_SCREEN_BUFFER_INFO VIDEO;
    DWORD ESCRITA = 0;
    TELA = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(TELA, &VIDEO);
    POS.Y = VIDEO.dwCursorPosition.Y;
    POS.X = VIDEO.dwCursorPosition.X;
    FillConsoleOutputCharacter(TELA, 32, 80 - POS.X, POS, &ESCRITA);
}

#else

// ACOES EXCLUSIVAS PARA MODO: TERMINAL ANSI

// LIMPAR TELA

void limpa(void)
{
    cout << "\033[2J";
}

// LIMPAR LINHA A PARTIR DA POSICAO DO CURSOR

void position(int LINHA, int COLUNA)
{
    if (COLUNA >= 1 && COLUNA <= 80 && LINHA >= 1 && LINHA <= 24)
        cout << "\033[" << LINHA << ";" << COLUNA << "H";
}

// LIMPAR LINHA A PARTIR DA POSICAO DO CURSOR

void clearline(void)
{
    cout << "\033[K";
}

#endif
int i,j;
void montaTela(void)
{
    position(10,17);
    clearline();
    position(11,17);
    clearline();
    position(12,17);
    clearline();
    position(13,17);
    clearline();
    position(14,17);
    clearline();
    position(15,17);
    clearline();
    position(10, 2);
    cout << "Nome ................: ";
    position(12, 2);
    cout << "Data de nascimento ..: ";
}
void cadastrar(void)
{
  char X[41];
  PESSOA P;

  limpa( );
  string tipo = "Cadastro";
//tracalinha(tipo);
  position(6, 2);
  cout << "Digite os dados abaixo:";
  position(22,2);
  clearline();
  position(22,2);
  cout << "Digite [0] para voltar ao menu: ";
  montaTela();
  position(10, 17);
  cin.getline(X,sizeof(X));
  P.SETNOME(X);
  P.GETNOME();






}
void tracalinha(string tipo)
{
    limpa( );
    position(1, 5);
    for (i = 0; i <= 90; i++)
        cout << "-";
    cout << endl;
    position(2, 27);
    cout << "PROGRAMA DE CADASTRO DE PESSOAS" << endl;
    position(3, 35);
    cout << tipo;
    cout << endl;
    position(4, 5);
    for (i = 0; i <= 90; i++)
        cout << "-";
}


void menu(void)
{
    limpa();
    string tipo;
    tipo = "Menu Principal";
    tracalinha(tipo);
    position( 8,26);
    cout << "Cadastrar <------------------------------ [1]";
    position(10,26);
    cout << "Pesquisar por nome <--------------------- [2]";
    position(12,26);
    cout << "Pesquisar por data de nascimento <------- [3]";
    position(14,26);
    cout << "Remover <-------------------------------- [4]";
    position(16,26);
    cout << "Alterar <-------------------------------- [5]";
    position(18,26);
    cout << "Finalizar <------------------------------ [6]";
    position(24,26);
    cout << "Entre com a opcao: --> ";
}
void pause(void)
{
  cout << endl;
  cout << "Tecle <Enter> para continuar... ";
  cin.get();
}

int main(void)
{
  char OP;
  menu();
  cin.get(OP);



  return 0;

    /*
    char op;


    menu();
    cin.get(op);
    switch(op){
    case 1:
        cadastrar();
        break;

    default:
        break;

    }


*/
}
