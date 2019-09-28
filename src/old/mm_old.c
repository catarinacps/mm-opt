#include "mm_old.h"

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
    int** matriz = (int**)calloc(m, sizeof(int*));

    if (matriz == NULL)
        exit(-2);

    for (int i = 0; i < m; i++)
        matriz[i] = (int*)calloc(n, sizeof(int));

    return matriz;
}

void desaloca_matriz(int m, int n, int** matriz)
{
    for (int i = 0; i < m; i++) {
        free(matriz[i]);
    }

    free(matriz);
}
