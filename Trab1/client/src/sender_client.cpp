#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <thread>
#include "header.h"
using namespace std;

//Thread responsável por gerir o envio de
//informações do cliente para o server
void sender_client(int client, buffer &Buffer)
{

    while (true)
    {
        while (!Buffer.flag_send)
        {
        }
        send(client, Buffer.dado.c_str(), Buffer.dado.length(), 0);
        Buffer.flag_send = false;
    }
}