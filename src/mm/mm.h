#pragma once

#include <malloc.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#ifdef OTM_3
void multiplica_matriz(int m, int n, int* restrict* restrict matA, int* restrict* restrict matB, int* restrict* restrict matC);
#else
void multiplica_matriz(int m, int n, int** matA, int** matB, int** matC);
#endif

int** aloca_matriz(int m, int n);

void desaloca_matriz(int m, int n, int** matriz);
