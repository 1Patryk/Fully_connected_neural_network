#include "../Include/Fully_connected_network.hpp"

int main(int argc, char* argv[])
{
	auto Start = std::chrono::high_resolution_clock::now();

	Fully_connected_network DATA;				

	DATA.Calculating_the_network_MLP();

	//DATA.Display_results_for_MLP();

	auto Stop = std::chrono::high_resolution_clock::now();
	DATA.Display_results_counting_time(Start, Stop, "Cumulatively", 2);
}