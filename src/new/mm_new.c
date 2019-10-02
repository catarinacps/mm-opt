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
    // calloc inicializa os m*n endereços com zero
    int* dados_matriz = (int*)calloc(m * n, sizeof(int));
    // como isso fica contínuo em memória?
    int** matriz = (int**)calloc(m, sizeof(int*));

    /*
     *  TODO depois de entender como essa alocação ta funcionando, fazer o
     *  esquema de alocar de forma alinhada com posix_memalign (stdlib)
     */

    if (dados_matriz == NULL || matriz == NULL)
        exit(-2);

    for (int i = 0; i < m; i++) {
        // se dados_matriz tem só zeros, pq usar ela aqui?
        // also, no código do caco a matriz de dados é inicializada de forma
        // diferente (i+j com dois laços). Iniciaizar dessa forma fica a mesma
        // coisa (já que na real estamos fazendo diferente e não uma matriz
        // "normal")? Pq se não fica, teríamos que provar a corretude do nosso
        // resultado.
        // Não to conseguindo enxergar como essa alocação e inicialização tão
        // funfando :/
        matriz[i] = dados_matriz + i * n;
    }

    return matriz;
}

void desaloca_matriz(int m, int n, int** matriz)
{
    free(matriz[0]);
}
