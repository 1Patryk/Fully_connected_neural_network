#include "../include/Fully_connected_network.hpp"

Fully_connected_network::Fully_connected_network
(

)
{
	Diag = bool{ false };
	Number_of_epochs = new int{ 10 };
	Number_of_input = new int{ 0 };
	Number_of_output = new int{ 0 };
	Number_of_hidden_layers = new int{ 0 };
	Train = new int{ 50 };
	Validation = new int{ 50 };
	Optimizer_function = new int{ 0 };	// 0 - GD, 1 - ADAM
	Data_normalizer = new int { 0 };	// 0 - Unipolar, 1 - Bipolar
	Beta = new float{ 1.0f };
	Learning_rate_factor = new float { 0.000001f };

    Open_filename = new std::string{ "" };
    Output_filename_path = new std::string{ "" };
	Number_of_neurons_in_hidden_layers = std::vector<int>{ 2, 1 };
	Activation_functions = std::vector<int>{ 1, 1, 0 }; // 0 - linear, 1 - unipolar sigmoidal, 2 - bipolar sigmoidal
	Vector_of_data = std::vector<std::vector<float>>(0);
	Range_of_pseudo_numbers_values = std::vector<float>{ -0.5, 0.5 };
	MAPE_value_training = std::vector<float>(*Number_of_epochs);
	MAPE_value_validation = std::vector<float>(*Number_of_epochs);

	Fully_connected_network::Max_training_value_vector = std::vector<float>(*Number_of_input + *Number_of_output);
	Fully_connected_network::Min_training_value_vector = std::vector<float>(*Number_of_input + *Number_of_output);
	Fully_connected_network::Max_validation_value_vector = std::vector<float>(*Number_of_input + *Number_of_output);
	Fully_connected_network::Min_validation_value_vector = std::vector<float>(*Number_of_input + *Number_of_output);

	// TRAINING

	Fully_connected_network::Vector_of_data_training = std::vector<std::vector<float>>(0);
	Fully_connected_network::Vector_of_neuron_values_training = std::vector<std::vector<float>>(0);
	Fully_connected_network::Vector_of_weights_training = std::vector<std::vector<float>>(0);
	Fully_connected_network::Vector_of_bias_training = std::vector<std::vector<float>>(0);
	Fully_connected_network::Vector_of_error_values_training = std::vector<std::vector<float>>(0);

	// VALIDATION

	Fully_connected_network::Vector_of_data_validation = std::vector<std::vector<float>>(0);
	Fully_connected_network::Vector_of_neuron_values_validation = std::vector<std::vector<float>>(0);
	Fully_connected_network::Vector_of_weights_validation = std::vector<std::vector<float>>(0);
	Fully_connected_network::Vector_of_bias_validation = std::vector<std::vector<float>>(0);
	Fully_connected_network::Vector_of_error_values_validation = std::vector<std::vector<float>>(0);
}

template<class start, class stop, class name, class unit>
void Fully_connected_network::Display_results_counting_time
(
	start Start, stop Stop, 
	name name_of_function, 
	unit unit_of_time
)
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

void Fully_connected_network::Startup_check_function
(

)
{
	// start counting time 
	const auto Start = std::chrono::high_resolution_clock::now();

	if ((Number_of_neurons_in_hidden_layers.capacity() + 1) != 
	(Activation_functions.capacity()))
	{
		std::cout << "ERROR: Number of elements 'Number_of_neurons_in_hidden_layers'" <<
		" is not greater than one more than 'Activation_functions' (output activation function)" << std::endl;
		exit(3);
	}

	// end counting time 
	const auto Stop = std::chrono::high_resolution_clock::now();

	Display_results_counting_time(Start, Stop, "Startup_check_function()", 2);
}

void Fully_connected_network::Read_data_MLP
(
	std::string* Open_filename
)
{
	// start counting time 
	const auto Start = std::chrono::high_resolution_clock::now();

	// ifstream only can open file
    std::ifstream file(*Open_filename);

	float One_piece_of_data = 0.0f;
	
    if (std::filesystem::is_empty(*Open_filename))
	{
	    std::cout << "Error, file is empty.";
		exit(3);
	}
	
	if (file)
	{
		// skip header
		std::string head = {};
		getline(file, head);
		getline(file, head);

		// read 2 int of data which specifying amound of input and output
		file >> One_piece_of_data;
		*Number_of_input = static_cast<int>(One_piece_of_data);
		file >> One_piece_of_data;
		*Number_of_output = static_cast<int>(One_piece_of_data);

		// skip describe columns
		std::string describe = {};
		getline(file, describe);
		getline(file, describe);
		getline(file, describe);

		// adding 'inp_out' vectors to data, where 'inp_out' is determined as amound of input and output signals
		for (int i = 0; i < (*Number_of_input + *Number_of_output); i++)
		{
			std::vector<float> vec(0);	// multi-declaration ?
			Vector_of_data_ref.push_back(vec);
		}	

		while(!file.eof())
		{
			for (int j = 0; j < (*Number_of_input + *Number_of_output); j++)
			{
				file >> One_piece_of_data;
				Vector_of_data_ref[j].push_back(One_piece_of_data);
			}
		}

		Vector_of_data_ref.shrink_to_fit();

		for (int i = 0; i < (*Number_of_input + *Number_of_output); i++)
		{
			Vector_of_data_ref[i].erase(Vector_of_data_ref[i].end());
			Vector_of_data_ref[i].shrink_to_fit();
		}

		std::cout << std::setprecision(10);

		// initialization of variable
		*Number_of_hidden_layers = Number_of_neurons_in_hidden_layers_ref.capacity();

		Vector_of_neuron_values_training_ref.resize(*Number_of_hidden_layers + 2);
		Vector_of_neuron_values_validation_ref.resize(*Number_of_hidden_layers + 2);
		Vector_of_bias_training_ref.resize(*Number_of_hidden_layers + 1);
		Vector_of_bias_validation_ref.resize(*Number_of_hidden_layers + 1);
		Vector_of_weights_training_ref.resize(*Number_of_hidden_layers + 1);
		Vector_of_weights_validation_ref.resize(*Number_of_hidden_layers + 1);
        Vector_of_error_values_training_ref.resize(*Number_of_hidden_layers + 1);
		Vector_of_error_values_validation_ref.resize(*Number_of_hidden_layers + 1);

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

void Fully_connected_network::Swap_data
(
	
)
{
	// start counting time 
	const auto Start = std::chrono::high_resolution_clock::now();

	std::srand(time(NULL));

	int ran_d = 0;
	for (int i = 0; i < Vector_of_data_ref.capacity() - 1; i++)
	{
		for (int j = 0; j < Vector_of_data_ref[i].capacity() - 1; j++)
		{
			ran_d = std::rand() % Vector_of_data_ref[i].capacity();
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

void Fully_connected_network::Divide_data_to_training_and_validation
(	
	
)
{
	// start counting time 
	const auto Start = std::chrono::high_resolution_clock::now();

	if (*Train + *Validation == 100)
	{
		float x = static_cast<float>((Vector_of_data_ref[0].capacity()) / 100.0f);

		float train_cap = x * static_cast<float>(*Train);
		float validation_cap = x * static_cast<float>(*Validation);

		std::vector<float> zero_vector = { 0 };

		// training
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

		// validation
		for (int i = 0; i < Vector_of_data_ref.capacity(); i++)
		{
			Vector_of_data_validation_ref.push_back(zero_vector);
			Vector_of_data_validation_ref.shrink_to_fit();
			for (int j = static_cast<int>(train_cap); j < (train_cap + validation_cap); j++)
			{
				Vector_of_data_validation_ref[i].push_back(Vector_of_data_ref[i][j]);
			}
			Vector_of_data_validation_ref[i].erase(Vector_of_data_validation_ref[i].begin());
			Vector_of_data_validation_ref[i].shrink_to_fit();
		}

		Vector_of_data_validation_ref.shrink_to_fit();
		
		///////////////
		
		/*
		for (int i = 0; i < Vector_of_data_training_ref.capacity(); i++)
		{
		    for (int j = 0; j < Vector_of_data_training_ref[i].capacity(); j++)
		    {
		        std::cout << "Vector_of_data_training_ref[" << i << "][" << j << "]: " <<
		        Vector_of_data_training_ref[i][j] << std::endl;
		    }
		}
		
		for (int i = 0; i < Vector_of_data_validation_ref.capacity(); i++)
		{
		    for (int j = 0; j < Vector_of_data_validation_ref[i].capacity(); j++)
		    {
		        std::cout << "Vector_of_data_validation_ref[" << i << "][" << j << "]: " <<
		        Vector_of_data_validation_ref[i][j] << std::endl;
		    }
		}
		*/
		
	}
	else
	{
		std::cout << "Sum validation and test is not equal 100%.";
		exit(3);
	}
	
	// end counting time 
	const auto Stop = std::chrono::high_resolution_clock::now();

	Display_results_counting_time(Start, Stop, "Divide_data_to_training_and_validation()", 2);
}

void Fully_connected_network::Min_max_unipolar_scaling
(
	std::vector<std::vector<float>>& Vector_of_data,
	std::string name_of_vector,
	std::vector<float>& Min_data_value_vector,
	std::vector<float>& Max_data_value_vector
)
{
	// start counting time 
	auto Start = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < (*Number_of_input + *Number_of_output); i++)
	{
		Min_data_value_vector.push_back(0);
		Max_data_value_vector.push_back(0);
	}


	for (int i = 0; i < (*Number_of_input + *Number_of_output); i++)
	{
		Min_data_value_vector[i] = *std::min_element(Vector_of_data[i].begin(), Vector_of_data[i].end());
		Max_data_value_vector[i] = *std::max_element(Vector_of_data[i].begin(), Vector_of_data[i].end());

		for (int j = 0; j < Vector_of_data[i].capacity(); ++j)
		{
			Vector_of_data[i][j] = (Vector_of_data[i][j] - Min_data_value_vector[i]) / (Max_data_value_vector[i] - Min_data_value_vector[i]);
		}
	}

	// end counting time 
	auto Stop = std::chrono::high_resolution_clock::now();

	Display_results_counting_time(Start, Stop, "Min_max_unipolar_scaling: " + name_of_vector, 2);
}

void Fully_connected_network::Min_max_bipolar_scaling
(
	std::vector<std::vector<float>>& Vector_of_data,
	std::string name_of_vector,
	std::vector<float>& Min_data_value_vector,
	std::vector<float>& Max_data_value_vector
)
{
	// start counting time 
	auto Start = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < (*Number_of_input + *Number_of_output); i++)
	{
		Min_data_value_vector[i]= *std::min_element(Vector_of_data[i].begin(), Vector_of_data[i].end());
		Max_data_value_vector[i] = *std::max_element(Vector_of_data[i].begin(), Vector_of_data[i].end());
		
		for (int j = 0; j < Vector_of_data[i].capacity(); ++j)
		{
			Vector_of_data[i][j] = 2 * ((Vector_of_data[i][j] - Min_data_value_vector[i]) / (Max_data_value_vector[i] - Min_data_value_vector[i])) - 1;
		}
	}
	
	// end counting time 
	auto Stop = std::chrono::high_resolution_clock::now();

	Display_results_counting_time(Start, Stop, "Min_max_bipolar_scaling: " + name_of_vector, 2);
}

void Fully_connected_network::Create_vector_of_neurons_values_bias_and_errors
(
	std::vector<std::vector<float>>& Vector_of_neuron_values,
	std::vector<std::vector<float>>& Vector_of_bias,
	std::vector<std::vector<float>>& Vector_of_error_values,
	std::string name_of_vector
)
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
			Vector_of_error_values[iter - 1].push_back(0.5f);
			Vector_of_bias[iter - 1].push_back(0);
		}
	}

	// output layer of neurons
	for (int i = 0; i < *Number_of_output; i++)
	{
		Vector_of_neuron_values[iter].push_back(0);
		Vector_of_error_values[iter - 1].push_back(0.5f);
		Vector_of_bias[iter - 1].push_back(0);
	}
	
	// capacity = amount of neurons
	Vector_of_neuron_values.shrink_to_fit();
	for (int i = 0; i < Vector_of_neuron_values.capacity(); i++)
	{
		Vector_of_neuron_values[i].shrink_to_fit();
	}
    
    Vector_of_error_values.shrink_to_fit();
    for (int i = 0; i < Vector_of_error_values.capacity(); i++)
	{
		Vector_of_error_values[i].shrink_to_fit();
	}
    
    
	Vector_of_bias.shrink_to_fit();
	for (int i = 0; i < Vector_of_bias.capacity(); i++)
	{
		Vector_of_bias[i].shrink_to_fit();
	}

	// end counting time 
	auto Stop = std::chrono::high_resolution_clock::now();

	Display_results_counting_time(Start, Stop, "Create_vector_of_neurons_values: " + name_of_vector, 2);
}

void Fully_connected_network::Create_vector_of_weights
(
	std::vector<std::vector<float>>& Vector_of_weights, 
	std::vector<std::vector<float>>& Vector_of_neuron_values,
	std::string name_of_vector
)
{
	// start counting time 
	auto Start = std::chrono::high_resolution_clock::now();

	// first layer
	for (int i = 0; i < (*Number_of_input * Vector_of_neuron_values[1].capacity()); i++)
	{
		Vector_of_weights[0].push_back(0.5);
	}

	// hidden layers
	int iter = 0;

	for (int i = 1; i < *Number_of_hidden_layers; i++)
	{
		iter = Vector_of_neuron_values[i].capacity() * Vector_of_neuron_values[i + 1].capacity();

		for (int j = 0; j < iter; j++)
		{
			Vector_of_weights[i].push_back(0.5);
		}
	}

	// output layers

	for (int i = 0; i < *Number_of_output; i++)
	{
		iter = Vector_of_neuron_values[*Number_of_hidden_layers].capacity() * *Number_of_output;

		for (int j = 0; j < iter; j++)
		{
			Vector_of_weights[*Number_of_hidden_layers].push_back(0.5);
		}
	}
	
	// capacity = amount of weights
	Vector_of_weights.shrink_to_fit();
	for (int i = 0; i < Vector_of_weights.capacity(); i++)
	{
		Vector_of_weights[i].shrink_to_fit();
	}

	// end counting time 
	auto Stop = std::chrono::high_resolution_clock::now();

	Display_results_counting_time(Start, Stop, "Create_vector_of_weights: " + name_of_vector, 2);
}

void Fully_connected_network::Pseudo_random_numbers
(
	std::vector<std::vector<float>>& Vector,
	std::string name_of_vector
)
{
	// start counting time
	auto Start = std::chrono::high_resolution_clock::now();

	//std::random_device rd;  // Will be used to obtain a seed for the random number engine
	//std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
	std::mt19937 gen(12345); // Standard mersenne_twister_engine seeded with rd()
	std::uniform_real_distribution<> dis(Range_of_pseudo_numbers_values_ref[0],
		Range_of_pseudo_numbers_values_ref[1]);

	for (int i = 0; i < Vector.capacity(); i++)
	{
		for (int j = 0; j < Vector[i].capacity(); ++j)
		{
			Vector[i][j] = dis(gen);
		}
	}

	// end counting time 
	auto Stop = std::chrono::high_resolution_clock::now();

	Display_results_counting_time(Start, Stop, "Pseudo_random_numbers: " + name_of_vector, 2);
}

void Fully_connected_network::Calculating_the_network_MLP
(
	std::string* Open_filename, 
	std::string* Output_filename_path
)
{
	auto Start = std::chrono::high_resolution_clock::now();

	Startup_check_function();
    Read_data_MLP(Open_filename);
    //Swap_data();
	if(*Validation != 0)
	{
		Divide_data_to_training_and_validation();
	}
	else
	{
		Vector_of_data_training_ref = Vector_of_data_ref;
	}
    
	/*
    for (int i = 0; i < Vector_of_neuron_values_training_ref.capacity(); i++)
	{
	    for (int j = 0; j < Vector_of_neuron_values_training_ref[i].capacity(); j++)
	    {
	        std::cout <<  "Vector_of_neuron_values_training[" << i << "][" << j << "]: " << std::endl;
	        std::cout <<  std::setprecision(15) << Vector_of_neuron_values_training_ref[i][j] << std::endl;
	    }
	}
	*/
	switch(*Optimizer_function)
	{
		case(0):
		// TRAINING
		Min_max_unipolar_scaling
		(
			Vector_of_data_training_ref, 
			"Vector_of_data_training_ref",
			Min_training_value_vector,
			Max_training_value_vector
		);
			
		// VALIDATION
		if(*Validation != 0)
		{
			Min_max_unipolar_scaling
			(
			Vector_of_data_validation_ref, 
			"Vector_of_data_validation_ref",
			Min_validation_value_vector,
			Max_validation_value_vector
			);
		}
		break;

		case(1):
		// TRAINING
		Min_max_bipolar_scaling
		(
			Vector_of_data_training_ref, 
			"Vector_of_data_training_ref",
			Min_training_value_vector,
			Max_training_value_vector
		);
			
		// VALIDATION
		if(*Validation != 0)
		{
			Min_max_bipolar_scaling
			(
			Vector_of_data_validation_ref, 
			"Vector_of_data_validation_ref",
			Min_validation_value_vector,
			Max_validation_value_vector
			);
		}
		break;
	}

	// TRAINING
	Create_vector_of_neurons_values_bias_and_errors(
		Vector_of_neuron_values_training_ref, 
		Vector_of_bias_training_ref,
		Vector_of_error_values_training,
		"Vector_of_neurons_values_bias_and_errors_training");

	// VALIDATION
	if(*Validation != 0)
	{
		Create_vector_of_neurons_values_bias_and_errors(
		Vector_of_neuron_values_validation_ref, 
		Vector_of_bias_validation_ref,
		Vector_of_error_values_validation,
		"Vector_of_neurons_values_bias_and_errors_validation");
	}

	// TRAINING
	Create_vector_of_weights(
		Vector_of_weights_training_ref,
		Vector_of_neuron_values_training_ref,
		"Vector_of_weights_training_ref");

	// VALIDATION
	if(*Validation != 0)
	{
		Create_vector_of_weights(
		Vector_of_weights_validation_ref,
		Vector_of_neuron_values_validation_ref,
		"Vector_of_weights_validation_ref");
	}
    
	// TRAINING
	Pseudo_random_numbers(
		Vector_of_weights_training_ref,
		"Vector_of_weights_training_ref");
	Pseudo_random_numbers(
		Vector_of_bias_training_ref,
		"Vector_of_bias_training_ref");

	// VALIDATION
	if(*Validation != 0)
	{
		Pseudo_random_numbers(
		Vector_of_weights_validation_ref,
		"Vector_of_weights_validation_ref");
		Pseudo_random_numbers(
		Vector_of_bias_validation_ref,
		"Vector_of_bias_validation_ref");
	}
	
	int it_neuron = 0;          // it_  - iterator ????????

	for (int epoch = 0; epoch < *Number_of_epochs; epoch++)
	{
		std::cout << ">> Calculating of the [" << epoch + 1 << "] epoch >";

		// TRAINING DATA

		std::cout << "> Training data MAPE >"; 

		for (int it_data = 0; it_data < Vector_of_data_training_ref[0].capacity(); it_data++)
		{
			// forward propagation

			Forward_propagation_the_network_MLP
			(
				Vector_of_data_training_ref,
				Vector_of_neuron_values_training_ref,
				Vector_of_weights_training_ref,
				Vector_of_bias_training_ref,
				it_data
			);

			// back propagation 

			Backpropagation_the_network_MLP
			(
				Vector_of_data_training_ref,
				Vector_of_neuron_values_training_ref,
				Vector_of_weights_training_ref,
				Vector_of_bias_training_ref,
				Vector_of_error_values_training_ref,
				Max_training_value_vector,
				Min_training_value_vector,
				MAPE_value_training_ref,
				it_data,
				epoch
			);
		}

		MAPE_value_training_ref[epoch]= ((1.0f / Vector_of_data_training_ref[0].capacity()) *
			MAPE_value_training_ref[epoch]);

		std::cout << "> " << std::fixed << std::setprecision(5) << MAPE_value_training_ref[epoch];

		if (epoch > 0)
		{
			std::cout << " ( " <<  std::fixed << std::showpos << std::setprecision(5) <<
			MAPE_value_training_ref[epoch] - MAPE_value_training_ref[epoch - 1] << " )" <<
			std::noshowpos; 
		}

		// VALIDATION DATA

		if(*Validation != 0)
		{
			std::cout << " >> Validation data MAPE >"; 

			for (int it_data = 0; it_data < Vector_of_data_validation_ref[0].capacity(); it_data++)
			{
				Forward_propagation_the_network_MLP
				(
					Vector_of_data_validation_ref,
					Vector_of_neuron_values_validation_ref,
					Vector_of_weights_validation_ref,
					Vector_of_bias_validation_ref,
					it_data
				);

				Backpropagation_the_network_MLP
				(
					Vector_of_data_validation_ref,
					Vector_of_neuron_values_validation_ref,
					Vector_of_weights_validation_ref,
					Vector_of_bias_validation_ref,
					Vector_of_error_values_validation_ref,
					Max_validation_value_vector,
					Min_validation_value_vector,
					MAPE_value_validation_ref,
					it_data,
					epoch
				); 
			}

			MAPE_value_validation_ref[epoch] = ((1.0f / Vector_of_data_validation_ref[0].capacity()) *
				MAPE_value_validation_ref[epoch]);
			
			std::cout << "> " << std::fixed << std::setprecision(5) << MAPE_value_validation_ref[epoch];
			if (epoch > 0)
			{
				std::cout << " ( " <<  std::fixed << std::showpos << std::setprecision(5) <<
				MAPE_value_validation_ref[epoch] - MAPE_value_validation_ref[epoch - 1] << " )" <<
				std::noshowpos; 
			}
		}

        /*
        std::cout << "Print: " << std::endl;
    	std::cout << "Vector_of_weights[0][0]" << Vector_of_weights_training_ref[0][0] << std::endl;
    	std::cout << "Vector_of_weights[0][1]" << Vector_of_weights_training_ref[0][1] << std::endl;
    	std::cout << "Vector_of_weights[0][2]" << Vector_of_weights_training_ref[0][2] << std::endl;
    	std::cout << "Vector_of_weights[0][3]" << Vector_of_weights_training_ref[0][3] << std::endl;
    	std::cout << "Vector_of_weights[0][4]" << Vector_of_weights_training_ref[0][4] << std::endl;
    	std::cout << "Vector_of_weights[0][5]" << Vector_of_weights_training_ref[0][5] << std::endl;
    	std::cout << "Vector_of_weights[1][0]" << Vector_of_weights_training_ref[1][0] << std::endl;
    	std::cout << "Vector_of_weights[1][1]" << Vector_of_weights_training_ref[1][1] << std::endl;
    	std::cout << "Vector_of_weights[1][2]" << Vector_of_weights_training_ref[1][2] << std::endl;
    	std::cout << "Vector_of_weights[1][3]" << Vector_of_weights_training_ref[1][3] << std::endl;
    	std::cout << "Vector_of_weights[1][4]" << Vector_of_weights_training_ref[1][4] << std::endl;
    	std::cout << "Vector_of_weights[1][5]" << Vector_of_weights_training_ref[1][5] << std::endl;
    	std::cout << "Vector_of_weights[2][0]" << Vector_of_weights_training_ref[2][0] << std::endl;
    	std::cout << "Vector_of_weights[2][1]" << Vector_of_weights_training_ref[2][1] << std::endl;
        
        */
        
		std::cout << std::endl;
	}

	std::cout << std::endl;

	std::cout << "MAPE_training(" << *Number_of_epochs << "): " << MAPE_value_training_ref[*Number_of_epochs - 1] << std::endl;

	if(*Validation != 0)
	{
		std::cout << "MAPE_validation(" << *Number_of_epochs << "): " << MAPE_value_validation_ref[*Number_of_epochs - 1] << std::endl;
	}
	
	std::cout << std::setprecision(10) << "Learning rate: " << *Learning_rate_factor << std::endl;
 
	auto Stop = std::chrono::high_resolution_clock::now();

	Display_results_counting_time(Start, Stop, "Calculating_the_network_MLP", 2);

    Write_data_MLP(Output_filename_path);
}

void Fully_connected_network::Forward_propagation_the_network_MLP
(
	std::vector<std::vector<float>>& Vector_of_data,
	std::vector<std::vector<float>>& Vector_of_neuron_values,
	std::vector<std::vector<float>>& Vector_of_weights,
	std::vector<std::vector<float>>& Vector_of_bias,
	int it_data
)
{
	// input layer

	for (int i = 0; i < Vector_of_neuron_values[0].capacity(); i++)
	{
		Vector_of_neuron_values[0][i] =
			Vector_of_data[i][it_data];
	}

	// hidden layers

	for (int i = 1; i < *Number_of_hidden_layers + 1; i++)
	{
		for (int j = 0; j < Vector_of_neuron_values[i].capacity(); j++)
		{
			for (int k = 0; k < Vector_of_neuron_values[i - 1].capacity(); k++)
			{
				Vector_of_neuron_values[i][j] +=
					((Vector_of_neuron_values[i - 1][k] *
						Vector_of_weights[i - 1][j + (k * Vector_of_neuron_values[i].capacity())]));
			}

			switch (Activation_functions[i - 1])
            {
                case(0):
                
                Vector_of_neuron_values[i][j] = Linear_activation_function
				(
                	Vector_of_neuron_values[i][j] +
                	Vector_of_bias[i-1][j]
				);
                break;
                case(1):
                		
                Vector_of_neuron_values[i][j] = Unipolar_sigmoidal_function
				(
                	Vector_of_neuron_values[i][j] +
                	Vector_of_bias[i-1][j]
				);
                break;
                
                case(2):
                		
                Vector_of_neuron_values[i][j] = Bipolar_sigmoidal_function
				(
                	Vector_of_neuron_values[i][j] +
                	Vector_of_bias[i-1][j]
				);
                break;
            }
		}
	}

	// output layer
	for (int n = 0; n < *Number_of_output; n++)
	{
		for (int o = 0; o < Vector_of_neuron_values[*Number_of_hidden_layers].capacity(); o++)
		{
			Vector_of_neuron_values[1 + *Number_of_hidden_layers][n] +=
				((Vector_of_neuron_values[*Number_of_hidden_layers][o] * Vector_of_weights[*Number_of_hidden_layers][o]));
		}

		switch (Activation_functions[*Number_of_hidden_layers])
        {
        	case(0):
        
        		Vector_of_neuron_values[1 + *Number_of_hidden_layers][n] = Linear_activation_function(
        			Vector_of_neuron_values[1 + *Number_of_hidden_layers][n] +
        			Vector_of_bias[*Number_of_hidden_layers][n]);
        	break;
        
        	case(1):
        
        		Vector_of_neuron_values[1 + *Number_of_hidden_layers][n] = Unipolar_sigmoidal_function(
        			Vector_of_neuron_values[1 + *Number_of_hidden_layers][n] +
        			Vector_of_bias[*Number_of_hidden_layers][n]);
        	break;
        	case(2):
        
        		Vector_of_neuron_values[1 + *Number_of_hidden_layers][n] = Bipolar_sigmoidal_function(
        			Vector_of_neuron_values[1 + *Number_of_hidden_layers][n] +
        			Vector_of_bias[*Number_of_hidden_layers][n]);
        	break;
        }
	}
	
	
	/*
	for (int i = 0; i < Vector_of_neuron_values.capacity(); i++)
	{
	    for (int j = 0; j < Vector_of_neuron_values[i].capacity(); j++)
	    {
	        std::cout <<  "Vector_of_neuron_values[" << i << "][" << j << "]: " << std::endl;
	        std::cout <<  std::setprecision(15) << Vector_of_neuron_values[i][j] << std::endl;
	    }
	}
	
	
	std::cout << Vector_of_data[0][it_data] << std::endl;
	
	for (int i = 0; i < Vector_of_weights.capacity(); i++)
	{
	    for (int j = 0; j < Vector_of_weights[i].capacity(); j++)
	    {
	        std::cout <<  "Vector_of_weights[" << i << "][" << j << "]: " << std::endl;
	        std::cout <<  std::setprecision(15) << Vector_of_weights[i][j] << std::endl;
	    }
	}
	for (int i = 0; i < Vector_of_bias.capacity(); i++)
	{
	    for (int j = 0; j < Vector_of_bias[i].capacity(); j++)
	    {
	        std::cout <<  "Vector_of_bias[" << i << "][" << j << "]: " << std::endl;
	        std::cout <<  std::setprecision(15) << Vector_of_bias[i][j] << std::endl;
	    }
	}
	
	std::cout << "END" << std::endl;
	*/
	
}

void Fully_connected_network::Backpropagation_the_network_MLP
(
	std::vector<std::vector<float>>& Vector_of_data,
	std::vector<std::vector<float>>& Vector_of_neuron_values,
	std::vector<std::vector<float>>& Vector_of_weights,
	std::vector<std::vector<float>>& Vector_of_bias,
	std::vector<std::vector<float>>& Vector_of_error_values,
	std::vector<float>& Max_value_vector,
	std::vector<float>& Min_value_vector,
	std::vector<float>& MAPE_value,
	int it_data,
	int epoch
)
{
	// reset error values
	for (int i = 0; i < Vector_of_error_values.capacity(); i++)
	{
		for (int j = 0; j < Vector_of_error_values[i].capacity(); j++)
		{
			Vector_of_error_values[i][j] = 0.0f;
		}
	}

	// error counting

	// output layer

	for (int i = static_cast<int>(Vector_of_weights.capacity() - 1);
		i > ((Vector_of_weights.capacity() - 1) - *Number_of_output); i--)
	{
		for (int j = *Number_of_output; j > 0; j--)
		{
			Vector_of_error_values[*Number_of_hidden_layers][*Number_of_output - j] =
				Vector_of_data[Vector_of_data.capacity() - j][it_data] -
				Vector_of_neuron_values[1 + *Number_of_hidden_layers][*Number_of_output - j];
			
			/*
			std::cout <<  "Vector_of_data[" << Vector_of_data.capacity() - j << "][" << it_data << "]: " << std::endl;
	        std::cout <<  Vector_of_data[Vector_of_data.capacity() - j][it_data] << std::endl;
	        std::cout <<  "Vector_of_neuron_values[" << 1 + *Number_of_hidden_layers << "][" << *Number_of_output - j << "]: " << std::endl;
	        std::cout <<  Vector_of_neuron_values[1 + *Number_of_hidden_layers][*Number_of_output - j] << std::endl;
			std::cout <<  "Vector_of_error_values[" << *Number_of_hidden_layers << "][" << *Number_of_output - j << "]: " << std::endl;
	        std::cout <<  Vector_of_error_values[*Number_of_hidden_layers][*Number_of_output - j] << std::endl;
			*/
	        
			switch(*Data_normalizer)
			{
				case(0):
				{
					float data_denormalization = 
					    Vector_of_data[Vector_of_data.capacity() - j][it_data] *
						(Max_value_vector[*Number_of_input] - 
						Min_value_vector[*Number_of_input]) +
						Min_value_vector[*Number_of_input];

					float prediction_denormalization = 
					    Vector_of_neuron_values[*Number_of_hidden_layers][*Number_of_output - j] *
						(Max_value_vector[*Number_of_input] - 
						Min_value_vector[*Number_of_input]) +
						Min_value_vector[*Number_of_input];
					
					MAPE_value[epoch] += (std::abs((data_denormalization - prediction_denormalization) /
						(data_denormalization))) * 100.0f;
					break;
				}
				
				case(1):
				
				{
					float data_denormalization = 
					    ((Vector_of_data[Vector_of_data.capacity() - j][it_data] + 1) / 2) *
						(Max_value_vector[*Number_of_input] - 
						Min_value_vector[*Number_of_input]) +
						Min_value_vector[*Number_of_input];

					float prediction_denormalization = 
					    ((Vector_of_neuron_values[*Number_of_hidden_layers][*Number_of_output - j] + 1) / 2) *
						(Max_value_vector[*Number_of_input] - 
						Min_value_vector[*Number_of_input]) +
						Min_value_vector[*Number_of_input];
					
					MAPE_value[epoch] += (std::abs((data_denormalization - prediction_denormalization) /
						(data_denormalization))) * 100.0f;
					break;
				}
			}
		}
	}
	
	//std::cout << "Hidden weights" << std::endl; 
	
	// hidden layers

	int weight_iter = 0;

	for (int i = *Number_of_hidden_layers; i > 0; i--)
	{
		weight_iter = 0;
		for (int j = 0; j < Vector_of_error_values[i - 1].capacity(); j++)		
		{
			for (int k = 0; k < Vector_of_error_values[i].capacity(); k++)
			{
				Vector_of_error_values[i - 1][j] +=
					Vector_of_error_values[i][k] *
					Vector_of_weights[i][weight_iter];
				//std::cout <<  "Vector_of_error_values[" << i - 1 << "][" << j << "]: " << std::endl;
    	        //std::cout <<  Vector_of_error_values[i - 1][j] << std::endl;
    	        //std::cout <<  " = " << std::endl;
    	        //std::cout <<  "Vector_of_error_values[" << i << "][" << k << "]: " << std::endl;
    	        //std::cout <<  Vector_of_error_values[i][k] << std::endl;
    	        //std::cout <<  " * " << std::endl;
    	        //std::cout <<  "Vector_of_weights[" << i << "][" << weight_iter << "]: " << std::endl;
    	        //std::cout <<  Vector_of_weights[i][j] << std::endl;
				weight_iter += 1;
			}
		}
	}

    // new values of weights
    
	switch(*Optimizer_function)
	{
		case(0):

		// new values of bias weight

		for (int i = 0; i < Vector_of_neuron_values.capacity() - 1; i++)
		{
			for (int j = 0; j < Vector_of_neuron_values[i + 1].capacity(); j++)
			{
				switch(Activation_functions[i])
				{
					case(0):    // linear
					Vector_of_bias[i][j] = Vector_of_bias[i][j] +
        				*Learning_rate_factor * Vector_of_error_values[i][j] * 1.0f;
					
					break;

					case(1):    // unipolar sigmoidal
					//std::cout <<  "OLDVector_of_bias[" << i << "][" << j << "]: " << std::endl;
	                //std::cout <<  Vector_of_bias[i][j] << std::endl;
                    Vector_of_bias[i][j] = Vector_of_bias[i][j] +
        				*Learning_rate_factor * Vector_of_error_values[i][j] *
        				(*Beta * Vector_of_neuron_values[i + 1][j] *
        					(1.0f - Vector_of_neuron_values[i + 1][j])) * 1.0f;
        			//std::cout <<  "NEWVector_of_bias[" << i << "][" << j << "]: " << std::endl;
	                //std::cout <<  Vector_of_bias[i][j] << std::endl;
					
					break;

					case(2):    // bipolar sigmoidla
					Vector_of_bias[i][j] = Vector_of_bias[i][j] +
        				*Learning_rate_factor * Vector_of_error_values[i][j] *
        				((*Beta / 2.0f) * (1.0f - pow((Vector_of_neuron_values[i + 1][j]), 2))) * 1.0f;
					
					break;
					
				}
			}
		}

		// new values of Vector_of_weights
        
        int weights_iterator = 0;
        
		for (int i = 1; i < Vector_of_neuron_values.capacity(); i++)
		{
		    for (int j = 0; j < Vector_of_neuron_values[i - 1].capacity(); j++)
		    {
		        for (int k = 0; k < Vector_of_neuron_values[i].capacity(); k++)
		        {
		            switch(Activation_functions[i - 1])
    				{
    					case(0):    // linear
            			Vector_of_weights[i - 1][k + weights_iterator] =
    				        Vector_of_weights[i - 1][k + weights_iterator] +
    				        *Learning_rate_factor *
    					    Vector_of_error_values[i - 1][k] *
    					    Vector_of_neuron_values[i - 1][j];
    					
    					break;
    
    					case(1):    // unipolar sigmoidal
    					//std::cout <<  "OLDVector_of_weights[" << i - 1 << "][" << k + weights_iterator << "]: " <<  std::endl;
	                    //std::cout <<  Vector_of_weights[i - 1][k + weights_iterator] << std::endl;
            			Vector_of_weights[i - 1][k + weights_iterator] =
    				        Vector_of_weights[i - 1][k + weights_iterator] +
    				        (*Learning_rate_factor *
    					    Vector_of_error_values[i - 1][k] *
    					    (*Beta * Vector_of_neuron_values[i][k] *
    						(1 - Vector_of_neuron_values[i][k])) *
    					    Vector_of_neuron_values[i - 1][j]);
                			//std::cout << std::endl;
                			//std::cout << "Vector_of_weights[" << i - 1 << "][" << k + weights_iterator << "]: " << Vector_of_weights[i - 1][k + weights_iterator] << std::endl;
                			//std::cout << "Vector_of_error_values[" << i - 1 << "][" << k << "]: " << Vector_of_error_values[i - 1][k] << std::endl;
                			//std::cout << "Vector_of_neuron_values[" << i << "][" << k << "]: " << Vector_of_neuron_values[i][k]  << std::endl;
                			//std::cout << "Vector_of_neuron_values[" << i - 1 << "][" << j << "]: " << Vector_of_neuron_values[i - 1][j] << std::endl;
                			//std::cout <<  "NEWVector_of_weights[" << i - 1 << "][" << k + weights_iterator << "]: " <<  std::endl;
	                        //std::cout <<  Vector_of_weights[i - 1][k + weights_iterator] << std::endl;
    					
    					break;
    
    					case(2):    // bipolar sigmoidla
            			Vector_of_weights[i - 1][k + weights_iterator] =
    				        Vector_of_weights[i - 1][k + weights_iterator] +
    				        (*Learning_rate_factor *
    					    Vector_of_error_values[i - 1][k] *
    					    ((*Beta / 2.0f) * (1.0f - pow((Vector_of_neuron_values[i][k]), 2))) *
    					    Vector_of_neuron_values[i - 1][j]);
    					
    					break;
    					
    				}
    				
		           
		        }
		        weights_iterator += Vector_of_neuron_values[i].capacity();
    		}
    		
    		weights_iterator = 0;
		}

		break;
		//case(1):
		

		
		//break;
	}
}

float Fully_connected_network::Linear_activation_function
(
	float e
)
{
	return static_cast<float>(e);
}

float Fully_connected_network::Unipolar_sigmoidal_function
(
	float e
)
{
	return static_cast<float>(1.0f / (1.0f + exp(-(*Beta) * e)));
}

float Fully_connected_network::Bipolar_sigmoidal_function
(
	float e
)
{
	return static_cast<float>(-1.0f + 2.0f / (1.0f + exp(-(*Beta) * e)));
}

void Fully_connected_network::Write_data_MLP
(
	std::string* Output_filename_path
)
{
	// start counting time 
	const auto Start = std::chrono::high_resolution_clock::now();

	auto now = std::chrono::system_clock::now();

	auto localTime = std::chrono::system_clock::to_time_t(now);

	// Creating .txt file with output data

	const char* extension = ".txt";

    std::stringstream ss;

    ss << "MLP_" << *Number_of_input;

    for (int i = 0; i < *Number_of_hidden_layers; i++)
    {
        ss << "-";
        ss << Number_of_neurons_in_hidden_layers[i];
    }

	ss << "-" << *Number_of_output;

    ss << "_" << "_" << *Number_of_epochs << "_Epochs_" <<
	std::put_time(std::localtime(&localTime), "%d_%m_%Y_%H_%M_%S") << extension;

    std::string file_date = ss.str();

    file_date.erase(remove(file_date.begin(), file_date.end(), '\"'), file_date.end());

    std::cout << *Output_filename_path + file_date << std::endl;

    // ofstream only can write file
    std::ofstream file_txt(*Output_filename_path + file_date);

	if (file_txt.is_open())
	{
		// head
		file_txt << file_date << std::endl;
		file_txt << std::endl;
		file_txt << "MAPE_training(" << *Number_of_epochs << "): " << MAPE_value_training_ref[*Number_of_epochs - 1] << std::endl;
		file_txt << "MAPE_validation(" << *Number_of_epochs << "): " << MAPE_value_validation_ref[*Number_of_epochs - 1] << std::endl;
		file_txt << std::endl;
        
        for(int i = 0; i < (*Number_of_input + *Number_of_output); i++)
		{
			file_txt << "*Max_training_value[" << i << "]: " << Max_training_value_vector[i] << std::endl;
			file_txt << "*Min_training_value[" << i << "]: " << Min_training_value_vector[i] << std::endl;

			file_txt << std::endl;
		}

		file_txt << std::endl;

		for(int i = 0; i < (*Number_of_input + *Number_of_output); i++)
		{
			file_txt << "*Max_validation_value[" << i << "]: " << Max_validation_value_vector[i] << std::endl;
			file_txt << "*Min_validation_value[" << i << "]: " << Min_validation_value_vector[i] << std::endl;

			file_txt << std::endl;
		}

		file_txt << std::endl;
		file_txt << "Number of epochs || MAPE_value_training || MAPE_value_validation" << std::endl;
		file_txt << std::endl;
		
		// data
		for (int i = 0; i < *Number_of_epochs; ++i)
		{
			file_txt << "[" << i + 1 << "]";
			file_txt << "\t" << "\t";
			file_txt << std::fixed << std::setprecision(6) << MAPE_value_training_ref[i];
			file_txt << "\t" << "\t";
			file_txt << std::fixed << std::setprecision(6) << MAPE_value_validation_ref[i];
			file_txt << std::endl;
		}

		file_txt << "\n" << "\n";

		file_txt << "Vector_of_weights_training";
		file_txt << "\n" << "\n";
		file_txt << "Pos. || value";
		file_txt << "\n" << "\n";

		for (int i = 0; i < Vector_of_weights_training_ref.capacity(); ++i)
		{
		    for (int j = 0; j < Vector_of_weights_training_ref[i].capacity(); j++)
		    {
		        file_txt << "[" << i << "][" << j << "]";
    			file_txt << "\t" << "\t";
    			file_txt << Vector_of_weights_training_ref[i][j];
    			file_txt << "\n"; 
		    }
		}

		file_txt << "\n" << "\n";

		file_txt << "Vector_of_bias_training";
		file_txt << "\n" << "\n";
		file_txt << "Pos. || value";
		file_txt << "\n" << "\n";

		for (int i = 0; i < Vector_of_bias_training_ref.capacity(); ++i)
		{
		    for (int j = 0; j < Vector_of_bias_training_ref[i].capacity(); ++j)
		    {
		        file_txt << "[" << i << "][" << j << "]";
    			file_txt << "\t" << "\t";
    			file_txt << Vector_of_bias_training_ref[i][j];
    			file_txt << "\n";   
		    }
		}
		
		file_txt << "\n" << "\n";

		file_txt << "Vector_of_weights_validation";
		file_txt << "\n" << "\n";
		file_txt << "Pos. || value";
		file_txt << "\n" << "\n";

		for (int i = 0; i < Vector_of_weights_validation_ref.capacity(); ++i)
		{
		    for (int j = 0; j < Vector_of_weights_validation_ref[i].capacity(); ++j)
		    {
    		    file_txt << "[" << i << "][" << j << "]";
    			file_txt << "\t" << "\t";
    			file_txt << Vector_of_weights_validation_ref[i][j];
    			file_txt << "\n";    
		    }
		}

		file_txt << "\n" << "\n";

		file_txt << "Vector_of_bias_validation";
		file_txt << "\n" << "\n";
		file_txt << "Pos. || value";
		file_txt << "\n" << "\n";

		for (int i = 0; i < Vector_of_bias_validation_ref.capacity(); ++i)
		{
		    for (int j = 0; j < Vector_of_bias_validation_ref[i].capacity(); ++j)
		    {
		        file_txt << "[" << i << "][" << j << "]";
    			file_txt << "\t" << "\t";
    			file_txt << Vector_of_bias_validation_ref[i][j];
    			file_txt << "\n";
		    }
		}

		file_txt.close();
	}
	else
	{
		std::cout << "Error, file '.txt' not created. Check if name of file is correct.";
		exit(3);
	}
    
	// Creating .c file for drawing plot (root cern)

	extension = ".c";

	std::stringstream cc;
	
    cc << "MLP_" << *Number_of_input;

    for (int i = 0; i < *Number_of_hidden_layers; i++)
    {
        cc << "-";
        cc << Number_of_neurons_in_hidden_layers[i];
    }

	cc << "-" << *Number_of_output;

    cc << "_" << "_" << *Number_of_epochs << "_Epochs_";
	cc << std::put_time(std::localtime(&localTime), "%d_%m_%Y_%H_%M_%S") << "_Plot" << extension;

    file_date = cc.str();

    file_date.erase(remove(file_date.begin(), file_date.end(), '\"'), file_date.end());

    std::cout << *Output_filename_path + file_date << std::endl;

    // ofstream only can write file
    std::ofstream file_c(*Output_filename_path + "../Output_data_graph/" + file_date);

	if (file_c.is_open())
	{	
		file_c << "{" << std::endl;
		
		
		file_c << "\t" << "float x[" << *Number_of_epochs << "] = {" << std::endl;

		for(int i = 0; i < *Number_of_epochs; i++)
		{
			file_c << "\t" << i + 1 << "," << std::endl;
		}

		file_c << "\t" << "};" << std::endl;
		file_c << std::endl;
		

		
		file_c << "\t" << "float y_training[" << *Number_of_epochs << "] = {" << std::endl;

		for(int i = 0; i < *Number_of_epochs; i++)
		{
			file_c << "\t" <<  MAPE_value_training_ref[i] << "," << std::endl;
		}

		file_c << "\t" << "};" << std::endl;
		file_c << std::endl;

		file_c << "\t" << "float y_validation[" << *Number_of_epochs << "] = {" << std::endl;

		for(int i = 0; i < *Number_of_epochs; i++)
		{
			file_c << "\t" <<  MAPE_value_validation_ref[i] << "," << std::endl;
		}
		
		file_c << "\t" << "};" << std::endl;
		file_c << std::endl;
		
		file_c << "\t" << "TMultiGraph *mg = new TMultiGraph();" << std::endl;
		
		// training graph
		file_c << "\t" << "TGraph* gr1 = new TGraph(" << *Number_of_epochs;
		file_c << ", x, y_training);" << std::endl;
		file_c << "\t" << "gr1->SetName(\"gr1\");" << std::endl;
		file_c << "\t" << "gr1->SetMarkerColor(1);" << std::endl;
		file_c << "\t" << "gr1->SetMarkerSize(0.05);" << std::endl;
		file_c << "\t" << "gr1->SetMarkerStyle(7);" << std::endl;
		file_c << "\t" << "gr1->SetLineColor(kGreen);" << std::endl;
		file_c << "\t" << "gr1->SetLineWidth(5);" << std::endl;

		// validation graph
		file_c << "\t" << "TGraph* gr2 = new TGraph(" << *Number_of_epochs;
		file_c << ", x, y_validation);" << std::endl;
		file_c << "\t" << "gr2->SetName(\"gr2\");" << std::endl;
		file_c << "\t" << "gr2->SetMarkerColor(2);" << std::endl;
		file_c << "\t" << "gr2->SetMarkerSize(0.05);" << std::endl;
		file_c << "\t" << "gr2->SetMarkerStyle(8);" << std::endl;
		file_c << "\t" << "gr2->SetLineColor(kOrange);" << std::endl;
		file_c << "\t" << "gr2->SetLineWidth(5);" << std::endl;

		file_c << "\t" << "mg->Add(gr1);" << std::endl;
		file_c << "\t" << "mg->Add(gr2);" << std::endl;
		file_c << "\t" << "mg->GetXaxis()->SetTitle(\"Number of epochs\");" << std::endl;
   		file_c << "\t" << "mg->GetYaxis()->SetTitle(\"MAPE\");" << std::endl;
		file_c << "\t" << "mg->SetMinimum(0.);" << std::endl;

		file_c << "\t" << "TCanvas *c1 = new TCanvas(\"c1\",\"multigraph\");" << std::endl;
		file_c << "\t" << "c1->SetGrid();" << std::endl;
		file_c << "\t" << "c1->SetCanvasSize(3840, 2160);" << std::endl;

		file_c << "\t" << "mg->Draw(" << "\"" << "AC*" << "\"" << ");" << std::endl;
		file_c << "\t" << "auto legend = new TLegend(0.9,0.9,0.9,0.9);" << std::endl;
   		file_c << "\t" << "legend->SetHeader(\"Legend\",\"C\");" << std::endl;
   		file_c << "\t" << "legend->AddEntry(\"gr1\",\"MAPE value training\",\"l\");" << std::endl;
   		file_c << "\t" << "legend->AddEntry(\"gr2\",\"MAPE value validation\",\"l\");" << std::endl;
   		file_c << "\t" << "legend->Draw();" << std::endl;
		file_c << "\t" << "c1->Print(" << "\"" << "../Output_data_graph/";
		file_c << file_date << ".bmp" << "\"" << ");" << std::endl;

		file_c << "}";

		file_c.close();
	}
	else
	{
		std::cout << "Error, file '.c' not created. Check if name of file is correct.";
		exit(3);
	}

	//system(("root -q ../Output_data_graph/" + file_date).c_str());
    
	// Creating .cpp file for a trained network

	extension = ".cpp";

	std::stringstream cpp;
	
    cpp << "MLP_" << *Number_of_input;

	for (int i = 0; i < *Number_of_hidden_layers; i++)
    {
        cpp << "-";
        cpp << Number_of_neurons_in_hidden_layers[i];
    }

	cpp << "-" << *Number_of_output;

	cpp << "_" << "_" << *Number_of_epochs << "_Epochs_";
	cpp << std::put_time(std::localtime(&localTime), "%d_%m_%Y_%H_%M_%S") << "_Test" << extension;

    file_date = cpp.str();

    file_date.erase(remove(file_date.begin(), file_date.end(), '\"'), file_date.end());

    std::cout << *Output_filename_path + file_date << std::endl;

    // ofstream only can write file
    std::ofstream file_cpp(*Output_filename_path + "../Test_example/" + file_date);

	if (file_cpp.is_open())
	{	
		file_cpp << "#include \"../include/Fully_connected_network.hpp\"" << std::endl;

		file_cpp << std::endl;

		file_cpp << "int main()" << std::endl;
		file_cpp << "{" << std::endl;
		
		file_cpp << "\t" << "std::vector<std::vector<float>> Vector_of_data =" << std::endl;
		file_cpp << "\t" << "{" << std::endl;

		for(int i = 0; i < (*Number_of_input); i++)
		{
			file_cpp << "\t" << "\t" << "{ 0 }, // enter the values" << std::endl;
		}
		
		file_cpp << "\t" << "};" << std::endl;

		file_cpp << std::endl;

		file_cpp << "\t" << "std::vector<std::vector<float>> Vector_of_neuron_values =" << std::endl;
		file_cpp << "\t" << "{" << std::endl;

		for(int i = 0; i < (*Number_of_input + *Number_of_output); i++)
		{
			file_cpp << "\t" << "\t" << "{ ";
			for(int j = 0; j < Vector_of_neuron_values_training_ref[i].capacity(); j++)
			{
				if(j < Vector_of_neuron_values_training_ref[i].capacity() - 1)
				{
					file_cpp << "0, ";
				}
				else
				{
					file_cpp << "0 },";
				}
			}
			file_cpp << std::endl;
		}
		
		file_cpp << "\t" << "};" << std::endl;

		file_cpp << std::endl;

		for(int i = 0; i < *Number_of_input; i++)
		{
			file_cpp << "\t" << "float input_" << i << "_max = " << Max_training_value_vector[i] << ";" << std::endl;
			file_cpp << "\t" << "float input_" << i << "_min = " << Min_training_value_vector[i] << ";" << std::endl;
		}

		file_cpp << std::endl;

		for(int i = 0; i < *Number_of_output; i++)
		{
			file_cpp << "\t" << "float output_" << i << "_max = " <<
			Max_training_value_vector[(*Number_of_input + (*Number_of_output - i)) - 1] << ";" << std::endl;
			file_cpp << "\t" << "float output_" << i << "_min = " <<
			Min_training_value_vector[(*Number_of_input + (*Number_of_output - i)) - 1] << ";" << std::endl;
		}

		file_cpp << std::endl;

		file_cpp << "\t" << "std::vector<std::vector<float>> Vector_of_weights_training =" << std::endl;
		file_cpp << "\t" << "{" << std::endl;

		for (int i = 0; i < Vector_of_weights_training_ref.capacity(); i++)
		{
			file_cpp << "\t" << "\t" << "{ ";
		    for (int j = 0; j < Vector_of_weights_training_ref[i].capacity(); j++)
		    {
				if(j < Vector_of_weights_training_ref[i].capacity() - 1)
				{
					file_cpp << Vector_of_weights_training_ref[i][j] << ", ";
				}
				else
				{
					file_cpp << Vector_of_weights_training_ref[i][j] << " },";
				}
		    }
			file_cpp << std::endl;
		}

		file_cpp << "\t" << "};" << std::endl;

		file_cpp << std::endl;

		file_cpp << "\t" << "std::vector<std::vector<float>> Vector_of_bias_training =" << std::endl;
		file_cpp << "\t" << "{" << std::endl;

		for (int i = 0; i < Vector_of_bias_training_ref.capacity(); i++)
		{
			file_cpp << "\t" << "\t" << "{ ";
		    for (int j = 0; j < Vector_of_bias_training_ref[i].capacity(); j++)
		    {
				if(j < Vector_of_bias_training_ref[i].capacity() - 1)
				{
					file_cpp << Vector_of_bias_training_ref[i][j] << ", ";
				}
				else
				{
					file_cpp << Vector_of_bias_training_ref[i][j] << " },";
				}
		    }
			file_cpp << std::endl;
		}

		file_cpp << "\t" << "};" << std::endl;

		file_cpp << std::endl;

		file_cpp << "\t" << 
		"std::vector<std::vector<float>>& Vector_of_data_ref = Vector_of_data;" << std::endl;
		file_cpp << "\t" << 
		"std::vector<std::vector<float>>& Vector_of_neuron_values_ref = Vector_of_neuron_values;" << std::endl;
		file_cpp << "\t" << 
		"std::vector<std::vector<float>>& Vector_of_weights_training_ref = Vector_of_weights_training;" << std::endl;
		file_cpp << "\t" << 
		"std::vector<std::vector<float>>& Vector_of_bias_training_ref = Vector_of_bias_training;" << std::endl;

		file_cpp << "\t" << "int it_data = 0;" << std::endl;

		file_cpp << "\t" << "int* Number_of_hidden_layers = new int{ " << *Number_of_hidden_layers << " };" << std::endl;

		file_cpp << std::endl;

		file_cpp << "\t" << "Fully_connected_network DATA;" << std::endl;

		file_cpp << "\t" << "DATA.Fully_connected_network::Forward_propagation_the_network_MLP" << std::endl;
		file_cpp << "\t" << "(" << std::endl;
		file_cpp << "\t" << "\t" << "Vector_of_data_ref," << std::endl;
		file_cpp << "\t" << "\t" << "Vector_of_neuron_values_ref," << std::endl;
		file_cpp << "\t" << "\t" << "Vector_of_weights_training_ref," << std::endl;
		file_cpp << "\t" << "\t" << "Vector_of_bias_training_ref," << std::endl;
		file_cpp << "\t" << "\t" << "it_data" << std::endl;
		file_cpp << "\t" << ");" << std::endl;

		file_cpp << std::endl;

		file_cpp << "\t" << "std::cout << Vector_of_neuron_values_ref.capacity() << std::endl;" << std::endl;
	
		file_cpp << "\t" << "for (int i = 0; i < Vector_of_neuron_values_ref.capacity(); i++)" << std::endl;
		file_cpp << "\t" << "{" << std::endl;
		file_cpp << "\t" << "\t" << "for (int j = 0; j < Vector_of_neuron_values_ref[i].capacity(); j++)" << std::endl;
		file_cpp << "\t" << "\t" << "{" << std::endl;
		file_cpp << "\t" << "\t" << "\t" << "std::cout << std::endl << \"Vector_of_neuron_values_ref[\" << i << \"][\" << j << \"]: \" <<" << std::endl;
		file_cpp << "\t" << "\t" << "\t" << "Vector_of_neuron_values_ref[i][j] << std::endl;" << std::endl;
		file_cpp << "\t" << "\t" << "}" << std::endl;
		file_cpp << "\t" << "}" << std::endl;

		file_cpp << std::endl;

		file_cpp << "\t" << "return 0;" << std::endl;

		file_cpp << "}" << std::endl;

		file_cpp.close();
	}
	else
	{
		std::cout << "Error, file '.cpp' (trained) not created. Check if name of file is correct.";
		exit(3);
	}

	// end counting time 
	const auto Stop = std::chrono::high_resolution_clock::now();

	Display_results_counting_time(Start, Stop, "Write_data_MLP()", 2);

}

Fully_connected_network::~Fully_connected_network
(
	
)
{

}