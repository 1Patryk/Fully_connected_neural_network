#include <iostream>
#include <vector>
#include <cmath>

int Beta = 1;

float Unipolar_sigmoidal_function(float e)
{
	return static_cast<float>(1.0 / (1.0 + exp(-(Beta) * e)));
}

int main()
{
	std::vector <float> input = {  }; // enter value
	std::vector <float> output =
	{
		0,
	};

	float input_0_max = 81;
	float input_0_min = 8;
	float input_1_max = 4;
	float input_1_min = 0.5;

	float output_0_max = -0.00149079;
	float output_0_min = -0.0464897;

	std::vector <int> Number_of_neurons_in_hidden_layers =
	{
		3,
		2,
	};

	std::vector <int>& Number_of_neurons_in_hidden_layers_ref = Number_of_neurons_in_hidden_layers;

	float Vector_of_weights_training[14] =
	{
		8.60414,
		-70.8146,
		-29.6931,
		9.59042,
		-0.001315,
		13.1429,
		-9.26885,
		11.0607,
		4.80859,
		-0.403601,
		13.2675,
		-0.00859097,
		-11.9531,
		-3.91642,
	};

	float Vector_of_bias_weights_training[6] =
	{
		4.80096,
		16.9322,
		-3.41854,
		-17.5978,
		-0.184255,
		4.5414,
	};

	// iterator
	int iter = 0;

	std::vector <float> Vector_of_neuron_values[8] = { };

	// input layer of neurons
	for (int i = 0; i <2; i++)
	{
		Vector_of_neuron_values[iter].push_back(0);
	}

	iter += 1;

	// hidden layers of neurons
	for (iter; iter <= 2; iter++)
	{
		for (int j = 0; j < Number_of_neurons_in_hidden_layers_ref[iter - 1]; j++)
		{
			Vector_of_neuron_values[iter].push_back(0);
		}
	}

	// output layer of neurons
	for (int i = 0; i < 1; i++)
	{
		Vector_of_neuron_values[iter].push_back(0);
	}

	Vector_of_neuron_values->shrink_to_fit();

	// capacity = amount of neurons
	for (int i = 0; i < Vector_of_neuron_values->capacity(); i++)
	{
		Vector_of_neuron_values[i].shrink_to_fit();
	}

	input[0] = (input[0]  - input_0_min) / (input_0_max -  input_0_min);
	input[1] = (input[1]  - input_1_min) / (input_1_max -  input_1_min);

	// Forward propagation

	// input layer
	for (int j = 0; j < 2; j++)
	{
		Vector_of_neuron_values[0][j] = input[j];
	}

	// hidden layers
	int it_weight = 0;
	int it_bias = 0;
	for (int k = 1; k < 2 + 1; k++)
	{
		for (int l = 0; l < Vector_of_neuron_values[k].capacity(); l++)
		{
			for (int m = 0; m < Vector_of_neuron_values[k - 1].capacity(); m++)
			{
				Vector_of_neuron_values[k][l] +=
				((Vector_of_neuron_values[k - 1][m] *
				Vector_of_weights_training[it_weight]));
				it_weight += 1;
			}

			Vector_of_neuron_values[k][l] = Unipolar_sigmoidal_function(
				Vector_of_neuron_values[k][l] +
				Vector_of_bias_weights_training[it_bias]);

			it_bias += 1;
		}
	}
	// output layer
	int it_prev_layer = 1 + 2;

	for (int n = 0; n < 1; n++)
	{
		for (int o = 0; o < Vector_of_neuron_values[it_prev_layer - 1].capacity(); o++)
		{
			Vector_of_neuron_values[it_prev_layer][n] +=
			(
				(Vector_of_neuron_values[it_prev_layer - 1][o] * Vector_of_weights_training[it_weight])
			);

			it_weight += 1;
		}

		Vector_of_neuron_values[it_prev_layer][n] = Unipolar_sigmoidal_function
		(
			Vector_of_neuron_values[it_prev_layer][n] +
			Vector_of_bias_weights_training[it_bias]
		);

		it_bias += 1;
	}

	output[0] = Vector_of_neuron_values[it_prev_layer][0];

	output[0] = output[0]  * (output_0_max - output_0_min) +  output_0_min;
	std::cout << "output[0] = " << output[0] << std::endl;

	return 0;
}
