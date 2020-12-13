// Trabalho 2 - Redes de Computadores
// O programa simula a transmissao de uma mensagem atraves da camada de enlace, levando em consideracao
// possiveis ocorrencias de erros na transmissao. Para o tratamento, foram implementadoa tres algoritmos de 
// verificacao de erro na transmissao: verificacao por paridade par, verificacao por paridade impar, algoritmo
// CRC-32 (IEEE 802).

// inclusao de bibliotecas e define's
#include <iostream>
#include <stdlib.h>
#include <string>
#include <cmath>
#define TAM_MENSAGEM 50         // tamanho da mensagem em byte's
#define TAM_BYTE 8              // tamanho de um byte em bits
#define TAM_FLAGS 32            // espaco em bits reservado para flags no quadro de trasmissao
#define tipoDeControleErro 1    // define o algoritmo de controle de erro (0: paridade par / 1: paridade impar / 2: CRC-32)
#define porcentagemDeErros 1    // porcentagem de erro na transmissao pelo meio de comunicacao

using namespace std;

// headers das funcoes
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

// funcao principal
int main(void){
    AplicacaoTransmissora();
}

// funcao que recebe a mensagem a ser transmitida
void AplicacaoTransmissora(void){
    string mensagem;
    cout << "Digite uma mensagem:" << endl;
    cin >> mensagem;

    CamadaDeAplicacaoTransmissora(mensagem);            // chama a proxima camada

}

void CamadaDeAplicacaoTransmissora(string mensagem){
    int * quadro = (int *) calloc(TAM_MENSAGEM*TAM_BYTE + TAM_FLAGS, sizeof(int));      // quadro de bits que sera transmitido
    int byte[TAM_BYTE];

    for(int i=0; i<mensagem.length(); i++){       
        Char2Bit(mensagem[i], byte);                // converte cada byte da string para bit
        for(int j=0; j<TAM_BYTE; j++){
            quadro[i*TAM_BYTE + j] = byte[j];       // aloca cada bit no quadro
        }

    }

    CamadaEnlaceDadosTransmissora(quadro);          // chama a proxima camada
}

void CamadaEnlaceDadosTransmissora(int quadro[]){
    CamadaEnlaceDadosTransmissoraControleDeErro(quadro);        // verifica a ocorrencia de erro
    MeioDeComunicacao(quadro);                                  // envia o quadro para o meio de comunicacao
}

void CamadaEnlaceDadosTransmissoraControleDeErro(int quadro[]){

    switch (tipoDeControleErro){                // a partir do define da flag, trata o erro por algum dos algoritmos
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

// funcao de tratamento por paridade par
void CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(int quadro[]){
    int flag = 0;

    for(int i=0; i<TAM_MENSAGEM*TAM_BYTE; i++){
        flag += quadro[i];                          // conta quantos '1' tem na mensagem
    }

    flag = flag % 2;
    quadro[TAM_BYTE*TAM_MENSAGEM] = flag;           // coloca '1' ou '0' no primeiro espaco para flag no quadro
}

// funcao de tratamento por paridade impar
void CamadaEnlaceDadosTransmissoraControleDeErroBitParidadeImpar(int quadro[]){
    int flag = 0;

    for(int i=0; i<TAM_MENSAGEM*TAM_BYTE; i++){
        flag += quadro[i];                          // conta quantos '1' tem na mensagem
    }

    flag = flag % 2;
    quadro[TAM_BYTE*TAM_MENSAGEM] = (flag % 2 == 1) ? 0 : 1;    // coloca '1' ou '0' no primeiro espaco para flag no quadro
}

// funcao de tratamento por CRC-32
void CamadaEnlaceDadosTransmissoraControleDeErroCRC(int quadro[]){
    int G[33] = {1,0,0,0,0,0,1,0,0,1,1,0,0,0,0,0,1,0,0,0,1,1,1,0,1,1,0,1,1,0,1,1,1};    // gerador G
    int res[TAM_BYTE*TAM_MENSAGEM+TAM_FLAGS];       // resultado do CRC
    int bit;                // bit auxiliar

    for(int i=0; i<TAM_BYTE*TAM_MENSAGEM+TAM_FLAGS; i++){
        res[i] = (i<TAM_BYTE*TAM_MENSAGEM) ? quadro[i] : 0;     // preenche o vetor de resposta com o quadro e '0' nos espacos restantes
    }

    for (int i=0; i<TAM_BYTE*TAM_MENSAGEM; i++) {               // realiza a divisao de res pelo gerador G
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

    for(int i=TAM_BYTE*TAM_MENSAGEM; i<TAM_BYTE*TAM_MENSAGEM+32; i++){  // os ultimos 32 bits de res armazenam o resto da divisao
        quadro[i] = res[i];                                             // o resto eh colocado no espaco de flags do quadro
    }
}

// funcao que simula o meio de comunicacao
void MeioDeComunicacao(int fluxoBrutoDeBits[]){
    int erro;
    int fluxoBrutoDeBitsPontoA[TAM_BYTE*TAM_MENSAGEM+TAM_FLAGS], fluxoBrutoDeBitsPontoB[TAM_BYTE*TAM_MENSAGEM+TAM_FLAGS];
    srand(time(NULL));              // para a geracao de numeros aleatorios

    for(int i=0; i<TAM_BYTE*TAM_MENSAGEM+TAM_FLAGS; i++){
        fluxoBrutoDeBitsPontoA[i] = fluxoBrutoDeBits[i];        // pontoA recebe o quadro a ser transmitido para o pontoB
    }

    for(int i=0; i<TAM_BYTE*TAM_MENSAGEM+TAM_FLAGS; i++){
        if(rand()%100 >= porcentagemDeErros){                   // gera um numero aleatorio e transmite com erros (ou nao), dependendo do numero gerado e do erro definido
            fluxoBrutoDeBitsPontoB[i] = fluxoBrutoDeBitsPontoA[i];
        }else{
            (fluxoBrutoDeBitsPontoA[i]==0)                      // atribui o bit complementar sempre
            ? fluxoBrutoDeBitsPontoB[i] += fluxoBrutoDeBitsPontoA[i] 
            : fluxoBrutoDeBitsPontoB[i] -= fluxoBrutoDeBitsPontoA[i];
        }
    }

    CamadaEnlaceDadosReceptora(fluxoBrutoDeBitsPontoB);         // chama a camada receptora
}

void CamadaEnlaceDadosReceptora(int quadro[]){
    CamadaEnlaceDadosReceptoraControleDeErro(quadro);           // funcao de verificacao de erro
    CamadaDeAplicacaoReceptora(quadro);                         // decodifica a mensagem (bit to char)
}

void CamadaEnlaceDadosReceptoraControleDeErro(int quadro[]){

    switch (tipoDeControleErro){                // a partir do define da flag, trata o erro por algum dos algoritmos
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
        flag += quadro[i];                      // soma os '1' da mensagem
    }

    flag = flag % 2;

    if(quadro[TAM_BYTE*TAM_MENSAGEM] != flag){      // verifica se ha numero par de '1'
        cout << "Erro de transmissao detectado!" << endl;
    }
    
}

void CamadaEnlaceDadosReceptoraControleDeErroBitParidadeImpar(int quadro[]){
    int flag = 0;

    for(int i=0; i<TAM_MENSAGEM*TAM_BYTE; i++){
        flag += quadro[i];                      // soma os '1' da mensagem
    }

    flag = (flag % 2 == 1) ? 0 : 1;

    if(quadro[TAM_BYTE*TAM_MENSAGEM] != flag){      // verifica se ha numero impar de '1'
        cout << "Erro de transmissao detectado!" << endl;
    }
}

void CamadaEnlaceDadosReceptoraControleDeErroCRC(int quadro[]){
    int G[33] = {1,0,0,0,0,0,1,0,0,1,1,0,0,0,0,0,1,0,0,0,1,1,1,0,1,1,0,1,1,0,1,1,1};    // gerador G
    int res[TAM_BYTE*TAM_MENSAGEM+TAM_FLAGS];
    int bit;
    bool flag = false;

    for(int i=0; i<TAM_BYTE*TAM_MENSAGEM+TAM_FLAGS; i++){
        res[i] = (i<TAM_BYTE*TAM_MENSAGEM) ? quadro[i] : 0;    // res recebe o quadro de transmissao e '0' nos espacos restantes
    }

    for (int i=0; i<TAM_BYTE*TAM_MENSAGEM; i++) {           // realiza a divisao da mesma forma que o transmissor
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

    for(int i=TAM_BYTE*TAM_MENSAGEM; i<TAM_BYTE*TAM_MENSAGEM+32; i++){      // verifica se ha diferenca entre os resultados
        if(quadro[i] != res[i]){                                            // do transmissor e do receptor
            flag = true;
        }
    }

    if(flag){                                                               // se houver diferenca, houve erro
        cout << "Erro de transmissao detectado!" << endl;
    }

}

void CamadaDeAplicacaoReceptora(int quadro[]){              // decodifica a mensagem (bit to char)
    string mensagem;
    int byte[TAM_BYTE];

    for(int i=0; i<TAM_MENSAGEM; i++){
        for(int j=0; j<TAM_BYTE; j++){
            byte[j] = quadro[i*TAM_BYTE + j];               // pega um byte da mensagem
        }
        mensagem.push_back(Bit2Char(byte));                 // passa cada byte para char
    }

    AplicacaoReceptora(mensagem);                           // chama a aplicacao receptora
}

void AplicacaoReceptora(string mensagem){
    cout << "A mensagem recebida foi:" << mensagem << endl;     // printa a mensagem recebida
}

// transforma 1 byte em 1 char
char Bit2Char(int byte[]){
    int num = 0;

    for(int i=0; i<TAM_BYTE; i++){
        num += byte[i] * pow(2,i);
    }

    return char(num);
}

// transforma 1 char em 1 byte (vetor de 8 bits)
void Char2Bit(char caracter, int* byte){
    int num = int(caracter);

    for(int i=0; i<TAM_BYTE; i++){
        byte[i] = num%2;
        num /= 2;
    }
}

// funcao que printa 1 byte (vetor de bits)
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

