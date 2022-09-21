#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "time.h"

#define NTHREADS 8

float *matrizA;
float *matrizB;
float *matrizFinal;
int linhasA, colunasA, linhasB, colunasB;

void *tarefa(void *arg)
{
    long int id = (long int)arg;
    for (size_t i = id; i < linhasA; i += NTHREADS) // Lamentável usar um código em o(n³)
    {
        for (size_t j = 0; j < colunasB; j++)
        {
            int acc = 0; // Utiliza-se um acumulador para armazenar o valor do item multiplicado
            for (size_t k = 0; k < linhasA; k++)
            {
                acc += matrizA[i * linhasA + k] * matrizB[k * linhasA + j]; // A matriz está sendo representada em um vetor único,
            }                                                               // cuja lógica utilizada é a seguinte:
            matrizFinal[i * linhasA + j] = acc;                             // vetor[linhaAtual * quantidadeDeLinhas + colunaAtual]
        }
    }
}

int main(int argc, char *argv[])
{
    double momentoInicializacao, momentoProcessamento, momentoFinalizacao; // Variáveis de contagem de tempo
    double duracaoInic, duracaoProc, duracaoFinal;

    long long int tam;
    FILE *arquivoEntradaA = fopen(argv[1], "rb");
    FILE *arquivoEntradaB = fopen(argv[2], "rb");
    FILE *arquivoSaida = fopen(argv[3], "wb");
    size_t ret;

    GET_TIME(momentoInicializacao);
    duracaoInic = momentoInicializacao;

    if (argc < 2)
    { // Verifica se os parâmetros foram todos passados ao compilar o programa
        fprintf(stderr, "INPUT INVÁLIDO!\nPor favor, digite %s <Arquivo de entrada 1> <Arquivo de entrada 2> <Arquivo de saída>\n", argv[0]);
        return 1;
    }

    if (!arquivoEntradaA)
    { // Verifica se é possível abrir o arquivo indicado
        fprintf(stderr, "Falha ao abrir o primeiro arquivo!\n");
        return 2;
    }

    if (!arquivoEntradaB)
    { // Verifica se é possível abrir o arquivo indicado
        fprintf(stderr, "Falha ao abrir o segundo arquivo!\n");
        return 2;
    }

    fread(&linhasA, sizeof(int), 1, arquivoEntradaA); // Obtendo a quantidade de linhas e colunas da primeira matriz
    fread(&colunasA, sizeof(int), 1, arquivoEntradaA);

    tam = colunasA * linhasA; // Calculando a quantidade de elementos da matriz para alocar espaço corretamente
    matrizA = (float *)malloc(sizeof(float) * tam);
    if (!matrizA)
    {
        fprintf(stderr, "Erro de alocao da memoria da primeira matriz\n");
        return 3;
    }

    ret = fread(matrizA, sizeof(float), tam, arquivoEntradaA);
    if (ret < tam)
    {
        fprintf(stderr, "Erro de leitura dos elementos da primeira matriz\n");
        return 4;
    }

    fclose(arquivoEntradaA);

    fread(&linhasB, sizeof(int), 1, arquivoEntradaB);
    fread(&colunasB, sizeof(int), 1, arquivoEntradaB);

    tam = colunasB * linhasB; // Calculando a quantidade de elementos da matriz para alocar espaço corretamente
    matrizB = (float *)malloc(sizeof(float) * tam);
    if (!matrizB)
    {
        fprintf(stderr, "Erro de alocao da memoria da segunda matriz\n");
        return 3;
    }

    ret = fread(matrizB, sizeof(float), tam, arquivoEntradaB);
    if (ret < tam)
    {
        fprintf(stderr, "Erro de leitura dos elementos da segunda matriz\n");
        return 4;
    }

    fclose(arquivoEntradaB);

    GET_TIME(momentoInicializacao);
    duracaoInic = momentoInicializacao - duracaoInic;

    GET_TIME(momentoProcessamento);
    duracaoProc = momentoProcessamento;

    pthread_t tid_sistema[NTHREADS]; // Identificadores das threads no sistema
    long int tid_local[NTHREADS];

    tam = linhasA * colunasB;
    matrizFinal = (float *)malloc(sizeof(float) * tam);

    if (!matrizFinal)
    {
        fprintf(stderr, "Erro de alocao da memoria da matriz final\n");
        return 3;
    }

    for (int i = 0; i < NTHREADS; i++)
    {
        tid_local[i] = i;
        if (pthread_create(&tid_sistema[i], NULL, tarefa, (void *)tid_local[i]))
        {
            fprintf(stderr, "ERRO--pthread_create\n");
            return 3;
        }
    }

    for (int thread = 0; thread < NTHREADS; thread++)
    {
        if (pthread_join(tid_sistema[thread], NULL))
        { // Espera todas as threads terminarem
            printf("--ERRO: pthread_join() \n");
            exit(-1);
        }
    }

    GET_TIME(momentoProcessamento);
    duracaoProc = momentoProcessamento - duracaoProc;
    GET_TIME(momentoFinalizacao);
    duracaoFinal = momentoFinalizacao;

    // escreve numero de linhas e de colunas
    fwrite(&linhasA, sizeof(int), 1, arquivoSaida);
    fwrite(&colunasB, sizeof(int), 1, arquivoSaida);
    // escreve os elementos da matriz
    ret = fwrite(matrizFinal, sizeof(float), tam, arquivoSaida);
    if (ret < tam)
    {
        fprintf(stderr, "Erro de escrita no  arquivo\n");
        return 4;
    }

    // finaliza o uso das variaveis
    fclose(arquivoSaida);
    free(matrizA);
    free(matrizB);
    free(matrizFinal);

    GET_TIME(momentoFinalizacao);
    duracaoFinal = momentoFinalizacao - duracaoFinal;

    printf("Tomada de tempo de execução interna:\nInicialização: %f ms\nProcessamento: %f ms\nFinalização: %f ms\n", duracaoInic, duracaoProc, duracaoFinal);

    return 0;
}