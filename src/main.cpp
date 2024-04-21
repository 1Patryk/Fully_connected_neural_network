#include "../Include/Fully_connected_network.hpp"

template<class start, class stop>
void Display_results_counting_time(start Start, stop Stop, std::string namefunction)
{
	std::cout << "Calculations '" << namefunction << "' lasted: "
		<< std::chrono::duration_cast<std::chrono::milliseconds>(Stop - Start).count()
		<< " millisecond/s\n" << std::endl;
	std::cout << "Calculations lasted: "
		<< (std::chrono::duration_cast<std::chrono::milliseconds>(Stop - Start).count()) / 1000
		<< " second/s\n" << std::endl;
}

int main()
{

	Fully_connected_network DATA;

	DATA.Display_results_for_MLP_x_x();
}







// Add to program value like: number of epochs, amount of data, from file, not from manualy-writen constructor.