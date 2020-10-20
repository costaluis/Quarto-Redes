#include <iostream>

int Transforma(char X){
    if(X>='a' && X<='f'){
        X=X-'a'+'A';
    }
    if(X>='A' && X<='F'){
        X=X-'A'+10;                     //Tranforma��o de Hexa em Inteiro
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
                else{std::cout << A[i][j][k];}
            }
        }
    }
    printf("\n");
}