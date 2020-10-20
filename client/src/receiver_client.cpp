#include <unistd.h>
#include <iostream>
#include "header.h"
using namespace std;

void receiver_client(int client, buffer & Buffer){
   
    while(true)
    {
        while (!Buffer.flag_rec){}
        char entrada[50];
        int leitura = read(client , entrada, 50);
        if(leitura > 0)
        {
            entrada[leitura] = '\0';
            Buffer.dado = string(entrada);
            Buffer.flag_rec = false;
        }else
        {
            cout << "Erro recebendo do server!";
        }
    }

}