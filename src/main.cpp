#include "../Include/Fully_connected_network.hpp"

int main()
{
	auto Start = std::chrono::high_resolution_clock::now();

	Fully_connected_network DATA;

	DATA.Diag = true;		// Diagnostic mode						
	DATA.Read_data_MLP(*DATA.Vector_of_data);
	DATA.Min_max_bipolar_scaling(*DATA.Vector_of_data);



	//DATA.Display_results_for_MLP();

	auto Stop = std::chrono::high_resolution_clock::now();
	DATA.Display_results_counting_time(Start, Stop, "Cumulatively", 2);
}


// Add to program value like: number of epochs, amount of data, from file, not from manualy-writen constructor.