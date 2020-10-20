#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <thread>
#include <string.h>
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
    char N;
    char P;
    char jogador1[15];
    char jogador2[15];
    int i;
    int Z;
    int j;
    int aux;
    int k; //Declara��o das Vari�veis
    int m;
    int v;
    int cont;
    int cont2;
    int A[4][4][4];
    int Num[16];
    int Pos[16];
    char Entrada[50];
    buffer Buffer;

    int leitura = read(meu_socket, entrada, 50);
    entrada[leitura] = '\0';

    posicao = entrada[0];

    if (posicao == 1)
    {
        cout << "Jogador 1, digite seu nome: ";
        getline(std::cin, msg);
        strcpy(jogador1, msg.c_str());
        send(meu_socket, msg.c_str(), msg.length(), 0);
        int leitura = read(meu_socket, entrada, 50);
        entrada[leitura] = '\0';
        strcpy(jogador2, entrada);
        cout << "Seu oponente se chama: " << entrada << endl;
    }
    else
    {
        cout << "Aguardando Jogador 1 ..." << endl;
        int leitura = read(meu_socket, entrada, 50);
        entrada[leitura] = '\0';
        strcpy(jogador1, entrada);
        cout << "Seu oponente se chama: " << entrada << endl;
        cout << "Jogador 2, digite seu nome: ";
        getline(std::cin, msg);
        send(meu_socket, msg.c_str(), msg.length(), 0);
        strcpy(jogador2, msg.c_str());
    }

    for (i = 0; i < 16; i++)
    {
        Num[i] = 20;
    }
    for (i = 0; i < 16; i++)
    {
        Pos[i] = 20;
    }

    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            for (k = 0; k < 4; k++)
            {
                A[i][j][k] = 2; //Preenchimento do tabuleiro
            }
        }
    }

    thread ClientReceiverThread(receiver_client, meu_socket, ref(Buffer));
    thread ClienteSenderThread(sender_client, meu_socket, ref(Buffer));
    ClientReceiverThread.detach();
    ClienteSenderThread.detach();

    Impressao(A);

    if (posicao == 1)
    {
        while (1)
        {
            printf("\n\n%s, faca sua jogada: ", jogador1);
            fflush(stdin); //Primeira Jogada
            fgets(Entrada, 48, stdin);
            if (strlen(Entrada) != 2)
            {
                printf("Entrada Invalida");
            }
            else
            {
                N = Transforma(Entrada[0]);
                if (N >= 0 && N <= 15)
                {
                    Buffer.dado = string(Entrada);
                    Buffer.flag_send = true;
                    break;
                }
            }
        }
    }
    else
    {
        cout << endl << "Aguardando jogada..." << endl;
        Buffer.flag_rec = true;
        while (Buffer.flag_rec)
        {
        }
        strcpy(Entrada, Buffer.dado.c_str());
        cout << jogador1 << " escolheu o numero: " << Entrada;
        N = Transforma(Entrada[0]);
    }

    for (m = 1; m < 17; m++)
    {

        while (1)
        {
            if (m % 2 == 1)
            {
                if (posicao == 2)
                {
                    printf("\n\n%s, faca sua jogada: ", jogador2);
                    fflush(stdin); //Primeira Jogada
                    fgets(Entrada, 48, stdin);
                    Buffer.dado = string(Entrada);
                    Buffer.flag_send = true;
                }
                else
                {
                    cout << endl << "Aguardando a vez de " << jogador2 << "..." << endl;
                    Buffer.flag_rec = true;
                    while (Buffer.flag_rec){}
                    strcpy(Entrada, Buffer.dado.c_str());
                }
                
                
                
            }
            else
            {
                if (posicao == 1)
                {
                    printf("\n\n%s, faca sua jogada: ", jogador1);
                    fflush(stdin); //Primeira Jogada
                    fgets(Entrada, 48, stdin);
                    Buffer.dado = string(Entrada);
                    Buffer.flag_send = true;
                }else
                {
                    cout << endl << "Aguardando a vez de " << jogador1 << "..." << endl;
                    Buffer.flag_rec = true;
                    while (Buffer.flag_rec){}
                    strcpy(Entrada, Buffer.dado.c_str());
                }
                
            }

            if (strlen(Entrada) > 3 || strlen(Entrada) < 2)
            {
                printf("Entrada Invalida");
            }
            else
            {
                P = Transforma(Entrada[0]);
                if (P < 0 || P > 15)
                {
                    printf("Entrada Invalida\n");
                    continue;
                }
                else
                {
                    for (i = 0; i < 16; i++)
                    {
                        v = 0;
                        if (Pos[i] == P)
                        {
                            printf("Posicao Ocupada\n");
                            v = 1;
                            break;
                        }
                    }
                    if (v == 1)
                    {
                        continue;
                    }
                    Pos[m - 1] = P;
                    aux = N;
                    for (i = 3; i >= 0; i--)
                    {
                        A[P / 4][P % 4][i] = aux % 2;
                        aux /= 2;
                    }

                    for (j = 0; j < 4; j++)
                    {
                        cont = 0;
                        cont2 = 0;
                        for (i = 0; i < 4; i++)
                        { //Verificac�o diagonal1
                            if (A[i][i][j] == 0)
                            {
                                cont++;
                            }
                            if (A[i][i][j] == 1)
                            {
                                cont2++;
                            }
                        }
                        if (cont == 4 || cont2 == 4)
                        {
                            Impressao(A);
                            if (m % 2 == 0)
                            {
                                printf("\n%s ganhou!\n", jogador1);
                            }
                            else
                            {
                                printf("\n%s ganhou!\n", jogador2);
                            }
                            return 0;
                        }
                    }

                    for (i = 0; i < 4; i++)
                    {
                        for (k = 0; k < 4; k++)
                        {
                            cont = 0;
                            cont2 = 0;
                            for (j = 0; j < 4; j++)
                            {
                                if (A[i][j][k] == 0)
                                {
                                    cont++;
                                } //Verificacao horizontal
                                if (A[i][j][k] == 1)
                                {
                                    cont2++;
                                }
                            }
                            if (cont == 4 || cont2 == 4)
                            {
                                Impressao(A);
                                if (m % 2 == 0)
                                {
                                    printf("\n%s ganhou!\n", jogador1);
                                }
                                else
                                {
                                    printf("\n%s ganhou!\n", jogador2);
                                }
                                return 0;
                            }
                        }
                    }

                    for (j = 0; j < 4; j++)
                    {
                        for (k = 0; k < 4; k++)
                        {
                            cont = 0;
                            cont2 = 0;
                            for (i = 0; i < 4; i++)
                            {
                                if (A[i][j][k] == 0)
                                {
                                    cont++;
                                } //Verificacao vertical
                                if (A[i][j][k] == 1)
                                {
                                    cont2++;
                                }
                            }
                            if (cont == 4 || cont2 == 4)
                            {
                                Impressao(A);
                                if (m % 2 == 0)
                                {
                                    printf("\n%s ganhou!\n", jogador1);
                                }
                                else
                                {
                                    printf("\n%s ganhou!\n", jogador2);
                                }
                                return 0;
                            }
                        }
                    }

                    for (k = 0; k < 4; k++)
                    {
                        cont = 0;
                        cont2 = 0;
                        for (i = 0, j = 3; i < 4; i++, j--)
                        { //Verificac�o diagonal2
                            if (A[i][j][k] == 0)
                            {
                                cont++;
                            }
                            if (A[i][j][k] == 1)
                            {
                                cont2++;
                            }
                        }
                        if (cont == 4 || cont2 == 4)
                        {
                            Impressao(A);
                            if (m % 2 == 0)
                            {
                                printf("\n%s ganhou!\n", jogador1);
                            }
                            else
                            {
                                printf("\n%s ganhou!\n", jogador2);
                            }
                            return 0;
                        }
                    }

                    Num[m - 1] = N;

                    if (m != 16)
                    {
                        Z = Transforma(Entrada[1]);
                        if (Z < 0 || Z > 15)
                        {
                            printf("Entrada Invalida\n");
                            Recupera(P, A, Pos, m);
                            continue;
                        }
                        else
                        {
                            //Recebe P e N e os Verifica
                            for (i = 0; i < 16; i++)
                            {
                                v = 0;
                                if (Num[i] == Z)
                                {
                                    printf("Numero Ja Utilizado\n");
                                    v = 1;
                                    break;
                                }
                            }
                            if (v == 1)
                            {
                                Recupera(P, A, Pos, m);
                                continue;
                            }
                            N = Z;
                            break;
                        }
                    }
                    else
                    {
                        break;
                    }
                }
            }
        }

        Impressao(A);
    }

    cout << endl << "O jogo empatou!" << endl;
}
