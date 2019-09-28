#include "mm_new.h"

void multiplica_matriz(int m, int n, int** matA, int** matB, int** matC)
{
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < m; k++) {
                matC[i][j] += matA[i][k] * matB[k][j];
            }
        }
    }
}

int** aloca_matriz(int m, int n)
{
    int* dados_matriz = (int*)calloc(m * n, sizeof(int));
    int** matriz = (int**)calloc(m, sizeof(int*));

    if (dados_matriz == NULL || matriz == NULL)
        exit(-2);

    for (int i = 0; i < m; i++)
        matriz[i] = dados_matriz + i * n;

    return matriz;
}

void desaloca_matriz(int m, int n, int** matriz)
{
    free(matriz[0]);
}
