#include <iostream>
#include <stdlib.h>
#include <string>
#include <cmath>
#define TAM_MENSAGEM 256
#define TAM_BYTE 8

using namespace std;

void AplicacaoTransmissora(void);
void CamadaDeAplicacaoTransmissora(string);
void Char2Bit(char, int*);
char Bit2Char(int*);
void CamadaDeAplicacaoReceptora(int*);
void AplicacaoReceptora(string);
void PrintByte(int*);

int main(void){
    AplicacaoTransmissora();
}

void AplicacaoTransmissora(void){
    string mensagem;
    cout << "Digite uma mensagem:" << endl;
    cin >> mensagem;

    CamadaDeAplicacaoTransmissora(mensagem);

}

void CamadaDeAplicacaoTransmissora(string mensagem){
    int * quadro = (int *) calloc(TAM_MENSAGEM*TAM_BYTE, sizeof(int));
    int byte[TAM_BYTE];

    for(int i=0; i<mensagem.length(); i++){
        Char2Bit(mensagem[i], byte);
        for(int j=0; j<TAM_BYTE; j++){
            quadro[i*TAM_BYTE + j] = byte[j];
        }

    }

    CamadaDeAplicacaoReceptora(quadro);
}

void CamadaDeAplicacaoReceptora(int quadro[]){
    string mensagem;
    int byte[TAM_BYTE];

    for(int i=0; i<TAM_MENSAGEM; i++){
        for(int j=0; j<TAM_BYTE; j++){
            byte[j] = quadro[i*TAM_BYTE + j];
        }
        mensagem.push_back(Bit2Char(byte));
    }

    AplicacaoReceptora(mensagem);
}

void AplicacaoReceptora(string mensagem){
    cout << "A mensagem recebida foi:" << mensagem << endl;
}

char Bit2Char(int byte[]){
    int num = 0;

    for(int i=0; i<TAM_BYTE; i++){
        num += byte[i] * pow(2,i);
    }

    return char(num);
}

void Char2Bit(char caracter, int* byte){
    int num = int(caracter);

    for(int i=0; i<TAM_BYTE; i++){
        byte[i] = num%2;
        num /= 2;
    }
}

void PrintByte(int * byte){
    cout << byte[0] << " "
        << byte[1] << " "
        << byte[2] << " "
        << byte[3] << " "
        << byte[4] << " " 
        << byte[5] << " "
        << byte[6] << " "
        << byte[7] << endl;
}

