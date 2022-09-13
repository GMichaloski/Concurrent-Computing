#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int obtemMatrizBinario(FILE *arquivo, int *linhas, int *colunas, float *matriz)
{
    arquivo = fread(&linhas, sizeof(int), 1, arquivo); // Lê o arquivo binário e verifica a existência dos dados de dimensão da matriz
    size_t ret = fread(linhas, sizeof(int), 1, arquivo);
    if (!ret)
    {
        fprintf(stderr, "Erro de leitura das dimensoes da matriz arquivo \n");
        return 3;
    }
    ret = fread(colunas, sizeof(int), 1, arquivo);
    if (!ret)
    {
        fprintf(stderr, "Erro de leitura das dimensoes da matriz arquivo \n");
        return 3;
    }
    int tam = (*linhas) * (*colunas); // calcula a qtde de elementos da matriz

    // aloca memoria para a matriz
    matriz = (float *)malloc(sizeof(float) * tam);
    if (!matriz)
    {
        fprintf(stderr, "Erro de alocao da memoria da matriz\n");
        return 3;
    }

    ret = fread(matriz, sizeof(float), tam, arquivo);
    if (ret < tam)
    {
        fprintf(stderr, "Erro de leitura dos elementos da matriz\n");
        return 4;
    }
}

int main(int argc, char *argv[])
{

    float *matrizA;
    float *matrizB;
    float *matrizFinal;
    int linhas, colunas;
    long long int tam;
    FILE *arquivoEntradaA = fopen(argv[1], "rb");
    FILE *arquivoEntradaB = fopen(argv[2], "rb");
    FILE *arquivoSaida = fopen(argv[3], "wb");

    if (argc < 2)
    { // Verifica se os parâmetros foram todos passados ao compilar o programa
        fprintf(stderr, "INPUT INVÁLIDO!\n Por favor, digite %s <Arquivo de entrada> <Arquivo de saída>\n", argv[0]);
        return 1;
    }

    if (!arquivoEntradaA)
    { // Verifica se é possível abrir o arquivo indicado
        fprintf(stderr, "Falha ao abrir o arquivo!\n");
        return 2;
    }

    int descritorArquivo = fread(&linhas, sizeof(int), 1, arquivoEntradaA); // Lê o arquivo binário e verifica a existência dos dados de dimensão da matriz
    if (!descritorArquivo)
    {
        fprintf(stderr, "Erro de abertura do arquivo\n"); // DÚVIDA AQUI IRMÃO
    }

    tam = linhas * colunas;                         // Calculando a quantidade de elementos da matriz para
    matrizA = (float *)malloc(sizeof(float) * tam); // alocar espaço corretamente
    matrizB = (float *)malloc(sizeof(float) * tam);
    matrizFinal = (float *)malloc(sizeof(float) * tam);

    if (matrizA == NULL || matrizB == NULL || matrizFinal == NULL)
    {
        printf("ERRO AO ALOCAR MEMÓRIA\n");
        return 2;
    }
    // Representar a matriz. Vetor_Linha?
    for (size_t i = 0; i < tam; i++)
    {
        // matriz[i] = 1;
    }

    for (size_t i = 0; i < linhas; i++)
    {
        for (size_t j = 0; j < colunas; j++)
        {
            matrizFinal[i * linhas + j];
        }
    }

    // PENSAR EM COMO ESCREVER A MATRIZ EM BINÁRIO
    // SALVAR O ARQUIVO
    // NÃO ESQUECE DOS CONTADORES DE TEMPO
    fclose(arquivoEntradaA);
}