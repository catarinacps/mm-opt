#include "mm.h"

#ifdef OTM_3
void multiplica_matriz(int m, int n, int* restrict* restrict matA, int* restrict* restrict matB, int* restrict* restrict matC)
#else
void multiplica_matriz(int m, int n, int** matA, int** matB, int** matC)
#endif
{
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
#ifdef OTM_3
#pragma omp simd
#endif
            for (int k = 0; k < m; k++) {
#ifdef OTM_2
                matC[i][j] += matA[i][k] * matB[j][k];
#else
                matC[i][j] += matA[i][k] * matB[k][j];
#endif
            }
        }
    }
}

int** aloca_matriz(int m, int n)
{
    int** matriz = (int**)calloc(m, sizeof(int*));

    if (matriz == NULL)
        exit(-2);

#ifdef OTM_1
    int* dados_matriz = calloc(m * n, sizeof(int));

    if (dados_matriz == NULL)
        exit(-2);

    for (int i = 0; i < m; i++)
        matriz[i] = &dados_matriz[i * n];
#else
    for (int i = 0; i < m; i++)
        matriz[i] = (int*)calloc(n, sizeof(int));
#endif

    return matriz;
}

void desaloca_matriz(int m, int n, int** matriz)
{
#ifdef OTM_1
    free(matriz[0]);
#else
    for (int i = 0; i < m; i++) {
        free(matriz[i]);
    }
#endif

    free(matriz);
}
