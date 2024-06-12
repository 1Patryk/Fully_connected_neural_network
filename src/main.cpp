#include "../Include/Fully_connected_network.hpp"

int main()
{
	auto Start = std::chrono::high_resolution_clock::now();

	Fully_connected_network DATA;

	DATA.Diag = false;		// Diagnostic mode						

	DATA.Calculating_the_network_MLP();

	//DATA.Display_results_for_MLP();

	auto Stop = std::chrono::high_resolution_clock::now();
	DATA.Display_results_counting_time(Start, Stop, "Cumulatively", 2);
}


// Add to program value like: number of epochs, amount of data, from file, not from manualy-writen constructor.

// jumble and validation
// after that, count up on paper all network