#include <iostream>

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
                    std::cout << A[i][j][k];
                }
            }
        }
    }
    printf("\n");
}

bool verifica(int A[4][4][4], char jogador1[15], char jogador2[15], int m)
{
    int cont;
    int cont2;
    int i;
    int j;
    int k;
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
            return true;
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
                return true;
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
                return true;
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
            return true;
        }
    }

    return false;
}

char Converte(char a)
{
    if (a > 9)
    {
        return(a + 'a');
    }
    else
    {
        return(a + '0');
    }
}