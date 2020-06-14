//============================================================================
// Name        : neural_network.cpp
// Author      : Khan
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "utils/MathUtils.h"
#include "utils/MemoryUtils.h"
#include "neural_structure/NeuralStructure.h"
#include <stdlib.h>
using namespace std;

void print_matrix(double **matrix, int m, int n) {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void print_vector(double *vector, int m) {
	for (int i = 0; i < m; i++) {
		cout << vector[i] << " ";
	}
	cout << endl;
}

void initialize_double_matrix(double **matrix, int m, int n) {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			matrix[i][j] = 1;
		}
	}
}

void print_full_nn(NN *item) {
	cout << "input layer" << endl;
	print_vector(item->input_layer, item->input_number);
	cout << "weight matrix" << endl;
	print_matrix(item->weight_matrix, item->input_number + 1,
			item->output_number);
	cout << "net layer" << endl;
	print_vector(item->net_input, item->output_number);
	cout << "output layer" << endl;
	print_vector(item->output_layer, item->output_number);
}

void epoch(double *input, double *output) {

}

int main() {
	int arr[] = { 3, 4, 3 };
	double input[] = { 0.1, 0.9, 0.7 };
	double output[] = { 0.9, 0.1, 0.6 };
	NeuralStructure ns;
	ns.create_layers(arr, 3);
	NeuralStructure::traverse(*ns.first,
			NeuralStructure::initialize_weight_matrix);
	NeuralStructure::traverse(*ns.first, print_full_nn);
	cout << "----------------------------" << endl;
	for (int i = 0; i < 100; i++) {
		ns.epoch(input, output);
	}
	NeuralStructure::traverse(*ns.first, print_full_nn);

	return 0;
}
