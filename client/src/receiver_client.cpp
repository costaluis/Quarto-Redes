#include <unistd.h>
#include <iostream>
using namespace std;

void receiver_client(int client){
   
    while(true)
    {
        
        char entrada[50];
        int leitura = read(client , entrada, 50);
        if(leitura > 0)
        {
            entrada[leitura] = '\0';
            cout << entrada << "\n";
        }else
        {
            cout << "Erro recebendo do server!";
        }
    }

}