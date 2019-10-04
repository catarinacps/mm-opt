#include <stdio.h>

#include "new/mm_new.h"
#include "utils/utils.h"

int main(int argc, char* argv[])
{
    int **mat_a, **mat_b, **mat_c;
    int m, n; // m linhas e n colunas

    if (argc != 3) {
        printf("Siga o seguinte modelo de utilização:\n");
        printf("\t%s <numero de linhas> <numero de colunas>\n", argv[0]);
        exit(-1);
    }

    m = atoi(argv[1]);
    n = atoi(argv[2]);

    /* aloca as matrizes */
    mat_a = aloca_matriz(m, n);
    mat_b = aloca_matriz(m, n);
    mat_c = aloca_matriz(m, n);

#ifdef IMPRIME
    printf("Antes da inicializacao!\n");
    imprime_matriz(m, n, mat_a);
    imprime_matriz(m, n, mat_b);
    imprime_matriz(m, n, mat_c);
    printf("\n");
#endif

    /* popula as matrizes a e b */
    inicializa_matriz(m, n, mat_a);
    inicializa_matriz(m, n, mat_b);

#ifdef IMPRIME
    printf("Depois da inicializacao!\n");
    imprime_matriz(m, n, matA);
    imprime_matriz(m, n, matB);
    imprime_matriz(m, n, matC);
    printf("\n");
#endif

    /* multiplica as matrizes a e b */
    double inicio_clock = pega_tempo();
    multiplica_matriz(m, n, mat_a, mat_b, mat_c);
    double duracao = (pega_tempo() - inicio_clock);

#ifdef IMPRIME
    printf("Depois da Multiplicacao!\n");
    imprime_matriz(m, n, mat_a);
    imprime_matriz(m, n, mat_b);
    imprime_matriz(m, n, mat_c);
    printf("\n");
#endif

    printf("%5lf\n", duracao);

    /* desaloca as matrizes */
    desaloca_matriz(m, n, mat_a);
    desaloca_matriz(m, n, mat_b);
    desaloca_matriz(m, n, mat_c);
    return 0;
}
