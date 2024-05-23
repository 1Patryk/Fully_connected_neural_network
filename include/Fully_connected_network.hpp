#pragma once

#include <iostream>				// adding standard input/output library
#include <vector>				// STL - Standard template library
#include <fstream>				// adding posibility connect with .txt files
#include <chrono>				// time executive in program 
#include <ctime>				// ...
#include <algorithm>			// min - max scaler
#include <string>

class Fully_connected_network
{
	//private:
public:
	float Bias;
	float Beta;
	int Amount_of_data;
	int Number_of_epochs;
	int Number_of_input;
	int Number_of_output;
	int Number_of_hidden_layers;
	int Number_of_weights;
	int Total_number_of_neurons;
	float Learning_rate_factor;
	std::string Open_filename;
	std::string Save_filename;
	std::vector<std::vector<float>>* Vector_of_data;
	std::vector<float>* Vector_of_weights;
	std::vector<float>* Vector_of_neuron_values;
	std::vector<float>* MSE_value_vector_X;
	std::vector<float>* MSE_value_vector_Y;

public:

	// constructor
	Fully_connected_network();

	// display times wich during from start to end function 
	template<class start, class stop, class name>
	void Display_results_counting_time(start Start, stop Stop, name name_of_function);

	// reading input data from file
	void Read_data_MLP(std::vector<std::vector<float>>& Vector_of_data);

	// write output data to file
	void Write_data_MLP(
		std::vector<float>& MSE_value_vector_X,
		std::vector<float>& MSE_value_vector_Y);

	// values from 0 to 1
	void Min_max_unipolar_scaling(std::vector<std::vector<float>>* Vector_of_data);

	// values from 0 to -1
	void Min_max_bipolar_scaling(std::vector<std::vector<float>>* Vector_of_data);

	void Reversal_min_max_unipolar_scaling();

	// for first weights wector
	void Pseudo_random_numbers(std::vector<std::vector<float>>* Vector_of_data);

	// forward and back propagation
	void Calculating_the_network_MLP(std::vector<std::vector<float>>* Vector_of_data,
		std::vector<float>& Vector_of_weights,
		std::vector<float>& Vector_of_neuron_values,
		std::vector<float>& MSE_value_vector_X,
		std::vector<float>& MSE_value_vector_Y,
		float& Bias);

	// values from 0 to 1 
	float Unipolar_sigmoidal_function(float e);

	// display results in main function
	void Display_results_for_MLP();



	// Diagnostic functions

	void Print_Vector_of_data(std::vector<std::vector<float>>& Vector_of_data, std::string information);
};
