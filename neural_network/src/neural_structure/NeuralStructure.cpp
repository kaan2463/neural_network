/*
 * NeuralStructure.cpp
 *
 *  Created on: Jun 13, 2020
 *      Author: khan
 */

#include "NeuralStructure.h"
#include "../utils/MathUtils.h"

#include<iostream>

void NeuralStructure::create_layers(int *layers, int sz) {
	if (sz < 2) {
		throw "InvalidLayersException";
	}
	this->first = new NN;
	this->first->init_first(layers[0], layers[1]);
	NN *temp = first;
	for (int i = 2; i < sz; i++) {
		temp->hook_next(layers[i]);
		temp = temp->next;
	}
	this->last = temp->prev;
}

void NeuralStructure::traverse(NN first, void (*callback)(NN*)) {
	NN *temp = &first;
	while (temp != NULL) {
		callback(temp);
		temp = temp->next;
	}
}

void NeuralStructure::traverse_by_error(NN first,
		void (*callback)(NN*, double*), double *error) {
	NN *temp = &first;
	while (temp != NULL) {
		callback(temp, error);
		temp = temp->next;
	}
}

void NeuralStructure::forward(NN *item) {
	MathUtils::mult_double_vector(item->input_layer, item->weight_matrix,
			item->net_input, item->input_number, item->output_number);
	//BIAS
	for (int i = 0; i < item->output_number; i++) {
		item->net_input[i] += item->BIAS
				* item->weight_matrix[item->input_number][i];
	}

	for (int i = 0; i < item->output_number; i++) {
		item->output_layer[i] = MathUtils::sigmoid(item->net_input[i]);
	}
}

double NeuralStructure::back_propagation_delta(NN *item, int index,
		double *error) {
	if (item == NULL) {
		return (-1.0) * error[index];
	}
	double sigma = 0;
	for (int i = 0; i < item->output_number; i++) {
		sigma += item->weight_matrix[index][i]
				* MathUtils::sigmoid(item->output_layer[i], true)
				* NeuralStructure::back_propagation_delta(item->next, i, error);
	}
	return sigma;
}

void NeuralStructure::back_propagation(NN *item, double *error) {
	for (int i = 0; i < item->input_number; i++) {
		for (int j = 0; j < item->output_number; j++) {
			item->weight_matrix[i][j] -= LEARNING_RATE * item->input_layer[i]
					* MathUtils::sigmoid(item->output_layer[j], true)
					* NeuralStructure::back_propagation_delta(item->next, j,
							error);
		}
	}
	//BIAS Case
	for (int j = 0; j < item->output_number; j++) {
		item->weight_matrix[item->input_number][j] -= LEARNING_RATE * item->BIAS
				* MathUtils::sigmoid(item->output_layer[j], true)
				* back_propagation_delta(item->next, j, error);
	}
}

void NeuralStructure::initialize_weight_matrix(NN *item) {
	for (int i = 0; i < item->input_number + 1; i++) {
		for (int j = 0; j < item->output_number; j++) {
			item->weight_matrix[i][j] = 0.05;
		}
	}
}

void NeuralStructure::epoch(double *input, double *output) {
	double error[this->last->output_number];

	for (int i = 0; i < this->first->input_number; i++) {
		this->first->input_layer[i] = input[i];
	}

	NeuralStructure::traverse(*this->first, forward);

	for (int i = 0; i < last->output_number; i++) {
		error[i] = output[i] - this->last->output_layer[i];
	}

	NeuralStructure::traverse_by_error(*this->first, back_propagation, error);
}
