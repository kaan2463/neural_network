/*
 * MemoryUtils.h
 *
 *  Created on: Jun 13, 2020
 *      Author: khan
 */

#ifndef UTILS_MEMORYUTILS_H_
#define UTILS_MEMORYUTILS_H_
#include <stdlib.h>

class MemoryUtils {
public:
	static void allocate_double_matrix(double **&matrix, int m, int n);
	static void allocate_double_vector(double *&matrix, int m);
};

#endif /* UTILS_MEMORYUTILS_H_ */
