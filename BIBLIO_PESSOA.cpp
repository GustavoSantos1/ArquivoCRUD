#include <iostream>
#include <cctype>
#include "PESSOA.h"
using namespace std;

  void PESSOA::GETNOME(void)
  {
    cout << NOME << endl;
  }
  void PESSOA::GETDTNASC(void)
  {
    cout << DTNASC << endl;

  }
  void PESSOA::SETNOME(char N[41])
  {
    int i;
    for(i = 0; i<strlen(N); i++)
    {
      NOME[i] = toupper(N[i]);
    }
    return;
  }
  void PESSOA::SETDTNASC(char DT[11])
  {
    DT = DTNASC;
    return;
  }

/*  int main(void)
  {
    char X[41];
    PESSOA P;
    cin.getline(X,sizeof(X));
    P.SETNOME(X);
    P.GETNOME();
    //pause();

  return 0;
  }
*/

