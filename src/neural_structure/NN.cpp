/*
 * NN.cpp
 *
 *  Created on: Jun 13, 2020
 *      Author: khan
 */

#include "NN.h"
#include "../utils/MemoryUtils.h"
#include "../utils/MathUtils.h"

void NN::init_first(int input_number, int output_number) {

	this->input_number = input_number;
	this->output_number = output_number;
	MemoryUtils::allocate_double_vector(this->input_layer, this->input_number);
	MemoryUtils::allocate_double_vector(this->net_input, this->output_number);
	MemoryUtils::allocate_double_vector(this->output_layer,
			this->output_number);
	//+1 for Bias
	MemoryUtils::allocate_double_matrix(this->weight_matrix,
			this->input_number + 1, this->output_number);
	this->next = NULL;
	this->prev = NULL;

}

void NN::hook_next(int out_number) {
	this->next = new NN;
	this->next->input_number = this->output_number;
	this->next->output_number = out_number;
	this->next->input_layer = this->output_layer;
	MemoryUtils::allocate_double_vector(this->next->net_input,
			this->next->output_number);
	MemoryUtils::allocate_double_vector(this->next->output_layer,
			this->next->output_number);
	//+1 for Bias
	MemoryUtils::allocate_double_matrix(this->next->weight_matrix,
			this->next->input_number + 1, this->next->output_number);
	this->next->prev = this;
}
