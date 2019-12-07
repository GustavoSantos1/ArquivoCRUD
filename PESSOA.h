#include <iostream>
#include <cstring>
#include <string>
#include <cstring>
#include <cctype>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <windows.h>
#include <iomanip>

#ifndef __PESSOA_H
#define __PESSOA_H

using namespace std;

#if defined _WIN32 || defined _WIN64

// Limpar tela

void limpa(void)
{
    HANDLE TELA;
    DWORD ESCRITA = 0;
    COORD POS;
    TELA = GetStdHandle(STD_OUTPUT_HANDLE);
    POS.X = 0;
    POS.Y = 0;
    FillConsoleOutputCharacter(TELA, 32, 100 * 100, POS, &ESCRITA);
}

// Posicionar cursor nos limites 80 x 24

void position(int LINHA, int COLUNA)
{
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
void clearline(void)
{
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

//DEFINIÇÃO DA CLASSE PESSOA
class PESSOA {
private:
    char NOME[41];
    char DTNASC[11];

public:
    char STATUS;
    char* getNome(void)
    {
        return NOME;
    }
    char* getDtNasc(void)
    {
        return DTNASC;
    }
    void setNome(char N[41])
    {
        int i;
        for (int i = 0; i < strlen(N); i++)
            N[i] = toupper(N[i]);
        strcpy(NOME, N);
        return;
    }
    void setDataNasc(char DT[11])
    {
        strcpy(DTNASC, DT);
        return;
    }
};

//FUNÇÃO QUE RETORNA CADEIA COM LETRAS MAISCULAS
char* uppercase(char* N)
{
    int i;
    for (int i = 0; i < strlen(N); i++)
        N[i] = toupper(N[i]);
    return N;
}

short sday(char DT[])
{
    return atoi(&DT[0]);
}

short smonth(char DT[])
{
    return atoi(&DT[3]);
}

short syear(char DT[])
{
    return atoi(&DT[6]);
}
//FUNCAO PARA REMOVER CARACTER DA DATA
void rmvachr(char CADEIA[], char CARACTERE)
{
    char* POS1 = CADEIA;
    char* POS2 = CADEIA;
    while (*POS1) {
        *POS2 = *POS1++;
        POS2 += (*POS2 != CARACTERE);
    }
    *POS2 = '\0';
}
//FUNCAO QUE RETORNA DATA EM FORMATO ANSI
unsigned long int dateansi(char DT[])
{
    char DATATEMP1[11] = {};
    char DATATEMP2[11] = {};
    short I;
    strcpy(DATATEMP1, DT);
    for (I = 0; I <= 9; I++)
        {
        if (I < 4)
            DATATEMP2[I] = DATATEMP1[I + 6];
        if (I == 4)
            DATATEMP2[4] = '/';
        if (I > 4 and I < 7)
            DATATEMP2[I] = DATATEMP1[I - 2];
        if (I == 7)
            DATATEMP2[7] = '/';
        if (I > 7)
            DATATEMP2[I] = DATATEMP1[I - 8];
        }
    rmvachr(DATATEMP2, '/');
    return atol(DATATEMP2);
}
//FUNCAO PARA RETORNAR OS DIAS JULIANOS DE UMA CERTA DATA
unsigned long int julianday(char DT[])
{
    short DIA, MES, ANO;
    float A, B, C, D, E, F;
    DIA = sday(DT);
    MES = smonth(DT);
    ANO = syear(DT);
    if (MES < 3)
    {
        ANO = ANO - 1;
        MES = MES + 12;
    }
    if (dateansi(DT) >= 2299161)
    {
        A = floor(ANO / 100);
        B = floor(A / 4);
        C = 2 - A + B;
    }
    else
        C = 0;
    D = floor(365.25 * (ANO + 4716));
    E = floor(30.6001 * (MES + 1));
    F = D + E + DIA + 0.5 + C - 1524.5;
    return (unsigned long int)F;
}
//FUNCAO PARA IDENTIFICAR O NUMERO DO MES
int numMes(char* m)
{
    int n = 0;
    if (strcmp(m, "Jan") == 0)
        n = 1;
    if (strcmp(m, "Feb") == 0)
        n = 2;
    if (strcmp(m, "Mar") == 0)
        n = 3;
    if (strcmp(m, "Apr") == 0)
        n = 4;
    if (strcmp(m, "May") == 0)
        n = 5;
    if (strcmp(m, "Jun") == 0)
        n = 6;
    if (strcmp(m, "Jul") == 0)
        n = 7;
    if (strcmp(m, "Aug") == 0)
        n = 8;
    if (strcmp(m, "Sep") == 0)
        n = 9;
    if (strcmp(m, "Oct") == 0)
        n = 10;
    if (strcmp(m, "Nov") == 0)
        n = 11;
    if (strcmp(m, "Dec") == 0)
        n = 12;
    return n;
}
//FUNCAO PARA FORMATAR A HORA ATUAL DO SISTEMA
char* formatarData(char* dataAtual)
{
    char m[4];
    int ano, dia, mes;
    for (int i = 0; i <= 2; ++i)
        m[i] = dataAtual[4 + i];
    mes = numMes(m);
    ano = atoi(&dataAtual[20]);
    dia = atoi(&dataAtual[8]);
    sprintf(dataAtual, "%2.2d/%2.2d/%4.4d", dia, mes, ano);
    return dataAtual;
}
// FUNCAO PARA RETORNAR A DATA ATUAL DO SISTEMA
char* dataHoje(void)
{
    time_t dataAgora = time(NULL);
    char* dtAgora = ctime(&dataAgora);
    char* hoje = formatarData(dtAgora);
    return hoje;
}
//PROCEDIMENTO QUE ALTERA CALCULA A IDADE EM ANOS, DIAS E MESES, ALTERA OS VALORES PASSADOS POR REFERENCIA
void calcIdade(int& dia, int& mes, int& ano, char* dtNascimento)
{
    unsigned long int ddJulian = (julianday(dataHoje())) - (julianday(dtNascimento));
    ano = ddJulian / 365;
    mes = (ddJulian - (365 * ano)) / 30;
    dia = ddJulian - (365 * ano) - (mes * 30);
    return;
}
PESSOA P;
int i, j;
char N[41], DT[11];

//FUNCAO QUE RETORNA NUMERO DA POSICAO DO REGISTRO EM QUE SE ENCONTRA O NOME INFORMADO POR PARAMETRO
int posicaoRegistro(char* PN)
{
    fstream cadastro("pessoas.dat", ios_base::in | ios_base::binary);
    unsigned int pos = -1, contador = 0;
    bool acha = false;
    while (not(cadastro.eof()) and acha != true)
    {
        cadastro.read(reinterpret_cast<char*>(&P), sizeof(PESSOA));
        if (strcmp(P.getNome(), PN) == 0 or strcmp(P.getDtNasc(), PN) == 0)
        {
            acha = true;
            pos = contador;
        }
        contador++;
    }
    cadastro.flush();
    cadastro.close();
    return pos;
}
//PROCEDIMENTO QUE EXCLUI O REGISTRO REFERENTE A POSICAO PASSADA POR PARAMETRO
void excluirRegistro(int pos)
{
    P.STATUS = '0';
    fstream cadastro("pessoas.dat", ios_base::in | ios_base::out | ios_base::binary);
    cadastro.seekp(pos * sizeof(P));
    cadastro.write(reinterpret_cast<char*>(&P), sizeof(PESSOA));
    cadastro.flush();
    cadastro.close();
}
//PROCEDIMENTO DE PAUSA
void pause(void)
{
    cout << endl;
    cout << "Tecle <Enter> para continuar... ";
    cin.get();
}
//PROCEDIMENTO DE LIMPEZA DE BUFFER
void lbuffer(void)
{
    cin.ignore(100, '\n');
}
//PROCEDIMENTO QUE MONTA A TELA DE ENTRADA PRINCIPAL DO PROGRAMA
void montaTela(void)
{
    position(1, 1);
    clearline();
    cout << "Digite o(s) dado(s) abaixo:";
    position(3, 1);
    clearline();
    position(4, 1);
    clearline();
    cout << "Nome ..................................: ";
    position(5, 1);
    cout << "Data de Nascimento (DD/MM/AAAA) .......: ";
    position(4, 42);
}
//PROCEDIMENTO QUE MONTA A TELA DE ENTRADA DE DATA DE NASCIMENTO
void montaTelaData(void)
{
    position(1, 1);
    clearline();
    cout << "Digite o(s) dado(s) abaixo:";
    position(3, 1);
    clearline();
    position(5, 1);
    clearline();
    cout << "Data de Nascimento (DD/MM/AAAA) .......: ";
    position(5, 42);
}
//PROCEDIMENTO QUE MONTA A TELA DE ENTRADA DE NOME
void montaTelaNome(void)
{
    position(1, 1);
    clearline();
    cout << "Digite o(s) dado(s) abaixo:";
    position(3, 1);
    clearline();
    position(5, 1);
    clearline();
    cout << "Nome ..................................: ";
    position(5, 42);
}
//PROCEDIMENTO QUE CRIA O ARQUIVO
void criarArquivo(void)
{
    fstream cadastro;
    cadastro.open("pessoas.dat", ios_base::out | ios_base::binary);
    cadastro.close();
}
//FUNCAO DE PESQUISA DE NOME, RETORNA VERDADEIRO OU FALSO
bool pesquisarNome(char* PN)
{
    fstream cadastro("pessoas.dat", ios_base::in | ios_base::binary);
    bool acha = false;
    while ((not cadastro.eof()) and acha != true)
    {
        cadastro.read(reinterpret_cast<char*>(&P), sizeof(PESSOA));
        limpa();
        if (strcmp(P.getNome(), PN) == 0 and P.STATUS == '1')
            acha = true;
    }
    cadastro.flush();
    cadastro.close();
    return acha;
}
//FUNCAO DE PESQUISA DE DATA DE NASCIMENTO, RETORNA VERDADEIRO OU FALSO
bool pesquisarDtNasc(char* PDT)
{
    fstream cadastro("pessoas.dat", ios_base::in | ios_base::binary);
    bool acha = false;
    while ((not cadastro.eof()) and acha != true)
    {
        cadastro.read(reinterpret_cast<char*>(&P), sizeof(PESSOA));
        limpa();
        if (strcmp(P.getDtNasc(), PDT) == 0 and P.STATUS == '1')
            acha = true;
    }
    cadastro.flush();
    cadastro.close();
    return acha;
}
//PROCEDIMENTO DE CONSULTA DE NOME (GERACAO DA TELA E EXECUCAO DA PESQUISA)
void consultarNome(void)
{
    char* PN;
    int dia,mes,ano;
    limpa();
    montaTelaNome();
    cin.getline(N, sizeof(N));
    PN = N;
    if (pesquisarNome(uppercase(PN)))
    {
        limpa();
        montaTela();
        cout << P.getNome();
        position(5, 42);
        cout << P.getDtNasc() << endl;
        calcIdade(dia,mes,ano,P.getDtNasc());
        cout << "Idade em Anos:...."   << ano << endl;
        cout << "Idade em Meses:..."   << mes << endl;
        cout << "Idade em Dias:.... "  << dia << endl;
        cout << "Registro Encontrado !" << endl;
        pause();
    }
    else
    {
        limpa();
        montaTela();
        position(6, 1);
        cout << "Registro Nao Encontrado !";
        pause();
    }
}
//PROCEDIMENTO DE CONSULTA DE DATA DE NASCIMENTO (GERACAO DA TELA E EXECUCAO DA PESQUISA)
void consultarDtNasc(void)
{
    char* PDT;
    int dia,mes,ano;
    unsigned long int dif;
    limpa();
    montaTelaData();
    cin.getline(DT, sizeof(DT));
    PDT = DT;
    if (pesquisarDtNasc(PDT))
    {
        limpa();
        montaTela();
        position(4, 42);
        cout << P.getNome();
        position(5, 42);
        cout << P.getDtNasc() << endl;
        calcIdade(dia,mes,ano,P.getDtNasc());
        cout << "Idade em Anos:...."   << ano + 1 << endl;
        cout << "Idade em Meses:..."   << mes << endl;
        cout << "Idade em Dias:.... "  << dia << endl;
        cout << "Registro Encontrado !";
        pause();
    }
    else
    {
        limpa();
        montaTela();
        position(6, 1);
        cout << "Registro Nao Encontrado !";
        pause();
    }
}
//PROCEDIMENTO QUE GERA A TELA PRINCIPAL DO PROGRAMA
void menu(void)
{
    limpa();
    position(1, 1);
    cout << "PROGRAMA DE CADASTRO DE PESSOAS" << endl
         << endl;
    cout << "<Cadastrar> ------------------------------> [1]" << endl
         << endl;
    cout << "<Pesquisar por nome> ---------------------> [2]" << endl
         << endl;
    cout << "<Pesquisar por data de nascimento> -------> [3]" << endl
         << endl;
    cout << "<Remover> --------------------------------> [4]" << endl
         << endl;
    cout << "<Alterar>  -------------------------------> [5]" << endl
         << endl;
    cout << "<Finalizar> ------------------------------> [6]" << endl
         << endl;
    cout << "Entre com a opcao desejada --> ";
}
//PROCEDIMENTO QUE GERA O MENU COM OPCOES DE ALTERACAO
void menuAlterar(void)
{
    limpa();
    position(1, 1);
    cout << "O QUE DESEJA ALTERAR?" << endl
         << endl;
    cout << "<Alterar Nome>  -------------------------------> [1]" << endl
         << endl;
    cout << "<Alterar Data de Nascimento>  -----------------> [2]" << endl
         << endl;
    cout << "Entre com a opcao desejada --> ";
}
//PROCEDIMENTO DE CADASTRO
void cadastrar(void)
{
    char OP;
    do
    {
        limpa();
        clearline();
        montaTela();
        position(4, 42);
        cin.getline(N, sizeof(N));
        position(5, 42);
        cin >> DT;
        lbuffer();
        fstream cadastro;
        P.setNome(N);
        P.setDataNasc(DT);
        position(8, 1);
        P.STATUS = '1';
        cadastro.open("pessoas.dat", ios_base::out | ios_base::app | ios_base::binary);
        cadastro.write(reinterpret_cast<char*>(&P), sizeof(PESSOA));
        cout << "Cadastro Efetuado!" << endl;
        cadastro.flush();
        cadastro.close();
        do
        {
            cout << "\nDeseja efetuar um novo cadastro? (S/N)";
            cin >> OP;
            lbuffer();
        } while (toupper(OP) != 'N' and toupper(OP) != 'S');
    } while (toupper(OP) != 'N');
}
//PROCEDIMENTO DE ALTERACAO DE REGISTRO POR NOME, DEVE SER INFORMADO A POSICAO DO REGISTRO A SER ALTERADO
void alterarNome(int pos)
{
    cin.getline(N, sizeof(N));
    P.setNome(N);
    fstream cadastro("pessoas.dat", ios_base::in | ios_base::out | ios_base::binary);
    cadastro.seekp(pos * sizeof(P));
    cadastro.write(reinterpret_cast<char*>(&P), sizeof(PESSOA));
    cadastro.flush();
    cadastro.close();
}
//PROCEDIMENTO DE ALTERACAO DE REGISTRO POR DATA DE NASCIMENTO, DEVE SER INFORMADO A POSICAO DO REGISTRO A SER ALTERADO
void alterarDtNasc(int pos)
{
    cin.getline(DT, sizeof(DT));
    P.setDataNasc(DT);
    fstream cadastro("pessoas.dat", ios_base::in | ios_base::out | ios_base::binary);
    cadastro.seekp(pos * sizeof(P));
    cadastro.write(reinterpret_cast<char*>(&P), sizeof(PESSOA));
    cadastro.flush();
    cadastro.close();
}
//PROCEDIMENTO DE ALTERACAO DE REGISTRO
void alterar(void)
{
    int OP;
    char* PN,*PDT;
    char OPALTER;
    limpa();
    menuAlterar();
    cin >> OP;
    lbuffer();
    if (OP == 1)
    {
      limpa();
      montaTelaNome();
      cin.getline(N, sizeof(N));
      PN = N;
      if (pesquisarNome(uppercase(PN)))
        {
          limpa();
          montaTela();
          cout << P.getNome();
          position(5, 42);
          cout << P.getDtNasc() << endl;
          cout << "Registro Encontrado !\nDeseja Altera-lo? (S/N)";
          cin.get(OPALTER);
          lbuffer();
          if (toupper(OPALTER) == 'S')
          {
              limpa();
              montaTelaNome();
              position(1,1);
              clearline();
              cout << "Insira um novo nome:";
              position(5, 42);
              alterarNome(posicaoRegistro(PN));
              cout << "Alteracao feita com sucesso !";
              pause();
          }
      }
      else
      {
          limpa();
          montaTela();
          position(6, 1);
          cout << "Registro Nao Encontrado !";
          pause();
      }
    }
    else if (OP == 2)
    {
        limpa();
        montaTelaData();
        cin.getline(DT, sizeof(DT));
        PDT = DT;
        if (pesquisarDtNasc(PDT))
        {
          limpa();
          montaTela();
          cout << P.getNome();
          position(5, 42);
          cout << P.getDtNasc() << endl;
          cout << "Registro Encontrado !\nDeseja Altera-lo? (S/N)";
          cin.get(OPALTER);
          lbuffer();
          if (toupper(OPALTER) == 'S')
          {
            limpa();
            montaTelaData();
            position(1,1);
            clearline();
            cout << "Insira uma nova data de nascimento:";
            position(5, 42);
            alterarDtNasc(posicaoRegistro(PDT));
            cout << "Alteracao feita com sucesso !";
            pause();
          }
        }
        else
        {
            limpa();
            montaTela();
            position(6, 1);
            cout << "Registro Nao Encontrado !";
            pause();
        }


    }
    else
    {
      limpa();
      position(3, 1);
      cout << "Opcao Invalida ! ";
      pause();
    }
}
//PROCEDIMENTO DE REMOCAO DE REGISTRO
void remover(void)
{
    char *PN, OP;
    limpa();
    montaTela();
    cin.getline(N, sizeof(N));
    PN = N;
    if (pesquisarNome(uppercase(PN)))
    {
        limpa();
        montaTela();
        cout << P.getNome();
        position(5, 42);
        cout << P.getDtNasc() << endl;
        cout << "Deseja Remover Esse Registro? (S/N)" << endl;
        cin.get(OP);
        if (toupper(OP) == 'S')
        {
            excluirRegistro(posicaoRegistro(PN));
            position(9, 1);
            cout << "Registro removido!";
            cin.get();
        }
        pause();
    }
    else
    {
        limpa();
        montaTela();
        position(6, 1);
        cout << "Registro Nao Encontrado!";
        pause();
    }
}

#endif
