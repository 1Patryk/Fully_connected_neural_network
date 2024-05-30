#include "../Include/Fully_connected_network.hpp"

Fully_connected_network::Fully_connected_network()
{
	Diag = false;
	Amount_of_data = 4;
	Number_of_epochs = 10;
	Number_of_input = 0;
	Number_of_output = 0;
	Number_of_hidden_layers = 3;
	Number_of_weights = 0;
	Total_number_of_neurons = 1;
	Beta = 1.0f;
	Learning_rate_factor = 1.0f;
	Open_filename = "Add_1000.txt";
	Save_filename = "Out_date.txt";
	Number_of_neuros_in_hidden_layers = new std::vector<int>{ 5, 3, 8 };
	Vector_of_data = new std::vector<std::vector<float>>(0);
	Vector_of_neuron_values = new std::vector<std::vector<float>> (Number_of_hidden_layers + 2);
	Vector_of_weights = new std::vector<float>(0, 0);
	Vector_of_bias_weights = new std::vector<float>(0, 0);
	Range_of_pseudo_numbers_values = new std::vector<float>{ -0.5, 0.5};
	MSE_value_vector_X = new std::vector<float>(Number_of_epochs);
	MSE_value_vector_Y = new std::vector<float>(Number_of_epochs);
}

template<class start, class stop, class name, class unit>
void Fully_connected_network::Display_results_counting_time(start Start, stop Stop, name name_of_function, unit unit_of_time)
{
	switch (unit_of_time)
	{
	case(0):
		std::cout << "Calculations " << name_of_function << " lasted: "
			<< std::chrono::duration_cast<std::chrono::nanoseconds>(Stop - Start).count()
			<< " nanosecond/s\n";
		break;

	case(1):
		std::cout << "Calculations " << name_of_function << " lasted: "
			<< std::chrono::duration_cast<std::chrono::microseconds>(Stop - Start).count()
			<< " microsecond/s\n";
		break;
	case(2):
		std::cout << "Calculations " << name_of_function << " lasted: "
			<< std::chrono::duration_cast<std::chrono::milliseconds>(Stop - Start).count()
			<< " milisecond/s\n";
		break;
	case(3):
		std::cout << "Calculations " << name_of_function << " lasted: "
			<< std::chrono::duration_cast<std::chrono::seconds>(Stop - Start).count()
			<< " second/s\n";
		break;
	case(4):
		std::cout << "Calculations " << name_of_function << " lasted: "
			<< std::chrono::duration_cast<std::chrono::minutes>(Stop - Start).count()
			<< " minute/s\n";
		break;
	case(5):
		std::cout << "Calculations " << name_of_function << " lasted: "
			<< std::chrono::duration_cast<std::chrono::hours>(Stop - Start).count()
			<< " hour/s\n";
		break;
	default:
		std::cout << "Invalid unit of time! " << std::endl;
		break;
	}
}

void Fully_connected_network::Read_data_MLP(std::vector<std::vector<float>>& Vector_of_data)
{
	// start counting time 
	const auto Start = std::chrono::high_resolution_clock::now();

	// ifstream only can open file
	std::ifstream file("../../../Data/" + Open_filename);

	float One_piece_of_data = 0.0f;

	if (file)
	{
		// read 2 int of data which specifying amound of input and output
		file >> One_piece_of_data;
		Number_of_input = One_piece_of_data;
		file >> One_piece_of_data;
		Number_of_output = One_piece_of_data;

		// adding 'inp_out' vectors to data, where 'inp_out' is determined as amound of input and output signals
		for (int i = 0; i < (Number_of_input + Number_of_output); i++)
		{
			std::vector<float> vec(0, 0);
			Vector_of_data.push_back(vec);
		}

		// Diagnostic function
		if (Diag == true)
		{
			Print_the_capacity_of_the_vector_of_data(Vector_of_data, "[Before main loop]");
		}
		

		for (int i = 0; !file.eof(); i++)
		{
			for (int j = 0; j < (Number_of_input + Number_of_output); j++)
			{
				file >> One_piece_of_data;
				Vector_of_data[j].push_back(One_piece_of_data);
				// if don't delete last row i txt, one_piece_of data uploads 2x times the same value!
			}
		}

		// Diagnostic function
		if (Diag == true)
		{
			Print_the_capacity_of_the_vector_of_data(Vector_of_data, "[After main loop, before shrink]");
		}

		Vector_of_data.shrink_to_fit();

		for (int i = 0; i < (Number_of_input + Number_of_output); i++)
		{
			Vector_of_data[i].shrink_to_fit();
		}

		// Diagnostic function
		if (Diag == true)
		{
			Print_the_capacity_of_the_vector_of_data(Vector_of_data, "[After shrink]");
		}

		file.close();
	}
	else
	{
		std::cout << "Error, file not opened. Check if name of file is correct, or if this file exist.";
		exit(3);
	}

	// Diagnostic function
	if (Diag == true)
	{
		Print_the_vector_of_data(Vector_of_data);
	}

	// end counting time 
	const auto Stop = std::chrono::high_resolution_clock::now();

	Display_results_counting_time(Start, Stop, "Read_data_MLP", 2);
}

void Fully_connected_network::Write_data_MLP(
	std::vector<float>& MSE_value_vector_X,
	std::vector<float>& MSE_value_vector_Y)
{
	// start counting time 
	const auto Start = std::chrono::high_resolution_clock::now();

	// ofstream only can write file
	std::ofstream file("../../../Output_data_(MSE)/" + Save_filename);

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

	Display_results_counting_time(Start, Stop, "Write_data_MLP", 2);
}

void Fully_connected_network::Min_max_unipolar_scaling(std::vector<std::vector<float>>& Vector_of_data)
{
	auto Start = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < (Number_of_input + Number_of_output); i++)
	{
		float max = *std::max_element(Vector_of_data[i].begin(), Vector_of_data[i].end());
		float min = *std::min_element(Vector_of_data[i].begin(), Vector_of_data[i].end());

		for (int j = 0; j < Vector_of_data[i].capacity(); ++j)
		{
			Vector_of_data[i][j] = (Vector_of_data[i][j] - min) / (max - min);
		}

		// Diagnostic function
		if (Diag == true)
		{
			Print_the_MIN_MAX_and_individual_values(Vector_of_data, min, max, i);
		}
	}

	auto Stop = std::chrono::high_resolution_clock::now();

	Display_results_counting_time(Start, Stop, "Min_max_unipolar_scaling", 2);
}

void Fully_connected_network::Min_max_bipolar_scaling(std::vector<std::vector<float>>& Vector_of_data)
{
	auto Start = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < (Number_of_input + Number_of_output); i++)
	{
		float max = *std::max_element(Vector_of_data[i].begin(), Vector_of_data[i].end());
		float min = *std::min_element(Vector_of_data[i].begin(), Vector_of_data[i].end());

		for (int j = 0; j < Vector_of_data[i].capacity(); ++j)
		{
			Vector_of_data[i][j] = 2 * ((Vector_of_data[i][j] - min) / (max - min)) - 1;
		}

		// Diagnostic function
		if (Diag == true)
		{
			Print_the_MIN_MAX_and_individual_values(Vector_of_data, min, max, i);
		}
	}
	
	auto Stop = std::chrono::high_resolution_clock::now();

	Display_results_counting_time(Start, Stop, "Min_max_bipolar_scaling", 2);
}

void Fully_connected_network::Reversal_min_max_unipolar_scaling(std::vector<std::vector<float>>& Vector_of_data)
{

}

void Fully_connected_network::Create_vector_of_neurons_values(std::vector<std::vector<float>>& Vector_of_neuron_values,
	std::vector <int>& Number_of_neuros_in_hidden_layers)
{
	// iterator
	int iter = 0;

	// input layer of neurons
	for (int i = 0; i < Number_of_input; i++)
	{
		Vector_of_neuron_values[iter].push_back(0);
	}

	iter += 1;

	// hidden layers of neurons
	for (iter; iter <= Number_of_hidden_layers; iter++)
	{
		for (int j = 0; j < Number_of_neuros_in_hidden_layers[iter - 1]; j++)
		{
			Vector_of_neuron_values[iter].push_back(0);
		}
	}

	// output layer of neurons
	for (int i = 0; i < Number_of_output; i++)
	{
		Vector_of_neuron_values[iter].push_back(0);
	}
	
	// capacity = amount of neurons
	Vector_of_neuron_values.shrink_to_fit();
	for (int i = 0; i < Vector_of_neuron_values.capacity(); i++)
	{
		Vector_of_neuron_values[i].shrink_to_fit();
	}

	// Diagnostic function
	if (Diag == true)
	{
		Capacity_of_Vector_of_neuron_values(Vector_of_neuron_values, iter);
	}
}

void Fully_connected_network::Create_vector_of_weights(std::vector<float>& Vector_of_weights, 
	std::vector<std::vector<float>>& Vector_of_neuron_values)
{
	int Add = 0;

	// weights of neurons
	for (int i = 0; i < Vector_of_neuron_values.capacity() - 1; i++)
	{
		Add += Vector_of_neuron_values[i].capacity() * 
			   Vector_of_neuron_values[i + 1].capacity();
	}
	
	// create vector of weights
	for (int i = 0; i < Add; i++)
	{
		Vector_of_weights.push_back(0);
	}

	Vector_of_weights.shrink_to_fit();

	// Diagnostic function
	if (Diag == true)
	{
		std::cout << "Vector_of_weights capacity: " << Vector_of_weights.capacity() << std::endl;
		std::cout << "Number of weights: " << Add << std::endl;
	}
}

void Fully_connected_network::Create_vector_of_bias(std::vector<float>& Vector_of_bias_weights,
	std::vector<std::vector<float>>& Vector_of_neuron_values)
{
	// bias weights = amount of hidden layer neurons
	int Add = 0;
	for (int i = 0; i < Vector_of_neuron_values.capacity(); i++)
	{
		Add += Vector_of_neuron_values[i].capacity();
	}

	Add -= (Number_of_input + Number_of_output);

	for (int i = 0; i < Add; i++)
	{
		Vector_of_bias_weights.push_back(0);
	}

	Vector_of_bias_weights.shrink_to_fit();

	// Diagnostic function
	if (Diag == true)
	{
		std::cout << "Amound of bias: " << Add << std::endl;
	}
}

void Fully_connected_network::Pseudo_random_numbers(std::vector<float>& Vector_of_weights,
	std::vector<float>& Vector_of_bias_weights, std::vector<float>& Range_of_pseudo_numbers_values)
{
	auto Start = std::chrono::high_resolution_clock::now();

	std::random_device rd;  // Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
	std::uniform_real_distribution<> dis(Range_of_pseudo_numbers_values[0], 
		Range_of_pseudo_numbers_values[1]);

	for (int i = 0; i < Vector_of_weights.capacity(); ++i)
	{
		Vector_of_weights[i] = dis(gen);
		std::cout << "Vector_of_weights[" << i << "]: " << Vector_of_weights[i] << std::endl;
	}

	for (int i = 0; i < Vector_of_bias_weights.capacity(); ++i)
	{
		Vector_of_bias_weights[i] = dis(gen);
		std::cout << "Vector_of_bias_weights[" << i << "]: " << Vector_of_weights[i] << std::endl;
	}

	auto Stop = std::chrono::high_resolution_clock::now();

	Display_results_counting_time(Start, Stop, "Pseudo_random_numbers", 2);
}

/*

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
*/

template<class Vec_of_data, class info>
void Fully_connected_network::Print_the_capacity_of_the_vector_of_data(Vec_of_data Vector_of_data, info information)
{
	std::cout << information << std::endl;

	std::cout << "Capacity(Vector_of_data): " << std::endl;
	std::cout << Vector_of_data.capacity() << std::endl;

	std::cout << "Capacity(Vector_of_data[0]): " << std::endl;
	std::cout << Vector_of_data[0].capacity() << std::endl;

	std::cout << "Capacity(Vector_of_data[1]): " << std::endl;
	std::cout << Vector_of_data[1].capacity() << std::endl;

	std::cout << "Capacity(Vector_of_data[2]): " << std::endl;
	std::cout << Vector_of_data[2].capacity() << std::endl;
}

void Fully_connected_network::Print_the_vector_of_data(std::vector<std::vector<float>>& Vector_of_data)
{
	for (int i = 0; i < (Number_of_input + Number_of_output); i++)
	{
		for (int j = 0; j < Vector_of_data[i].capacity(); j++)
		{
			std::cout << "Vector_of_data[" << i << "][" << j << "]: " << Vector_of_data[i][j] << std::endl;
		}
	}
}

void Fully_connected_network::Print_the_MIN_MAX_and_individual_values(std::vector<std::vector<float>>& Vector_of_data, 
	float min, float max, int iterator)
{
	std::cout << "MAX value Vector_of_data[" << iterator << "] = " << max << std::endl;
	std::cout << "MIN value Vector_of_data[" << iterator << "] = " << min << std::endl;
	std::cout << "Individual value Vector_of_data[" << iterator << "]: " << std::endl;

	for (int j = 0; j < Vector_of_data[iterator].capacity(); ++j)
	{
		std::cout << "No[" << j + 1 << "]: " << Vector_of_data[iterator][j] << std::endl;
	}
}

void Fully_connected_network::Capacity_of_Vector_of_neuron_values(std::vector<std::vector<float>>& Vector_of_neuron_values,
	int iterator)
{
	std::cout << "Capacity of Vector_of_neuron_values:" << Vector_of_neuron_values.capacity() << std::endl;
	for (int i = 0; i <= iterator; ++i)
	{
		std::cout << "Capacity of Vector_of_neuron_values[" << i << "] = " <<
			Vector_of_neuron_values[i].capacity() << std::endl;
	}
}
