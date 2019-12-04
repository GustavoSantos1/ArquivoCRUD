#include <iostream>
#include <cstring>
#include <string>

#ifndef __PESSOA_H
#define __PESSOA_H

class PESSOA
{
    private:
      char  NOME[41];
      char  DTNASC[11];
    public:
      char STATUS;
      char *getNome(void)
      {
          return NOME;
      }
      char *getDtNasc(void)
      {
          return DTNASC;
      }
      void setNome(char N[41])
      {
        int i;
        for (int i=0; i<strlen(N); i++)
            N[i] = toupper(N[i]);
        strcpy(NOME,N);
        return;
      }
      void  setDataNasc(char DT[11])
      {
          strcpy(DTNASC,DT);
          return;
      }

};
      char *uppercase(char *N)
      {
      int i;
      for (int i=0; i<strlen(N); i++)
        N[i] = toupper(N[i]);
      return N;

      }


#endif
