#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

typedef struct dado{
  int send_flag;
  int rec_flag;
  char mensagem[50];
}dado;

int Transforma(char X)
{
  if (X >= 'a' && X <= 'f')
  {
    X = X - 'a' + 'A';
  }
  if (X >= 'A' && X <= 'F')
  {
    X = X - 'A' + 10; //Tranforma��o de Hexa em Inteiro
  }
  if (X >= '0' && X <= '9')
  {
    X = X - '0';
  }
  return (X);
}

void Recupera(int A, int B[4][4][4], int C[], int D)
{
  int i;
  for (i = 0; i < 4; i++)
  {
    B[A / 4][A % 4][i] = 2;
  }
  C[D - 1] = 20;
}

void Impressao(int A[4][4][4])
{
  int i, j, k;

  for (i = 0; i < 4; i++)
  {
    printf("\n__________________________\n");
    for (j = 0; j < 4; j++)
    {
      if (j != 0)
      {
        printf(" | ");
      }
      for (k = 0; k < 4; k++)
      {
        if (A[i][j][k] == 2)
        {
          printf(" ");
        }
        else
        {
          printf("%d", A[i][j][k]);
        }
      }
    }
  }
  printf("\n");
}

int meu_socket;
pthread_mutex_t mutexsum = PTHREAD_MUTEX_INITIALIZER;
struct sockaddr_in addr;
void *sendmessage();
void *listener();
int done = 1;

int main()
{
  dado * dado_user = calloc(1,sizeof(dado));

  meu_socket = socket(AF_INET, SOCK_STREAM, 0);

  if (meu_socket == -1)
  {
    printf("Erro ao criar o socket!\n");
    return 1;
  }

  addr.sin_family = AF_INET;
  addr.sin_port = htons(1234);
  addr.sin_addr.s_addr = inet_addr("127.0.0.1");

  memset(&addr.sin_zero, 0, sizeof(addr.sin_zero));

  printf("Tentando se conectar ao servidor...\n");

  if (connect(meu_socket, (struct sockaddr *)&addr, sizeof(addr)) == -1)
  {
    printf("Erro ao se conectar!\n");
    return 1;
  }

  printf("Conectado!\n\n");

  pthread_t threads[2];
  void *status;
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

  pthread_create(&threads[1], &attr, listener, (void*)dado_user);
  pthread_create(&threads[0], &attr, sendmessage, (void*)dado_user);
  

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

  while(!dado_user->rec_flag){}
  if(dado_user->mensagem[0] == 0){
    printf("Eu sou o 0\n");
  }else{
    printf("Eu sou o 1\n");
  }
  dado_user->rec_flag = 0;


  printf("Jogador, digite seu nome: ");
  fflush(stdin);
  fgets(jogador1,49,stdin);
  strcpy(dado_user->mensagem,jogador1);
  dado_user->send_flag = 1;
  while(!dado_user->rec_flag){}
  strcpy(jogador2,dado_user->mensagem);
  dado_user->rec_flag = 0;

  printf("Jogador 2: %s\n",jogador2);

  while(1){}


  return 0;
}

void *sendmessage(void * dados)
{
  int enviados;
  char mensagem[256];
  dado * dados_user = (dado*) dados;

  do
  {
    while(!dados_user->send_flag){
    }
    mensagem[strlen(dados_user->mensagem) - 1] = '\0';
    enviados = send(meu_socket, dados_user->mensagem, strlen(dados_user->mensagem), 0);
    dados_user->send_flag = 0;

  } while (strcmp(dados_user->mensagem, "exit") != 0);

  pthread_mutex_destroy(&mutexsum);
  pthread_exit(NULL);
  close(meu_socket);
  done = 0;
}

void *listener(void * dados)
{
  int recebidos;
  char resposta[50];
  dado * dados_user = (dado*) dados;

  recebidos = recv(meu_socket, dados_user->mensagem, 50, 0);
  dados_user->mensagem[1] = '\0';
  dados_user->rec_flag = 1;
  printf("Recebi\n");
  do
  {
    recebidos = recv(meu_socket, dados_user->mensagem, 50, 0);
    dados_user->mensagem[recebidos] = '\0';
    dados_user->rec_flag = 1;
    printf("To aqui");

  } while (recebidos != -1);
}
