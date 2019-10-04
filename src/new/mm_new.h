#pragma once

#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <stdbool.h>
#include <omp.h>

void multiplica_matriz(int m, int n, int** matA, int** matB, int** matC);

int** aloca_matriz(int m, int n);

void desaloca_matriz(int m, int n, int** matriz);
