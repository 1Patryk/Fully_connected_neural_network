#include "../Include/Fully_connected_network.hpp"

int main()
{
	Fully_connected_network DATA;

	DATA.Read_data_MLP(*DATA.Vector_of_data);
	//DATA.Display_results_for_MLP();
}


// Add to program value like: number of epochs, amount of data, from file, not from manualy-writen constructor.