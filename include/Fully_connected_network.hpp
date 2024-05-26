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
	bool Diag;												// Diagnostic mode
	int Amount_of_data;										// delete this?
	int Number_of_epochs;									// user specifed
	int Number_of_input;									// defined in txt. file header
	int Number_of_output;									// defined in txt. file header
	int Number_of_hidden_layers;							// user specifed
	int Number_of_weights;
	int Total_number_of_neurons;
	float Bias;
	float Beta;
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
	// auto Start, Stop = value now() function of chrono library
	// auto name = ID of this counting time
	// const char[] = unit (Unit of time) : 0 - nano, 1 - micro, 
	// 2 - mili, 3 - seconds, 4 - minutes, 5 - hours
	template<class start, class stop, class name, class unit>
	void Display_results_counting_time(start Start, stop Stop, name name_of_function, unit unit_of_time);

	// reading input data from file
	void Read_data_MLP(std::vector<std::vector<float>>& Vector_of_data);

	// write output data to file
	void Write_data_MLP(
		std::vector<float>& MSE_value_vector_X,
		std::vector<float>& MSE_value_vector_Y);

	// values from 0 to 1
	void Min_max_unipolar_scaling(std::vector<std::vector<float>>& Vector_of_data);

	// values from -1 to 1
	void Min_max_bipolar_scaling(std::vector<std::vector<float>>& Vector_of_data);

	// ???
	void Reversal_min_max_unipolar_scaling(std::vector<std::vector<float>>& Vector_of_data);

	// for first weights wector
	void Pseudo_random_numbers(std::vector<std::vector<float>>& Vector_of_data);

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

	template<class Vec_of_data, class info>
	void Print_the_capacity_of_the_vector_of_data(Vec_of_data Vector_of_data, info information);

	void Print_the_vector_of_data(std::vector<std::vector<float>>& Vector_of_data);

	void Print_the_MIN_MAX_and_individual_values(std::vector<std::vector<float>>& Vector_of_data,
		float min, float max, int iterator);
};
