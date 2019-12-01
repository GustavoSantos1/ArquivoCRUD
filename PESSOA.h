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
      void  GETNOME(void);
      void  GETDTNASC(void);
      void  SETNOME(char N[41]);
      void  SETDTNASC(char DT[11]);
};

#endif
