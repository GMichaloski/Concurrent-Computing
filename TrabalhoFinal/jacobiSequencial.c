#include <stdio.h>
#include <math.h>
#include <stdlib.h>

float matriz[10][10], vetorResultados[10], vetorAuxiliar[10], vetorFinal[10], EPSILON = 0.00001, soma;

void geraEquacao(int numeroVariaveis)
{
}

void geraMatrizResultados(int numeroVariaveis)
{
}

void main()
{
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
        flag = 0;
        for (int i = 0; i < numeroDeVariaveis; i++)
            if (fabs(vetorAuxiliar[i] - vetorFinal[i]) < EPSILON)
                flag = 1;
        if (flag == 1)
            for (int i = 1; i < numeroDeVariaveis; i++)
                vetorAuxiliar[i] = vetorFinal[i];

    } while (flag == 1);

    printf("Solução: \n");
    for (int i = 0; i < numeroDeVariaveis; i++)
        printf("x%d: %8.5f \n", i + 1, vetorFinal[i]);
}