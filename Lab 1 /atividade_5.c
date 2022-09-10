#include <stdio.h>
#include <stdlib.h> 
#include <pthread.h>

#define NTHREADS 2 // Total de threads a serem criadas
#define TAMANHOARRAY 10000 // Tamanho do array operado

float *arrayQualquer;
float *arrayFinal; 

void *incrementaArray (void *arg) {
    int idThread = * (int*) arg;
    printf("ID DA THREAD AQUI %d\n", idThread);
    for (int i = idThread; i<TAMANHOARRAY;i+=NTHREADS){
        arrayFinal[i] = arrayQualquer[i] * 1.1;
        // printf("THREAD %d operou o valor %f\n", idThread, arrayFinal[i]);
        printf("Operação número %d feita pela THREAD %d\n", i, idThread);
    }
    pthread_exit(NULL);
}

void preenchedorDeArray(float* array){
    for (int i = 0; i < TAMANHOARRAY; i++){
        array[i] = rand() % 10;
    }
}

int main (void * arg){

    pthread_t tid_sistema[NTHREADS]; // Identificadores das threads no sistema
    int tid_local[NTHREADS];
    arrayQualquer = (float *) malloc (sizeof(float) * TAMANHOARRAY); // Criando um array de floats 😎
    arrayFinal = (float *) malloc (sizeof(float) * TAMANHOARRAY); 

    if (arrayQualquer == NULL || arrayFinal == NULL){
        printf("Erro na alocação de memória");
    }

    preenchedorDeArray(arrayQualquer);

    for (int thread = 0; thread < NTHREADS; thread++){
        tid_local[thread] = thread;
        if (pthread_create(&tid_sistema[thread], NULL, incrementaArray, (void*) &tid_local[thread])){
            printf("ERRO NA CRIAÇÃO DA THREAD %d 😔😔😔\n", thread);
        }
        printf("Cria a thread %d \n", thread);
    }

    return 0;
}