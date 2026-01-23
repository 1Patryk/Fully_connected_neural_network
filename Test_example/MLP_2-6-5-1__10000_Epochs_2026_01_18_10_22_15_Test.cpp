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
	float output_0_min = -0.0467309;

	std::vector <int> Number_of_neurons_in_hidden_layers =
	{
		6,
		5,
	};

	std::vector <int>& Number_of_neurons_in_hidden_layers_ref = Number_of_neurons_in_hidden_layers;

	float Vector_of_weights_training[47] =
	{
		0.292821,
		-0.0620061,
		-0.231343,
		-0.457847,
		0.0841033,
		-0.11253,
		-0.129614,
		-0.332114,
		0.191744,
		-0.297752,
		-0.310622,
		-0.165494,
		-0.353208,
		-0.475842,
		-0.212157,
		-0.341901,
		0.483919,
		0.468158,
		-0.410408,
		-0.216467,
		0.186294,
		0.216628,
		-0.183054,
		0.110345,
		0.333182,
		-0.343162,
		0.284822,
		-0.330313,
		0.167751,
		0.374505,
		0.0562123,
		0.0389236,
		-0.410971,
		0.279327,
		-0.241264,
		-0.237464,
		-0.367014,
		-0.419708,
		0.43394,
		0.0444483,
		-0.145237,
		-0.117875,
		0.380691,
		-0.164924,
		-0.368906,
		-0.148601,
		0.065967,
	};

	float Vector_of_bias_weights_training[12] =
	{
		0.284035,
		-0.0205859,
		0.482756,
		-0.144724,
		-0.21579,
		0.485094,
		-0.191371,
		-0.0693309,
		-0.0858113,
		0.497106,
		-0.154948,
		-0.0795561,
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
