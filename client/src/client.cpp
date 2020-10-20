#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <thread>
#include "header.h"
using namespace std;

int main()
{
    int meu_socket;
    struct sockaddr_in addr;

    meu_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (meu_socket == -1)
    {
        cout << "Erro ao criar o socket!" << endl;
        return 1;
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(4321);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    cout << "Tentando se conectar ao servidor..." << endl;
    if (connect(meu_socket, (struct sockaddr *)&addr, sizeof(addr)) == -1)
    {
        cout << "Erro ao se conectar!" << endl;
        return 1;
    }

    cout << "Conectado!" << endl;

    char entrada[50];
    int posicao;
    string msg;

    int leitura = read(meu_socket, entrada, 50);
    entrada[leitura] = '\0';

    posicao = entrada[0];

    if(posicao == 1){
        cout << "Jogador 1, digite seu nome: ";
        getline(std::cin, msg);
        send(meu_socket, msg.c_str(), msg.length(), 0 );
        int leitura = read(meu_socket, entrada, 50);
        entrada[leitura] = '\0';
        cout << "Seu oponente se chama: " << entrada << endl;
    }else{
        cout << "Aguardando Jogador 1 ..." << endl;
        int leitura = read(meu_socket, entrada, 50);
        entrada[leitura] = '\0';
        cout << "Seu oponente se chama: " << entrada << endl;
        cout << "Jogador 2, digite seu nome: ";
        getline(std::cin, msg);
        send(meu_socket, msg.c_str(), msg.length(), 0 ); 
    }

    thread ClientReceiverThread(receiver_client, meu_socket);
    thread ClienteSenderThread(sender_client, meu_socket);
    ClientReceiverThread.detach();
    ClienteSenderThread.detach();

    while (true)
    {
        /* code */
    }
}
