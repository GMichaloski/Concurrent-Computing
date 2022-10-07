#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NTHREADS 4

int x = 0;
pthread_mutex_t x_mutex;
pthread_cond_t x_cond;
pthread_cond_t x_cond2;

void *VolteSempre(void *t)
{
    pthread_mutex_lock(&x_mutex);
    while (x < 3)
    {
        pthread_cond_wait(&x_cond2, &x_mutex);
    }
    printf("Volte sempre!\n");
    pthread_mutex_unlock(&x_mutex);

    pthread_exit(NULL);
}

void *Intermediario1(void *t)
{
    pthread_mutex_lock(&x_mutex);
    if (x == 0)
    {
        pthread_cond_wait(&x_cond, &x_mutex);
    }
    printf("Sente-se, por favor!s\n");
    x++;
    if (x == 3)
    {
        pthread_cond_signal(&x_cond2);
    }
    pthread_mutex_unlock(&x_mutex);

    pthread_exit(NULL);
}

void *Intermediario2(void *t)
{
    pthread_mutex_lock(&x_mutex);
    if (x == 0)
    {
        pthread_cond_wait(&x_cond, &x_mutex);
    }
    printf("Fique à vontade!\n");
    x++;
    if (x == 3)
    {
        pthread_cond_signal(&x_cond2);
    }
    pthread_mutex_unlock(&x_mutex);

    pthread_exit(NULL);
}

void *BemVindo(void *t)
{
    pthread_mutex_lock(&x_mutex);
    printf("Seja bem-vindo!\n");
    x++;
    pthread_cond_broadcast(&x_cond);
    pthread_mutex_unlock(&x_mutex);

    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    int i;
    int *thread1, *thread2, *thread3, *thread4, *thread5;
    pthread_t threads[NTHREADS];

    thread1 = malloc(sizeof(int));
    thread2 = malloc(sizeof(int));
    thread3 = malloc(sizeof(int));
    thread4 = malloc(sizeof(int));
    *thread1 = 1, *thread2 = 2, *thread3 = 3;
    *thread4 = 4;

    /* Inicializa o mutex (lock de exclusao mutua) e a variavel de condicao */
    pthread_mutex_init(&x_mutex, NULL);
    pthread_cond_init(&x_cond, NULL);
    pthread_cond_init(&x_cond2, NULL);

    /* Cria as threads */

    pthread_create(&threads[3], NULL, BemVindo, (void *)thread4);
    pthread_create(&threads[2], NULL, Intermediario2, (void *)thread3);
    pthread_create(&threads[1], NULL, Intermediario1, (void *)thread2);
    pthread_create(&threads[0], NULL, VolteSempre, (void *)thread1);

    for (int thread = 0; thread < NTHREADS; thread++)
    {
        if (pthread_join(threads[thread], NULL))
        { // Espera todas as threads terminarem
            printf("--ERRO: pthread_join() \n");
            exit(-1);
        }
    }

    /* Desaloca variaveis e termina */
    pthread_mutex_destroy(&x_mutex);
    pthread_cond_destroy(&x_cond);
    pthread_cond_destroy(&x_cond2);
}