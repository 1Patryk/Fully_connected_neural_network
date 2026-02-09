#include "../include/Fully_connected_network.hpp"

int main()
{
	std::vector<std::vector<float>> Vector_of_data =
	{
		{ 0 }, // enter the values
		{ 0 }, // enter the values
	};

	std::vector<std::vector<float>> Vector_of_neuron_values =
	{
		{ 0, 0 },
		{ 0, 0 },
		{ 0 },
	};

	float input_0_max = 5;
	float input_0_min = 1;
	float input_1_max = 100;
	float input_1_min = 92;

	float output_0_max = 101;
	float output_0_min = 97;

	std::vector<std::vector<float>> Vector_of_weights_training =
	{
		{ 0.390155, -0.369292, -0.460241, 0.326437 },
		{ 0.0320804, 0.456312 },
		{ -0.0382913 },
	};

	std::vector<std::vector<float>> Vector_of_bias_training =
	{
		{ 0.390155, -0.369291 },
		{ -0.460237 },
		{ 0.326074 },
	};

	std::vector<std::vector<float>>& Vector_of_data_ref = Vector_of_data;
	std::vector<std::vector<float>>& Vector_of_neuron_values_ref = Vector_of_neuron_values;
	std::vector<std::vector<float>>& Vector_of_weights_training_ref = Vector_of_weights_training;
	std::vector<std::vector<float>>& Vector_of_bias_training_ref = Vector_of_bias_training;
	int it_data = 0;
	int* Number_of_hidden_layers = new int{ 2 };

	Fully_connected_network DATA;
	DATA.Fully_connected_network::Forward_propagation_the_network_MLP
	(
		Vector_of_data_ref,
		Vector_of_neuron_values_ref,
		Vector_of_weights_training_ref,
		Vector_of_bias_training_ref,
		it_data
	);

	std::cout << Vector_of_neuron_values_ref.capacity() << std::endl;
	for (int i = 0; i < Vector_of_neuron_values_ref.capacity(); i++)
	{
		for (int j = 0; j < Vector_of_neuron_values_ref[i].capacity(); j++)
		{
			std::cout << std::endl << "Vector_of_neuron_values_ref[" << i << "][" << j << "]: " <<
			Vector_of_neuron_values_ref[i][j] << std::endl;
		}
	}

	return 0;
}
