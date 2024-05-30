#include "../Include/Fully_connected_network.hpp"

int main()
{
	auto Start = std::chrono::high_resolution_clock::now();

	Fully_connected_network DATA;

	DATA.Diag = false;		// Diagnostic mode						

	DATA.Calculating_the_network_MLP(
		*DATA.Number_of_neurons_in_hidden_layers,
		*DATA.Vector_of_data,
		*DATA.Vector_of_neuron_values,
		*DATA.Vector_of_weights,
		*DATA.Vector_of_bias_weights, 
		*DATA.Vector_of_error_values,
		*DATA.MSE_value_vector_X,
		*DATA.MSE_value_vector_Y);

	//DATA.Display_results_for_MLP();

	auto Stop = std::chrono::high_resolution_clock::now();
	DATA.Display_results_counting_time(Start, Stop, "Cumulatively", 2);
}


// Add to program value like: number of epochs, amount of data, from file, not from manualy-writen constructor.

// jumble and validation
// after that, count up on paper all network