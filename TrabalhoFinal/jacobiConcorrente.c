#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <pthread.h>
/* Variaveis globais */
int bloqueadas = 0, nthreads = 1, numeroDeVariaveis;
pthread_mutex_t x_mutex;
pthread_cond_t x_cond;
float matriz[10][10], vetorResultados[10], vetorAuxiliar[10], vetorFinal[10], EPSILON = 0.00001, soma;

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
    int id = *(int *)arg;
    for (int i = id; i < numeroDeVariaveis; i += nthreads)
    {
        soma = vetorResultados[i];
        for (int j = 0; j < numeroDeVariaveis; j++)
            if (j != i)
                soma -= matriz[i][j] * vetorAuxiliar[j];
        vetorFinal[i] = soma / matriz[i][i];
    }
    barreira(nthreads);
}

void main(int argc, char **argv)
{
    pthread_t *tid; // identificadores das threads no sistema
    if (argc > 1)
    {
        nthreads = atoi(argv[1]);
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

    int flag;
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
    printf("Solução: \n");
    for (int i = 0; i < numeroDeVariaveis; i++)
        printf("x%d: %8.5f \n", i + 1, vetorFinal[i]);
}