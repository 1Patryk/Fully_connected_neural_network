#include "../Include/Fully_connected_network.hpp"

int main()
{
	auto Start = std::chrono::high_resolution_clock::now();

	Fully_connected_network DATA;

	DATA.Diag = false;		// Diagnostic mode						
	DATA.Read_data_MLP(*DATA.Vector_of_data);
	DATA.Min_max_bipolar_scaling(*DATA.Vector_of_data);
	DATA.Create_vector_of_neurons_values(*DATA.Vector_of_neuron_values, *DATA.Number_of_neuros_in_hidden_layers);
	DATA.Create_vector_of_weights(*DATA.Vector_of_weights, *DATA.Vector_of_neuron_values);
	DATA.Create_vector_of_bias(*DATA.Vector_of_bias_weights, *DATA.Vector_of_neuron_values);
	DATA.Pseudo_random_numbers(*DATA.Vector_of_weights, *DATA.Vector_of_bias_weights, *DATA.Range_of_pseudo_numbers_values);


	//DATA.Display_results_for_MLP();

	auto Stop = std::chrono::high_resolution_clock::now();
	DATA.Display_results_counting_time(Start, Stop, "Cumulatively", 2);
}


// Add to program value like: number of epochs, amount of data, from file, not from manualy-writen constructor.