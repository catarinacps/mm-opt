#pragma once

#include <malloc.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>

void multiplica_matriz(int m, int n, int** __restrict__ matA, int** __restrict__ matB, int** __restrict__ matC);

int** aloca_matriz(int m, int n);

void desaloca_matriz(int m, int n, int** matriz);
