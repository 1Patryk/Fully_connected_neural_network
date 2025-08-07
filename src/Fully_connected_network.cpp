#include "../include/Fully_connected_network.hpp"

Fully_connected_network::Fully_connected_network()
{
	Diag = bool{ false };
	Number_of_epochs = new int{ 2000 };
	Number_of_input = new int{ 0 };
	Number_of_output = new int{ 0 };
	Number_of_hidden_layers = new int{ 0 };
	Number_of_layers = new int{ 0 };
	Number_of_weights = new int{ 0 };
	Total_number_of_neurons = new int{ 0 };
	Train = new int{ 60 };
	Validation = new int{ 40 };
	Beta = new float{ 1.0f };
	Bias = new float{ 1.0f };
	Learning_rate_factor = new float { 0.01f };

    Open_filename = new std::string{ "" };
    Output_filename_path = new std::string{ "" };
	Number_of_neurons_in_hidden_layers = std::vector<int>{4, 8, 16};
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
	Fully_connected_network::Vector_of_neuron_values_training = std::vector<std::vector<float>>(*Number_of_hidden_layers + 2);
	Fully_connected_network::Vector_of_neuron_values_one_dim_training = std::vector<float>(0, 0);
	Fully_connected_network::Vector_of_weights_training = std::vector<float>(0, 0);
	Fully_connected_network::Vector_of_bias_weights_training = std::vector<float>(0, 0);
	Fully_connected_network::Vector_of_error_values_training = std::vector<float>(0, 0);

	// VALIDATION

	Fully_connected_network::Vector_of_data_validation = std::vector<std::vector<float>>(0);
	Fully_connected_network::Vector_of_neuron_values_validation = std::vector<std::vector<float>>(*Number_of_hidden_layers + 2);
	Fully_connected_network::Vector_of_neuron_values_one_dim_validation = std::vector<float>(0, 0);
	Fully_connected_network::Vector_of_weights_validation = std::vector<float>(0, 0);
	Fully_connected_network::Vector_of_bias_weights_validation = std::vector<float>(0, 0);
	Fully_connected_network::Vector_of_error_values_validation = std::vector<float>(0, 0);
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

void Fully_connected_network::Read_data_MLP(std::string* Open_filename)
{
	// start counting time 
	const auto Start = std::chrono::high_resolution_clock::now();

	// ifstream only can open file
    std::ifstream file(*Open_filename);

	float One_piece_of_data = 0.0f;

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
			std::vector<float> vec(0);
			Vector_of_data_ref.push_back(vec);
		}	
		/*
		for (int i = 0; !file.eof(); ++i)
		{
			for (int j = 0; j < (*Number_of_input + *Number_of_output); j++)
			{
				file >> One_piece_of_data;
				Vector_of_data_ref[j].push_back(One_piece_of_data);
				// if don't delete last row i txt, one_piece_of data uploads 2x times the same value!
			}
		}
		*/

		while(!file.eof())
		{
			for (int j = 0; j < (*Number_of_input + *Number_of_output); j++)
			{
				file >> One_piece_of_data;
				Vector_of_data_ref[j].push_back(One_piece_of_data);
				// if don't delete last row i txt, one_piece_of data uploads 2x times the same value!
			}
		}

		Vector_of_data_ref.shrink_to_fit();

		std::cout <<"UNO:" <<  std::setprecision(10) << Vector_of_data_ref[0][0] << std::endl;
		std::cout << "UNO:" <<  std::setprecision(10) << Vector_of_data_ref[1][0]  << std::endl;
		std::cout << "UNO:" <<  std::setprecision(10) << Vector_of_data_ref[2][0]  << std::endl;

		for (int i = 0; i < (*Number_of_input + *Number_of_output); i++)
		{
			Vector_of_data_ref[i].erase(Vector_of_data_ref[i].end());
			Vector_of_data_ref[i].shrink_to_fit();
		}

		std::cout << std::setprecision(10);


		std::cout << "UNO:" << 	std::setprecision(10) << *Vector_of_data_ref[0].end()  << std::endl;
		std::cout << "UNO:" <<  std::setprecision(10) << *Vector_of_data_ref[1].end()   << std::endl;
		std::cout << "UNO:" <<  std::setprecision(10) << *Vector_of_data_ref[2].end()  << std::endl;

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

	// end counting time 
	const auto Stop = std::chrono::high_resolution_clock::now();

	Display_results_counting_time(Start, Stop, "Read_data_MLP()", 2);
}

void Fully_connected_network::Write_data_MLP(
	std::string* Output_filename_path)
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

    ss << "_" << "_" << *Number_of_epochs << "_Epochs_" <<
	std::put_time(std::localtime(&localTime), "%Y_%m_%d_%H_%M_%S") << extension;

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
		file_txt << "Number of epochs || MAPE_value_training || MAPE_value_validation" << std::endl;
		file_txt << std::endl;

		// data
		for (int i = 0; i < *Number_of_epochs; ++i)
		{
			file_txt << i + 1;
			file_txt << "\t" << "\t";
			file_txt << MAPE_value_training_ref[i];
			file_txt << "\t" << "\t";
			file_txt << MAPE_value_validation_ref[i];
			file_txt << std::endl;
		}

		file_txt << "\n" << "\n";

		file_txt << "Vector_of_weights_training";
		file_txt << "\n" << "\n";
		file_txt << "Lp. || value";
		file_txt << "\n" << "\n";

		for (int i = 0; i < Vector_of_weights_training_ref.capacity(); ++i)
		{
			file_txt << i + 1;
			file_txt << "\t" << "\t";
			file_txt << Vector_of_weights_training_ref[i];
			file_txt << "\n";
		}

		file_txt << "\n" << "\n";

		file_txt << "Vector_of_bias_weights_training";
		file_txt << "\n" << "\n";
		file_txt << "Lp. || value";
		file_txt << "\n" << "\n";

		for (int i = 0; i < Vector_of_bias_weights_training_ref.capacity(); ++i)
		{
			file_txt << i + 1;
			file_txt << "\t" << "\t";
			file_txt << Vector_of_bias_weights_training_ref[i];
			file_txt << "\n";
		}
		
		file_txt << "\n" << "\n";

		file_txt << "Vector_of_weights_validation";
		file_txt << "\n" << "\n";
		file_txt << "Lp. || value";
		file_txt << "\n" << "\n";

		for (int i = 0; i < Vector_of_weights_validation_ref.capacity(); ++i)
		{
			file_txt << i + 1;
			file_txt << "\t" << "\t";
			file_txt << Vector_of_weights_validation_ref[i];
			file_txt << "\n";
		}

		file_txt << "\n" << "\n";

		file_txt << "Vector_of_bias_weights_validation";
		file_txt << "\n" << "\n";
		file_txt << "Lp. || value";
		file_txt << "\n" << "\n";

		for (int i = 0; i < Vector_of_bias_weights_validation_ref.capacity(); ++i)
		{
			file_txt << i + 1;
			file_txt << "\t" << "\t";
			file_txt << Vector_of_bias_weights_validation_ref[i];
			file_txt << "\n";
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

    cc << "_" << "_" << *Number_of_epochs << "_Epochs_";
	cc << std::put_time(std::localtime(&localTime), "%Y_%m_%d_%H_%M_%S") << "_Plot" << extension;

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

	system(("root -q ../Output_data_graph/" + file_date).c_str());

	// Creating .txt file for test

	extension = ".txt";

	std::stringstream tt;
	
    tt << "MLP_" << *Number_of_input;

	for (int i = 0; i < *Number_of_hidden_layers; i++)
    {
        tt << "-";
        tt << Number_of_neurons_in_hidden_layers[i];
    }

	tt << "_" << "_" << *Number_of_epochs << "_Epochs_";
	tt << std::put_time(std::localtime(&localTime), "%Y_%m_%d_%H_%M_%S") << "_Test" << extension;

    file_date = tt.str();

    file_date.erase(remove(file_date.begin(), file_date.end(), '\"'), file_date.end());

    std::cout << *Output_filename_path + file_date << std::endl;

    // ofstream only can write file
    std::ofstream file_test(*Output_filename_path + "../Test_example/" + file_date);

	if (file_test.is_open())
	{	
		// head
		file_test << file_date << std::endl;
		file_test << std::endl;

		file_test << "Vector_of_weights_training";
		file_test << "\n" << "\n";
		file_test << "Lp. || value";
		file_test << "\n" << "\n";

		for (int i = 0; i < Vector_of_weights_training_ref.capacity(); ++i)
		{
			file_test << i + 1;
			file_test << "\t" << "\t";
			file_test << Vector_of_weights_training_ref[i];
			file_test << "\n";
		}

		file_test << "\n";

		file_test << "Vector_of_bias_weights_training";
		file_test << "\n" << "\n";
		file_test << "Lp. || value";
		file_test << "\n" << "\n";

		for (int i = 0; i < Vector_of_bias_weights_training_ref.capacity(); ++i)
		{
			file_test << i + 1;
			file_test << "\t" << "\t";
			file_test << Vector_of_bias_weights_training_ref[i];
			file_test << "\n";
		}
		
		file_test << "\n";

		file_test << "Vector_of_weights_validation";
		file_test << "\n" << "\n";
		file_test << "Lp. || value";
		file_test << "\n" << "\n";

		for (int i = 0; i < Vector_of_weights_validation_ref.capacity(); ++i)
		{
			file_test << i + 1;
			file_test << "\t" << "\t";
			file_test << Vector_of_weights_validation_ref[i];
			file_test << "\n";
		}

		file_test << "\n";

		file_test << "Vector_of_bias_weights_validation";
		file_test << "\n" << "\n";
		file_test << "Lp. || value";
		file_test << "\n" << "\n";

		for (int i = 0; i < Vector_of_bias_weights_validation_ref.capacity(); ++i)
		{
			file_test << i + 1;
			file_test << "\t" << "\t";
			file_test << Vector_of_bias_weights_validation_ref[i];
			file_test << "\n";
		}

		file_test << "\n";

		file_test << "MAPE_training(" << *Number_of_epochs << "): " << MAPE_value_training_ref[*Number_of_epochs - 1] << std::endl;
		file_test << "MAPE_validation(" << *Number_of_epochs << "): " << MAPE_value_validation_ref[*Number_of_epochs - 1] << std::endl;
		file_test << std::endl;
		
		for(int i = 0; i < (*Number_of_input + *Number_of_output); i++)
		{
			file_test << "*Max_training_value[" << i << "]: " << Max_training_value_vector[i] << std::endl;
			file_test << "*Min_training_value[" << i << "]: " << Min_training_value_vector[i] << std::endl;

			file_test << std::endl;
		}

		file_test << std::endl;

		for(int i = 0; i < (*Number_of_input + *Number_of_output); i++)
		{
			file_test << "*Max_validation_value[" << i << "]: " << Max_validation_value_vector[i] << std::endl;
			file_test << "*Min_validation_value[" << i << "]: " << Min_validation_value_vector[i] << std::endl;

			file_test << std::endl;
		}

		file_test << std::endl;

		file_test.close();
	}
	else
	{
		std::cout << "Error, file '.txt' (test) not created. Check if name of file is correct.";
		exit(3);
	}

	// Creating .cpp file for a trained network

	extension = ".cpp";

	std::stringstream cpp;
	
    cpp << "MLP_" << *Number_of_input;

	for (int i = 0; i < *Number_of_hidden_layers; i++)
    {
        cpp << "-";
        cpp << Number_of_neurons_in_hidden_layers[i];
    }

	cpp << "_" << "_" << *Number_of_epochs << "_Epochs_";
	cpp << std::put_time(std::localtime(&localTime), "%Y_%m_%d_%H_%M_%S") << "_Test" << extension;

    file_date = cpp.str();

    file_date.erase(remove(file_date.begin(), file_date.end(), '\"'), file_date.end());

    std::cout << *Output_filename_path + file_date << std::endl;

    // ofstream only can write file
    std::ofstream file_cpp(*Output_filename_path + "../Test_example/" + file_date);

	if (file_cpp.is_open())
	{	
		file_cpp << "#include <iostream>" << std::endl;
		file_cpp << "#include <vector>" << std::endl;
		file_cpp << "#include <cmath>" << std::endl;

		file_cpp << std::endl;

		file_cpp << "int Beta = " << *Beta << ";" << std::endl;

		file_cpp << std::endl;
		
		file_cpp << "float Unipolar_sigmoidal_function(float e)" << std::endl;
		file_cpp << "{" << std::endl;
		file_cpp << "\t" << "return static_cast<float>(1.0 / (1.0 + exp(-(Beta) * e)));" << std::endl;
		file_cpp << "}" << std::endl;

		file_cpp << std::endl;

		file_cpp << "int main()" << std::endl;
		file_cpp << "{" << std::endl;

		file_cpp << "\t" << "std::vector <float> input = {  }; // enter value" << std::endl;
		file_cpp << "\t" << "std::vector <float> output =" << std::endl;
		file_cpp << "\t" << "{" << std::endl;
		for(int i = 0; i < *Number_of_output; i++)
		{
			file_cpp << "\t" << "\t" << "0," << std::endl;
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

		file_cpp << "\t" << "std::vector <int> Number_of_neurons_in_hidden_layers =" << std::endl;
		file_cpp << "\t" << "{";

		for (int i = 0; i < Number_of_neurons_in_hidden_layers.capacity(); ++i)
		{
			file_cpp << std::endl;
			file_cpp << "\t" << "\t" << Number_of_neurons_in_hidden_layers[i] << ",";
		}

		file_cpp << std::endl;

		file_cpp << "\t" << "};" << std::endl;

		file_cpp << std::endl;

		file_cpp << "\t" << "std::vector <int>& Number_of_neurons_in_hidden_layers_ref = Number_of_neurons_in_hidden_layers;" << std::endl;

		file_cpp << std::endl;

		file_cpp << "\t" << "float Vector_of_weights_training[" << Vector_of_weights_training_ref.capacity() << "] =" << std::endl; 
		file_cpp << "\t" << "{";

		for (int i = 0; i < Vector_of_weights_training_ref.capacity(); ++i)
		{
			file_cpp << std::endl;
			file_cpp << "\t" << "\t" << Vector_of_weights_training_ref[i] << ",";
		}

		file_cpp << std::endl;

		file_cpp << "\t" << "};" << std::endl;

		file_cpp << std::endl;

		file_cpp << "\t" << "float Vector_of_bias_weights_training[" << Vector_of_bias_weights_training.capacity() << "] =" << std::endl; 
		file_cpp << "\t" << "{";

		for (int i = 0; i < Vector_of_bias_weights_training.capacity(); ++i)
		{
			file_cpp << std::endl;
			file_cpp << "\t" << "\t" << Vector_of_bias_weights_training[i] << ",";
		}

		file_cpp << std::endl;

		file_cpp << "\t" << "};" << std::endl;

		file_cpp << std::endl;

		file_cpp << "\t" << "// iterator" << std::endl << "\t" << "int iter = 0;" << std::endl;

		file_cpp << std::endl;

		file_cpp << "\t" << "std::vector <float> Vector_of_neuron_values[" << *Total_number_of_neurons << "] = { };" << std::endl;

		file_cpp << std::endl;

		file_cpp << "\t" << "// input layer of neurons" << std::endl; 
		file_cpp << "\t" << "for (int i = 0; i <" << *Number_of_input << "; i++)" << std::endl;
		file_cpp << "\t" << "{" << std::endl;
		file_cpp << "\t" << "\t" << "Vector_of_neuron_values[iter].push_back(0);" << std::endl;
		file_cpp << "\t" << "}"	<< std::endl;

		file_cpp << std::endl;

		file_cpp << "\t" << "iter += 1;" << std::endl; 

		file_cpp << std::endl;

		file_cpp << "\t" << "// hidden layers of neurons" << std::endl; 
		
		file_cpp << "\t" << "for (iter; iter <= " << *Number_of_hidden_layers << "; iter++)" << std::endl;
		file_cpp << "\t" << "{" << std::endl;
		file_cpp << "\t" << "\t" << "for (int j = 0; j < Number_of_neurons_in_hidden_layers_ref[iter - 1]; j++)" << std::endl;
		file_cpp << "\t" << "\t" << "{" << std::endl;
		file_cpp << "\t" << "\t" << "\t" << "Vector_of_neuron_values[iter].push_back(0);" << std::endl;
		file_cpp << "\t" << "\t" << "}" << std::endl;
		file_cpp << "\t" << "}"	<< std::endl;

		file_cpp << std::endl;

		file_cpp << "\t" << "// output layer of neurons"<< std::endl; 

		file_cpp << "\t" << "for (int i = 0; i < " << *Number_of_output << "; i++)" << std::endl;
		file_cpp << "\t" << "{" << std::endl;
		file_cpp << "\t" <<	"\t" <<	"Vector_of_neuron_values[iter].push_back(0);" << std::endl;
		file_cpp << "\t" << "}"	<< std::endl;

		file_cpp << std::endl;

		file_cpp << "\t" << "Vector_of_neuron_values->shrink_to_fit();"<< std::endl; 

		file_cpp << std::endl;

		file_cpp << "\t" << "// capacity = amount of neurons"<< std::endl; 

		file_cpp << "\t" << "for (int i = 0; i < Vector_of_neuron_values->capacity(); i++)"<< std::endl; 
		file_cpp << "\t" << "{" << std::endl;
		file_cpp << "\t" << "\t" << "Vector_of_neuron_values[i].shrink_to_fit();" << std::endl;
		file_cpp << "\t" << "}"	<< std::endl;
		
		file_cpp << std::endl;

		for(int i = 0; i < *Number_of_input; i++)
		{
			file_cpp << "\t" << "input[" << i << "] = (input[" << i << "]  -";
			file_cpp << " " << "input_" << i << "_min) / (input_" << i << "_max - ";
			file_cpp << " " << "input_" << i << "_min);" << std::endl;
		}

		file_cpp << std::endl;

		file_cpp << "\t" << "// Forward propagation"<< std::endl; 

		file_cpp << std::endl;

		file_cpp << "\t" << "// input layer"<< std::endl; 

		file_cpp << "\t" << "for (int j = 0; j < " << Vector_of_neuron_values_training_ref[0].capacity() << "; j++)" << std::endl;
		file_cpp << "\t" << "{" << std::endl;
		file_cpp << "\t" << "\t" << "Vector_of_neuron_values[0][j] = input[j];" << std::endl;
		file_cpp << "\t" << "}" << std::endl;

		file_cpp << std::endl;

		file_cpp << "\t" << "// hidden layers"<< std::endl; 
		// hidden layers
		file_cpp << "\t" << "int it_weight = 0;" << std::endl;
		file_cpp << "\t" << "int it_bias = 0;" << std::endl;

		file_cpp << "\t" << "for (int k = 1; k < " << *Number_of_hidden_layers << " + 1; k++)" << std::endl;
		file_cpp << "\t" << "{" << std::endl;
		file_cpp << "\t" << "\t" << "for (int l = 0; l < Vector_of_neuron_values[k].capacity(); l++)" << std::endl;
		file_cpp << "\t" << "\t" << "{" << std::endl;
		file_cpp << "\t" << "\t" << "\t" << "for (int m = 0; m < Vector_of_neuron_values[k - 1].capacity(); m++)" << std::endl;
		file_cpp << "\t" << "\t" << "\t" <<	"{" << std::endl;
		file_cpp << "\t" << "\t" << "\t" << "\t" << "Vector_of_neuron_values[k][l] +=" << std::endl;
		file_cpp << "\t" << "\t" << "\t" << "\t" << "((Vector_of_neuron_values[k - 1][m] *" << std::endl;
		file_cpp << "\t" << "\t" << "\t" << "\t" << "Vector_of_weights_training[it_weight]));" << std::endl;
		file_cpp << "\t" << "\t" << "\t" << "\t" << "it_weight += 1;" << std::endl;
		file_cpp << "\t" << "\t" << "\t" <<	"}" << std::endl;
		file_cpp << std::endl;
		file_cpp << "\t" << "\t" << "\t" <<	"Vector_of_neuron_values[k][l] = Unipolar_sigmoidal_function(" << std::endl;
		file_cpp << "\t" << "\t" << "\t" <<	"\t" << "Vector_of_neuron_values[k][l] +" << std::endl;
		file_cpp << "\t" << "\t" << "\t" <<	"\t" << "Vector_of_bias_weights_training[it_bias]);" << std::endl;

		file_cpp << std::endl;
		
		file_cpp << "\t" << "\t" << "\t" <<	"it_bias += 1;" << std::endl;
		file_cpp << "\t" << "\t" << "}" << std::endl;
		file_cpp << "\t" << "}" << std::endl;

		
		file_cpp << "\t" << "// output layer"<< std::endl; 

		file_cpp << "\t" << "int it_prev_layer = 1 + " << *Number_of_hidden_layers << ";" << std::endl;

		file_cpp << std::endl;

		file_cpp << "\t" << "for (int n = 0; n < " << *Number_of_output << "; n++)" << std::endl;
		file_cpp << "\t" << "{" << std::endl;
		file_cpp << "\t" << "\t" << "for (int o = 0; o < Vector_of_neuron_values[it_prev_layer - 1].capacity(); o++)" << std::endl;
		file_cpp << "\t" << "\t" << "{" << std::endl;
		file_cpp << "\t" << "\t" << "\t" << "Vector_of_neuron_values[it_prev_layer][n] +=" << std::endl;
		file_cpp << "\t" << "\t" << "\t" << "(" << std::endl;
		file_cpp << "\t" << "\t" << "\t" << "\t" << "(Vector_of_neuron_values[it_prev_layer - 1][o] * Vector_of_weights_training[it_weight])" << std::endl;
		file_cpp << "\t" << "\t" << "\t" << ");" << std::endl;
		file_cpp << std::endl;
		file_cpp << "\t" << "\t" << "\t" << "it_weight += 1;" << std::endl;
		file_cpp << "\t" << "\t" << "}" << std::endl;
		file_cpp << std::endl;
		file_cpp << "\t" << "\t" << "Vector_of_neuron_values[it_prev_layer][n] = Unipolar_sigmoidal_function" << std::endl;
		file_cpp << "\t" << "\t" << "(" << std::endl;
		file_cpp << "\t" << "\t" << "\t" << "Vector_of_neuron_values[it_prev_layer][n] +" << std::endl;
		file_cpp << "\t" << "\t" << "\t" << "Vector_of_bias_weights_training[it_bias]" << std::endl;
		file_cpp << "\t" << "\t" << ");" << std::endl;

		file_cpp << std::endl;

		file_cpp << "\t" <<	"\t" << "it_bias += 1;" << std::endl;
		file_cpp << "\t" << "}" << std::endl;

		file_cpp << std::endl;

		for(int i = 0; i < *Number_of_output; i++)
		{
			file_cpp << "\t" << "output[" << i << "] = Vector_of_neuron_values[it_prev_layer][" << 
			i << "];" << std::endl;
		}

		file_cpp << std::endl;

		for(int i = 0; i < *Number_of_output; i++)
		{
			file_cpp << "\t" << "output[" << i << "] = output[" << i << "]  *";
			file_cpp << " (output_" << i << "_max - output_" << i << "_min) + ";
			file_cpp << " output_" << i << "_min;" << std::endl;
			file_cpp << "\t" << "std::cout << \"output[" << i << "] = \" << " << "output[" << i << "] << std::endl;" << std::endl;
		}

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

void Fully_connected_network::Swap_data()
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

void Fully_connected_network::Divide_data_to_training_and_validation()
{
	// start counting time 
	const auto Start = std::chrono::high_resolution_clock::now();

	if (*Train + *Validation == 100)
	{
		float x = static_cast<float>((Vector_of_data_ref[0].capacity()) / 100);
		
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
	}
	else
	{
		std::cout << "Sum train, validation and test is not equal 100%.";
		exit(3);
	}
	
	// end counting time 
	const auto Stop = std::chrono::high_resolution_clock::now();

	Display_results_counting_time(Start, Stop, "Divide_data_to_training_test_and_validation()", 2);
}

void Fully_connected_network::Min_max_unipolar_scaling(
	std::vector<std::vector<float>>& Vector_of_data,
	std::string name_of_vector,
	std::vector<float>& Min_data_value_vector,
	std::vector<float>& Max_data_value_vector)
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

void Fully_connected_network::Min_max_bipolar_scaling(
	std::vector<std::vector<float>>& Vector_of_data,
	std::string name_of_vector,
	std::vector<float>& Min_data_value_vector,
	std::vector<float>& Max_data_value_vector)
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

	// end counting time 
	auto Stop = std::chrono::high_resolution_clock::now();

	Display_results_counting_time(Start, Stop, "Pseudo_random_numbers: " + name_of_vector, 2);
}

void Fully_connected_network::Calculating_the_network_MLP(
	std::string* Open_filename, 
	std::string* Output_filename_path)
{
	auto Start = std::chrono::high_resolution_clock::now();

    Read_data_MLP(Open_filename);
    Swap_data();
	Divide_data_to_training_and_validation();

	// TRAINING
	Min_max_unipolar_scaling(
		Vector_of_data_training_ref, 
		"Vector_of_data_training_ref",
		Min_training_value_vector,
		Max_training_value_vector);

	// VALIDATION
	Min_max_unipolar_scaling(
		Vector_of_data_validation_ref, 
		"Vector_of_data_validation_ref",
		Min_validation_value_vector,
		Max_validation_value_vector);
	
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
	Vector_of_error_values_training_ref.resize(*Total_number_of_neurons - *Number_of_input);
	// VALIDATION
	Vector_of_error_values_validation_ref.resize(*Total_number_of_neurons - *Number_of_input);

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
		std::cout << "##### START [" << epoch << "] EPOCH #####" << std::endl;

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
				MAPE_value_training_ref,
				it_data,
				it_weight,
				it_bias,
				it_prev_layer,
				it_error,
				it_iterator_one_dim,
				it_value_neuron,
				it_back_neuron,
				epoch
			);
		}

		MAPE_value_training_ref[epoch]= ((1.0f / Vector_of_data_training_ref[0].capacity()) *
			MAPE_value_training_ref[epoch]);

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
				MAPE_value_validation_ref,
				it_data,
				it_weight,
				it_bias,
				it_prev_layer,
				it_error,
				it_iterator_one_dim,
				it_value_neuron,
				it_back_neuron,
				epoch
			); 
		}

		MAPE_value_validation_ref[epoch] = ((1.0f / Vector_of_data_validation_ref[0].capacity()) *
			MAPE_value_validation_ref[epoch]);
	}

	std::cout << "MAPE_training(" << *Number_of_epochs << "): " << MAPE_value_training_ref[*Number_of_epochs - 1] << std::endl;
	std::cout << "MAPE_validation(" << *Number_of_epochs << "): " << MAPE_value_validation_ref[*Number_of_epochs - 1] << std::endl;

	auto Stop = std::chrono::high_resolution_clock::now();

	Display_results_counting_time(Start, Stop, "Calculating_the_network_MLP", 2);

    Write_data_MLP(Output_filename_path);
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
		}
	}

	// output layer
	it_prev_layer = 1 + *Number_of_hidden_layers;		// previous layers
	for (int n = 0; n < *Number_of_output; n++)
	{
		for (int o = 0; o < Vector_of_neuron_values[it_prev_layer - 1].capacity(); o++)
		{
			Vector_of_neuron_values[it_prev_layer][n] +=
				((Vector_of_neuron_values[it_prev_layer - 1][o] * Vector_of_weights[it_weight]));
			it_weight += 1;
		}
		Vector_of_neuron_values[it_prev_layer][n] = Unipolar_sigmoidal_function(
			Vector_of_neuron_values[it_prev_layer][n] +
			Vector_of_bias_weights[it_bias]);

		it_bias += 1;
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
	std::vector<float>& MAPE_value,
	int it_data,
	int it_weight,
	int it_bias,
	int it_prev_layer,
	int it_error, 
	int it_iterator_one_dim,
	int it_value_neuron,
	int it_back_neuron,
	int epoch
)
{
	it_prev_layer = 1 + *Number_of_hidden_layers;		// previous layers
	it_value_neuron = 0;
	it_back_neuron = 0;

	// reset error values
	for (int i = 0; i < Vector_of_error_values.capacity(); i++)
	{
		Vector_of_error_values[i] = 0.0f;
	}

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
			
			/*
			std::cout << Vector_of_data[Vector_of_data.capacity() - r][it_data] << std::endl;
			std::cout << "-" << std::endl;
			std::cout << Vector_of_neuron_values[it_prev_layer][*Number_of_output - r] << std::endl;
			std::cout << "=" << std::endl;
			std::cout << Vector_of_error_values[it_error] << std::endl;
			*/

			// conditional instruction
			if (Vector_of_data[Vector_of_data.capacity() - r][it_data] == 0 ||
				Vector_of_neuron_values[it_prev_layer][*Number_of_output - r] == 0)
			{
				MAPE_value[epoch] += (std::abs(Vector_of_data[Vector_of_data.capacity() - r][it_data] -
					Vector_of_neuron_values[it_prev_layer][*Number_of_output - r]));
			}
			else
			{
				MAPE_value[epoch] += (std::abs(Vector_of_data[Vector_of_data.capacity() - r][it_data] -
					Vector_of_neuron_values[it_prev_layer][*Number_of_output - r]) /
					(Vector_of_data[Vector_of_data.capacity() - r][it_data])) * 100.0f;
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
				}
				else
				{
					Vector_of_error_values[it_error] +=
						Vector_of_error_values[it_error + j + k] *
						Vector_of_weights[it_weight - (
							(Vector_of_neuron_values[i + 1].capacity() - k) *
							Vector_of_neuron_values[i].capacity())];
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
		}
		it_iterator_one_dim += Number_of_neurons_in_hidden_layers_ref.back();
	}
}

float Fully_connected_network::Unipolar_sigmoidal_function(float e)
{
	return static_cast<float>(1.0 / (1.0 + exp(-(*Beta) * e)));
}

Fully_connected_network::~Fully_connected_network()
{

}