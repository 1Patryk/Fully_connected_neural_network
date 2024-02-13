#pragma once

#include <iostream>				// adding standard input/output library
#include <vector>				// STL - Standard template library
#include <fstream>				// adding posibility connect with .txt files
#include <chrono>				// time executive in program 
#include <ctime>				// ...
#include "pbPlots.hpp"			// library for drawn plots
#include "supportLib.hpp"		// ...

class Fully_connected_network
{
private:

	double Bias;
	double Beta;
	int Amount_of_data;
	int Number_of_epochs;
	int Number_of_input;
	int Number_of_output;
	int Number_of_hidden_layers;
	int Number_of_weights;
	int Total_number_of_neurons;
	float Learning_rate_factor;
	std::string filename;
	std::string plotname;
	std::vector<double>* Input_x1;
	std::vector<double>* Input_x2;
	std::vector<double>* Output_y1;
	std::vector<double>* Vector_of_weights;
	std::vector<double>* Vector_of_neuron_values;

public:

	// constructor
	Fully_connected_network();

	// display times wich during from start to end function 
	template<class start, class stop>
	void Display_results_counting_time(start Start, stop Stop);

	// reading input data from file
	void Read_data_MLP_x_x(std::vector<double>& Input_x1,
		std::vector<double>& Input_x2,
		std::vector<double>& Output_y1);

	// values from 0 to 1
	void Min_max_unipolar_scaling(std::vector<double>& Vector);

	// values from 0 to -1
	void Min_max_bipolar_scaling(std::vector<double>& Vector);

	void Reversal_min_max_unipolar_scaling();

	// for first weights wector
	void Pseudo_random_numbers(std::vector<double>& Vector);

	// forward and back propagation
	void Calculating_the_network_MLP_X_X(std::vector<double>& Input_x1,
		std::vector<double>& Input_x2,
		std::vector<double>& Output_y1,
		std::vector<double>& Vector_of_weights,
		std::vector<double>& Vector_of_neuron_values,
		double& Bias);

	// creating file with plot
	int Drawning_plot(std::vector<double>* Vector_of_neuron_values);

	// values from 0 to 1 
	double Unipolar_sigmoidal_function(double e);

	// display results in main function
	void Display_results_for_MLP_x_x();
};					
