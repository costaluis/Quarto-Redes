#include <vector>
#include <string>

#ifndef MYHEADER
#define MYHEADER


class buffer
{
private:
    /* data */
public:
    bool flag_rec;
    bool flag_send;
    int flag_res;
    std::string dado;
    buffer();
    ~buffer();
};

void receiver_client(int client, buffer & Buffer);

void sender_client(int client, buffer & Buffer);

int Transforma(char X);

void Recupera(int A, int B[4][4][4], int C[], int D);

void Impressao(int A[4][4][4]);

bool verifica(int A[4][4][4], char jogador1[15], char jogador2[15], int m);

char Converte(char a);


#endif