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

	float input_0_max = 10;
	float input_0_min = 1;
	float input_1_max = 100;
	float input_1_min = 82;

	float output_0_max = 101;
	float output_0_min = 92;

	std::vector <int> Number_of_neurons_in_hidden_layers =
	{
		6,
		5,
	};

	std::vector <int>& Number_of_neurons_in_hidden_layers_ref = Number_of_neurons_in_hidden_layers;

	float Vector_of_weights_training[47] =
	{
		0.481743,
		0.0631351,
		-0.191625,
		-0.0651482,
		0.02003,
		0.0667125,
		0.239037,
		-0.283874,
		-0.221532,
		0.495298,
		-0.152436,
		0.204722,
		-0.47534,
		0.218845,
		0.34882,
		0.408072,
		-0.398134,
		0.126806,
		-0.0550584,
		-0.100366,
		-0.157877,
		0.223627,
		0.0995757,
		0.454399,
		0.47027,
		-0.453233,
		0.382153,
		0.359162,
		-0.118621,
		0.344854,
		0.360306,
		0.299404,
		-0.284605,
		-0.0949714,
		0.300951,
		0.297397,
		0.338403,
		-0.424504,
		-0.391732,
		0.37983,
		-0.125335,
		0.0529999,
		0.257627,
		0.229002,
		0.222726,
		0.0446382,
		-0.135343,
	};

	float Vector_of_bias_weights_training[12] =
	{
		0.00822797,
		0.201527,
		0.149897,
		-0.0851483,
		0.430795,
		0.21517,
		0.346307,
		-0.304133,
		0.310815,
		-0.491953,
		0.357076,
		-0.513674,
	};

	// iterator
	int iter = 0;

	std::vector <float> Vector_of_neuron_values[14] = { };

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
