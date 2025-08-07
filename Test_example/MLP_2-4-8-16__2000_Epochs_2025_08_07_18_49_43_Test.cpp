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
	float output_0_min = -0.0466939;

	std::vector <int> Number_of_neurons_in_hidden_layers =
	{
		4,
		8,
		16,
	};

	std::vector <int>& Number_of_neurons_in_hidden_layers_ref = Number_of_neurons_in_hidden_layers;

	float Vector_of_weights_training[184] =
	{
		7.21388,
		-15.3367,
		-16.642,
		1.59617,
		-9.52248,
		11.8322,
		1.11036,
		15.2956,
		1.78786,
		-13.1528,
		-5.57285,
		-2.14581,
		1.96989,
		-13.3401,
		4.52516,
		-11.4628,
		3.47485,
		-3.25811,
		-3.38067,
		-4.09059,
		-6.66614,
		8.89501,
		-0.269555,
		6.35339,
		-6.23507,
		6.20441,
		3.39183,
		4.20466,
		-15.6889,
		7.68383,
		0.577181,
		4.96849,
		0.728863,
		-11.4482,
		-1.84527,
		-0.116506,
		2.28195,
		-12.1858,
		-5.27562,
		-2.14014,
		0.26453,
		1.30752,
		0.563108,
		-0.521328,
		-0.912233,
		-1.83814,
		0.903038,
		0.39168,
		-2.05705,
		0.221725,
		-0.0105215,
		1.50583,
		1.11709,
		1.45916,
		-1.00375,
		-2.37964,
		0.00725905,
		0.188304,
		0.0160511,
		-0.0817266,
		0.130537,
		-0.456838,
		-0.0176036,
		0.140515,
		-2.61385,
		-0.0364818,
		0.502325,
		2.0798,
		1.3511,
		1.54976,
		-1.27484,
		-2.07975,
		-2.86157,
		-0.230249,
		1.21118,
		2.01513,
		1.95569,
		2.42619,
		-1.97464,
		-1.92504,
		0.526502,
		1.01224,
		0.308658,
		-0.507418,
		-1.07531,
		-0.608817,
		0.238843,
		0.132624,
		-0.084535,
		0.0614825,
		0.133438,
		0.0188081,
		0.0867543,
		-0.691543,
		0.0192245,
		-0.0536857,
		-0.997,
		-3.63819,
		-1.21907,
		1.17795,
		-0.559619,
		4.17987,
		-0.822585,
		-1.13561,
		-0.777746,
		-0.63928,
		0.0637085,
		1.05152,
		0.693343,
		0.304525,
		-0.538368,
		-0.359157,
		0.714997,
		3.37638,
		0.622093,
		0.168939,
		0.429545,
		-6.14203,
		1.04315,
		1.02911,
		0.585774,
		2.16077,
		1.07741,
		-0.537422,
		-0.0491309,
		-3.52673,
		0.926157,
		0.659221,
		1.62664,
		4.5101,
		0.657321,
		-2.6654,
		-2.00404,
		-2.87089,
		1.07929,
		1.24044,
		-1.20539,
		-4.37329,
		-0.885107,
		2.22399,
		0.578526,
		3.79475,
		-0.646059,
		-1.33453,
		1.08507,
		3.52701,
		1.04885,
		-2.03824,
		-1.47575,
		-2.38736,
		0.942461,
		1.05968,
		0.348651,
		-0.360069,
		-0.308397,
		-0.306074,
		-0.414436,
		-0.078407,
		-0.0639038,
		-0.328407,
		-0.621177,
		-1.3791,
		-0.365947,
		0.646851,
		0.255286,
		1.20877,
		-0.777084,
		-0.32375,
		0.081413,
		-0.304591,
		0.0165592,
		-0.377678,
		-0.523795,
		0.0215833,
		0.0266594,
		-0.424171,
		-0.0865564,
		0.597544,
		0.230894,
		0.502813,
		-0.463386,
		0.301714,
		0.00860197,
		-0.0515964,
	};

	float Vector_of_bias_weights_training[29] =
	{
		5.46639,
		10.3735,
		-0.74409,
		-6.36504,
		1.03942,
		9.70348,
		1.6086,
		-9.25918,
		-5.68858,
		-10.7965,
		2.42915,
		0.481625,
		0.283395,
		1.9037,
		0.105861,
		1.94528,
		1.90642,
		-0.583573,
		-0.494304,
		-1.94267,
		0.858782,
		1.89182,
		0.926384,
		-0.237381,
		-0.392073,
		-0.673359,
		0.0702609,
		-0.157523,
		0.22552,
	};

	// iterator
	int iter = 0;

	std::vector <float> Vector_of_neuron_values[31] = { };

	// input layer of neurons
	for (int i = 0; i <2; i++)
	{
		Vector_of_neuron_values[iter].push_back(0);
	}

	iter += 1;

	// hidden layers of neurons
	for (iter; iter <= 3; iter++)
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
	for (int k = 1; k < 3 + 1; k++)
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
	int it_prev_layer = 1 + 3;

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
