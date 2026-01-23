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

	float output_0_max = -0.00118075;
	float output_0_min = -0.0467309;

	std::vector <int> Number_of_neurons_in_hidden_layers =
	{
		6,
		5,
	};

	std::vector <int>& Number_of_neurons_in_hidden_layers_ref = Number_of_neurons_in_hidden_layers;

	float Vector_of_weights_training[47] =
	{
		0.034139,
		-0.174838,
		0.0690874,
		-0.750215,
		-0.12537,
		-0.0803038,
		0.0210353,
		0.0975349,
		0.108741,
		0.512581,
		0.0663172,
		-0.14766,
		-0.0300457,
		-0.373038,
		-0.179301,
		0.310726,
		-0.0827812,
		0.450435,
		0.0867475,
		0.0199099,
		-0.310397,
		-0.128422,
		0.122338,
		0.305712,
		-0.483454,
		-0.0302824,
		-0.534715,
		-0.308414,
		-0.465629,
		0.149982,
		-0.130459,
		0.451326,
		0.348296,
		0.343393,
		-0.278424,
		-0.186067,
		0.0950509,
		0.320119,
		-0.386448,
		0.302883,
		-0.619605,
		0.101319,
		-0.31477,
		-0.301723,
		0.134207,
		0.0942629,
		0.350281,
	};

	float Vector_of_bias_weights_training[12] =
	{
		0.149712,
		0.145728,
		0.359281,
		0.279031,
		0.0676484,
		0.431178,
		0.082414,
		0.569484,
		-0.251397,
		0.15624,
		-0.668212,
		-0.0492642,
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
