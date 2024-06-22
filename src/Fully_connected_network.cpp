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
	Learning_rate_factor = new float { 1.0f };
	MSE_training = float{ 0.0f };
	MSE_validation = float{ 0.0f };

	// DELETE Q !!!

	Open_filename = new std::string{ "Add_1000.txt" };
	Save_filename = new std::string{ "Out_date.txt" };
	Number_of_neurons_in_hidden_layersQ = std::vector<int>{  4 ,  3 ,  2  };
	Vector_of_dataQ = std::vector<std::vector<float>>(0);
	Range_of_pseudo_numbers_valuesQ = std::vector<float>{ -0.5, 0.5 };
	MSE_value_vector_XQ = std::vector<float>(*Number_of_epochs);
	MSE_value_vector_YQ = std::vector<float>(*Number_of_epochs);

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

	// Diagnostic function
	if (Diag == true || false)
	{
		std::string name_of_function = "Read_data_MLP(): Vector_of_data";
		Print_the_vector_of_data(Vector_of_data_ref, name_of_function);
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

	// Diagnostic function
	if (Diag == true || false)
	{
		std::string name_of_function = "Swap_data(): Vector_of_data";
		Print_the_vector_of_data(Vector_of_data_ref, name_of_function);
	}

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

	// Diagnostic function
	if (Diag == true || false)
	{
		std::string name_of_function = "Swap_data(): Vector_of_data";
		Print_the_vector_of_data(Vector_of_data_ref, name_of_function);
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
		
		// Diagnostic function
		if (Diag == true || false)
		{
			std::string name_of_function = "Divide_data_to_training_test_and_validation(): Vector_of_data_train";
			Print_the_vector_of_data(Vector_of_data_training_ref, name_of_function);
		}

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

		// Diagnostic function
		if (Diag == true || false)
		{
			std::string name_of_function = "Divide_data_to_training_test_and_validation(): Vector_of_data_test";
			Print_the_vector_of_data(Vector_of_data_test_ref, name_of_function);
		}

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

		// Diagnostic function
		if (Diag == true || false)
		{
			std::string name_of_function = "Divide_data_to_training_test_and_validation(): Vector_of_data_validation";
			Print_the_vector_of_data(Vector_of_data_validation_ref, name_of_function);
		}
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

		// Diagnostic function
		if (Diag == true || false)
		{
			Print_the_MIN_MAX_and_individual_values(Vector_of_data, min, max, i);
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

		// Diagnostic function
		if (Diag == true || false)
		{
			Print_the_MIN_MAX_and_individual_values(Vector_of_data, min, max, i);
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

	// Diagnostic function
	if (Diag == true || false)
	{
		Capacity_of_Vector_of_neuron_values(Vector_of_neuron_values, iter);
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

	// Diagnostic function
	if (Diag == true || true)
	{
		std::cout << "Vector_of_weights capacity: " << Vector_of_weights.capacity() << std::endl;
		std::cout << "Number of weights: " << Add << std::endl;
	}

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

	// Diagnostic function
	if (Diag == true || false)
	{
		std::cout << "Amound of bias: " << Add << std::endl;
	}

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

	// Diagnostic function
	if (Diag == true || false)
	{
		Print_pseudo_random_numbers(Vector);
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
	Vector_of_error_values_training_ref.resize(*Total_number_of_neurons);
	// VALIDATION
	Vector_of_error_values_validation_ref.resize(*Total_number_of_neurons);

	int it_weight = 0;						// it_  - iterator
	int it_bias = 0;
	int it_prev_layer = 0;
	int it_neuron = 0;
	int it_error = 0;
	int it_iterator_one_dim = 0;
	int it_value_neuron = 0;
	int it_back_neuron = 0;

	for (int epoch = 0; epoch < *Number_of_epochs; epoch++)
	{
		MSE_training = 0;
		MSE_validation = 0;

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
				MSE_training
			);

		}

		std::cout << "BEFORE" << std::endl;
		std::cout << "MSE(" << epoch << "): " << MSE_training << std::endl;

		MSE_training = MSE_training / Vector_of_data_training_ref[0].capacity();

		std::cout << "AFTER" << std::endl;
		std::cout << "MSE(" << epoch << "): " << MSE_training << std::endl;

			/*
		MSE_training += static_cast<float>(pow((Vector_of_neuron_values[0] - Output_y1[i]), 2));
			*/
			
			/*
			MSE = MSE / Amount_of_data;

			float iterator = (e + 1);			// float because MSE_value_vector_x have float type

			std::cout << "MSE(" << iterator << "): " << MSE << std::endl;

			MSE_value_vector_X.push_back(iterator);
			MSE_value_vector_Y.push_back(MSE);
			*/
		

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
				MSE_validation
			);
		}

		std::cout << "BEFORE" << std::endl;
		std::cout << "MSE(" << epoch << "): " << MSE_validation << std::endl;

		MSE_validation = MSE_validation / Vector_of_data_validation_ref[0].capacity();

		std::cout << "AFTER" << std::endl;
		std::cout << "MSE(" << epoch << "): " << MSE_validation << std::endl;
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

		// Diagnostic function
		if (Diag == true || false)
		{
			std::cout << "Vector_of_neuron_values[0][" << j << "]: " <<
				Vector_of_neuron_values[0][j] << std::endl;
		}
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

			// Diagnostic function
			if (Diag == true || false)
			{
				std::cout << "Vector_of_neuron_values[" <<
					k << "][" << l << "]: " <<
					Vector_of_neuron_values[k][l] << std::endl;
			}
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

		// Diagnostic function
		if (Diag == true || false)
		{
			std::cout << "Vector_of_neuron_values[" <<
				it_prev_layer << "][" << n << "]: " <<
				Vector_of_neuron_values[it_prev_layer][n] << std::endl;
		}
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
	float& MSE
)
{
	MSE = 0.0f;
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

			MSE += Vector_of_error_values[it_error];

			// Diagnostic function
			if (Diag == true || false)
			{
				std::cout << "  " << std::endl;
				std::cout << "  " << std::endl;
				std::cout << "Vector_of_error_values[" <<
					it_error << "]:" <<
					Vector_of_error_values
					[it_error] << std::endl;
				std::cout << " = " << std::endl;
				std::cout << "Vector_of_data[" <<
					Vector_of_data.capacity() - r << "][" << it_data << "]: " <<
					Vector_of_data[Vector_of_data.capacity() - r][it_data] << std::endl;
				std::cout << " - " << std::endl;
				std::cout << "Vector_of_neuron_values[" <<
					it_prev_layer << "][" << *Number_of_output - r << "]: " <<
					Vector_of_neuron_values[it_prev_layer][*Number_of_output - r] << std::endl;
				std::cout << "  " << std::endl;
				std::cout << "  " << std::endl;
				std::cout << "  " << std::endl;
				std::cout << "  " << std::endl;
			}

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

					// Diagnostic function
					if (Diag == true || false)
					{
						std::cout << "Vector_of_error_values[" <<
							it_error << "]:" <<
							Vector_of_error_values[it_error] << std::endl;
						std::cout << " += " << std::endl;
						std::cout << "Vector_of_error_values[" <<
							it_error + j + k << "]: " <<
							Vector_of_error_values[it_error + j + k] << std::endl;
						std::cout << " * " << std::endl;
						std::cout << "Vector_of_weights[" <<
							it_weight << "]: " <<
							Vector_of_weights[it_weight] << std::endl;
						std::cout << "  " << std::endl;
						std::cout << "  " << std::endl;
						std::cout << "  " << std::endl;
						std::cout << "  " << std::endl;
					}
				}
				else
				{
					Vector_of_error_values[it_error] +=
						Vector_of_error_values[it_error + j + k] *
						Vector_of_weights[it_weight - (
							(Vector_of_neuron_values[i + 1].capacity() - k) *
							Vector_of_neuron_values[i].capacity())];

					// Diagnostic function
					if (Diag == true || false)
					{
						std::cout << "Vector_of_error_values[" <<
							it_error << "]:" <<
							Vector_of_error_values[it_error] << std::endl;
						std::cout << " += " << std::endl;
						std::cout << "Vector_of_error_values[" <<
							it_error + j + k << "]: " <<
							Vector_of_error_values[it_error + j + k] << std::endl;
						std::cout << " * " << std::endl;
						std::cout << "Vector_of_weights[" <<
							it_weight - (
								(Vector_of_neuron_values[i + 1].capacity() - k) *
								Vector_of_neuron_values[i].capacity()) << "]: " <<
							Vector_of_weights[it_weight - (
								(Vector_of_neuron_values[i + 1].capacity() - k) *
								Vector_of_neuron_values[i].capacity())] << std::endl;
						std::cout << "  " << std::endl;
						std::cout << "  " << std::endl;
						std::cout << "  " << std::endl;
						std::cout << "  " << std::endl;
					}
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

			// Diagnostic function
			if (Diag == true || false)
			{
				std::cout << " " << std::endl;
				std::cout << " " << std::endl;
				std::cout << " " << std::endl;
				std::cout << "Vector_of_weights[" << it_iterator_one_dim + j << "]: " <<
					Vector_of_weights[it_iterator_one_dim + j] << std::endl;
				std::cout << " = " << std::endl;
				std::cout << "Vector_of_weights[" << it_iterator_one_dim + j << "]: " <<
					Vector_of_weights[it_iterator_one_dim + j] << std::endl;
				std::cout << " + ( " << std::endl;
				std::cout << "Learning_rate_factor:" << Learning_rate_factor << std::endl;
				std::cout << " * " << std::endl;
				std::cout << "Vector_of_error_values[" << i << "]: " <<
					Vector_of_error_values[i] << std::endl;
				std::cout << " * ( " << std::endl;
				std::cout << "Beta:" << Beta << std::endl;
				std::cout << " * " << std::endl;
				std::cout << "Vector_of_neuron_values_one_dim[" << *Number_of_input + i << "]: " <<
					Vector_of_neuron_values_one_dim[*Number_of_input + i] << std::endl;
				std::cout << " * " << std::endl;
				std::cout << "( 1 - Vector_of_neuron_values_one_dim[" << Number_of_input + i << "]: " <<
					1 - Vector_of_neuron_values_one_dim[*Number_of_input + i] << std::endl;
				std::cout << " * " << std::endl;
				std::cout << "Vector_of_neuron_values_one_dim[" << j << "]: " <<
					Vector_of_neuron_values_one_dim[j] << std::endl;
				std::cout << " " << std::endl;
				std::cout << " " << std::endl;
				std::cout << " " << std::endl;
			}

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

				// Diagnostic function
				if (Diag == true || false)
				{
					std::cout << "i" << i << std::endl;
					std::cout << "j" << j << std::endl;
					std::cout << "k" << k << std::endl;
					std::cout << " " << std::endl;
					std::cout << " " << std::endl;
					std::cout << " " << std::endl;
					std::cout << "Vector_of_weights[" << it_iterator_one_dim + k << "]: " <<
						Vector_of_weights[it_iterator_one_dim + k] << std::endl;
					std::cout << " = " << std::endl;
					std::cout << "Vector_of_weights[" << it_iterator_one_dim + k << "]: " <<
						Vector_of_weights[it_iterator_one_dim + k] << std::endl;
					std::cout << " + ( " << std::endl;
					std::cout << "Learning_rate_factor:" << Learning_rate_factor << std::endl;
					std::cout << " * " << std::endl;
					std::cout << "Vector_of_error_values[" << it_value_neuron + j - *Number_of_input << "]: " <<
						Vector_of_error_values[it_value_neuron + j - *Number_of_input] << std::endl;
					std::cout << " * ( " << std::endl;
					std::cout << "Beta:" << Beta << std::endl;
					std::cout << " * " << std::endl;
					std::cout << "Vector_of_neuron_values_one_dim[" <<
						it_value_neuron + j << "]: " <<
						Vector_of_neuron_values_one_dim[it_value_neuron + j] <<
						std::endl;
					std::cout << " * " << std::endl;
					std::cout << "( 1 - Vector_of_neuron_values_one_dim[" <<
						it_value_neuron + j << "]: " <<
						1 - Vector_of_neuron_values_one_dim[it_value_neuron + j] <<
						std::endl;
					std::cout << " * " << std::endl;
					std::cout << "Vector_of_neuron_values_one_dim[" << it_back_neuron + k << "]: " <<
						Vector_of_neuron_values_one_dim[it_back_neuron + k] << std::endl;
					std::cout << " " << std::endl;
					std::cout << " " << std::endl;
					std::cout << " " << std::endl;
				}
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

			// Diagnostic function
			if (Diag == true || false)
			{
				std::cout << "i" << i << std::endl;
				std::cout << "j" << j << std::endl;
				std::cout << " " << std::endl;
				std::cout << " " << std::endl;
				std::cout << " " << std::endl;
				std::cout << "Vector_of_weights[" << it_iterator_one_dim + j << "]: " <<
					Vector_of_weights[it_iterator_one_dim + j] << std::endl;
				std::cout << " = " << std::endl;
				std::cout << "Vector_of_weights[" << it_iterator_one_dim + j << "]: " <<
					Vector_of_weights[it_iterator_one_dim + j] << std::endl;
				std::cout << " + ( " << std::endl;
				std::cout << "Learning_rate_factor:" << Learning_rate_factor << std::endl;
				std::cout << " * " << std::endl;
				std::cout << "Vector_of_error_values[" << it_value_neuron + i - *Number_of_input << "]: " <<
					Vector_of_error_values[it_value_neuron + i - *Number_of_input] << std::endl;
				std::cout << " * ( " << std::endl;
				std::cout << "Beta:" << Beta << std::endl;
				std::cout << " * " << std::endl;
				std::cout << "Vector_of_neuron_values_one_dim[" <<
					it_value_neuron + i << "]: " <<
					Vector_of_neuron_values_one_dim[it_value_neuron + i] <<
					std::endl;
				std::cout << " * " << std::endl;
				std::cout << "( 1 - Vector_of_neuron_values_one_dim[" <<
					it_value_neuron + i << "]: " <<
					1 - Vector_of_neuron_values_one_dim[it_value_neuron + i] <<
					std::endl;
				std::cout << " * " << std::endl;
				std::cout << "Vector_of_neuron_values_one_dim[" << it_back_neuron + j << "]: " <<
					Vector_of_neuron_values_one_dim[it_back_neuron + j] << std::endl;
				std::cout << " " << std::endl;
				std::cout << " " << std::endl;
				std::cout << " " << std::endl;
			}

		}
		it_iterator_one_dim += Number_of_neurons_in_hidden_layers_ref.back();
	}


	it_value_neuron = 0;
	it_back_neuron = 0;
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
	std::vector<float>& Vector)
{
	std::cout << "Vector.capacity: " << std::endl;
	for (int i = 0; i < Vector.capacity(); i++)
	{
		std::cout << "Vector[" << i << "]: " << Vector[i] << std::endl;
	}
}
