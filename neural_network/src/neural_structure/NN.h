/*
 * NN.h
 *
 *  Created on: Jun 13, 2020
 *      Author: khan
 */

#ifndef NEURAL_STRUCTURE_NN_H_
#define NEURAL_STRUCTURE_NN_H_

class NN {
public:
	const double BIAS = 1;
	int input_number;
	int output_number;
	double *input_layer;
	double *net_input;
	double *output_layer;
	double **weight_matrix;
	NN *next;
	NN *prev;
	void init_first(int input_number, int output_number);
	void hook_next(int out_number);
};

#endif /* NEURAL_STRUCTURE_NN_H_ */
