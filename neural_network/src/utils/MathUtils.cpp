/*
 * MathUtils.cpp
 *
 *  Created on: Jun 13, 2020
 *      Author: khan
 */

#include "MathUtils.h"
#include <math.h>
/**
 * mat1    m*n matrix
 * mat2    n*p matrix
 * result  m*p matrix
 *
 * result = mat1 * mat2
 */
void MathUtils::mult_double_matrix(double **mat1, double **mat2,
		double **result, int m, int n, int p) {

//	clear result first
	for (int i = 0; i < m; i++) {
		for (int k = 0; k < p; k++) {
			result[i][k] = 0;
		}
	}
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < p; k++) {
				result[i][k] += mat1[i][j] * mat2[j][k];
			}
		}
	}
}

/**
 * vector  1*m matrix
 * mat     m*n matrix
 * result  1*n matrix
 *
 * result = vector * mat
 */
void MathUtils::mult_double_vector(double *vector, double **mat, double *result,
		int m, int n) {

	//	clear result first
	for (int j = 0; j < n; j++) {
		result[j] = 0;
	}
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			result[j] += vector[i] * mat[i][j];
		}
	}
}
double MathUtils::sigmoid(double x, bool derivative) {

	if (derivative) {
		return (1 - x) * x;
	}

	return 1 / (1 + exp(-x));
}
