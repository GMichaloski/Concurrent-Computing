#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <pthread.h>
#include "time.h"

#define QUANTIDADELINHAS 2 // tamanho do buffer
/* Variaveis globais */
int bloqueadas = 0, nthreads = 1, numeroDeVariaveis = QUANTIDADELINHAS;
pthread_mutex_t x_mutex;
pthread_cond_t x_cond;
float matriz[QUANTIDADELINHAS][QUANTIDADELINHAS], vetorResultados[QUANTIDADELINHAS], vetorAuxiliar[QUANTIDADELINHAS], vetorFinal[QUANTIDADELINHAS], EPSILON = 0.00001;

// Função barreira vista em aula
void barreira(int nthreads)
{
    pthread_mutex_lock(&x_mutex); // inicio secao critica
    if (bloqueadas == (nthreads - 1))
    {
        // ultima thread a chegar na barreira
        pthread_cond_broadcast(&x_cond);
        bloqueadas = 0;
    }
    else
    {
        bloqueadas++;
        pthread_cond_wait(&x_cond, &x_mutex);
    }
    pthread_mutex_unlock(&x_mutex); // fim secao critica
}

void *tarefaJacobi(void *arg)
{
    int id = (long int)arg; // Identificação das threads
    for (int i = id; i < numeroDeVariaveis; i += nthreads)
    {
        int soma = vetorResultados[i];
        for (int j = 0; j < numeroDeVariaveis; j++)
            if (j != i)
                soma -= matriz[i][j] * vetorAuxiliar[j];
        vetorFinal[i] = soma / matriz[i][i];
    }
    barreira(nthreads);
}

void main(int argc, char **argv)
{
    double momentoInicializacao, momentoProcessamento, momentoFinalizacao, tempoInicializacao, tempoProcessamento, tempoFinalizacao;
    GET_TIME(momentoInicializacao);
    tempoInicializacao = momentoInicializacao;
    pthread_t *tid; // Identificadores das threads no sistema
    if (argc > 1)
    {
        nthreads = atoi(argv[1]); // Argumento que recebe a quantidade de threads que o programa utilizará
    }

    printf("PROGRAMA EXECUTANDO COM %d THREADS \n", nthreads);
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

    tid = (pthread_t *)malloc(sizeof(pthread_t) * nthreads);
    if (tid == NULL)
    {
        fprintf(stderr, "ERRO--malloc\n");
        return;
    }

    GET_TIME(momentoInicializacao);
    tempoInicializacao = momentoInicializacao - tempoInicializacao;

    GET_TIME(momentoProcessamento);
    tempoProcessamento = momentoProcessamento;

    int flag; // Variável para calcular até quando o algoritmo deve iterar
    do
    {
        for (long int i = 0; i < nthreads; i++)
        {
            if (pthread_create(tid + i, NULL, tarefaJacobi, (void *)i))
            {
                fprintf(stderr, "ERRO--pthread_create\n");
                return;
            }
        }
        for (long int i = 0; i < nthreads; i++)
        {
            if (pthread_join(*(tid + i), NULL))
            {
                printf("--ERRO: pthread_join() \n");
                exit(-1);
            }
        }

        flag = 0;
        for (int i = 0; i < numeroDeVariaveis; i++)
            if (fabs(vetorAuxiliar[i] - vetorFinal[i]) < EPSILON)
                flag = 1;
        if (flag == 1)
            for (int i = 1; i < numeroDeVariaveis; i++)
                vetorAuxiliar[i] = vetorFinal[i];

    } while (flag == 1);

    GET_TIME(momentoProcessamento);
    tempoProcessamento = momentoProcessamento - tempoProcessamento;

    GET_TIME(momentoFinalizacao);
    tempoFinalizacao = momentoFinalizacao;

    printf("Solução: \n");
    for (int i = 0; i < numeroDeVariaveis; i++) // Imprime o valor das variáveis
        printf("x%d: %8.5f \n", i + 1, vetorFinal[i]);
    GET_TIME(momentoFinalizacao);
    tempoFinalizacao = momentoFinalizacao - tempoFinalizacao;
    printf("Tempo de inicialização: %0.6f \nTempo de processamento: %0.6f \nTempo de finalização: %0.6f \n ", tempoInicializacao, tempoProcessamento, tempoFinalizacao);
}