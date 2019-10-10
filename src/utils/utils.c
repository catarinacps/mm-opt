#include "utils.h"

double pega_tempo(void)
{
    struct timeval tr;
    gettimeofday(&tr, NULL);
    return (double)tr.tv_sec + (double)tr.tv_usec / 1000000;
}

void imprime_matriz(int m, int n, int** matriz)
{
    int i, j;
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

void inicializa_matriz(int m, int n, int** matriz)
{
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            matriz[i][j] = i + j;
        }
    }
}

void inicializa_matriz_t(int m, int n, int** matriz)
{
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            matriz[j][i] = i + j;
        }
    }
}
