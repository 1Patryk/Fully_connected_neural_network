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
		-4.32945,
		4.81176,
		4.30526,
		-4.91823,
		2.8557,
		-3.69239,
		-2.58154,
		2.23762,
		0.908298,
		-1.36725,
		-3.22403,
		2.99504,
		2.04617,
		-2.22046,
		-1.27608,
		0.966295,
		-0.767035,
		1.09814,
		-1.43275,
		1.49009,
		1.08031,
		-0.691836,
		-0.299295,
		-0.789909,
		-0.216429,
		0.343544,
		-0.142671,
		0.48579,
		0.422343,
		-0.038077,
		-1.84256,
		1.65023,
		1.12646,
		-0.379556,
		0.284648,
		-0.997218,
		-0.696976,
		0.688828,
		-0.027246,
		-0.28318,
		0.224957,
		-0.792023,
		-0.364082,
		0.179387,
		-0.00953975,
		0.202197,
		0.0460886,
	};

	float Vector_of_bias_weights_training[12] =
	{
		-0.959805,
		0.0370319,
		0.0760162,
		-0.378357,
		0.0404459,
		-0.471988,
		-0.367205,
		-0.115165,
		-0.228491,
		-0.435481,
		0.237569,
		-0.343074,
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
