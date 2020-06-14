/*
 * NeuralStructure.h
 *
 *  Created on: Jun 13, 2020
 *      Author: khan
 */

#ifndef NEURAL_STRUCTURE_NEURALSTRUCTURE_H_
#define NEURAL_STRUCTURE_NEURALSTRUCTURE_H_
#include "NN.h"
#include <stdlib.h>

#define LEARNING_RATE 0.5

class NeuralStructure {
public:
	NN *first = NULL;
	NN *last = NULL;
	void create_layers(int *layers, int sz);
	static void initialize_weight_matrix(NN *item);
	static void traverse(NN first, void (*callback)(NN*));
	static void traverse_by_error(NN first, void (*callback)(NN*, double*),
			double *error);
	static void forward(NN *item);
	static double back_propagation_delta(NN *item, int index, double *error);
	static void back_propagation(NN *item, double *error);
	void epoch(double *input, double *output);
};

#endif /* NEURAL_STRUCTURE_NEURALSTRUCTURE_H_ */
