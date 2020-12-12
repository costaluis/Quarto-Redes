#include <iostream>
#include <stdlib.h>
#include <string>
#include <cmath>
#define TAM_MENSAGEM 50
#define TAM_BYTE 8
#define TAM_FLAGS 32
#define tipoDeControleErro 1
#define porcentagemDeErros 1

using namespace std;

void AplicacaoTransmissora(void);
void CamadaDeAplicacaoTransmissora(string);
void CamadaDeAplicacaoReceptora(int*);
void CamadaEnlaceDadosTransmissora(int*);
void CamadaEnlaceDadosTransmissoraControleDeErro(int*);
void CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(int*);
void CamadaEnlaceDadosTransmissoraControleDeErroBitParidadeImpar(int*);
void CamadaEnlaceDadosTransmissoraControleDeErroCRC(int*);
void MeioDeComunicacao(int*);
void CamadaEnlaceDadosReceptora(int*);
void CamadaEnlaceDadosReceptoraControleDeErro(int*);
void CamadaEnlaceDadosReceptoraControleDeErroBitParidadePar(int*);
void CamadaEnlaceDadosReceptoraControleDeErroBitParidadeImpar(int*);
void CamadaEnlaceDadosReceptoraControleDeErroCRC(int*);
void AplicacaoReceptora(string);
void PrintByte(int*);
void Char2Bit(char, int*);
char Bit2Char(int*);

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
    int * quadro = (int *) calloc(TAM_MENSAGEM*TAM_BYTE + TAM_FLAGS, sizeof(int));
    int byte[TAM_BYTE];

    for(int i=0; i<mensagem.length(); i++){
        Char2Bit(mensagem[i], byte);
        for(int j=0; j<TAM_BYTE; j++){
            quadro[i*TAM_BYTE + j] = byte[j];
        }

    }

    CamadaEnlaceDadosTransmissora(quadro);
}

void CamadaEnlaceDadosTransmissora(int quadro[]){
    CamadaEnlaceDadosTransmissoraControleDeErro(quadro);
    MeioDeComunicacao(quadro);
}

void CamadaEnlaceDadosTransmissoraControleDeErro(int quadro[]){

    switch (tipoDeControleErro){
    case 0:
        CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(quadro);
        break;
    case 1:
        CamadaEnlaceDadosTransmissoraControleDeErroBitParidadeImpar(quadro);
        break;
    case 2:
        CamadaEnlaceDadosTransmissoraControleDeErroCRC(quadro);
        break;
    default:
        cout << "Opcao Invalida!" << endl;
        break;
    }
}

void CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(int quadro[]){
    int flag = 0;

    for(int i=0; i<TAM_MENSAGEM*TAM_BYTE; i++){
        flag += quadro[i];
    }

    flag = flag % 2;
    quadro[TAM_BYTE*TAM_MENSAGEM] = flag;
}

void CamadaEnlaceDadosTransmissoraControleDeErroBitParidadeImpar(int quadro[]){
    int flag = 0;

    for(int i=0; i<TAM_MENSAGEM*TAM_BYTE; i++){
        flag += quadro[i];
    }

    flag = flag % 2;
    quadro[TAM_BYTE*TAM_MENSAGEM] = (flag % 2 == 1) ? 0 : 1;
}

void CamadaEnlaceDadosTransmissoraControleDeErroCRC(int quadro[]){
    int G[33] = {1,0,0,0,0,0,1,0,0,1,1,0,0,0,0,0,1,0,0,0,1,1,1,0,1,1,0,1,1,0,1,1,1};
    int res[TAM_BYTE*TAM_MENSAGEM+TAM_FLAGS];
    int bit;

    for(int i=0; i<TAM_BYTE*TAM_MENSAGEM+TAM_FLAGS; i++){
        res[i] = (i<TAM_BYTE*TAM_MENSAGEM) ? quadro[i] : 0;
    }

    for (int i=0; i<TAM_BYTE*TAM_MENSAGEM; i++) {
        if (res[i]) {
            for (int j=0; i+j < TAM_BYTE*TAM_MENSAGEM + 32; j++) {
                if (j <= 32) {
                    bit = (res[i + j] != G[j]) ? 1 : 0;
                } else {
                    bit = res[i + j];
                }
                res[i + j] = bit;
            }
        }
    }

    for(int i=TAM_BYTE*TAM_MENSAGEM; i<TAM_BYTE*TAM_MENSAGEM+32; i++){
        quadro[i] = res[i];
    }
}

void MeioDeComunicacao(int fluxoBrutoDeBits[]){
    int erro;
    int fluxoBrutoDeBitsPontoA[TAM_BYTE*TAM_MENSAGEM+TAM_FLAGS], fluxoBrutoDeBitsPontoB[TAM_BYTE*TAM_MENSAGEM+TAM_FLAGS];
    srand(time(NULL));

    for(int i=0; i<TAM_BYTE*TAM_MENSAGEM+TAM_FLAGS; i++){
        fluxoBrutoDeBitsPontoA[i] = fluxoBrutoDeBits[i];
    }

    for(int i=0; i<TAM_BYTE*TAM_MENSAGEM+TAM_FLAGS; i++){
        if(rand()%100 >= porcentagemDeErros){
            fluxoBrutoDeBitsPontoB[i] = fluxoBrutoDeBitsPontoA[i];
        }else{
            (fluxoBrutoDeBitsPontoA[i]==0) 
            ? fluxoBrutoDeBitsPontoB[i] += fluxoBrutoDeBitsPontoA[i] 
            : fluxoBrutoDeBitsPontoB[i] -= fluxoBrutoDeBitsPontoA[i];
        }
    }

    CamadaEnlaceDadosReceptora(fluxoBrutoDeBitsPontoB);
}

void CamadaEnlaceDadosReceptora(int quadro[]){
    CamadaEnlaceDadosReceptoraControleDeErro(quadro);
    CamadaDeAplicacaoReceptora(quadro);
}

void CamadaEnlaceDadosReceptoraControleDeErro(int quadro[]){

    switch (tipoDeControleErro){
    case 0:
        CamadaEnlaceDadosReceptoraControleDeErroBitParidadePar(quadro);
        break;
    case 1:
        CamadaEnlaceDadosReceptoraControleDeErroBitParidadeImpar(quadro);
        break;
    case 2:
        CamadaEnlaceDadosReceptoraControleDeErroCRC(quadro);
        break;
    default:
        cout << "Opcao Invalida!" << endl;
        break;
    }
}

void CamadaEnlaceDadosReceptoraControleDeErroBitParidadePar(int quadro[]){
    int flag = 0;

    for(int i=0; i<TAM_MENSAGEM*TAM_BYTE; i++){
        flag += quadro[i];
    }

    flag = flag % 2;

    if(quadro[TAM_BYTE*TAM_MENSAGEM] != flag){
        cout << "Erro de transmissao detectado!" << endl;
    }
    
}

void CamadaEnlaceDadosReceptoraControleDeErroBitParidadeImpar(int quadro[]){
    int flag = 0;

    for(int i=0; i<TAM_MENSAGEM*TAM_BYTE; i++){
        flag += quadro[i];
    }

    flag = (flag % 2 == 1) ? 0 : 1;

    if(quadro[TAM_BYTE*TAM_MENSAGEM] != flag){
        cout << "Erro de transmissao detectado!" << endl;
    }
}

void CamadaEnlaceDadosReceptoraControleDeErroCRC(int quadro[]){
    int G[33] = {1,0,0,0,0,0,1,0,0,1,1,0,0,0,0,0,1,0,0,0,1,1,1,0,1,1,0,1,1,0,1,1,1};
    int res[TAM_BYTE*TAM_MENSAGEM+TAM_FLAGS];
    int bit;
    bool flag = false;

    for(int i=0; i<TAM_BYTE*TAM_MENSAGEM+TAM_FLAGS; i++){
        res[i] = (i<TAM_BYTE*TAM_MENSAGEM) ? quadro[i] : 0;
    }

    for (int i=0; i<TAM_BYTE*TAM_MENSAGEM; i++) {
        if (res[i]) {
            for (int j=0; i+j < TAM_BYTE*TAM_MENSAGEM + 32; j++) {
                if (j <= 32) {
                    bit = (res[i + j] != G[j]) ? 1 : 0;
                } else {
                    bit = res[i + j];
                }
                res[i + j] = bit;
            }
        }
    }

    for(int i=TAM_BYTE*TAM_MENSAGEM; i<TAM_BYTE*TAM_MENSAGEM+32; i++){
        if(quadro[i] != res[i]){
            flag = true;
        }
    }

    if(flag){
        cout << "Erro de transmissao detectado!" << endl;
    }

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

