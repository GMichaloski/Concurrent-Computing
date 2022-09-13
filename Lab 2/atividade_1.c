#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int main(int argc, char *argv[])
{

    float *matriz;
    int linhas, colunas;
    long long int tam;
    FILE *arquivo_entrada = fopen(argv[1], "rb");

    if (argc < 2)
    { // Verifica se os parâmetros foram todos passados ao compilar o programa
        fprintf(stderr, "INPUT INVÁLIDO!\n Por favor, digite %s <Arquivo de entrada> <Arquivo de saída>\n", argv[0]);
        return 1;
    }

    if (!arquivo_entrada)
    { // Verifica se é possível abrir o arquivo indicado
        fprintf(stderr, "Falha ao abrir o arquivo!\n");
        return 2;
    }

    int leitor_arquivo = fread(&linhas, sizeof(int), 1, arquivo_entrada); // Lê o arquivo binário e verifica a existência dos dados de dimensão da matriz
    if (!leitor_arquivo)
    {
        fprintf(stderr, "Erro de abertura do arquivo\n"); // DÚVIDA AQUI IRMÃO
    }

    tam = linhas * colunas;
    matriz = (float *)malloc(sizeof(float) * tam); // Alocando espaço para a matriz
    if (matriz == NULL)
    {
        printf("ERRO AO ALOCAR MEMÓRIA\n");
        return 2;
    }
    // Representar a matriz. Vetor_Linha?

    for (size_t i = 0; i < linhas; i++)
    {
        for (size_t j = 0; j < colunas; j++)
        {
            // RELEMBRAR A FORMATAÇÃO DE MATRIZ EM C
        }
    }

    // PENSAR EM COMO ESCREVER A MATRIZ EM BINÁRIO
    // SALVAR O ARQUIVO
    // NÃO ESQUECE DOS CONTADORES DE TEMPO
}