#include <unistd.h>
#include <iostream>
#include <string.h>
#include "header.h"
using namespace std;

//Thread responsável por gerir o recebimento de informações
//do server para o cliente
void receiver_client(int client, buffer &Buffer)
{

    while (true)
    {
        while (!Buffer.flag_rec)
        {
        }
        char entrada[50];
        int leitura = read(client, entrada, 50);
        if (!strncmp(entrada, "vitoria", 6))
        {
            Buffer.flag_res = 1;
            entrada[0] = entrada[7];
            entrada[1] = entrada[8];
            entrada[2] = '\0';
            Buffer.dado = string(entrada);
            Buffer.flag_rec = false;
        }
        if (!strncmp(entrada, "empate", 5))
        {
            Buffer.flag_res = -1;
            entrada[0] = entrada[6];
            entrada[1] = '\0';
            Buffer.dado = string(entrada);
            Buffer.flag_rec = false;
        }
        if (leitura > 0)
        {
            entrada[leitura] = '\0';
            Buffer.dado = string(entrada);
            Buffer.flag_rec = false;
        }
        else
        {
            cout << "Erro recebendo do server!";
        }
    }
}