#include "../include/Fully_connected_network.hpp"

int main()
{
	Fully_connected_network DATA;

	std::string *Open_filename = new std::string{"../Data/Iris.txt"};
	std::string *Output_filename_path = new std::string{"../Output_data_(MSE)/"};

	DATA.Calculating_the_network_MLP(Open_filename, Output_filename_path);

}