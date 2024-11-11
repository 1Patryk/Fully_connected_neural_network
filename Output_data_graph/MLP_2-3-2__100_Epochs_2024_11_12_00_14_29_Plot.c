{
	float x[100] = {
	1,
	2,
	3,
	4,
	5,
	6,
	7,
	8,
	9,
	10,
	11,
	12,
	13,
	14,
	15,
	16,
	17,
	18,
	19,
	20,
	21,
	22,
	23,
	24,
	25,
	26,
	27,
	28,
	29,
	30,
	31,
	32,
	33,
	34,
	35,
	36,
	37,
	38,
	39,
	40,
	41,
	42,
	43,
	44,
	45,
	46,
	47,
	48,
	49,
	50,
	51,
	52,
	53,
	54,
	55,
	56,
	57,
	58,
	59,
	60,
	61,
	62,
	63,
	64,
	65,
	66,
	67,
	68,
	69,
	70,
	71,
	72,
	73,
	74,
	75,
	76,
	77,
	78,
	79,
	80,
	81,
	82,
	83,
	84,
	85,
	86,
	87,
	88,
	89,
	90,
	91,
	92,
	93,
	94,
	95,
	96,
	97,
	98,
	99,
	100,
	};

	float y_training[100] = {
	122.683,
	112.652,
	108.413,
	106.71,
	106.027,
	105.754,
	105.644,
	105.6,
	105.582,
	105.575,
	105.572,
	105.571,
	105.57,
	105.57,
	105.57,
	105.57,
	105.57,
	105.57,
	105.569,
	105.569,
	105.569,
	105.569,
	105.569,
	105.569,
	105.569,
	105.569,
	105.568,
	105.568,
	105.568,
	105.568,
	105.568,
	105.568,
	105.568,
	105.567,
	105.567,
	105.567,
	105.567,
	105.567,
	105.567,
	105.567,
	105.567,
	105.566,
	105.566,
	105.566,
	105.566,
	105.566,
	105.566,
	105.566,
	105.566,
	105.566,
	105.565,
	105.565,
	105.565,
	105.565,
	105.565,
	105.565,
	105.565,
	105.565,
	105.565,
	105.565,
	105.565,
	105.565,
	105.565,
	105.565,
	105.565,
	105.565,
	105.565,
	105.565,
	105.565,
	105.565,
	105.566,
	105.566,
	105.566,
	105.566,
	105.566,
	105.566,
	105.567,
	105.567,
	105.567,
	105.567,
	105.567,
	105.567,
	105.568,
	105.568,
	105.568,
	105.568,
	105.568,
	105.567,
	105.567,
	105.567,
	105.566,
	105.565,
	105.564,
	105.563,
	105.561,
	105.559,
	105.556,
	105.552,
	105.548,
	105.543,
	};

	float y_validation[100] = {
	272.141,
	270.719,
	269.943,
	269.525,
	269.3,
	269.178,
	269.111,
	269.074,
	269.053,
	269.04,
	269.032,
	269.027,
	269.023,
	269.02,
	269.017,
	269.015,
	269.013,
	269.011,
	269.01,
	269.008,
	269.007,
	269.006,
	269.005,
	269.004,
	269.004,
	269.003,
	269.002,
	269.002,
	269.001,
	269.001,
	269.001,
	269,
	269,
	269,
	269,
	269,
	269,
	269,
	269,
	269,
	269,
	269,
	269,
	268.999,
	268.998,
	268.998,
	268.996,
	268.995,
	268.994,
	268.992,
	268.99,
	268.987,
	268.984,
	268.98,
	268.975,
	268.97,
	268.964,
	268.958,
	268.95,
	268.941,
	268.931,
	268.919,
	268.907,
	268.892,
	268.876,
	268.858,
	268.837,
	268.815,
	268.79,
	268.762,
	268.731,
	268.697,
	268.66,
	268.618,
	268.573,
	268.523,
	268.468,
	268.408,
	268.341,
	268.269,
	268.189,
	268.101,
	268.004,
	267.898,
	267.78,
	267.651,
	267.507,
	267.347,
	267.17,
	266.972,
	266.751,
	266.504,
	266.226,
	265.914,
	265.561,
	265.163,
	264.713,
	264.203,
	263.625,
	262.97,
	};

	TMultiGraph *mg = new TMultiGraph();
	TGraph* gr1 = new TGraph(100, x, y_training);
	gr1->SetName("gr1");
	gr1->SetMarkerColor(1);
	gr1->SetMarkerSize(0.05);
	gr1->SetMarkerStyle(7);
	gr1->SetLineColor(kGreen);
	gr1->SetLineWidth(5);
	TGraph* gr2 = new TGraph(100, x, y_validation);
	gr2->SetName("gr2");
	gr2->SetMarkerColor(2);
	gr2->SetMarkerSize(0.05);
	gr2->SetMarkerStyle(8);
	gr2->SetLineColor(kOrange);
	gr2->SetLineWidth(5);
	mg->Add(gr1);
	mg->Add(gr2);
	mg->GetXaxis()->SetTitle("Number of epochs");
	mg->GetYaxis()->SetTitle("MAPE");
	mg->SetMinimum(0.);
	TCanvas *c1 = new TCanvas("c1","multigraph");
	c1->SetGrid();
	c1->SetCanvasSize(3840, 2160);
	mg->Draw("AC*");
	auto legend = new TLegend(0.9,0.9,0.9,0.9);
	legend->SetHeader("Legend","C");
	legend->AddEntry("gr1","MAPE value training","l");
	legend->AddEntry("gr2","MAPE value validation","l");
	legend->Draw();
	c1->Print("../Output_data_graph/MLP_2-3-2__100_Epochs_2024_11_12_00_14_29_Plot.c.bmp");
}