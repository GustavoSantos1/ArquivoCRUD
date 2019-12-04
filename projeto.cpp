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

PESSOA P;
int i,j;
char N[41],DT[11];

int posicaoRegistro(char *PN) {
    fstream cadastro("pessoas.dat", ios_base::in | ios_base::binary);
    unsigned int pos = -1, contador = 0;
    bool acha = false;
    while (not(cadastro.eof()) and acha != true) {
        cadastro.read(reinterpret_cast<char*>(&P), sizeof(PESSOA));
        if (strcmp(P.getNome(),PN) == 0) {
            acha = true;
            pos = contador;
        }
        contador++;
    }
    cadastro.flush();
    cadastro.close();
    return pos;
}
void excluirRegistro(int pos) {
    P.STATUS = '0';
    fstream cadastro("pessoas.dat",ios_base::in | ios_base::out | ios_base::binary);
    cadastro.seekp(pos * sizeof(P));
    cadastro.write(reinterpret_cast<char*>(&P), sizeof(PESSOA));
    cadastro.flush();
    cadastro.close();
}

void pause(void)
{
  cout << endl;
  cout << "Tecle <Enter> para continuar... ";
  cin.get();
}

void lbuffer(void) {
    cin.ignore(100, '\n');
}

void montaTela(void)
{
    position(1, 1);
    clearline();
    cout << "Digite os dados abaixo:";
    position(3,1);
    clearline();
    position(4,1);
    clearline();
    cout << "Nome ......................: ";
    position(5,1);
    cout << "Data de Nascimento ........: ";
    position(4, 30);
}
void montaTelaSec(void)
{
    position(1, 1);
    clearline();
    cout << "Digite os dados abaixo:";
    position(3,1);
    clearline();
    position(5,1);
    clearline();
    cout << "Data de Nascimento ........: ";
    position(5, 30);
}
void criarArquivo(void) {
    fstream cadastro;
    cadastro.open("pessoas.dat", ios_base::out | ios_base::binary);
    cadastro.close();
}
bool pesquisarNome(char *PN) {
    fstream cadastro("pessoas.dat", ios_base::in | ios_base::binary);
    bool acha = false;
    while ((not cadastro.eof()) and acha != true) {
        cadastro.read(reinterpret_cast<char*>(&P), sizeof(PESSOA));
        limpa();
        if (strcmp(P.getNome(),PN) == 0 and P.STATUS == '1')
            acha = true;
    }
    cadastro.flush();
    cadastro.close();
    return acha;
}
bool pesquisarDtNasc(char *PDT) {
    fstream cadastro("pessoas.dat", ios_base::in | ios_base::binary);
    bool acha = false;
    while ((not cadastro.eof()) and acha != true) {
        cadastro.read(reinterpret_cast<char*>(&P), sizeof(PESSOA));
        limpa();
        if (strcmp(P.getDtNasc(),PDT) == 0 and P.STATUS == '1')
            acha = true;
    }
    cadastro.flush();
    cadastro.close();
    return acha;
}
void consultarNome(void)
{
  char *PN;
  limpa();
  montaTela();
  cin.getline(N,sizeof(N));
  PN = N;
  if (pesquisarNome(uppercase(PN)))
  {
    limpa();
    montaTela();
    cout << P.getNome();
    position(5,30);
    cout << P.getDtNasc() << endl;
    cout << "Registro Encontrado !" << endl;
    pause();
  }
  else
  {
    limpa();
    montaTela();
    position(6,1);
    cout << "Registro Nao Encontrado !";
    pause();
  }
}

void consultarDtNasc(void)
{
  char *PDT;
  limpa();
  montaTelaSec();
  cin.getline(DT,sizeof(DT));
  PDT = DT;
  if (pesquisarDtNasc(PDT))
  {
    limpa();
    montaTela();
    position(4,30);
    cout << P.getNome();
    position(5,30);
    cout << P.getDtNasc() << endl;
    cout << "Registro Encontrado !";
    pause();
  }
  else
  {
    limpa();
    montaTela();
    position(6,1);
    cout << "Registro Nao Encontrado !";
    pause();
  }
}

void menu(void)
{
    limpa();
    position(1,1);
    cout << "PROGRAMA DE CADASTRO DE PESSOAS" << endl << endl;
    cout << "<Cadastrar> ------------------------------> [1]" << endl << endl;
    cout << "<Pesquisar por nome> ---------------------> [2]" << endl << endl;
    cout << "<Pesquisar por data de nascimento> -------> [3]" << endl << endl;
    cout << "<Remover> --------------------------------> [4]" << endl << endl;
    cout << "<Alterar>  -------------------------------> [5]" << endl << endl;
    cout << "<Finalizar> ------------------------------> [6]" << endl << endl;
    cout << "Entre com a opcao desejada --> ";
}

void menuSec(void)
{
    limpa();
    position(1,1);
    cout << "O QUE DESEJA ALTERAR?" << endl << endl;
    cout << "<Alterar Nome>  -------------------------------> [1]" << endl << endl;
    cout << "<Alterar Data de Nascimento>  -----------------> [2]" << endl << endl;
    cout << "Entre com a opcao desejada --> ";
}
void cadastrar(void)
{
   char OP;
   do
    {
      limpa();
      clearline();
      montaTela();
      cin.getline(N,sizeof(N));
      position(5, 30);
      cin.getline(DT,sizeof(DT));
      fstream cadastro;
      P.setNome(N);
      P.setDataNasc(DT);
      position(8,1);
      P.STATUS = '1';
      cadastro.open("pessoas.dat", ios_base::out | ios_base::app |  ios_base::binary);
      cadastro.write(reinterpret_cast<char*>(&P), sizeof(PESSOA));
      cout << "Cadastro Efetuado!"<< endl;
      cadastro.flush();
      cadastro.close();
      do
        {
          cout << "\nDeseja efetuar um novo cadastro? (S/N)";
          cin >> OP;
          lbuffer();
        }
        while(toupper(OP) != 'S' && toupper(OP) != 'N');
   }
   while(toupper(OP) != 'N');

}

void alterar(void)
{


}
void remover(void)
{
  char *PN,OP;
  limpa();
  montaTela();
  cin.getline(N,sizeof(N));
  PN = N;
  if (pesquisarNome(uppercase(PN)))
  {
    limpa();
    montaTela();
    cout << P.getNome();
    position(5,30);
    cout << P.getDtNasc() << endl;
    cout << "Deseja Remover Esse Registro? (S/N)" << endl;
    cin.get(OP);
    if (toupper(OP) == 'S')
    {
      excluirRegistro(posicaoRegistro(PN));
      position(9,1);
      cout <<"Registro removido!";
    }
    pause();
  }
  else
  {
    limpa();
    montaTela();
    position(6,1);
    cout << "Registro Nao Encontrado!";
    pause();
  }
}



int main(void)
{
  int OPCAO;
  fstream cadastro("pessoas.dat", ios_base::in | ios_base::binary);
  if(cadastro.fail())
    criarArquivo();
  do
  {
    menu();
    cin >> OPCAO;
    lbuffer();
    switch(OPCAO)
      {
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
      }
  }while(OPCAO != 6);

  return 0;
}
