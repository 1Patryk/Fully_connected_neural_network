#include "../Include/Fully_connected_network.hpp"

Fully_connected_network::Fully_connected_network()
{
	Diag = new bool{ false };
	Amount_of_data = new int { 4 };
	Number_of_epochs = new int{ 10 };
	Number_of_input = new int{ 0 };
	Number_of_output = new int{ 0 };
	Number_of_hidden_layers = new int{ 0 };
	Number_of_layers = new int{ 0 };
	Number_of_weights = new int{ 0 };
	Total_number_of_neurons = new int{ 0 };
	Train = new int{ 70 };
	Test = new int{ 20 };
	Validation = new int{ 10 };
	Beta = new float{ 1.0f };
	Bias = new float{ 1.0f };
	Learning_rate_factor = new float { 1.0f };
	Open_filename = new std::string{ "Add_1000.txt" };
	Save_filename = new std::string{ "Out_date.txt" };
	Number_of_neurons_in_hidden_layers = new std::vector<int>{  4 ,  3 ,  2  };
	Vector_of_data = new std::vector<std::vector<float>>(0);
	Vector_of_data_train = new std::vector<std::vector<float>>(0);
	Vector_of_data_validation = new std::vector<std::vector<float>>(0);
	Vector_of_data_test = new std::vector<std::vector<float>>(0);

	Vector_of_neuron_values_train = new std::vector<std::vector<float>> (*Number_of_hidden_layers + 2);
	Vector_of_neuron_values_one_dim_train = new std::vector<float>(0, 0);
	Vector_of_error_values_train = new std::vector<float>(0, 0);
	Vector_of_weights_train = new std::vector<float>(0, 0);
	Vector_of_bias_weights_train = new std::vector<float>(0, 0);

	Vector_of_neuron_values_validation = new std::vector<std::vector<float>>(*Number_of_hidden_layers + 2);
	Vector_of_neuron_values_one_dim_validation = new std::vector<float>(0, 0);
	Vector_of_error_values_validation = new std::vector<float>(0, 0);
	Vector_of_weights_validation = new std::vector<float>(0, 0);
	Vector_of_bias_weights_validation = new std::vector<float>(0, 0);

	Range_of_pseudo_numbers_values = new std::vector<float>{ -0.5, 0.5 };
	MSE_value_vector_X = new std::vector<float>(*Number_of_epochs);
	MSE_value_vector_Y = new std::vector<float>(*Number_of_epochs);
}

template<class start, class stop, class name, class unit>
void Fully_connected_network::Display_results_counting_time(
	start Start, stop Stop, name name_of_function, 
	unit unit_of_time)
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

void Fully_connected_network::Read_data_MLP(
	std::vector<std::vector<float>>& Vector_of_data)
{
	// start counting time 
	const auto Start = std::chrono::high_resolution_clock::now();

	// ifstream only can open file
	std::ifstream file("../../../Data/" + *Fully_connected_network::Open_filename);

	float One_piece_of_data = 0.0f;

	if (file)
	{
		// read 2 int of data which specifying amound of input and output
		file >> One_piece_of_data;
		*Fully_connected_network::Number_of_input = One_piece_of_data;
		file >> One_piece_of_data;
		*Fully_connected_network::Number_of_output = One_piece_of_data;

		// adding 'inp_out' vectors to data, where 'inp_out' is determined as amound of input and output signals
		for (int i = 0; i < (*Number_of_input + *Fully_connected_network::Number_of_output); i++)
		{
			std::vector<float> vec(0);
			Vector_of_data.push_back(vec);
		}	

		for (int i = 0; !file.eof(); i++)
		{
			for (int j = 0; j < (*Number_of_input + *Fully_connected_network::Number_of_output); j++)
			{
				file >> One_piece_of_data;
				Vector_of_data[j].push_back(One_piece_of_data);
				// if don't delete last row i txt, one_piece_of data uploads 2x times the same value!
			}
		}

		Fully_connected_network::Vector_of_data->shrink_to_fit();

		for (int i = 0; i < (*Number_of_input + *Fully_connected_network::Number_of_output); i++)
		{
			Vector_of_data[i].shrink_to_fit();
		}

		// initialization of variable
		*Fully_connected_network::Number_of_hidden_layers = 
			Fully_connected_network::Number_of_neurons_in_hidden_layers->capacity();

		Fully_connected_network::Vector_of_neuron_values_train->resize(*Fully_connected_network::Number_of_hidden_layers + 2);

		auto& Number_of_neurons_in_hidden_layers_ref = *Number_of_neurons_in_hidden_layers;

		for (int i = 0; i < Number_of_neurons_in_hidden_layers->capacity(); i++)
		{
			*Fully_connected_network::Total_number_of_neurons += 
				Number_of_neurons_in_hidden_layers_ref[i];
		}
		Fully_connected_network::Total_number_of_neurons += (*Number_of_input + *Number_of_output);
		Fully_connected_network::Number_of_layers = 1 + Number_of_hidden_layers + 1;						// 1 - input / 1 - output

		file.close();
	}
	else
	{
		std::cout << "Error, file not opened. Check if name of file is correct, or if this file exist.";
		exit(3);
	}

	// Diagnostic function
	if (Diag == true || false)
	{
		std::string name_of_function = "Vector_of_data";
		Print_the_vector_of_data(Vector_of_data, name_of_function);
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
	std::ofstream file("../../../Output_data_(MSE)/" + *Save_filename);

	if (file)
	{
		for (int i = 0; i < *Number_of_epochs; ++i)
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

void Fully_connected_network::Swap_data(
	std::vector<std::vector<float>>& Vector_of_data)
{
	// start counting time 
	const auto Start = std::chrono::high_resolution_clock::now();

	// Diagnostic function
	if (Diag == true || false)
	{
		std::string name_of_function = "Vector_of_data";
		Print_the_vector_of_data(Vector_of_data, name_of_function);
	}

	int ran_d = 0;
	for (int i = 0; i < Vector_of_data.capacity() - 1; i++)
	{
		for (int j = 0; j < Vector_of_data[i].capacity(); j++)
		{
			ran_d = std::rand() % Vector_of_data[0].capacity();
			for (int k = 0; k < Vector_of_data.capacity(); k++)
			{
				std::swap(Vector_of_data[k][j], Vector_of_data[k][ran_d]);
			}
		}
	}

	// Diagnostic function
	if (Diag == true || false)
	{
		std::string name_of_function = "Vector_of_data";
		Print_the_vector_of_data(Vector_of_data, name_of_function);
	}

	// end counting time 
	const auto Stop = std::chrono::high_resolution_clock::now();

	Display_results_counting_time(Start, Stop, "Swap_data", 2);
}

void Fully_connected_network::Divide_data_to_training_test_and_validation(
	std::vector<std::vector<float>>& Vector_of_data,
	std::vector<std::vector<float>>& Vector_of_data_train,
	std::vector<std::vector<float>>& Vector_of_data_validation,
	std::vector<std::vector<float>>& Vector_of_data_test,
	int Train,
	int Test,
	int Validation)
{
	if (Train + Test + Validation == 100)
	{
		float x = (Vector_of_data[0].capacity()) / 100;
		
		float train_cap = x * static_cast<float>(Train);
		float test_cap = x * static_cast<float>(Test);
		float validation_cap = x * static_cast<float>(Validation);

		std::vector<float> zero_vector = { 0 };

		// train
		for (int i = 0; i < Vector_of_data.capacity(); i++)
		{
			Vector_of_data_train.push_back(zero_vector);
			Vector_of_data_train.shrink_to_fit();
			for (int j = 0; j < train_cap; j++)
			{
				Vector_of_data_train[i].push_back(Vector_of_data[i][j]);
			}
			Vector_of_data_train[i].erase(Vector_of_data_train[i].begin());
			Vector_of_data_train[i].shrink_to_fit();
		}

		Vector_of_data_train.shrink_to_fit();
		
		// Diagnostic function
		if (Diag == true || false)
		{
			std::string name_of_function = "Vector_of_data_train";
			Print_the_vector_of_data(Vector_of_data_train, name_of_function);
		}

		// test
		for (int i = 0; i < Vector_of_data.capacity(); i++)
		{
			Vector_of_data_test.push_back(zero_vector);
			Vector_of_data_test.shrink_to_fit();
			for (int j = train_cap; j < (train_cap + test_cap); j++)
			{
				Vector_of_data_test[i].push_back(Vector_of_data[i][j]);
			}
			Vector_of_data_test[i].erase(Vector_of_data_test[i].begin());
			Vector_of_data_test[i].shrink_to_fit();
		}

		Vector_of_data_test.shrink_to_fit();

		// Diagnostic function
		if (Diag == true || false)
		{
			std::string name_of_function = "Vector_of_data_test";
			Print_the_vector_of_data(Vector_of_data_test, name_of_function);
		}

		// validation
		for (int i = 0; i < Vector_of_data.capacity(); i++)
		{
			Vector_of_data_validation.push_back(zero_vector);
			Vector_of_data_validation.shrink_to_fit();
			for (int j = (train_cap + test_cap); j < (train_cap + test_cap + validation_cap); j++)
			{
				Vector_of_data_validation[i].push_back(Vector_of_data[i][j]);
			}
			Vector_of_data_validation[i].erase(Vector_of_data_validation[i].begin());
			Vector_of_data_validation[i].shrink_to_fit();
		}

		Vector_of_data_validation.shrink_to_fit();

		// Diagnostic function
		if (Diag == true || true)
		{
			std::string name_of_function = "Vector_of_data_validation";
			Print_the_vector_of_data(Vector_of_data_validation, name_of_function);
		}
	}
	else
	{
		std::cout << "Sum of 3 parameters is not equal 100%.";
		exit(3);
	}
	
}

void Fully_connected_network::Min_max_unipolar_scaling(
	std::vector<std::vector<float>>& Vector_of_data)
{
	auto Start = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < (*Number_of_input + *Number_of_output); i++)
	{
		float max = *std::max_element(Vector_of_data[i].begin(), Vector_of_data[i].end());
		float min = *std::min_element(Vector_of_data[i].begin(), Vector_of_data[i].end());

		for (int j = 0; j < Vector_of_data[i].capacity(); ++j)
		{
			Vector_of_data[i][j] = (Vector_of_data[i][j] - min) / (max - min);
		}

		// Diagnostic function
		if (Diag == true || false)
		{
			Print_the_MIN_MAX_and_individual_values(Vector_of_data, min, max, i);
		}
	}

	auto Stop = std::chrono::high_resolution_clock::now();

	Display_results_counting_time(Start, Stop, "Min_max_unipolar_scaling", 2);
}

void Fully_connected_network::Min_max_bipolar_scaling(
	std::vector<std::vector<float>>& Vector_of_data)
{
	auto Start = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < (*Number_of_input + *Number_of_output); i++)
	{
		float max = *std::max_element(Vector_of_data[i].begin(), Vector_of_data[i].end());
		float min = *std::min_element(Vector_of_data[i].begin(), Vector_of_data[i].end());

		for (int j = 0; j < Vector_of_data[i].capacity(); ++j)
		{
			Vector_of_data[i][j] = 2 * ((Vector_of_data[i][j] - min) / (max - min)) - 1;
		}

		// Diagnostic function
		if (Diag == true || false)
		{
			Print_the_MIN_MAX_and_individual_values(Vector_of_data, min, max, i);
		}
	}
	
	auto Stop = std::chrono::high_resolution_clock::now();

	Display_results_counting_time(Start, Stop, "Min_max_bipolar_scaling", 2);
}

void Fully_connected_network::Reversal_min_max_unipolar_scaling(
	std::vector<std::vector<float>>& Vector_of_data)
{

}

void Fully_connected_network::Create_vector_of_neurons_values(
	std::vector<std::vector<float>>& Vector_of_neuron_values,
	std::vector <int>& Number_of_neuros_in_hidden_layers)
{
	// iterator
	int iter = 0;

	// input layer of neurons
	for (int i = 0; i < *Number_of_input; i++)
	{
		Vector_of_neuron_values[iter].push_back(0);
	}

	iter += 1;

	// hidden layers of neurons
	for (iter; iter <= *Number_of_hidden_layers; iter++)
	{
		for (int j = 0; j < Number_of_neuros_in_hidden_layers[iter - 1]; j++)
		{
			Vector_of_neuron_values[iter].push_back(0);
		}
	}

	// output layer of neurons
	for (int i = 0; i < *Number_of_output; i++)
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
	if (Diag == true || false)
	{
		Capacity_of_Vector_of_neuron_values(Vector_of_neuron_values, iter);
	}
}

void Fully_connected_network::Create_vector_of_weights(
	std::vector<float>& Vector_of_weights, 
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
	if (Diag == true || false)
	{
		std::cout << "Vector_of_weights capacity: " << Vector_of_weights.capacity() << std::endl;
		std::cout << "Number of weights: " << Add << std::endl;
	}
}

void Fully_connected_network::Create_vector_of_bias(
	std::vector<float>& Vector_of_bias_weights,
	std::vector<std::vector<float>>& Vector_of_neuron_values)
{
	// bias weights = amount of hidden layer neurons
	int Add = 0;
	for (int i = 0; i < Vector_of_neuron_values.capacity(); i++)
	{
		Add += Vector_of_neuron_values[i].capacity();
	}

	Add -= (*Number_of_input);

	for (int i = 0; i < Add; i++)
	{
		Vector_of_bias_weights.push_back(0);
	}

	Vector_of_bias_weights.shrink_to_fit();

	// Diagnostic function
	if (Diag == true || false)
	{
		std::cout << "Amound of bias: " << Add << std::endl;
	}
}

void Fully_connected_network::Pseudo_random_numbers(
	std::vector<float>& Vector_of_weights,
	std::vector<float>& Vector_of_bias_weights, 
	std::vector<float>& Range_of_pseudo_numbers_values)
{
	auto Start = std::chrono::high_resolution_clock::now();

	std::random_device rd;  // Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
	std::uniform_real_distribution<> dis(Range_of_pseudo_numbers_values[0], 
		Range_of_pseudo_numbers_values[1]);

	for (int i = 0; i < Vector_of_weights.capacity(); ++i)
	{
		Vector_of_weights[i] = dis(gen);
	}

	for (int i = 0; i < Vector_of_bias_weights.capacity(); ++i)
	{
		Vector_of_bias_weights[i] = dis(gen);
	}

	// Diagnostic function
	if (Diag == true || false)
	{
		Print_pseudo_random_numbers(Vector_of_weights, Vector_of_bias_weights);
	}

	auto Stop = std::chrono::high_resolution_clock::now();

	Display_results_counting_time(Start, Stop, "Pseudo_random_numbers", 2);
}

void Fully_connected_network::Calculating_the_network_MLP(
	//std::vector <int> Number_of_neurons_in_hidden_layers,
	//std::vector<std::vector<float>>& Vector_of_data,
	//std::vector<std::vector<float>>& Vector_of_data_validation,
	//std::vector<std::vector<float>>& Vector_of_data_test,
	//std::vector<std::vector<float>>& Vector_of_neuron_values,
	//std::vector<float>& Vector_of_neuron_values_one_dim,
	//std::vector<float>& Vector_of_error_values,
	//std::vector<float>& Vector_of_weights,
	//std::vector<float>& Vector_of_bias_weights,
	//std::vector<float>& MSE_value_vector_X,
	//std::vector<float>& MSE_value_vector_Y,
	//int Learn,
	//int Test,
	//int Validation
	)
{
	auto Start = std::chrono::high_resolution_clock::now();

	Read_data_MLP(*Fully_connected_network::Vector_of_data);
	Swap_data(*Fully_connected_network::Vector_of_data);
	Divide_data_to_training_test_and_validation(
		*Fully_connected_network::Vector_of_data,
		*Fully_connected_network::Vector_of_data_train,
		*Fully_connected_network::Vector_of_data_validation,
		*Fully_connected_network::Vector_of_data_test,
		*Fully_connected_network::Train,
		*Fully_connected_network::Test,
		*Fully_connected_network::Validation);

	// changes for user interface (uniporar/bipolar)
	Min_max_unipolar_scaling(*Fully_connected_network::Vector_of_data_train);
	Min_max_unipolar_scaling(*Vector_of_data_validation);

	Create_vector_of_neurons_values(
		*Fully_connected_network::Vector_of_neuron_values_train, 
		*Number_of_neurons_in_hidden_layers);

	Create_vector_of_neurons_values(
		*Fully_connected_network::Vector_of_neuron_values_validation,
		*Number_of_neurons_in_hidden_layers);

	Create_vector_of_weights(
		*Fully_connected_network::Vector_of_weights_train, 
		*Fully_connected_network::Vector_of_neuron_values_train);

	Create_vector_of_weights(
		*Fully_connected_network::Vector_of_weights_validation,
		*Fully_connected_network::Vector_of_neuron_values_validation);

	Create_vector_of_bias(
		*Fully_connected_network::Vector_of_bias_weights_train, 
		*Fully_connected_network::Vector_of_neuron_values_train);

	Create_vector_of_bias(
		*Fully_connected_network::Vector_of_bias_weights_validation,
		*Fully_connected_network::Vector_of_neuron_values_validation);

	Pseudo_random_numbers(
		*Fully_connected_network::Vector_of_weights_train, 
		*Fully_connected_network::Vector_of_bias_weights_train, 
		*Range_of_pseudo_numbers_values);

	// create errors vector

	Fully_connected_network::Vector_of_neuron_values_train->resize(Total_number_of_neurons - Number_of_input);
	Fully_connected_network::Vector_of_neuron_values_one_dim_train->resize(*Total_number_of_neurons);

	Fully_connected_network::Vector_of_neuron_values_validation->resize(Total_number_of_neurons - Number_of_input);
	Fully_connected_network::Vector_of_neuron_values_one_dim_validation->resize(*Total_number_of_neurons);

	float MSE = 0;
	int e = 0;
	int dat = 0;
	int weight = 0;
	int bias_iter = 0;
	int prev_layer = 0;
	int neu_iter = 0;
	int error_iter = 0;
	int weigh_iter = 0;
	int iterator = 0;
	int back_neuron_iter = 0;
	int value_neuron_iter = 0;

	auto& Number_of_neurons_in_hidden_layers_ref = *Number_of_neurons_in_hidden_layers;
	auto& Vector_of_data_train_ref = *Vector_of_data_train;
	auto& Vector_of_neuron_values_train_ref = *Vector_of_neuron_values_train;
	auto& Vector_of_neuron_values_one_dim_train_ref = *Vector_of_neuron_values_one_dim_train;
	auto& Vector_of_error_values_train_ref = *Vector_of_error_values_train;
	auto& Vector_of_weights_train_ref = *Vector_of_weights_train;
	auto& Vector_of_bias_weights_train_ref = *Vector_of_bias_weights_train;

	for (e = 0; e < *Number_of_epochs; ++e)
	{
		MSE = 0;

		for (dat = 0; dat < Vector_of_data[0].capacity(); dat++)
		{
			// forward propagation
			// 
			// input layer

			for (int j = 0; j < Vector_of_neuron_values_train_ref[0].capacity(); j++)
			{
				Vector_of_neuron_values_train_ref[0][j] =
					Vector_of_data_train_ref[j][dat];

				// Diagnostic function
				if (Diag == true || false)
				{
					std::cout << "Vector_of_neuron_values_train[0][" << j << "]: " <<
						Vector_of_neuron_values_train_ref[0][j] << std::endl;
				}
			}

			// hidden layers
			weight = 0;
			bias_iter = 0;
			

			for (int k = 1; k < *Number_of_hidden_layers + 1; k++)
			{
				for (int l = 0; l < Vector_of_neuron_values_train[k].capacity(); l++)
				{
					for (int m = 0; m < Vector_of_neuron_values_train[k - 1].capacity(); m++)
					{
						Vector_of_neuron_values_train_ref[k][l] +=
							((Vector_of_neuron_values_train_ref[k - 1][m] *
								Vector_of_weights_train_ref[weight]));
						weight += 1;
					}

					Vector_of_neuron_values_train_ref[k][l] = Unipolar_sigmoidal_function(
						Vector_of_neuron_values_train_ref[k][l] +
						Vector_of_bias_weights_train_ref[bias_iter]);

					bias_iter += 1;

					// Diagnostic function
					if (Diag == true || false)
					{
						std::cout << "Vector_of_neuron_values[" <<
							k << "][" << l << "]: " <<
							Vector_of_neuron_values_train_ref[k][l] << std::endl;
					}
				}
			}


			// output layer
			prev_layer = 1 + *Number_of_hidden_layers;		// previous layers
			for (int n = 0; n < *Number_of_output; n++)
			{
				for (int o = 0; o < Vector_of_neuron_values_train_ref[prev_layer].capacity(); o++)
				{
					Vector_of_neuron_values_train_ref[prev_layer][n] +=
						((Vector_of_neuron_values_train_ref[prev_layer - 1][o] * Vector_of_weights_train_ref[weight]));
					weight += 1;
				}
				Vector_of_neuron_values_train_ref[prev_layer][n] = Unipolar_sigmoidal_function(
					Vector_of_neuron_values_train_ref[prev_layer][n] +
					Vector_of_bias_weights_train_ref[bias_iter]);

				bias_iter += 1;

				// Diagnostic function
				if (Diag == true || false)
				{
					std::cout << "Vector_of_neuron_values[" <<
						prev_layer << "][" << n << "]: " <<
						Vector_of_neuron_values_train_ref[prev_layer][n] << std::endl;
				}
			}

			// back propagation 
			// 
			// error count 

			// output layer
			error_iter = Vector_of_error_values_train_ref.capacity() - 1;

			for (int p = (Vector_of_weights_train_ref.capacity() - 1);
				p > ((Vector_of_weights_train_ref.capacity() - 1) - *Number_of_output); p--)
			{
				for (int r = *Number_of_output; r > 0; r--)
				{
					Vector_of_error_values_train_ref[error_iter] =
						Vector_of_data_train_ref[Vector_of_data_train_ref.capacity() - r][dat] -
						Vector_of_neuron_values_train_ref[prev_layer][*Number_of_output - r];

					// Diagnostic function
					if (Diag == true || false)
					{
						std::cout << "  " << std::endl;
						std::cout << "  " << std::endl;
						std::cout << "Vector_of_error_values[" <<
							error_iter << "]:" <<
							Vector_of_error_values_train_ref
							[error_iter] << std::endl;
						std::cout << " = " << std::endl;
						std::cout << "Vector_of_data[" <<
							Vector_of_data_train_ref.capacity() - r << "][" << dat << "]: " <<
							Vector_of_data_train_ref[Vector_of_data_train_ref.capacity() - r][dat] << std::endl;
						std::cout << " - " << std::endl;
						std::cout << "Vector_of_neuron_values[" <<
							prev_layer << "][" << *Number_of_output - r << "]: " <<
							Vector_of_neuron_values_train_ref[prev_layer][*Number_of_output - r] << std::endl;
						std::cout << "  " << std::endl;
						std::cout << "  " << std::endl;
						std::cout << "  " << std::endl;
						std::cout << "  " << std::endl;
					}

					error_iter -= 1;
				}
			}


			// hidden layers

			weigh_iter = (Vector_of_weights_train_ref.capacity() - 1);

			for (int i = Number_of_neurons_in_hidden_layers_ref.capacity(); i > 0; i--)
			{
				for (int j = 0; j < Vector_of_neuron_values_train_ref[i].capacity(); j++)
				{
					for (int k = Vector_of_neuron_values_train_ref[i + 1].capacity(); k > 0; k--)
					{
						if (Vector_of_neuron_values_train_ref[i + 1].capacity() == k)
						{
							Vector_of_error_values_train_ref[error_iter] +=
								Vector_of_error_values_train_ref[error_iter + j + k] *
								Vector_of_weights_train_ref[weigh_iter];

							// Diagnostic function
							if (Diag == true || false)
							{
								std::cout << "Vector_of_error_values[" <<
									error_iter << "]:" <<
									Vector_of_error_values_train_ref[error_iter] << std::endl;
								std::cout << " += " << std::endl;
								std::cout << "Vector_of_error_values[" <<
									error_iter + j + k << "]: " <<
									Vector_of_error_values_train_ref[error_iter + j + k] << std::endl;
								std::cout << " * " << std::endl;
								std::cout << "Vector_of_weights[" <<
									weigh_iter << "]: " <<
									Vector_of_weights_train_ref[weigh_iter] << std::endl;
								std::cout << "  " << std::endl;
								std::cout << "  " << std::endl;
								std::cout << "  " << std::endl;
								std::cout << "  " << std::endl;
							}
						}
						else
						{
							Vector_of_error_values_train_ref[error_iter] +=
								Vector_of_error_values_train_ref[error_iter + j + k] *
								Vector_of_weights_train_ref[weigh_iter - (
									(Vector_of_neuron_values_train_ref[i + 1].capacity() - k) *
									Vector_of_neuron_values_train_ref[i].capacity())];

							// Diagnostic function
							if (Diag == true || false)
							{
								std::cout << "Vector_of_error_values[" <<
									error_iter << "]:" <<
									Vector_of_error_values_train_ref[error_iter] << std::endl;
								std::cout << " += " << std::endl;
								std::cout << "Vector_of_error_values[" <<
									error_iter + j + k << "]: " <<
									Vector_of_error_values_train_ref[error_iter + j + k] << std::endl;
								std::cout << " * " << std::endl;
								std::cout << "Vector_of_weights[" <<
									weigh_iter - (
										(Vector_of_neuron_values_train_ref[i + 1].capacity() - k) *
										Vector_of_neuron_values_train_ref[i].capacity()) << "]: " <<
									Vector_of_weights_train_ref[weigh_iter - (
										(Vector_of_neuron_values_train_ref[i + 1].capacity() - k) *
										Vector_of_neuron_values_train_ref[i].capacity())] << std::endl;
								std::cout << "  " << std::endl;
								std::cout << "  " << std::endl;
								std::cout << "  " << std::endl;
								std::cout << "  " << std::endl;
							}
						}
					}
					weigh_iter -= 1;
					error_iter -= 1;
				}

			}

			iterator = 0;

			for (int i = 0; i < Vector_of_neuron_values_train_ref.capacity(); i++)
			{
				for (int j = 0; j < Vector_of_neuron_values_train_ref[i].capacity(); j++)
				{
					Vector_of_neuron_values_one_dim_train_ref[iterator] = Vector_of_neuron_values_train_ref[i][j];
					iterator += 1;
				}
			}
 
			// new values of weight
			// for sigmoidal function only

			// bias weights
			for (int i = 0; i < Vector_of_bias_weights_train_ref.capacity(); i++)
			{
				Vector_of_bias_weights_train_ref[i] = Vector_of_bias_weights_train_ref[i] +
					*Learning_rate_factor * Vector_of_error_values_train_ref[i] *
					(*Beta * Vector_of_neuron_values_one_dim_train_ref[i + *Number_of_input] *
					(1 - Vector_of_neuron_values_one_dim_train_ref[i + *Number_of_input])) * *Bias;
			}

			// new values of Vector_of_weights
			// first hidden layer

			iterator = 0;
			for (int i = 0; i < Number_of_neurons_in_hidden_layers_ref[0]; i++)
			{
				for (int j = 0; j < *Number_of_input; j++)
				{
					Vector_of_weights_train_ref[iterator + j] =
						Vector_of_weights_train_ref[iterator + j] +
						(*Learning_rate_factor *
							Vector_of_error_values_train_ref[i] *
							(*Beta *
								Vector_of_neuron_values_one_dim_train_ref[*Number_of_input + i] *
								(1 - Vector_of_neuron_values_one_dim_train_ref[*Number_of_input + i])) *
							Vector_of_neuron_values_one_dim_train_ref[j]);

					// Diagnostic function
					if (Diag == true || false)
					{
						std::cout << " " << std::endl;
						std::cout << " " << std::endl;
						std::cout << " " << std::endl;
						std::cout << "Vector_of_weights[" << iterator + j << "]: " <<
							Vector_of_weights_train_ref[iterator + j] << std::endl;
						std::cout << " = " << std::endl;
						std::cout << "Vector_of_weights[" << iterator + j << "]: " <<
							Vector_of_weights_train_ref[iterator + j] << std::endl;
						std::cout << " + ( " << std::endl;
						std::cout << "Learning_rate_factor:" << Learning_rate_factor << std::endl;
						std::cout << " * " << std::endl;
						std::cout << "Vector_of_error_values[" << i << "]: " <<
							Vector_of_error_values_train_ref[i] << std::endl;
						std::cout << " * ( " << std::endl;
						std::cout << "Beta:" << Beta << std::endl;
						std::cout << " * " << std::endl;
						std::cout << "Vector_of_neuron_values_one_dim[" << *Number_of_input + i << "]: " <<
							Vector_of_neuron_values_one_dim_train_ref[*Number_of_input + i ] << std::endl;
						std::cout << " * " << std::endl;
						std::cout << "( 1 - Vector_of_neuron_values_one_dim[" << Number_of_input + i << "]: " <<
							1 - Vector_of_neuron_values_one_dim_train_ref[*Number_of_input + i ] << std::endl;
						std::cout << " * " << std::endl;
						std::cout << "Vector_of_neuron_values_one_dim[" << j << "]: " <<
							Vector_of_neuron_values_one_dim_train_ref[j] << std::endl;
						std::cout << " " << std::endl;
						std::cout << " " << std::endl;
						std::cout << " " << std::endl;
					}

				}
				iterator += *Number_of_input;
			}

			// reaminder hidden layers

			value_neuron_iter += *Number_of_input;
			back_neuron_iter += *Number_of_input;
			for (int i = 0; i < Number_of_neurons_in_hidden_layers_ref.capacity() - 1; i++)
			{
				value_neuron_iter += Number_of_neurons_in_hidden_layers_ref[i];
				for (int j = 0; j < Number_of_neurons_in_hidden_layers_ref[i + 1]; j++)
				{
					for (int k = 0; k < Number_of_neurons_in_hidden_layers_ref[i]; k++)
					{
						Vector_of_weights_train_ref[iterator + k] =
							Vector_of_weights_train_ref[iterator + k] +
							*Learning_rate_factor *
							Vector_of_error_values_train_ref[value_neuron_iter + j - *Number_of_input] *
							(*Beta * Vector_of_neuron_values_one_dim_train_ref[value_neuron_iter + j] *
								(1 - Vector_of_neuron_values_one_dim_train_ref[value_neuron_iter + j])) *
							Vector_of_neuron_values_one_dim_train_ref[back_neuron_iter + k];

						// Diagnostic function
						if (Diag == true || false)
						{
							std::cout << "i" << i << std::endl;
							std::cout << "j" << j << std::endl;
							std::cout << "k" << k << std::endl;
							std::cout << " " << std::endl;
							std::cout << " " << std::endl;
							std::cout << " " << std::endl;
							std::cout << "Vector_of_weights[" << iterator + k << "]: " <<
								Vector_of_weights_train_ref[iterator + k] << std::endl;
							std::cout << " = " << std::endl;
							std::cout << "Vector_of_weights[" << iterator + k << "]: " <<
								Vector_of_weights_train_ref[iterator + k] << std::endl;
							std::cout << " + ( " << std::endl;
							std::cout << "Learning_rate_factor:" << Learning_rate_factor << std::endl;
							std::cout << " * " << std::endl;
							std::cout << "Vector_of_error_values[" << value_neuron_iter + j - *Number_of_input << "]: " <<
								Vector_of_error_values_train_ref[value_neuron_iter + j - *Number_of_input] << std::endl;
							std::cout << " * ( " << std::endl;
							std::cout << "Beta:" << Beta << std::endl;
							std::cout << " * " << std::endl;
							std::cout << "Vector_of_neuron_values_one_dim[" <<
								value_neuron_iter + j << "]: " <<
								Vector_of_neuron_values_one_dim_train_ref[value_neuron_iter + j] <<
								std::endl;
							std::cout << " * " << std::endl;
							std::cout << "( 1 - Vector_of_neuron_values_one_dim[" <<
								value_neuron_iter + j << "]: " <<
								1 - Vector_of_neuron_values_one_dim_train_ref[value_neuron_iter + j] <<
								std::endl;
							std::cout << " * " << std::endl;
							std::cout << "Vector_of_neuron_values_one_dim[" << back_neuron_iter + k << "]: " <<
								Vector_of_neuron_values_one_dim_train_ref[back_neuron_iter + k] << std::endl;
							std::cout << " " << std::endl;
							std::cout << " " << std::endl;
							std::cout << " " << std::endl;
						}
					}
					iterator += Number_of_neurons_in_hidden_layers_ref[i];
				}
				back_neuron_iter += Number_of_neurons_in_hidden_layers_ref[i];
			}

			// output layer

			value_neuron_iter += Number_of_neurons_in_hidden_layers_ref.back();
			for (int i = 0; i < *Number_of_output; i++)
			{
				for (int j = 0; j < Number_of_neurons_in_hidden_layers_ref.back(); j++)
				{
					Vector_of_weights_train_ref[iterator + j] =
						Vector_of_weights_train_ref[iterator + j] +
						(*Learning_rate_factor *
							Vector_of_error_values_train_ref[value_neuron_iter + i - Number_of_neurons_in_hidden_layers_ref.back()] *
							(*Beta *
								Vector_of_neuron_values_one_dim_train_ref[value_neuron_iter + i] *
								(1 - Vector_of_neuron_values_one_dim_train_ref[value_neuron_iter + i])) *
							Vector_of_neuron_values_one_dim_train_ref[back_neuron_iter + j]);

					// Diagnostic function
					if (Diag == true || false)
					{
						std::cout << "i" << i << std::endl;
						std::cout << "j" << j << std::endl;
						std::cout << " " << std::endl;
						std::cout << " " << std::endl;
						std::cout << " " << std::endl;
						std::cout << "Vector_of_weights[" << iterator + j << "]: " <<
							Vector_of_weights_train_ref[iterator + j] << std::endl;
						std::cout << " = " << std::endl;
						std::cout << "Vector_of_weights[" << iterator + j << "]: " <<
							Vector_of_weights_train_ref[iterator + j] << std::endl;
						std::cout << " + ( " << std::endl;
						std::cout << "Learning_rate_factor:" << Learning_rate_factor << std::endl;
						std::cout << " * " << std::endl;
						std::cout << "Vector_of_error_values[" << value_neuron_iter + i - *Number_of_input << "]: " <<
							Vector_of_error_values_train_ref[value_neuron_iter + i - *Number_of_input] << std::endl;
						std::cout << " * ( " << std::endl;
						std::cout << "Beta:" << Beta << std::endl;
						std::cout << " * " << std::endl;
						std::cout << "Vector_of_neuron_values_one_dim[" <<
							value_neuron_iter + i << "]: " <<
							Vector_of_neuron_values_one_dim_train_ref[value_neuron_iter + i] <<
							std::endl;
						std::cout << " * " << std::endl;
						std::cout << "( 1 - Vector_of_neuron_values_one_dim[" <<
							value_neuron_iter + i << "]: " <<
							1 - Vector_of_neuron_values_one_dim_train_ref[value_neuron_iter + i] <<
							std::endl;
						std::cout << " * " << std::endl;
						std::cout << "Vector_of_neuron_values_one_dim[" << back_neuron_iter + j << "]: " <<
							Vector_of_neuron_values_one_dim_train_ref[back_neuron_iter + j] << std::endl;
						std::cout << " " << std::endl;
						std::cout << " " << std::endl;
						std::cout << " " << std::endl;
					}

				}
				iterator += Number_of_neurons_in_hidden_layers_ref.back();
			}


			value_neuron_iter = 0;
			back_neuron_iter = 0;

			/*
			Vector_of_weights

			Vector_of_weights[0] = Vector_of_weights[0] + Learning_rate_factor * error *
				(Beta * Vector_of_neuron_values[0] * (1 - Vector_of_neuron_values[0])) * Input_x1[i];

			Vector_of_weights[1] = Vector_of_weights[1] + Learning_rate_factor * error *
				(Beta * Vector_of_neuron_values[0] * (1 - Vector_of_neuron_values[0])) * Input_x2[i];

			Bias = Bias + Learning_rate_factor * error *
				(Beta * Vector_of_neuron_values[0] * (1 - Vector_of_neuron_values[0]));

			MSE += static_cast<float>(pow((Vector_of_neuron_values[0] - Output_y1[i]), 2));
			*/
			
			/*
			MSE = MSE / Amount_of_data;

			float iterator = (e + 1);			// float because MSE_value_vector_x have float type

			std::cout << "MSE(" << iterator << "): " << MSE << std::endl;

			MSE_value_vector_X.push_back(iterator);
			MSE_value_vector_Y.push_back(MSE);
			*/
		}

		//Write_data_MLP(MSE_value_vector_X, MSE_value_vector_Y);

		




		/*
		for (e = 0; e < Number_of_epochs; ++e)
		{
			MSE = 0;

			for (i = 0; i < Amount_of_data; ++i)
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

		Display_results_counting_time(Start, Stop, "Calculating_the_network_MLP", 2);
		*/
	}

	auto Stop = std::chrono::high_resolution_clock::now();

	Display_results_counting_time(Start, Stop, "Calculating_the_network_MLP", 2);


}

float Fully_connected_network::Unipolar_sigmoidal_function(float e)
{
	return static_cast<float>(1.0 / (1.0 + exp(-(*Beta) * e)));
}
/*
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

void Fully_connected_network::Print_the_vector_of_data(
	std::vector<std::vector<float>>& Vector_of_data,
	std::string name_of_vector)
{
	std::cout << "Capacity(" << name_of_vector << "): " << std::endl;
	std::cout << Vector_of_data.capacity() << std::endl;

	for (int i = 0; i < Vector_of_data.capacity(); i++)
	{
		std::cout << "Capacity(" << name_of_vector << "[" << i << "]: " << std::endl;
		std::cout << Vector_of_data[i].capacity() << std::endl;
	}
	
	for (int i = 0; i < Vector_of_data[0].capacity(); i++)
	{
		for (int j = 0; j < (*Number_of_input + *Number_of_output); j++)
		{
			std::cout << name_of_vector << "[" << j << "][" << i << "]: " << Vector_of_data[j][i] << "       __        ";
		}
		std::cout << std::endl;
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

void Fully_connected_network::Print_pseudo_random_numbers(
	std::vector<float>& Vector_of_weights,
	std::vector<float>& Vector_of_bias_weights)
{
	std::cout << "Vector_of_weights: " << std::endl;
	for (int i = 0; i < Vector_of_weights.capacity(); i++)
	{
		std::cout << "Vector_of_weights[" << i << "]: " << Vector_of_weights[i] << std::endl;
	}

	std::cout << "Vector_of_bias_weights: " << std::endl;
	for (int i = 0; i < Vector_of_bias_weights.capacity(); i++)
	{
		std::cout << "Vector_of_bias_weights[" << i << "]: " << Vector_of_bias_weights[i] << std::endl;
	}
	

}
