#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <thread>
#include <iostream>
#include <string>
#include <vector>
#include "header.h"
#include <bits/stdc++.h>

//Função principal responsável pela execução
//do servidor do Quarto
int main()
{
    //Criação de socket e conexão
    struct sockaddr_in addr;

    std::vector<int> clientes;

    int meu_socket;
    meu_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (meu_socket == -1)
    {
        printf("\nErro ao criar o socket!\n");
        return 1;
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(4321);
    addr.sin_addr.s_addr = INADDR_ANY;
    //memset(&addr.sin_zero, 0, sizeof(addr.sin_zero));

    if (bind(meu_socket, (struct sockaddr *)&addr, sizeof(addr)) == -1)
    {
        printf("\nErro na funcao bind()\n");
        return 1;
    }

    if (listen(meu_socket, 3) == -1)
    {
        printf("\nErro na funcao listen()\n");
        return 1;
    }

    int new_client;
    char entrada[50];

    //For que aceita os clientes e cria as threads de cada um
    for (int i = 0; i < 2; i++)
    {
        new_client = accept(meu_socket, 0, 0);
        if (new_client == -1)
        {
            printf("\nErro na funcao accept()\n");
            return 1;
        }

        clientes.push_back(new_client);

        entrada[0] = i + 1;
        entrada[1] = '\0';
        send(new_client, entrada, strlen(entrada), 0);

        std::thread Server_Thread(server_function, std::ref(clientes), i, new_client);
        Server_Thread.detach();

        std::cout << "Conectado Cliente: " << i << std::endl;
    }

    //While que mantém o programa rodando
    //enquanto as threads executam as comunicações
    while (true)
    {
        if(!clientes.size()){
            return 0;
        }
    }

    return 0;
}