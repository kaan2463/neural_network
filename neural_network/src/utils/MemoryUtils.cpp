/*
 * MemoryUtils.cpp
 *
 *  Created on: Jun 13, 2020
 *      Author: khan
 */

#include "MemoryUtils.h"
#include <stdlib.h>

void MemoryUtils::allocate_double_matrix(double **&matrix, int m, int n) {
	matrix = (double**) malloc(sizeof(double*) * m);
	for (int i = 0; i < m; i++) {
		matrix[i] = (double*) malloc(sizeof(double) * n);
	}
}

void MemoryUtils::allocate_double_vector(double *&matrix, int m) {
	matrix = (double*) malloc(sizeof(double) * m);
}
