#include "../Include/Fully_connected_network.hpp"

Fully_connected_network::Fully_connected_network()
{
	Bias = 1;
	Beta = 1;
	Amount_of_data = 4;
	Number_of_epochs = 100;
	Number_of_input = 2;
	Number_of_output = 1;
	Number_of_hidden_layers = 1;
	Number_of_weights = 2;
	Total_number_of_neurons = 1;
	Learning_rate_factor = 1;
	filename = "Table_XOR.txt";
	plotname = "Plot_MLP_X_X.png";
	Input_x1 = new std::vector<double>(Amount_of_data);			// This is probably problematic with more data (memory)
	Input_x2 = new std::vector<double>(Amount_of_data);
	Output_y1 = new std::vector<double>(Amount_of_data);
	Vector_of_weights = new std::vector<double>(Number_of_weights);
	Vector_of_neuron_values = new std::vector<double>(Total_number_of_neurons);
}

template<class start, class stop>
void Fully_connected_network::Display_results_counting_time(start Start, stop Stop)
{
	std::cout << "Calculations lasted: "
		<< std::chrono::duration_cast<std::chrono::milliseconds>(Stop - Start).count()
		<< " millisecond/s\n";
}

void Fully_connected_network::Read_data_MLP_x_x(std::vector<double>& Input_x1,
	std::vector<double>& Input_x2,
	std::vector<double>& Output_y1)
{
	// start counting time 
	const auto Start = std::chrono::high_resolution_clock::now();

	// ifstream only can open file
	std::ifstream file(filename);

	if (file)
	{
		for (int i = 0; i < Amount_of_data; ++i)
		{
			file >> Input_x1[i];
			file >> Input_x2[i];
			file >> Output_y1[i];
			std::cout << Input_x1[i] << std::endl;
			std::cout << Input_x2[i] << std::endl;
			std::cout << Output_y1[i] << std::endl;
		}
		file.close();
	}
	else
	{
		std::cout << "Error, file not opened. Check if name of file is correct, or if this file exist.";
		exit(3);
	}

	// end counting time 
	const auto Stop = std::chrono::high_resolution_clock::now();

	Display_results_counting_time(Start, Stop);
}

void Fully_connected_network::Min_max_unipolar_scaling(std::vector<double>& Vector)
{
	auto Start = std::chrono::high_resolution_clock::now();

	double max = *max_element(Vector.begin(), Vector.end());
	double min = *min_element(Vector.begin(), Vector.end());

	for (int i = 0; i < Amount_of_data; ++i)
	{
		Vector[i] = (Vector[i] - min) / (max - min);
	}

	for (int i = 0; i < Amount_of_data; ++i)
	{
		std::cout << "Wektor: " << Vector[i] << std::endl;
	}

	auto Stop = std::chrono::high_resolution_clock::now();

	Display_results_counting_time(Start, Stop);
}

void Fully_connected_network::Min_max_bipolar_scaling(std::vector<double>& Vector)
{
	auto Start = std::chrono::high_resolution_clock::now();

	double max = *max_element(Vector.begin(), Vector.end());
	double min = *min_element(Vector.begin(), Vector.end());

	for (int i = 0; i < Amount_of_data; ++i)
	{
		Vector[i] = 2 * ((Vector[i] - min) / (max - min)) - 1;
	}

	for (int i = 0; i < Amount_of_data; ++i)
	{
		std::cout << "Wektor: " << Vector[i] << std::endl;
	}

	auto Stop = std::chrono::high_resolution_clock::now();

	Display_results_counting_time(Start, Stop);
}

void Fully_connected_network::Reversal_min_max_unipolar_scaling()
{

}

void Fully_connected_network::Pseudo_random_numbers(std::vector<double>& Vector)
{
	auto Start = std::chrono::high_resolution_clock::now();

	srand(static_cast<unsigned int>(time(NULL)));

	for (int i = 0; i < Number_of_weights; ++i)
	{
		Vector[i] = (float)(rand() % 100) / 100;
		std::cout << "Iteration number: " << i << " " << Vector[i] << std::endl;
	}

	auto Stop = std::chrono::high_resolution_clock::now();

	Display_results_counting_time(Start, Stop);
}

void Fully_connected_network::Calculating_the_network_MLP_X_X(std::vector<double>& Input_x1,
	std::vector<double>& Input_x2,
	std::vector<double>& Output_y1,
	std::vector<double>& Vector_of_weights,
	std::vector<double>& Vector_of_neuron_values,
	double& Bias)
{
	auto Start = std::chrono::high_resolution_clock::now();
	std::vector<double> Graph_value_vector;
	// capacity reduction
	Graph_value_vector.shrink_to_fit();

	Read_data_MLP_x_x(Input_x1, Input_x2, Output_y1);

	// changes for user interface (uniporar/bipolar)
	Min_max_unipolar_scaling(Input_x1);
	Min_max_unipolar_scaling(Input_x2);
	Min_max_unipolar_scaling(Output_y1);

	Pseudo_random_numbers(Vector_of_weights);

	double MSE = 0;

	for (int e = 0; e < Number_of_epochs; ++e)
	{
		MSE = 0;

		for (int i = 0; i < Amount_of_data; ++i)
		{
			Vector_of_neuron_values[0] = Unipolar_sigmoidal_function((Input_x1[i] *
				Vector_of_weights[0]) + (Input_x2[i] * Vector_of_weights[1]) + Bias);

			// last neuron error
			double error = Output_y1[i] - Vector_of_neuron_values[0];

			// new values of weight

			Vector_of_weights[0] = Vector_of_weights[0] + Learning_rate_factor * error *
				(Beta * Vector_of_neuron_values[0] * (1 - Vector_of_neuron_values[0])) * Input_x1[i];

			Vector_of_weights[1] = Vector_of_weights[1] + Learning_rate_factor * error *
				(Beta * Vector_of_neuron_values[0] * (1 - Vector_of_neuron_values[0])) * Input_x2[i];

			Bias = Bias + Learning_rate_factor * error *
				(Beta * Vector_of_neuron_values[0] * (1 - Vector_of_neuron_values[0]));

			MSE += pow((Vector_of_neuron_values[0] - Output_y1[i]), 2);
		}

		MSE = MSE / Amount_of_data;

		std::cout << "MSE: " << MSE << std::endl;

		Graph_value_vector.push_back(MSE);
	}

	Drawning_plot(&Graph_value_vector);

	auto Stop = std::chrono::high_resolution_clock::now();

	Display_results_counting_time(Start, Stop);
}

int Fully_connected_network::Drawning_plot(std::vector<double>* Graph_value_vector)
{
	bool success;

	StringReference* errorMessage = CreateStringReferenceLengthValue(0, L' ');
	RGBABitmapImageReference* imageReference = CreateRGBABitmapImageReference();

	std::vector<double> x_values;

	for (int i = 0; i < Number_of_epochs; ++i)
	{
		x_values.push_back(i);
	}

	ScatterPlotSeries* series = GetDefaultScatterPlotSeriesSettings();
	series->xs = &x_values;
	series->ys = Graph_value_vector;
	series->linearInterpolation = true;
	series->lineType = toVector(L"solid");			// dashed line
	series->lineThickness = 2;
	series->color = GetGray(0.3);

	ScatterPlotSettings* settings = GetDefaultScatterPlotSettings();
	settings->width = 1920;	// 600 1920 3840
	settings->height = 1080;		// 400 1080 2160
	settings->autoBoundaries = true;
	settings->autoPadding = true;
	settings->title = toVector(L"MLP_X_X");
	settings->xLabel = toVector(L"Number of epoch");
	settings->yLabel = toVector(L"MSE");
	settings->scatterPlotSeries->push_back(series);

	success = DrawScatterPlotFromSettings(imageReference, settings, errorMessage);

	if (success) {
		std::vector<double>* pngdata = ConvertToPNG(imageReference->image);
		WriteToFile(pngdata, plotname);
		DeleteImage(imageReference->image);
	}
	else
	{
		std::cerr << "Error: ";
		for (wchar_t c : *errorMessage->string)
		{
			std::wcerr << c;
		}
		std::cerr << std::endl;
	}

	//FreeAllocations();

	return success ? 0 : 1;
}

double Fully_connected_network::Unipolar_sigmoidal_function(double e)
{
	return (1.0 / (1.0 + exp(-Beta * e)));
}

void Fully_connected_network::Display_results_for_MLP_x_x()
{
	std::cout << &Input_x1[0] << std::endl;
	std::cout << &Input_x2[0] << std::endl;
	std::cout << &Output_y1[0] << std::endl;
	std::cout << &Vector_of_weights[0] << std::endl;
	std::cout << &Vector_of_neuron_values[0] << std::endl;
	std::cout << &Bias << std::endl;


	Calculating_the_network_MLP_X_X(*&Input_x1[0],
		*&Input_x2[0],
		*&Output_y1[0],
		*&Vector_of_weights[0],
		*&Vector_of_neuron_values[0],
		*&Bias);

}