{
	float x[10] = {
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
	};

	float y_training[10] = {
	2.51468,
	2.21268,
	2.21233,
	2.21232,
	2.21232,
	2.21232,
	2.21232,
	2.21233,
	2.21232,
	2.21233,
	};

	float y_validation[10] = {
	3.41825,
	3.24811,
	3.2479,
	3.2479,
	3.2479,
	3.2479,
	3.2479,
	3.24791,
	3.24791,
	3.24791,
	};

	TMultiGraph *mg = new TMultiGraph();
	TGraph* gr1 = new TGraph(10, x, y_training);
	gr1->SetName("gr1");
	gr1->SetMarkerColor(1);
	gr1->SetMarkerSize(0.05);
	gr1->SetMarkerStyle(7);
	gr1->SetLineColor(kGreen);
	gr1->SetLineWidth(5);
	TGraph* gr2 = new TGraph(10, x, y_validation);
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
	c1->Print("../Output_data_graph/MLP_2-2-1-1__10_Epochs_09_02_2026_18_11_59_Plot.c.bmp");
}