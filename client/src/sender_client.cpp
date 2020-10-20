#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <thread>
using namespace std;

void sender_client(int client){
   
    while(true)
    {
        string sendMessage;
        getline(std::cin, sendMessage);
        send(client , sendMessage.c_str() , sendMessage.length() , 0 ); 
    }

}