#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define primeiraThread 4 // numero de threads com comportamento T1
#define segundaThread 2  // numero de threads com comportamento T2
#define terceiraThread 1 // numero de threads com comportamento T3

/*ESTRUTURA DAS THREADS:
• T1: modifica a variavel incrementando seu valor de 1 (opera de escrita).  ̃
• T2: le a variável e a imprime na tela indicando se é um valor par ou ́ımpar
(operação de leitura).  ̃
• T3: primeiro le a vari ˆ avel e a imprime na tela (operação de leitura); faz um pro-  ̃
cessamento “bobo” qualquer (mais significativo); e depois modifica a variavel  ́
escrevendo o valor do seu identificador de thread (operação de escrita).  ̃
*/

// variaveis do problema
int leit = 0; // contador de threads lendo
int escr = 0; // contador de threads escrevendo

// variaveis para sincronizacao
pthread_mutex_t mutex;
pthread_cond_t cond_leit, cond_escr;

// valor global observado pela atividade
int valor = 0;

// entrada leitura
void InicLeit(int id)
{
    pthread_mutex_lock(&mutex);
    printf("L[%d] quer ler\n", id);
    while (escr > 0)
    {
        printf("L[%d] bloqueou\n", id);
        pthread_cond_wait(&cond_leit, &mutex);
        printf("L[%d] desbloqueou\n", id);
    }
    leit++;
    pthread_mutex_unlock(&mutex);
}

// saida leitura
void FimLeit(int id)
{
    pthread_mutex_lock(&mutex);
    printf("L[%d] terminou de ler\n", id);
    leit--;
    if (leit == 0)
        pthread_cond_signal(&cond_escr);
    pthread_mutex_unlock(&mutex);
}

// entrada escrita
void InicEscr(int id)
{
    pthread_mutex_lock(&mutex);
    printf("E[%d] quer escrever\n", id);
    while ((leit > 0) || (escr > 0))
    {
        printf("E[%d] bloqueou\n", id);
        pthread_cond_wait(&cond_escr, &mutex);
        printf("E[%d] desbloqueou\n", id);
    }
    escr++;
    pthread_mutex_unlock(&mutex);
}

// saida escrita
void FimEscr(int id)
{
    pthread_mutex_lock(&mutex);
    printf("E[%d] terminou de escrever\n", id);
    escr--;
    pthread_cond_signal(&cond_escr);
    pthread_cond_broadcast(&cond_leit);
    pthread_mutex_unlock(&mutex);
}

// thread leitora
void *leitor(void *arg)
{
    int *id = (int *)arg;
    while (1)
    {
        InicLeit(*id);
        (valor % 2) ? printf("O valor %d, lido pela leitora %d, é ímpar!\n", valor, *id) : printf("O valor %d, lido pela leitora %d, é par!\n", valor, *id);
        FimLeit(*id);
        sleep(1);
    }
    free(arg);
    pthread_exit(NULL);
}

// thread leitora
void *escritor(void *arg)
{
    int *id = (int *)arg;
    while (1)
    {
        InicEscr(*id);
        int valorIncrementado = valor + 1;
        printf("Escritora %d está escrevendo o valor %d\n", *id, valorIncrementado);
        valor = valorIncrementado;
        FimEscr(*id);
        sleep(1);
    }
    free(arg);
    pthread_exit(NULL);
}

void *leitorFeatEscritorBobo(void *arg)
{
    int *id = (int *)arg;
    while (1)
    {
        int variavelBoba = 0;
        InicLeit(*id);
        printf("Leitora boba %d está lendo o valor %d\n", *id, valor);
        FimLeit(*id);
        InicEscr(*id);
        variavelBoba = valor * 2 + 1;
        printf("Escritora boba %d está escrevendo o valor %d\n", *id, variavelBoba);
        valor = variavelBoba;
        FimEscr(*id);
        sleep(1);
    }
    free(arg);
    pthread_exit(NULL);
}
// funcao principal
int main(void)
{
    // identificadores das threads
    pthread_t tid[primeiraThread + segundaThread + terceiraThread];
    int id[primeiraThread + segundaThread + terceiraThread];

    // inicializa as variaveis de sincronizacao
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond_leit, NULL);
    pthread_cond_init(&cond_escr, NULL);

    // cria as threads T2
    for (int i = 0; i < segundaThread; i++)
    {
        id[i] = i + 1;
        if (pthread_create(&tid[i], NULL, leitor, (void *)&id[i]))
            exit(-1);
    }

    // cria as threads T1
    for (int i = 0; i < primeiraThread; i++)
    {
        id[i + segundaThread] = i + 1;
        if (pthread_create(&tid[i + segundaThread], NULL, escritor, (void *)&id[i + segundaThread]))
            exit(-1);
    }

    // cria as threads T3
    int somaTamanhoThreads = primeiraThread + segundaThread;
    for (int i = 0; i < terceiraThread; i++)
    {
        id[i + somaTamanhoThreads] = i + 1;
        if (pthread_create(&tid[i + somaTamanhoThreads], NULL, leitorFeatEscritorBobo, (void *)&id[i + somaTamanhoThreads]))
            exit(-1);
    }

    pthread_exit(NULL);
    return 0;
}