#ifndef MYHEADER
#define MYHEADER
#include <vector>

void receiver_client(int client);

void sender_client(int client);

void server_function(std::vector<int> * clientes, int indice, int client);
#endif