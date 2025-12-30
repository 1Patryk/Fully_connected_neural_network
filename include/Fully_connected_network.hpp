#pragma once

#include <iostream>				// adding standard input/output library
#include <filesystem>			// operations on file systems (since c++ 17)
#include <vector>				// STL - Standard template library
#include <fstream>				// adding posibility connect with .txt files
#include <chrono>				// time executive in program 
#include <sstream> 
#include <ctime>				// ...
#include <algorithm>			// min - max scaler
#include <string>
#include <random>				// pseudo random numbers
#include <cmath>				// absolute values

class Fully_connected_network
{
private:

	bool Diag;														// Diagnostic mode
	int* Number_of_epochs;											// user specifed
	int* Number_of_input;											// defined in txt. file header
	int* Number_of_output;											// defined in txt. file header
	int* Number_of_hidden_layers;									// user specifed
	int* Number_of_layers;
	int* Number_of_weights;
	int* Total_number_of_neurons;
	int* Train;
	int* Validation;
	float* Beta;
	float* Bias;
	float* Learning_rate_factor;

	std::string* Open_filename;
    std::string* Output_filename_path;
	std::vector <int> Number_of_neurons_in_hidden_layers;
	std::vector <int> Activation_functions;
	std::vector<std::vector<float>> Vector_of_data;
	std::vector<float> Range_of_pseudo_numbers_values;
	std::vector<float> MAPE_value_training;
	std::vector<float> MAPE_value_validation;

	std::vector<float> Max_training_value_vector;
	std::vector<float> Min_training_value_vector;
	std::vector<float> Max_validation_value_vector;
	std::vector<float> Min_validation_value_vector;

	std::vector<float>& Max_training_value_vector_ref = Max_training_value_vector;
	std::vector<float>& Min_training_value_vector_ref = Min_training_value_vector;
	std::vector<float>& Max_validation_value_vector_ref = Max_validation_value_vector;
	std::vector<float>& Min_validation_value_vector_ref = Min_validation_value_vector;

	std::vector <int>& Number_of_neurons_in_hidden_layers_ref = Number_of_neurons_in_hidden_layers;
	std::vector<std::vector<float>>& Vector_of_data_ref = Vector_of_data;
	std::vector<float>& Range_of_pseudo_numbers_values_ref = Range_of_pseudo_numbers_values;
	std::vector<float>& MAPE_value_training_ref = MAPE_value_training;
	std::vector<float>& MAPE_value_validation_ref = MAPE_value_validation;

	// TRAINING

	std::vector<std::vector<float>> Vector_of_data_training;
	std::vector<std::vector<float>> Vector_of_neuron_values_training;
	std::vector<float> Vector_of_neuron_values_one_dim_training;		// one dimensional Vector_of_neuron_values
	std::vector<float> Vector_of_weights_training;
	std::vector<float> Vector_of_bias_weights_training;
	std::vector<float> Vector_of_error_values_training;

	// TRAINING (REFERENCE)

	std::vector<std::vector<float>>& Vector_of_data_training_ref = Vector_of_data_training;
	std::vector<std::vector<float>>& Vector_of_neuron_values_training_ref = Vector_of_neuron_values_training;
	std::vector<float>& Vector_of_neuron_values_one_dim_training_ref = Vector_of_neuron_values_one_dim_training;
	std::vector<float>& Vector_of_weights_training_ref = Vector_of_weights_training;
	std::vector<float>& Vector_of_bias_weights_training_ref = Vector_of_bias_weights_training;
	std::vector<float>& Vector_of_error_values_training_ref = Vector_of_error_values_training;

	// VALIDATION

	std::vector<std::vector<float>> Vector_of_data_validation;
	std::vector<std::vector<float>> Vector_of_neuron_values_validation;
	std::vector<float> Vector_of_neuron_values_one_dim_validation;		// one dimensional Vector_of_neuron_values
	std::vector<float> Vector_of_weights_validation;
	std::vector<float> Vector_of_bias_weights_validation;
	std::vector<float> Vector_of_error_values_validation;

	// VALIDATION (REFERENCE)

	std::vector<std::vector<float>>& Vector_of_data_validation_ref = Vector_of_data_validation;
	std::vector<std::vector<float>>& Vector_of_neuron_values_validation_ref = Vector_of_neuron_values_validation;
	std::vector<float>& Vector_of_neuron_values_one_dim_validation_ref = Vector_of_neuron_values_one_dim_validation;
	std::vector<float>& Vector_of_weights_validation_ref = Vector_of_weights_validation;
	std::vector<float>& Vector_of_bias_weights_validation_ref = Vector_of_bias_weights_validation;
	std::vector<float>& Vector_of_error_values_validation_ref = Vector_of_error_values_validation;

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
    void Read_data_MLP(std::string* Open_filename);

	// swap input data 
	void Swap_data();

	// dividing data to train, test and validation sets.
	void Divide_data_to_training_and_validation();

	// values from 0 to 1
	void Min_max_unipolar_scaling(
		std::vector<std::vector<float>>& Vector_of_data,
		std::string name_of_vector,
		std::vector<float>& Min_data_value_vector,
		std::vector<float>& Max_data_value_vector);

	// values from -1 to 1
	void Min_max_bipolar_scaling(
		std::vector<std::vector<float>>& Vector_of_data,
		std::string name_of_vector,
		std::vector<float>& Min_data_value_vector,
		std::vector<float>& Max_data_value_vector);

	// create vector of neuron values
	void Create_vector_of_neurons_values(
		std::vector<std::vector<float>>& Vector_of_neuron_values,
		std::string name_of_vector);

	void Create_vector_of_weights(std::vector<float>& Vector_of_weights,
		std::vector<std::vector<float>>& Vector_of_neuron_values,
		std::string name_of_vector);

	void Create_vector_of_bias(std::vector<float>& Vector_of_bias_weights,
		std::vector<std::vector<float>>& Vector_of_neuron_values,
		std::string name_of_vector);

	// for first weights wector
	void Pseudo_random_numbers(std::vector<float>& Vector,
		std::string name_of_vector);

	// main function of Fully_connected_network
    void Calculating_the_network_MLP(std::string* Open_filename, std::string* Output_filename_path);

	// forward propagation
	void Forward_propagation_the_network_MLP
	(
		std::vector<std::vector<float>>& Vector_of_data,
		std::vector<std::vector<float>>& Vector_of_neuron_values,
		std::vector<float>& Vector_of_weights,
		std::vector<float>& Vector_of_bias_weights,
		int it_data,
		int it_weight,
		int it_bias,
		int it_prev_layer
	);

	// backpropagation
	void Backpropagation_the_network_MLP
	(
		std::vector<std::vector<float>>& Vector_of_data,
		std::vector<std::vector<float>>& Vector_of_neuron_values,
		std::vector<float>& Vector_of_neuron_values_one_dim,
		std::vector<float>& Vector_of_weights,
		std::vector<float>& Vector_of_bias_weights,
		std::vector<float>& Vector_of_error_values,
		std::vector<float>& MAPE_value,
		int it_data,
		int it_weight,
		int it_bias,
		int it_prev_layer,
		int it_error,
		int it_iterator_one_dim,
		int it_value_neuron,
		int it_back_neuron,
		int epoch
	);

	// linear activation funcion
	float Linear_activation_function(float e);

	// values from 0 to 1 
	float Unipolar_sigmoidal_function(float e);

	// values from -1 to 1 
	float Bipolar_sigmoidal_function(float e);

	// test
	void Testing_network
	(
		std::vector<std::vector<float>>& Vector_of_data,
		std::vector<std::vector<float>>& Vector_of_neuron_values,
		std::vector<float>& Vector_of_weights,
		std::vector<float>& Vector_of_bias_weights,
		int it_data,
		int it_weight,
		int it_bias,
		int it_prev_layer
	);

	// write output data to file
    void Write_data_MLP(std::string* Output_filename_path);

	// destructor
	~Fully_connected_network();
};