#include <stdio.h>
#include <math.h>
#include <stdlib.h>
// #include "time.h"

float matriz[10][10], vetorResultados[10], vetorAuxiliar[10], vetorFinal[10], EPSILON = 0.00001, soma;

void main(int argc, char **argv)
{
    // double momentoInicializacao, momentoProcessamento, momentoFinalizacao, tempoInicializacao, tempoProcessamento, tempoFinalizacao;
    // GET_TIME(momentoInicializacao);
    // tempoInicializacao = momentoInicializacao;

    int numeroDeVariaveis, flag;

    printf("\nQuantas variáveis possui na equação?: ");
    scanf("%d", &numeroDeVariaveis);

    printf("\nEntre com a matriz de equações: ");
    for (int i = 0; i < numeroDeVariaveis; i++)
    {
        for (int j = 0; j < numeroDeVariaveis; j++)
        {
            scanf("%f", &matriz[i][j]);
        }
    }
    printf("\nEntre com o vetor de resultados: ");
    for (int i = 0; i < numeroDeVariaveis; i++)
        scanf("%f", &vetorResultados[i]);
    for (int i = 0; i < numeroDeVariaveis; i++)
        vetorAuxiliar[i] = 0;

    // GET_TIME(momentoInicializacao);
    // tempoInicializacao = momentoInicializacao - tempoInicializacao;

    // GET_TIME(momentoProcessamento);
    // tempoProcessamento = momentoProcessamento;

    do
    {
        for (int i = 0; i < numeroDeVariaveis; i++)
        {
            soma = vetorResultados[i];
            for (int j = 0; j < numeroDeVariaveis; j++)
                if (j != i)
                    soma -= matriz[i][j] * vetorAuxiliar[j];
            vetorFinal[i] = soma / matriz[i][i];
        }

        flag = 1;

        for (int i = 0; i < numeroDeVariaveis; i++)
            if (fabs(vetorAuxiliar[i] - vetorFinal[i]) < EPSILON)
                flag = 0;

        if (flag == 1)
            for (int i = 0; i < numeroDeVariaveis; i++)
                vetorAuxiliar[i] = vetorFinal[i];

    } while (flag == 1);

    // GET_TIME(momentoProcessamento);
    // tempoProcessamento = momentoProcessamento - tempoProcessamento;

    // GET_TIME(momentoFinalizacao);
    // tempoFinalizacao = momentoFinalizacao;

    printf("Solução: \n");
    for (int i = 0; i < numeroDeVariaveis; i++)
        printf("x%d: %8.5f \n", i + 1, vetorFinal[i]);

    // GET_TIME(momentoFinalizacao);
    // tempoFinalizacao = momentoFinalizacao - tempoFinalizacao;

    // printf("Tempo de inicialização: %0.6f \nTempo de processamento: %0.6f \nTempo de finalização: %0.6f \n ", tempoInicializacao, tempoProcessamento, tempoFinalizacao);
}