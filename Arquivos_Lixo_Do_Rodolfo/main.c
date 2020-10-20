#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int Transforma(char X){
    if(X>='a' && X<='f'){
        X=X-'a'+'A';
    }
    if(X>='A' && X<='F'){
        X=X-'A'+10;                     //Tranformação de Hexa em Inteiro
    }
    if(X>='0' && X<='9'){
        X=X-'0';
    }
    return(X);
}

void Recupera(int A, int B[4][4][4], int C[], int D){
    int i;
    for(i=0;i<4;i++){
        B[A/4][A%4][i]=2;
}
    C[D-1]=20;
}

void Impressao(int A[4][4][4]){
    int i, j, k;

    for(i=0;i<4;i++){
        printf("\n__________________________\n");
        for(j=0;j<4;j++){
            if(j!=0){printf(" | ");}
            for(k=0;k<4;k++){
                if(A[i][j][k]==2){printf(" ");}
                else{printf("%d",A[i][j][k]);}
            }
        }
    }
    printf("\n");
}


int main()
{
char N;
char P;
char jogador1[15];
char jogador2[15];
int i;
int Z;
int j;
int aux;
int k;                      //Declaração das Variáveis
int m;
int v;
int cont;
int cont2;
int A[4][4][4];
int Num[16];
int Pos[16];
char Entrada[50];

printf("Jogador 1, digite seu nome: ");
fflush(stdin);
fgets(jogador1,49,stdin);
fflush(stdin);                                   //Nomeação dos jogadores
printf("Jogador 2, digite seu nome: ");
fgets(jogador2,49,stdin);

for(i=0;i<16;i++){Num[i]=20;}
for(i=0;i<16;i++){Pos[i]=20;}

for(i=0;i<4;i++){
    for(j=0;j<4;j++){
        for(k=0;k<4;k++){
            A[i][j][k] = 2;                                         //Preenchimento do tabuleiro
        }
    }
}


Impressao(A);

while(1){
    printf("\n\n%sFaca sua jogada: ",jogador1);
    fflush(stdin);                                                                  //Primeira Jogada
    fgets(Entrada,48,stdin);
    if(strlen(Entrada)!=2){printf("Entrada Invalida");}
    else{
    N=Transforma(Entrada[0]);
    if(N>=0 && N<=15){break;}
    }
}

for(m=1;m<17;m++){

    while(1){
    if(m%2==1){printf("\n\n%sFaca sua jogada: ",jogador2);}else{printf("\n\n%sFaca sua jogada: ",jogador1);}
    fflush(stdin);
    fgets(Entrada,48,stdin);
    if(strlen(Entrada)>3||strlen(Entrada)<2){printf("Entrada Invalida");}
    else{
        P=Transforma(Entrada[0]);
        if(P<0 || P>15){printf("Entrada Invalida\n");continue;}else{
        for(i=0;i<16;i++){
        v=0;
        if(Pos[i]==P){printf("Posicao Ocupada\n");v=1;break;}}
        if(v==1){continue;}
        Pos[m-1]=P;
        aux = N;
        for(i=3;i>=0;i--){
            A[P/4][P%4][i]=aux%2;
            aux /= 2;}

           for(j=0;j<4;j++){
        cont = 0;
        cont2 = 0;
        for(i=0;i<4;i++){                       //Verificacão diagonal1
            if(A[i][i][j]==0){cont++;}
            if(A[i][i][j]==1){cont2++;}
}
        if(cont == 4 || cont2==4){Impressao(A);if(m%2==0){printf("\n%sGanhou!\n",jogador1);}else{printf("\n%sGanhou!\n",jogador2);}return 0;}}




    for(i=0;i<4;i++){
        for(k=0;k<4;k++){
            cont = 0;
            cont2 = 0;
            for(j=0;j<4;j++){
                if(A[i][j][k]==0){cont++;}          //Verificacao horizontal
                if(A[i][j][k]==1){cont2++;}}
    if(cont == 4 || cont2 == 4){Impressao(A);if(m%2==0){printf("\n%sGanhou!\n",jogador1);}else{printf("\n%sGanhou!\n",jogador2);}return 0;}}}




    for(j=0;j<4;j++){
    for(k=0;k<4;k++){
            cont = 0;
            cont2 = 0;
        for(i=0;i<4;i++){
            if(A[i][j][k]==0){cont++;}          //Verificacao vertical
            if(A[i][j][k]==1){cont2++;}
    }
    if(cont == 4 || cont2 == 4){Impressao(A);if(m%2==0){printf("\n%sGanhou!\n",jogador1);}else{printf("\n%sGanhou!\n",jogador2);}return 0;}}}




    for(k=0;k<4;k++){
        cont = 0;
        cont2 = 0;
        for(i=0,j=3;i<4;i++,j--){                       //Verificacão diagonal2
            if(A[i][j][k]==0){cont++;}
            if(A[i][j][k]==1){cont2++;}
}
    if(cont == 4 || cont2==4){Impressao(A);if(m%2==0){printf("\n%sGanhou!\n",jogador1);}else{printf("\n%sGanhou!\n",jogador2);}return 0;}}


        Num[m-1]=N;

        if(m!=16){
        Z=Transforma(Entrada[1]);
        if(Z<0 || Z>15){printf("Entrada Invalida\n");Recupera(P,A,Pos,m);continue;}else{
                                                                            //Recebe P e N e os Verifica
        for(i=0;i<16;i++){
        v=0;
        if(Num[i]==Z){printf("Numero Ja Utilizado\n");v=1;break;}}
        if(v==1){Recupera(P,A,Pos,m);continue;}
        N=Z;
        break;}
        }else{break;} }}}


    Impressao(A);

}

printf("\n\nEmpate!\n");

}
