/*
 * NeuralStructure.cpp
 *
 *  Created on: Jun 13, 2020
 *      Author: khan
 */

#include "NeuralStructure.h"
#include "../utils/MathUtils.h"

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
	this->last = temp;
}

void NeuralStructure::traverse(NN first, void (*callback)(NN*), bool next) {
	NN *temp = &first;
	while (temp != nullptr) {
		callback(temp);
		if (next) {
			temp = temp->next;
		} else {
			temp = temp->prev;
		}
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

void NeuralStructure::initialize_weight_matrix(NN *item) {
	for (int i = 0; i < item->input_number + 1; i++) {
		for (int j = 0; j < item->output_number; j++) {
			//TODO: choose better approach for initializing nets (random etc.)
			item->weight_matrix[i][j] = 0.05;
		}
	}
}

void NeuralStructure::backward(NN *item) {
	//clear sigma
	for (int i = 0; i < item->input_number; i++) {
		item->sigma[i] = 0.0;
	}

	for (int i = 0; i < item->input_number; i++) {
		for (int j = 0; j < item->output_number; j++) {
			item->sigma[i] += MathUtils::sigmoid(item->output_layer[j], true)
					* item->weight_matrix[i][j] * item->next->sigma[j];
		}
	}

	for (int i = 0; i < item->input_number; i++) {
		for (int j = 0; j < item->output_number; j++) {
			item->weight_matrix[i][j] -= LEARNING_RATE * item->input_layer[i]
					* item->next->sigma[j];
		}
	}

	// BIAS case
	for (int i = 0; i < item->output_number; i++) {
		item->weight_matrix[item->input_number][i] -= LEARNING_RATE * item->BIAS
				* item->next->sigma[i];
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
	//Back Prop.
	for (int i = 0; i < this->last->input_number; i++) {
		for (int j = 0; j < this->last->output_number; j++) {
			this->last->sigma[i] += MathUtils::sigmoid(
					this->last->output_layer[j], true)
					* this->last->weight_matrix[i][j] * (-1) * error[j];
		}
	}
	if (this->last->prev != nullptr) {
		NeuralStructure::traverse(*this->last->prev, backward, false);
	}

	for (int i = 0; i < this->last->input_number; i++) {
		for (int j = 0; j < this->last->output_number; j++) {
			this->last->weight_matrix[i][j] -= LEARNING_RATE
					* this->last->input_layer[i] * (-1) * error[j];
		}
	}

	// BIAS case
	for (int i = 0; i < this->last->output_number; i++) {
		this->last->weight_matrix[this->last->input_number][i] -= LEARNING_RATE
				* this->last->BIAS * (-1) * error[i];
	}

}
