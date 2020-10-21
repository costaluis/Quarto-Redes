#include <unistd.h>
#include <bits/stdc++.h>
#include <string>
#include <iostream>
#include <vector>
#include <sys/socket.h>

//Thread responsável por gerir o repassamento
//de informações entre os clientes pelo server
void server_function(std::vector<int> & clientes, int indice, int client)
{
    char entrada[50];
    int leitura;
    while ((leitura = read(client, entrada, 50)))
    {
        entrada[leitura] = '\0';
        for (int cliente :clientes)
        {
            if (client != cliente)
            {
                send(cliente, entrada, strlen(entrada), 0);
            }
        }
    }
    std::cout << "Cliente desconectado" << std::endl;
    std::vector<int>::iterator p = find(clientes.begin(), clientes.end(), client);
    clientes.erase(p);

    return;
}