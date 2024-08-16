#include "../Include/Fully_connected_network.hpp"

int main(int argc, char *argv[])
{
	Fully_connected_network DATA;

	std::string *Open_filename = new std::string{"../Data/Add_1000.txt"};
	std::string *Output_filename_path = new std::string{"../Output_data_(MSE)/"};

	DATA.Calculating_the_network_MLP(Open_filename, Output_filename_path);

	// DATA.Display_results_for_MLP();
}