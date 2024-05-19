#include "../Include/Fully_connected_network.hpp"

Fully_connected_network::Fully_connected_network()
{
	Bias = 1.0f;
	Beta = 1.0f;
	Amount_of_data = 4;
	Number_of_epochs = 10;
	Number_of_input = 2;
	Number_of_output = 1;
	Number_of_hidden_layers = 1;
	Number_of_weights = 2;
	Total_number_of_neurons = 1;
	Learning_rate_factor = 1.0f;
	Open_filename = "Add_1000.txt";
	Save_filename = "Out_date.txt";
	Input_x1 = new std::vector<float>(0, 0);			
	Input_x2 = new std::vector<float>(0, 0);
	Output_y1 = new std::vector<float>(0, 0);
	Vector_of_weights = new std::vector<float>(Number_of_weights);
	Vector_of_neuron_values = new std::vector<float>(Total_number_of_neurons);
	MSE_value_vector_X = new std::vector<float>(Number_of_epochs);
	MSE_value_vector_Y = new std::vector<float>(Number_of_epochs);
}

template<class start, class stop, class name>
void Fully_connected_network::Display_results_counting_time(start Start, stop Stop, name name_of_function)
{
	std::cout << "Calculations " << name_of_function << " lasted: "
		<< std::chrono::duration_cast<std::chrono::milliseconds>(Stop - Start).count()
		<< " millisecond/s\n";
}

void Fully_connected_network::Read_data_MLP(std::vector<float>& Input_x1,
	std::vector<float>& Input_x2,
	std::vector<float>& Output_y1)
{
	// start counting time 
	const auto Start = std::chrono::high_resolution_clock::now();

	// ifstream only can open file
	std::ifstream file("../../../Data/" + Open_filename);

	float x1 = 0.0f;
	float x2 = 0.0f;
	float y1 = 0.0f;

	if (file)
	{
		for (int i = 0; !file.eof(); ++i)
		{
			file >> x1;
			file >> x2;
			file >> y1;
			Input_x1.push_back(x1);
			Input_x2.push_back(x2);
			Output_y1.push_back(y1);

			std::cout << Input_x1[i] << std::endl;
			std::cout << Input_x2[i] << std::endl;
			std::cout << Output_y1[i] << std::endl;
		}
		std::cout << "Before: " << std::endl;
		std::cout << "capacity(Input_x1): " << std::endl;
		std::cout << Input_x1.capacity() << std::endl;
		std::cout << "capacity(Input_x2): " << std::endl;
		std::cout << Input_x2.capacity() << std::endl;
		std::cout << "capacity(Output_y1): " << std::endl;
		std::cout << Output_y1.capacity() << std::endl;

		Input_x1.shrink_to_fit();
		Input_x2.shrink_to_fit();
		Output_y1.shrink_to_fit();

		std::cout << "After: " << std::endl;
		std::cout << "capacity(Input_x1): " << std::endl;
		std::cout << Input_x1.capacity() << std::endl;
		std::cout << "capacity(Input_x2): " << std::endl;
		std::cout << Input_x2.capacity() << std::endl;
		std::cout << "capacity(Output_y1): " << std::endl;
		std::cout << Output_y1.capacity() << std::endl;


		file.close();
	}
	else
	{
		std::cout << "Error, file not opened. Check if name of file is correct, or if this file exist.";
		exit(3);
	}



	// end counting time 
	const auto Stop = std::chrono::high_resolution_clock::now();

	Display_results_counting_time(Start, Stop, "Read_data_MLP");
}

void Fully_connected_network::Write_data_MLP(
	std::vector<float>& MSE_value_vector_X,
	std::vector<float>& MSE_value_vector_Y)
{
	// start counting time 
	const auto Start = std::chrono::high_resolution_clock::now();

	// ifstream only can open file
	std::ofstream file(Save_filename);

	if (file)
	{
		for (int i = 0; i < Number_of_epochs; ++i)
		{
			file << MSE_value_vector_X[i];
			file << " ";
			file << MSE_value_vector_Y[i];
			file << "\n";
		}
		file.close();
	}
	else
	{
		std::cout << "Error, file not created. Check if name of file is correct.";
		exit(3);
	}

	// end counting time 
	const auto Stop = std::chrono::high_resolution_clock::now();

	Display_results_counting_time(Start, Stop, "Write_data_MLP");
}

void Fully_connected_network::Min_max_unipolar_scaling(std::vector<float>& Vector)
{
	auto Start = std::chrono::high_resolution_clock::now();

	float max = *max_element(Vector.begin(), Vector.end());
	float min = *min_element(Vector.begin(), Vector.end());

	for (int i = 0; i < Amount_of_data; ++i)
	{
		Vector[i] = (Vector[i] - min) / (max - min);
	}

	for (int i = 0; i < Amount_of_data; ++i)
	{
		std::cout << "Wektor: " << Vector[i] << std::endl;
	}

	auto Stop = std::chrono::high_resolution_clock::now();

	Display_results_counting_time(Start, Stop, "Min_max_unipolar_scaling");
}

void Fully_connected_network::Min_max_bipolar_scaling(std::vector<float>& Vector)
{
	auto Start = std::chrono::high_resolution_clock::now();

	float max = *max_element(Vector.begin(), Vector.end());
	float min = *min_element(Vector.begin(), Vector.end());

	for (int i = 0; i < Amount_of_data; ++i)
	{
		Vector[i] = 2 * ((Vector[i] - min) / (max - min)) - 1;
	}

	for (int i = 0; i < Amount_of_data; ++i)
	{
		std::cout << "Wektor: " << Vector[i] << std::endl;
	}

	auto Stop = std::chrono::high_resolution_clock::now();

	Display_results_counting_time(Start, Stop, "Min_max_bipolar_scaling");
}

void Fully_connected_network::Reversal_min_max_unipolar_scaling()
{

}

void Fully_connected_network::Pseudo_random_numbers(std::vector<float>& Vector)
{
	auto Start = std::chrono::high_resolution_clock::now();

	srand(static_cast<unsigned int>(time(NULL)));

	for (int i = 0; i < Number_of_weights; ++i)
	{
		Vector[i] = (float)(rand() % 100) / 100;
		std::cout << "Iteration number: " << i << " " << Vector[i] << std::endl;
	}

	auto Stop = std::chrono::high_resolution_clock::now();

	Display_results_counting_time(Start, Stop, "Pseudo_random_numbers");
}

void Fully_connected_network::Calculating_the_network_MLP(std::vector<float>& Input_x1,
	std::vector<float>& Input_x2,
	std::vector<float>& Output_y1,
	std::vector<float>& Vector_of_weights,
	std::vector<float>& Vector_of_neuron_values,
	std::vector<float>& MSE_value_vector_X,
	std::vector<float>& MSE_value_vector_Y,
	float& Bias)
{
	auto Start = std::chrono::high_resolution_clock::now();

	// capacity reduction
	MSE_value_vector_X.shrink_to_fit();
	MSE_value_vector_Y.shrink_to_fit();

	Read_data_MLP(Input_x1, Input_x2, Output_y1);

	// changes for user interface (uniporar/bipolar)
	Min_max_unipolar_scaling(Input_x1);
	Min_max_unipolar_scaling(Input_x2);
	Min_max_unipolar_scaling(Output_y1);

	Pseudo_random_numbers(Vector_of_weights);

	float MSE = 0;
	int e = 0;
	int i = 0;

	for (e = 0 ; e < Number_of_epochs; ++e)
	{
		MSE = 0;

		for (i = 0 ; i < Amount_of_data; ++i)
		{
			Vector_of_neuron_values[0] = Unipolar_sigmoidal_function((Input_x1[i] *
				Vector_of_weights[0]) + (Input_x2[i] * Vector_of_weights[1]) + Bias);

			// last neuron error
			float error = Output_y1[i] - Vector_of_neuron_values[0];

			// new values of weight

			Vector_of_weights[0] = Vector_of_weights[0] + Learning_rate_factor * error *
				(Beta * Vector_of_neuron_values[0] * (1 - Vector_of_neuron_values[0])) * Input_x1[i];

			Vector_of_weights[1] = Vector_of_weights[1] + Learning_rate_factor * error *
				(Beta * Vector_of_neuron_values[0] * (1 - Vector_of_neuron_values[0])) * Input_x2[i];

			Bias = Bias + Learning_rate_factor * error *
				(Beta * Vector_of_neuron_values[0] * (1 - Vector_of_neuron_values[0]));

			MSE += static_cast<float>(pow((Vector_of_neuron_values[0] - Output_y1[i]), 2));
		}

		MSE = MSE / Amount_of_data;

		float iterator = (e + 1);			// float because MSE_value_vector_x have float type

		std::cout << "MSE(" << iterator << "): " << MSE << std::endl;

		MSE_value_vector_X.push_back(iterator);
		MSE_value_vector_Y.push_back(MSE);
	}

	Write_data_MLP(MSE_value_vector_X, MSE_value_vector_Y);

	auto Stop = std::chrono::high_resolution_clock::now();

	Display_results_counting_time(Start, Stop, "Calculating_the_network_MLP");
}

float Fully_connected_network::Unipolar_sigmoidal_function(float e)
{
	return static_cast<float>(1.0 / (1.0 + exp(-Beta * e)));
}

void Fully_connected_network::Display_results_for_MLP()
{
	std::cout << &Input_x1[0] << std::endl;
	std::cout << &Input_x2[0] << std::endl;
	std::cout << &Output_y1[0] << std::endl;
	std::cout << &Vector_of_weights[0] << std::endl;
	std::cout << &Vector_of_neuron_values[0] << std::endl;
	std::cout << &Bias << std::endl;


	Calculating_the_network_MLP(*&Input_x1[0],
		*&Input_x2[0],
		*&Output_y1[0],
		*&Vector_of_weights[0],
		*&Vector_of_neuron_values[0],
		*&MSE_value_vector_X[0],
		*&MSE_value_vector_Y[0],
		*&Bias);

}
