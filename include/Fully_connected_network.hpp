#pragma once

#include <iostream>				// adding standard input/output library
#include <vector>				// STL - Standard template library
#include <fstream>				// adding posibility connect with .txt files
#include <chrono>				// time executive in program 
#include <ctime>				// ...
#include <algorithm>			// min - max scaler
#include <string>
#include <random>				// pseudo random numbers

class Fully_connected_network
{
	//private:
public:
	bool Diag;														// Diagnostic mode
	int* Amount_of_data;												// delete this?
	int* Number_of_epochs;											// user specifed
	int* Number_of_input;											// defined in txt. file header
	int* Number_of_output;											// defined in txt. file header
	int* Number_of_hidden_layers;									// user specifed
	int* Number_of_layers;
	int* Number_of_weights;
	int* Total_number_of_neurons;
	int* Train;
	int* Test;
	int* Validation;
	float* Beta;
	float* Bias;
	float* Learning_rate_factor;
	std::string* Open_filename;
	std::string* Save_filename;
	std::vector <int>* Number_of_neurons_in_hidden_layers;
	std::vector<std::vector<float>>* Vector_of_data;
	std::vector<float>* Range_of_pseudo_numbers_values;
	std::vector<float>* MSE_value_vector_X;
	std::vector<float>* MSE_value_vector_Y;


	std::vector<std::vector<float>>* Vector_of_data_train;
	std::vector<std::vector<float>>* Vector_of_neuron_values_train;
	std::vector<float>* Vector_of_neuron_values_one_dim_train;		// one dimensional Vector_of_neuron_values
	std::vector<float>* Vector_of_error_values_train;
	std::vector<float>* Vector_of_weights_train;
	std::vector<float>* Vector_of_bias_weights_train;

	std::vector<std::vector<float>>* Vector_of_data_validation;
	std::vector<std::vector<float>>* Vector_of_neuron_values_validation;
	std::vector<float>* Vector_of_neuron_values_one_dim_validation;		// one dimensional Vector_of_neuron_values
	std::vector<float>* Vector_of_error_values_validation;
	std::vector<float>* Vector_of_weights_validation;
	std::vector<float>* Vector_of_bias_weights_validation;


	std::vector<std::vector<float>>* Vector_of_data_test;
	
public:

	// constructor
	Fully_connected_network();

	// display times wich during from start to end function 
	// auto Start, Stop = value now() function of chrono library
	// auto name = ID of this counting time
	// const char[] = unit (Unit of time) : 0 - nano, 1 - micro, 
	// 2 - mili, 3 - seconds, 4 - minutes, 5 - hours
	template<class start, class stop, class name, class unit>
	void Display_results_counting_time(start Start, stop Stop, name name_of_function, unit unit_of_time);

	// reading input data from file
	void Read_data_MLP(
		std::vector<std::vector<float>>& Vector_of_data);

	// write output data to file
	void Write_data_MLP(
		std::vector<float>& MSE_value_vector_X,
		std::vector<float>& MSE_value_vector_Y);

	// swap input data (every piece of data together)
	void Swap_data(std::vector<std::vector<float>>& Vector_of_data);

	// dividing data to train, test and validation sets. 3 next parameters is a 
	// participations percent  on Vector_of_data (unit %)
	void Divide_data_to_training_test_and_validation(
		std::vector<std::vector<float>>& Vector_of_data,
		std::vector<std::vector<float>>& Vector_of_data_train,
		std::vector<std::vector<float>>& Vector_of_data_validation,
		std::vector<std::vector<float>>& Vector_of_data_test,
		int Train,
		int Test,
		int Validation);

	// values from 0 to 1
	void Min_max_unipolar_scaling(std::vector<std::vector<float>>& Vector_of_data);

	// values from -1 to 1
	void Min_max_bipolar_scaling(std::vector<std::vector<float>>& Vector_of_data);

	// ???
	void Reversal_min_max_unipolar_scaling(std::vector<std::vector<float>>& Vector_of_data);

	// create vector of neuron values
	void Create_vector_of_neurons_values(std::vector<std::vector<float>>& Vector_of_neuron_values, 
		std::vector <int>& Number_of_neuros_in_hidden_layers);

	void Create_vector_of_weights(std::vector<float>& Vector_of_weights, 
		std::vector<std::vector<float>>& Vector_of_neuron_values);

	void Create_vector_of_bias(std::vector<float>& Vector_of_bias_weights,
		std::vector<std::vector<float>>& Vector_of_neuron_values);

	// for first weights wector
	void Pseudo_random_numbers(std::vector<float>& Vector_of_weights,
		std::vector<float>& Vector_of_bias_weights, std::vector<float>& Range_of_pseudo_numbers_values);

	// main function of Fully_connected_network
	void Calculating_the_network_MLP(
		//std::vector <int> Number_of_neurons_in_hidden_layers,
		//std::vector<std::vector<float>>& Vector_of_data,
		//std::vector<std::vector<float>>& Vector_of_data_validation,
		//std::vector<std::vector<float>>& Vector_of_data_test,
		//std::vector<std::vector<float>>& Vector_of_neuron_values,
		//std::vector<float>& Vector_of_neuron_values_one_dim,
		//std::vector<float>& Vector_of_error_values,
		//std::vector<float>& Vector_of_weights,
		//std::vector<float>& Vector_of_bias_weights,
		//std::vector<float>& MSE_value_vector_X,
		//std::vector<float>& MSE_value_vector_Y,
		//int Train,
		//int Test,
		//int Validation
		);

	// values from 0 to 1 
	float Unipolar_sigmoidal_function(float e);

	// display results in main function
	void Display_results_for_MLP();



	// Diagnostic functions

	void Print_the_vector_of_data(
		std::vector<std::vector<float>>& Vector_of_data,
		std::string name_of_vector);

	void Print_the_MIN_MAX_and_individual_values(
		std::vector<std::vector<float>>& Vector_of_data,
		float min, float max, int iterator);

	void Capacity_of_Vector_of_neuron_values(
		std::vector<std::vector<float>>& Vector_of_neuron_values,
		int iterator);

	void Print_pseudo_random_numbers(
		std::vector<float>& Vector_of_weights,
		std::vector<float>& Vector_of_bias_weights);
};
