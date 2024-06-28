#include "../Include/Fully_connected_network.hpp"

Fully_connected_network::Fully_connected_network()
{
	Diag = bool{ false };
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
	Learning_rate_factor = new float { 0.1f };
	MAPE_training = float{ 0.0f };
	MAPE_validation = float{ 0.0f };

	// DELETE Q !!!

	Open_filename = new std::string{ "Load.txt" };
	Save_filename = new std::string{ "Out_date.txt" };
	Number_of_neurons_in_hidden_layersQ = std::vector<int>{  4 ,  3 ,  2  };
	Vector_of_dataQ = std::vector<std::vector<float>>(0);
	Range_of_pseudo_numbers_valuesQ = std::vector<float>{ -0.5, 0.5 };
	MAPE_value_vector_XQ = std::vector<float>(*Number_of_epochs);
	MAPE_value_vector_YQ = std::vector<float>(*Number_of_epochs);

	// TRAINING

	Fully_connected_network::Vector_of_data_trainingQ = std::vector<std::vector<float>>(0);
	Fully_connected_network::Vector_of_neuron_values_trainingQ = std::vector<std::vector<float>>(*Number_of_hidden_layers + 2);
	Fully_connected_network::Vector_of_neuron_values_one_dim_trainingQ = std::vector<float>(0, 0);
	Fully_connected_network::Vector_of_weights_trainingQ = std::vector<float>(0, 0);
	Fully_connected_network::Vector_of_bias_weights_trainingQ = std::vector<float>(0, 0);
	Fully_connected_network::Vector_of_error_values_trainingQ = std::vector<float>(0, 0);

	// VALIDATION

	Fully_connected_network::Vector_of_data_validationQ = std::vector<std::vector<float>>(0);
	Fully_connected_network::Vector_of_neuron_values_validationQ = std::vector<std::vector<float>>(*Number_of_hidden_layers + 2);
	Fully_connected_network::Vector_of_neuron_values_one_dim_validationQ = std::vector<float>(0, 0);
	Fully_connected_network::Vector_of_weights_validationQ = std::vector<float>(0, 0);
	Fully_connected_network::Vector_of_bias_weights_validationQ = std::vector<float>(0, 0);
	Fully_connected_network::Vector_of_error_values_validationQ = std::vector<float>(0, 0);

	// TEST

	Fully_connected_network::Vector_of_data_testQ = std::vector<std::vector<float>>(0);;
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

void Fully_connected_network::Read_data_MLP()
{
	// start counting time 
	const auto Start = std::chrono::high_resolution_clock::now();

	// ifstream only can open file
	std::ifstream file("../../../Data/" + *Open_filename);

	float One_piece_of_data = 0.0f;

	if (file)
	{
		// read 2 int of data which specifying amound of input and output
		file >> One_piece_of_data;
		*Number_of_input = static_cast<int>(One_piece_of_data);
		file >> One_piece_of_data;
		*Number_of_output = static_cast<int>(One_piece_of_data);

		// adding 'inp_out' vectors to data, where 'inp_out' is determined as amound of input and output signals
		for (int i = 0; i < (*Number_of_input + *Number_of_output); i++)
		{
			std::vector<float> vec(0);
			Vector_of_data_ref.push_back(vec);
		}	

		for (int i = 0; !file.eof(); i++)
		{
			for (int j = 0; j < (*Number_of_input + *Number_of_output); j++)
			{
				file >> One_piece_of_data;
				Vector_of_data_ref[j].push_back(One_piece_of_data);
				// if don't delete last row i txt, one_piece_of data uploads 2x times the same value!
			}
		}

		Vector_of_data_ref.shrink_to_fit();

		for (int i = 0; i < (*Number_of_input + *Number_of_output); i++)
		{
			Vector_of_data_ref[i].shrink_to_fit();
		}

		// initialization of variable
		*Number_of_hidden_layers = Number_of_neurons_in_hidden_layers_ref.capacity();

		Vector_of_neuron_values_training_ref.resize(*Number_of_hidden_layers + 2);
		Vector_of_neuron_values_validation_ref.resize(*Number_of_hidden_layers + 2);

		for (int i = 0; i < Number_of_neurons_in_hidden_layers_ref.capacity(); i++)
		{
			*Total_number_of_neurons += Number_of_neurons_in_hidden_layers_ref[i];
		}
		*Total_number_of_neurons += (*Number_of_input + *Number_of_output);
		*Number_of_layers = 1 + *Number_of_hidden_layers + 1;						// 1 - input / 1 - output

		file.close();
	}
	else
	{
		std::cout << "Error, file not opened. Check if name of file is correct, or if this file exist.";
		exit(3);
	}

	// end counting time 
	const auto Stop = std::chrono::high_resolution_clock::now();

	Display_results_counting_time(Start, Stop, "Read_data_MLP()", 2);
}

void Fully_connected_network::Write_data_MLP()
{
	// start counting time 
	const auto Start = std::chrono::high_resolution_clock::now();

	// ofstream only can write file
	std::ofstream file("../../../Output_data_(MSE)/" + *Save_filename);

	if (file)
	{
		for (int i = 0; i < *Number_of_epochs; ++i)
		{
			file << MSE_value_vector_X_ref[i];
			file << " ";
			file << MSE_value_vector_Y_ref[i];
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

	Display_results_counting_time(Start, Stop, "Write_data_MLP()", 2);
}

void Fully_connected_network::Swap_data()
{
	// start counting time 
	const auto Start = std::chrono::high_resolution_clock::now();

	int ran_d = 0;
	for (int i = 0; i < Vector_of_data_ref.capacity() - 1; i++)
	{
		for (int j = 0; j < Vector_of_data_ref[i].capacity(); j++)
		{
			ran_d = std::rand() % Vector_of_data_ref[0].capacity();
			for (int k = 0; k < Vector_of_data_ref.capacity(); k++)
			{
				std::swap(Vector_of_data_ref[k][j], Vector_of_data_ref[k][ran_d]);
			}
		}
	}

	// end counting time 
	const auto Stop = std::chrono::high_resolution_clock::now();

	Display_results_counting_time(Start, Stop, "Swap_data()", 2);
}

void Fully_connected_network::Divide_data_to_training_test_and_validation()
{
	// start counting time 
	const auto Start = std::chrono::high_resolution_clock::now();

	if (*Train + *Test + *Validation == 100)
	{
		float x = static_cast<float>((Vector_of_data_ref[0].capacity()) / 100);
		
		float train_cap = x * static_cast<float>(*Train);
		float test_cap = x * static_cast<float>(*Test);
		float validation_cap = x * static_cast<float>(*Validation);

		std::vector<float> zero_vector = { 0 };

		// train
		for (int i = 0; i < Vector_of_data_ref.capacity(); i++)
		{
			Vector_of_data_training_ref.push_back(zero_vector);
			Vector_of_data_training_ref.shrink_to_fit();
			for (int j = 0; j < train_cap; j++)
			{
				Vector_of_data_training_ref[i].push_back(Vector_of_data_ref[i][j]);
			}
			Vector_of_data_training_ref[i].erase(Vector_of_data_training_ref[i].begin());
			Vector_of_data_training_ref[i].shrink_to_fit();
		}

		Vector_of_data_training_ref.shrink_to_fit();

		// test
		for (int i = 0; i < Vector_of_data_ref.capacity(); i++)
		{
			Vector_of_data_test_ref.push_back(zero_vector);
			Vector_of_data_test_ref.shrink_to_fit();
			for (int j = static_cast<int>(train_cap); j < (train_cap + test_cap); j++)
			{
				Vector_of_data_test_ref[i].push_back(Vector_of_data_ref[i][j]);
			}
			Vector_of_data_test_ref[i].erase(Vector_of_data_test_ref[i].begin());
			Vector_of_data_test_ref[i].shrink_to_fit();
		}

		Vector_of_data_test_ref.shrink_to_fit();

		// validation
		for (int i = 0; i < Vector_of_data_ref.capacity(); i++)
		{
			Vector_of_data_validation_ref.push_back(zero_vector);
			Vector_of_data_validation_ref.shrink_to_fit();
			for (int j = static_cast<int>(train_cap + test_cap); j < (train_cap + test_cap + validation_cap); j++)
			{
				Vector_of_data_validation_ref[i].push_back(Vector_of_data_ref[i][j]);
			}
			Vector_of_data_validation_ref[i].erase(Vector_of_data_validation_ref[i].begin());
			Vector_of_data_validation_ref[i].shrink_to_fit();
		}

		Vector_of_data_validation_ref.shrink_to_fit();
	}
	else
	{
		std::cout << "Sum of 3 parameters is not equal 100%.";
		exit(3);
	}
	
	// end counting time 
	const auto Stop = std::chrono::high_resolution_clock::now();

	Display_results_counting_time(Start, Stop, "Divide_data_to_training_test_and_validation()", 2);
}

void Fully_connected_network::Min_max_unipolar_scaling(
	std::vector<std::vector<float>>& Vector_of_data,
	std::string name_of_vector)
{
	// start counting time 
	auto Start = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < (*Number_of_input + *Number_of_output); i++)
	{
		float max = *std::max_element(Vector_of_data[i].begin(), Vector_of_data[i].end());
		float min = *std::min_element(Vector_of_data[i].begin(), Vector_of_data[i].end());

		for (int j = 0; j < Vector_of_data[i].capacity(); ++j)
		{
			Vector_of_data[i][j] = (Vector_of_data[i][j] - min) / (max - min);
		}
	}

	// end counting time 
	auto Stop = std::chrono::high_resolution_clock::now();

	Display_results_counting_time(Start, Stop, "Min_max_unipolar_scaling: " + name_of_vector, 2);
}

void Fully_connected_network::Min_max_bipolar_scaling(
	std::vector<std::vector<float>>& Vector_of_data,
	std::string name_of_vector)
{
	// start counting time 
	auto Start = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < (*Number_of_input + *Number_of_output); i++)
	{
		float max = *std::max_element(Vector_of_data[i].begin(), Vector_of_data[i].end());
		float min = *std::min_element(Vector_of_data[i].begin(), Vector_of_data[i].end());

		for (int j = 0; j < Vector_of_data[i].capacity(); ++j)
		{
			Vector_of_data[i][j] = 2 * ((Vector_of_data[i][j] - min) / (max - min)) - 1;
		}
	}
	
	// end counting time 
	auto Stop = std::chrono::high_resolution_clock::now();

	Display_results_counting_time(Start, Stop, "Min_max_bipolar_scaling: " + name_of_vector, 2);
}

void Fully_connected_network::Create_vector_of_neurons_values(
	std::vector<std::vector<float>>& Vector_of_neuron_values,
	std::string name_of_vector)
{
	// start counting time 
	auto Start = std::chrono::high_resolution_clock::now();

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
		for (int j = 0; j < Number_of_neurons_in_hidden_layers_ref[iter - 1]; j++)
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

	// end counting time 
	auto Stop = std::chrono::high_resolution_clock::now();

	Display_results_counting_time(Start, Stop, "Create_vector_of_neurons_values: " + name_of_vector, 2);
}

void Fully_connected_network::Create_vector_of_weights(
	std::vector<float>& Vector_of_weights, 
	std::vector<std::vector<float>>& Vector_of_neuron_values,
	std::string name_of_vector)
{
	// start counting time 
	auto Start = std::chrono::high_resolution_clock::now();

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

	// end counting time 
	auto Stop = std::chrono::high_resolution_clock::now();

	Display_results_counting_time(Start, Stop, "Create_vector_of_weights: " + name_of_vector, 2);
}

void Fully_connected_network::Create_vector_of_bias(
	std::vector<float>& Vector_of_bias_weights,
	std::vector<std::vector<float>>& Vector_of_neuron_values,
	std::string name_of_vector)
{
	// start counting time 
	auto Start = std::chrono::high_resolution_clock::now();

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

	// end counting time 
	auto Stop = std::chrono::high_resolution_clock::now();

	Display_results_counting_time(Start, Stop, "Create_vector_of_bias: " + name_of_vector, 2);
}

void Fully_connected_network::Pseudo_random_numbers(
	std::vector<float>& Vector,
	std::string name_of_vector)
{
	// start counting time
	auto Start = std::chrono::high_resolution_clock::now();

	std::random_device rd;  // Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
	std::uniform_real_distribution<> dis(Range_of_pseudo_numbers_values_ref[0],
		Range_of_pseudo_numbers_values_ref[1]);

	for (int i = 0; i < Vector.capacity(); ++i)
	{
		Vector[i] = dis(gen);
	}

	for (int i = 0; i < Vector.capacity(); ++i)
	{
		Vector[i] = dis(gen);
	}

	// end counting time 
	auto Stop = std::chrono::high_resolution_clock::now();

	Display_results_counting_time(Start, Stop, "Pseudo_random_numbers: " + name_of_vector, 2);
}

void Fully_connected_network::Calculating_the_network_MLP()
{
	auto Start = std::chrono::high_resolution_clock::now();

	Read_data_MLP();
	Swap_data();
	Divide_data_to_training_test_and_validation();

	// TRAINING
	Min_max_unipolar_scaling(
		Vector_of_data_training_ref, 
		"Vector_of_data_training_ref");
	// VALIDATION
	Min_max_unipolar_scaling(
		Vector_of_data_validation_ref, 
		"Vector_of_data_validation_ref");

	// TRAINING
	Create_vector_of_neurons_values(
		Vector_of_neuron_values_training_ref, 
		"Vector_of_neuron_values_training_ref");
	// VALIDATION
	Create_vector_of_neurons_values(
		Vector_of_neuron_values_validation_ref, 
		"Vector_of_neuron_values_validation_ref");

	// TRAINING
	Create_vector_of_weights(
		Vector_of_weights_training_ref,
		Vector_of_neuron_values_training_ref,
		"Vector_of_weights_training_ref");
	// VALIDATION
	Create_vector_of_weights(
		Vector_of_weights_validation_ref,
		Vector_of_neuron_values_validation_ref,
		"Vector_of_weights_validation_ref");

	// TRAINING
	Create_vector_of_bias(
		Vector_of_bias_weights_training_ref,
		Vector_of_neuron_values_training_ref,
		"Vector_of_bias_weights_training_ref");
	// VALIDATION
	Create_vector_of_bias(
		Vector_of_bias_weights_validation_ref,
		Vector_of_neuron_values_validation_ref,
		"Vector_of_bias_weights_validation_ref");

	// TRAINING
	Pseudo_random_numbers(
		Vector_of_weights_training_ref,
		"Vector_of_weights_training_ref");
	Pseudo_random_numbers(
		Vector_of_bias_weights_training_ref,
		"Vector_of_bias_weights_training_ref");
	// VALIDATION
	Pseudo_random_numbers(
		Vector_of_weights_validation_ref,
		"Vector_of_weights_validation_ref");
	Pseudo_random_numbers(
		Vector_of_bias_weights_validation_ref,
		"Vector_of_bias_weights_validation_ref");

	// creating one-dimensional vector of neuron values 

	// TRAINING
	Vector_of_neuron_values_one_dim_training_ref.resize(*Total_number_of_neurons);
	// VALIDATION
	Vector_of_neuron_values_one_dim_validation_ref.resize(*Total_number_of_neurons);

	// creating vectors of error values
	// 
	// TRAINING
	Vector_of_error_values_training_ref.resize(*Total_number_of_neurons - *Number_of_input);
	// VALIDATION
	Vector_of_error_values_validation_ref.resize(*Total_number_of_neurons - *Number_of_input);

	int it_weight = 0;						// it_  - iterator
	int it_bias = 0;
	int it_prev_layer = 0;
	int it_neuron = 0;
	int it_error = 0;
	int it_iterator_one_dim = 0;
	int it_value_neuron = 0;
	int it_back_neuron = 0;

	// Diagnostic function
	if (Diag == true || true)
	{
		Print_MLP_data();
	}
	
	for (int epoch = 0; epoch < *Number_of_epochs; epoch++)
	{
		MAPE_training = 0.0f;
		MAPE_validation = 0.0f;

		// TRAINING DATA

		for (int it_data = 0; it_data < Vector_of_data_training_ref[0].capacity(); it_data++)
		{
			// forward propagation

			Forward_propagation_the_network_MLP
			(
				Vector_of_data_training_ref,
				Vector_of_neuron_values_training_ref,
				Vector_of_weights_training_ref,
				Vector_of_bias_weights_training_ref,
				it_data,
				it_weight,
				it_bias,
				it_prev_layer
			);

			// back propagation 

			Backpropagation_the_network_MLP
			(
				Vector_of_data_training_ref,
				Vector_of_neuron_values_training_ref,
				Vector_of_neuron_values_one_dim_training_ref,
				Vector_of_weights_training_ref,
				Vector_of_bias_weights_training_ref,
				Vector_of_error_values_training_ref,
				it_data,
				it_weight,
				it_bias,
				it_prev_layer,
				it_error,
				it_iterator_one_dim,
				it_value_neuron,
				it_back_neuron, 
				MAPE_training
			);

		}

		std::cout << "BEFORE" << std::endl;
		std::cout << "MAPE_training(" << epoch << "): " << MAPE_training << std::endl;

		MAPE_training = ((1.0f / Vector_of_data_training_ref[0].capacity()) * 
			MAPE_training * 100.0f);

		std::cout << "Vector_of_data_training_ref[0].capacity(): " << Vector_of_data_training_ref[0].capacity() << std::endl;
		std::cout << "AFTER" << std::endl;
		std::cout << "MAPE_training(" << epoch << "): " << MAPE_training << std::endl;

		// VALIDATION DATA

		for (int it_data = 0; it_data < Vector_of_data_validation_ref[0].capacity(); it_data++)
		{
			Forward_propagation_the_network_MLP
			(
				Vector_of_data_validation_ref,
				Vector_of_neuron_values_validation_ref,
				Vector_of_weights_validation_ref,
				Vector_of_bias_weights_validation_ref,
				it_data,
				it_weight,
				it_bias,
				it_prev_layer
			);

			Backpropagation_the_network_MLP
			(
				Vector_of_data_validation_ref,
				Vector_of_neuron_values_validation_ref,
				Vector_of_neuron_values_one_dim_validation_ref,
				Vector_of_weights_validation_ref,
				Vector_of_bias_weights_validation_ref,
				Vector_of_error_values_validation_ref,
				it_data,
				it_weight,
				it_bias,
				it_prev_layer,
				it_error,
				it_iterator_one_dim,
				it_value_neuron,
				it_back_neuron,
				MAPE_validation
			);
		}

		std::cout << "BEFORE" << std::endl;
		std::cout << "MAPE_validation(" << epoch << "): " << MAPE_validation << std::endl;

		MAPE_validation = ((1.0f / Vector_of_data_validation_ref[0].capacity()) *
			MAPE_validation * 100.0f);

		std::cout << "Vector_of_data_validation_ref[0].capacity(): " << Vector_of_data_validation_ref[0].capacity() << std::endl;
		std::cout << "AFTER" << std::endl;
		std::cout << "MAPE_validation(" << epoch << "): " << MAPE_validation << std::endl;
	}

	// Diagnostic function
	if (Diag == true || true)
	{
		Print_MLP_data();
	}

	auto Stop = std::chrono::high_resolution_clock::now();

	Display_results_counting_time(Start, Stop, "Calculating_the_network_MLP", 2);


}

void Fully_connected_network::Forward_propagation_the_network_MLP
(
	std::vector<std::vector<float>>& Vector_of_data,
	std::vector<std::vector<float>>& Vector_of_neuron_values,
	std::vector<float>& Vector_of_weights,
	std::vector<float>& Vector_of_bias_weights,
	int it_data, 
	int it_weight,
	int it_bias,
	int it_prev_layer
)
{
	// input layer

	for (int j = 0; j < Vector_of_neuron_values[0].capacity(); j++)
	{
		Vector_of_neuron_values[0][j] =
			Vector_of_data[j][it_data];
	}

	// hidden layers
	it_weight = 0;
	it_bias = 0;

	for (int k = 1; k < *Number_of_hidden_layers + 1; k++)
	{
		for (int l = 0; l < Vector_of_neuron_values[k].capacity(); l++)
		{
			for (int m = 0; m < Vector_of_neuron_values[k - 1].capacity(); m++)
			{
				Vector_of_neuron_values[k][l] +=
					((Vector_of_neuron_values[k - 1][m] *
						Vector_of_weights[it_weight]));
				it_weight += 1;
			}

				Vector_of_neuron_values[k][l] = Unipolar_sigmoidal_function(
					Vector_of_neuron_values[k][l] +
					Vector_of_bias_weights[it_bias]);

				it_bias += 1;
		}
	}

	// output layer
	it_prev_layer = 1 + *Number_of_hidden_layers;		// previous layers
	for (int n = 0; n < *Number_of_output; n++)
	{
		for (int o = 0; o < Vector_of_neuron_values[it_prev_layer].capacity(); o++)
		{
			Vector_of_neuron_values[it_prev_layer][n] +=
				((Vector_of_neuron_values[it_prev_layer - 1][o] * Vector_of_weights[it_weight]));
			it_weight += 1;
		}
		Vector_of_neuron_values[it_prev_layer][n] = Unipolar_sigmoidal_function(
			Vector_of_neuron_values[it_prev_layer][n] +
			Vector_of_bias_weights[it_bias]);

		it_bias += 1;
	}
}

void Fully_connected_network::Backpropagation_the_network_MLP
(
	std::vector<std::vector<float>>& Vector_of_data,
	std::vector<std::vector<float>>& Vector_of_neuron_values,
	std::vector<float>& Vector_of_neuron_values_one_dim,
	std::vector<float>& Vector_of_weights,
	std::vector<float>& Vector_of_bias_weights,
	std::vector<float>& Vector_of_error_values,
	int it_data,
	int it_weight,
	int it_bias,
	int it_prev_layer,
	int it_error, 
	int it_iterator_one_dim,
	int it_value_neuron,
	int it_back_neuron,
	float& MAPE
)
{
	MAPE = 0.0f;
	it_value_neuron = 0;
	it_back_neuron = 0;

	// reset error values
	for (int i = 0; i < Vector_of_error_values.capacity(); i++)
	{
		Vector_of_error_values[i] = 0.0f;
	}

	// error counting

	// output layer
	it_error = Vector_of_error_values.capacity() - 1;

	for (int p = static_cast<int>(Vector_of_weights.capacity() - 1);
		p > ((Vector_of_weights.capacity() - 1) - *Number_of_output); p--)
	{
		for (int r = *Number_of_output; r > 0; r--)
		{
			Vector_of_error_values[it_error] =
				Vector_of_data[Vector_of_data.capacity() - r][it_data] -
				Vector_of_neuron_values[it_prev_layer][*Number_of_output - r];

			MAPE += std::abs(Vector_of_error_values[it_error] /
				Vector_of_data[Vector_of_data.capacity() - r][it_data]);

			it_error -= 1;
		}
	}

	// hidden layers

	it_weight = (Vector_of_weights.capacity() - 1);

	for (int i = static_cast<int>(Number_of_neurons_in_hidden_layers_ref.capacity()); i > 0; i--)
	{
		for (int j = 0; j < Vector_of_neuron_values[i].capacity(); j++)
		{
			for (int k = static_cast<int>(Vector_of_neuron_values[i + 1].capacity()); k > 0; k--)
			{
				if (Vector_of_neuron_values[i + 1].capacity() == k)
				{
					Vector_of_error_values[it_error] +=
						Vector_of_error_values[it_error + j + k] *
						Vector_of_weights[it_weight];
				}
				else
				{
					Vector_of_error_values[it_error] +=
						Vector_of_error_values[it_error + j + k] *
						Vector_of_weights[it_weight - (
							(Vector_of_neuron_values[i + 1].capacity() - k) *
							Vector_of_neuron_values[i].capacity())];
				}
			}
			it_weight -= 1;
			it_error -= 1;
		}

	}

	it_iterator_one_dim = 0;

	for (int i = 0; i < Vector_of_neuron_values.capacity(); i++)
	{
		for (int j = 0; j < Vector_of_neuron_values[i].capacity(); j++)
		{
			Vector_of_neuron_values_one_dim[it_iterator_one_dim] = Vector_of_neuron_values[i][j];
			it_iterator_one_dim += 1;
		}
	}

	// new values of bias weight
	// for sigmoidal function only

	// bias weights
	for (int i = 0; i < Vector_of_bias_weights.capacity(); i++)
	{
		Vector_of_bias_weights[i] = Vector_of_bias_weights[i] +
			*Learning_rate_factor * Vector_of_error_values[i] *
			(*Beta * Vector_of_neuron_values_one_dim[i + *Number_of_input] *
				(1 - Vector_of_neuron_values_one_dim[i + *Number_of_input])) * *Bias;
	}

	// new values of Vector_of_weights
	// first hidden layer

	it_iterator_one_dim = 0;
	for (int i = 0; i < Number_of_neurons_in_hidden_layers_ref[0]; i++)
	{
		for (int j = 0; j < *Number_of_input; j++)
		{
			Vector_of_weights[it_iterator_one_dim + j] =
				Vector_of_weights[it_iterator_one_dim + j] +
				(*Learning_rate_factor *
					Vector_of_error_values[i] *
					(*Beta *
						Vector_of_neuron_values_one_dim[*Number_of_input + i] *
						(1 - Vector_of_neuron_values_one_dim[*Number_of_input + i])) *
					Vector_of_neuron_values_one_dim[j]);
		}
		it_iterator_one_dim += *Number_of_input;
	}

	// reaminder hidden layers

	it_value_neuron += *Number_of_input;
	it_back_neuron += *Number_of_input;

	for (int i = 0; i < Number_of_neurons_in_hidden_layers_ref.capacity() - 1; i++)
	{
		it_value_neuron += Number_of_neurons_in_hidden_layers_ref[i];
		for (int j = 0; j < Number_of_neurons_in_hidden_layers_ref[i + 1]; j++)
		{
			for (int k = 0; k < Number_of_neurons_in_hidden_layers_ref[i]; k++)
			{
				Vector_of_weights[it_iterator_one_dim + k] =
					Vector_of_weights[it_iterator_one_dim + k] +
					*Learning_rate_factor *
					Vector_of_error_values[it_value_neuron + j - *Number_of_input] *
					(*Beta * Vector_of_neuron_values_one_dim[it_value_neuron + j] *
						(1 - Vector_of_neuron_values_one_dim[it_value_neuron + j])) *
					Vector_of_neuron_values_one_dim[it_back_neuron + k];
			}
			it_iterator_one_dim += Number_of_neurons_in_hidden_layers_ref[i];
		}
		it_back_neuron += Number_of_neurons_in_hidden_layers_ref[i];
	}

	// output layer

	it_value_neuron += Number_of_neurons_in_hidden_layers_ref.back();
	for (int i = 0; i < *Number_of_output; i++)
	{
		for (int j = 0; j < Number_of_neurons_in_hidden_layers_ref.back(); j++)
		{
			Vector_of_weights[it_iterator_one_dim + j] =
				Vector_of_weights[it_iterator_one_dim + j] +
				(*Learning_rate_factor *
					Vector_of_error_values[it_value_neuron + i - Number_of_neurons_in_hidden_layers_ref.back()] *
					(*Beta *
						Vector_of_neuron_values_one_dim[it_value_neuron + i] *
						(1 - Vector_of_neuron_values_one_dim[it_value_neuron + i])) *
					Vector_of_neuron_values_one_dim[it_back_neuron + j]);
		}
		it_iterator_one_dim += Number_of_neurons_in_hidden_layers_ref.back();
	}
}

float Fully_connected_network::Unipolar_sigmoidal_function(float e)
{
	return static_cast<float>(1.0 / (1.0 + exp(-(*Beta) * e)));
}

void Fully_connected_network::Print_MLP_data()
{
	std::cout << "<< << << << PRINT DATA MLP >> >> >> >>" << std::endl;

	// training
	 
	std::cout << "<< << << << TRAINING >> >> >> >>" << std::endl;

	if (false)
	{
		std::cout << "====================================================" << std::endl;
		std::cout << "Vector_of_data_training_ref.Capacity(): " << std::endl;
		std::cout << Vector_of_data_training_ref.capacity() << std::endl;

		for (int i = 0; i < Vector_of_data_training_ref.capacity(); i++)
		{
			std::cout << "Vector_of_data_training_ref[" << i << "].capacity(): " << std::endl;
			std::cout << Vector_of_data_training_ref[i].capacity() << std::endl;
		}

		for (int i = 0; i < Vector_of_data_training_ref[0].capacity(); i++)
		{
			for (int j = 0; j < (*Number_of_input + *Number_of_output); j++)
			{
				std::cout << "Vector_of_data_training_ref[" << j << "][" << i << "]: "
					<< Vector_of_data_training_ref[j][i] << "       __        ";
			}
			std::cout << std::endl;
		}
	}

	if (false)
	{
		std::cout << "====================================================" << std::endl;
		std::cout << "Vector_of_neuron_values_training_ref.Capacity(): " << std::endl;
		std::cout << Vector_of_neuron_values_training_ref.capacity() << std::endl;

		for (int i = 0; i < Vector_of_neuron_values_training_ref.capacity(); i++)
		{
			std::cout << "Vector_of_neuron_values_training_ref[" << i << "].capacity(): " << std::endl;
			std::cout << Vector_of_neuron_values_training_ref[i].capacity() << std::endl;
		}

		for (int i = 0; i < Vector_of_neuron_values_training_ref[0].capacity(); i++)
		{
			for (int j = 0; j < (*Number_of_input + *Number_of_output); j++)
			{
				std::cout << "Vector_of_neuron_values_training_ref[" << j << "][" << i << "]: "
					<< Vector_of_neuron_values_training_ref[j][i] << "       __        ";
			}
			std::cout << std::endl;
		}
	}
	
	if (false)
	{
		std::cout << "====================================================" << std::endl;
		std::cout << "Vector_of_neuron_values_one_dim_training_ref.capacity(): "
			<< Vector_of_neuron_values_one_dim_training_ref.capacity() << std::endl;
		std::cout << "Vector_of_neuron_values_one_dim_training_ref values: " << std::endl;
		for (int i = 0; i < Vector_of_neuron_values_one_dim_training_ref.capacity(); i++)
		{
			std::cout << "Vector[" << i << "]: "
				<< Vector_of_neuron_values_one_dim_training_ref[i] << std::endl;
		}
	}

	if (true)
	{
		std::cout << "====================================================" << std::endl;
		std::cout << "Vector_of_weights_training_ref.capacity(): "
			<< Vector_of_weights_training_ref.capacity() << std::endl;
		std::cout << "Vector_of_weights_training_ref values: " << std::endl;
		for (int i = 0; i < Vector_of_weights_training_ref.capacity(); i++)
		{
			std::cout << "Vector_of_weights_training_ref[" << i << "]: "
				<< Vector_of_weights_training_ref[i] << std::endl;
		}
	}

	if (true)
	{
		std::cout << "====================================================" << std::endl;
		std::cout << "Vector_of_bias_weights_training_ref.capacity(): "
			<< Vector_of_bias_weights_training_ref.capacity() << std::endl;
		std::cout << "Vector_of_bias_weights_training_ref values: " << std::endl;
		for (int i = 0; i < Vector_of_bias_weights_training_ref.capacity(); i++)
		{
			std::cout << "Vector_of_bias_weights_training_ref[" << i << "]: "
				<< Vector_of_bias_weights_training_ref[i] << std::endl;
		}
	}

	if (true)
	{
		std::cout << "====================================================" << std::endl;
		std::cout << "Vector_of_error_values_training_ref.capacity(): "
			<< Vector_of_error_values_training_ref.capacity() << std::endl;
		std::cout << "Vector_of_error_values_training_ref values: " << std::endl;
		for (int i = 0; i < Vector_of_error_values_training_ref.capacity(); i++)
		{
			std::cout << "Vector_of_error_values_training_ref[" << i << "]: "
				<< Vector_of_error_values_training_ref[i] << std::endl;
		}
	}

	// validation

	std::cout << "<< << << << VALIDATION >> >> >> >>" << std::endl;

	if (false)
	{
		std::cout << "====================================================" << std::endl;
		std::cout << "Vector_of_data_validation_ref.Capacity(): " << std::endl;
		std::cout << Vector_of_data_validation_ref.capacity() << std::endl;

		for (int i = 0; i < Vector_of_data_validation_ref.capacity(); i++)
		{
			std::cout << "Vector_of_data_validation_ref[" << i << "].capacity(): " << std::endl;
			std::cout << Vector_of_data_validation_ref[i].capacity() << std::endl;
		}

		for (int i = 0; i < Vector_of_data_validation_ref[0].capacity(); i++)
		{
			for (int j = 0; j < (*Number_of_input + *Number_of_output); j++)
			{
				std::cout << "Vector_of_data_validation_ref[" << j << "][" << i << "]: "
					<< Vector_of_data_validation_ref[j][i] << "       __        ";
			}
			std::cout << std::endl;
		}
	}

	if (false)
	{
		std::cout << "====================================================" << std::endl;
		std::cout << "Vector_of_neuron_values_validation_ref.Capacity(): " << std::endl;
		std::cout << Vector_of_neuron_values_validation_ref.capacity() << std::endl;

		for (int i = 0; i < Vector_of_neuron_values_validation_ref.capacity(); i++)
		{
			std::cout << "Vector_of_neuron_values_validation_ref[" << i << "].capacity(): " << std::endl;
			std::cout << Vector_of_neuron_values_validation_ref[i].capacity() << std::endl;
		}

		for (int i = 0; i < Vector_of_neuron_values_validation_ref[0].capacity(); i++)
		{
			for (int j = 0; j < (*Number_of_input + *Number_of_output); j++)
			{
				std::cout << "Vector_of_neuron_values_validation_ref[" << j << "][" << i << "]: "
					<< Vector_of_neuron_values_validation_ref[j][i] << "       __        ";
			}
			std::cout << std::endl;
		}
	}

	if (false)
	{
		std::cout << "====================================================" << std::endl;
		std::cout << "Vector_of_neuron_values_one_dim_validation_ref.capacity(): "
			<< Vector_of_neuron_values_one_dim_validation_ref.capacity() << std::endl;
		std::cout << "Vector_of_neuron_values_one_dim_validation_ref values: " << std::endl;
		for (int i = 0; i < Vector_of_neuron_values_one_dim_validation_ref.capacity(); i++)
		{
			std::cout << "Vector[" << i << "]: "
				<< Vector_of_neuron_values_one_dim_validation_ref[i] << std::endl;
		}
	}

	if (true)
	{
		std::cout << "====================================================" << std::endl;
		std::cout << "Vector_of_weights_validation_ref.capacity(): "
			<< Vector_of_weights_validation_ref.capacity() << std::endl;
		std::cout << "Vector_of_weights_validation_ref values: " << std::endl;
		for (int i = 0; i < Vector_of_weights_validation_ref.capacity(); i++)
		{
			std::cout << "Vector_of_weights_validation_ref[" << i << "]: "
				<< Vector_of_weights_validation_ref[i] << std::endl;
		}
	}

	if (true)
	{
		std::cout << "====================================================" << std::endl;
		std::cout << "Vector_of_bias_weights_validation_ref.capacity(): "
			<< Vector_of_bias_weights_validation_ref.capacity() << std::endl;
		std::cout << "Vector_of_bias_weights_validation_ref values: " << std::endl;
		for (int i = 0; i < Vector_of_bias_weights_validation_ref.capacity(); i++)
		{
			std::cout << "Vector_of_bias_weights_validation_ref[" << i << "]: "
				<< Vector_of_bias_weights_validation_ref[i] << std::endl;
		}
	}

	if (true)
	{
		std::cout << "====================================================" << std::endl;
		std::cout << "Vector_of_error_values_validation_ref.capacity(): "
			<< Vector_of_error_values_validation_ref.capacity() << std::endl;
		std::cout << "Vector_of_error_values_validation_ref values: " << std::endl;
		for (int i = 0; i < Vector_of_error_values_validation_ref.capacity(); i++)
		{
			std::cout << "Vector_of_error_values_validation_ref[" << i << "]: "
				<< Vector_of_error_values_validation_ref[i] << std::endl;
		}
	}
}