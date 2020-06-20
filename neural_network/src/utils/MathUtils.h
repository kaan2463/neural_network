/*
 * MathUtils.h
 *
 *  Created on: Jun 13, 2020
 *      Author: khan
 */

#ifndef UTILS_MATHUTILS_H_
#define UTILS_MATHUTILS_H_

class MathUtils {
public:
	static void mult_double_matrix(double **mat1, double **mat2,
			double **result, int m, int n, int p);
	static void mult_double_vector(double *vector, double **mat, double *result,
			int m, int n);
	static double sigmoid(double x, bool deriv = false);
};

#endif /* UTILS_MATHUTILS_H_ */
