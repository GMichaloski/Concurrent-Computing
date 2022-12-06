
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// #include "time.h"

float A[3][3], b[3], vetorAuxiliar[3], vetorFinal[3], EPSILON = 0.00001, soma;

// Código de testes
void main(int argc, char **argv)
{

    int n;
    // double momentoInicializacao, momentoProcessamento, momentoFinalizacao, tempoInicializacao, tempoProcessamento, tempoFinalizacao;
    // GET_TIME(momentoInicializacao);
    // tempoInicializacao = momentoInicializacao;
    printf("\nQuantas variáveis possui na equação?: ");
    scanf("%d", &n);

    printf("\nEntre com a matriz de equações: ");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%f", &A[i][j]);
        }
    }
    printf("\nEntre com o vetor de resultados: ");
    for (int i = 0; i < n; i++)
        scanf("%f", &b[i]);
    for (int i = 0; i < n; i++)
        vetorAuxiliar[i] = 0;

    int i, j, k, l, m;
    // ETAPA DE ESCALONAMENTO
    for (k = 0; k < n - 1; k++)
    {
        double max = fabs(A[k][k]);
        int maxIndex = k;
        // procura o maior coeficiente em modulo
        for (i = k + 1; i < n; i++)
        {
            if (max < fabs(A[i][k]))
            {
                max = fabs(A[i][k]);
                maxIndex = i;
            }
        }
        if (maxIndex != k)
        {

            // troca a equacao pela equacao com o maior coeficiente em modulo
            for (j = 0; j < n; j++)
            {
                double temp = A[k][j];
                A[k][j] = A[maxIndex][j];
                A[maxIndex][j] = temp;
            }
            double temp = b[k];
            b[k] = b[maxIndex];
            b[maxIndex] = temp;
        }
        // Se A[k][k] e zero, entao a matriz dos coeficiente e singular
        // det A = 0
        if (A[k][k] == 0)
        {
            printf("A matriz dos coeficientes é singular\n");
            return;
        }
        else
        {
            // realiza o escalonamento
            for (m = k + 1; m < n; m++)
            {
                double F = -A[m][k] / A[k][k];
                A[m][k] = 0;
                b[m] = b[m] + F * b[k];
                for (l = k + 1; l < n; l++)
                {
                    A[m][l] = A[m][l] + F * A[k][l];
                }
            }
        }
    }
    // ETAPA DE RESOLUCAO DO SISTEMA
    for (i = n - 1; i >= 0; i--)
    {
        vetorFinal[i] = b[i];
        for (j = i + 1; j < n; j++)
        {
            vetorFinal[i] = vetorFinal[i] - vetorFinal[j] * A[i][j];
        }
        vetorFinal[i] = vetorFinal[i] / A[i][i];
    }
    printf("Solução: \n");
    for (int i = 0; i < n; i++)
        printf("x%d: %f \n", i + 1, vetorFinal[i]);
}