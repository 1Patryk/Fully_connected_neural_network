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
	275.795,
	275.348,
	274.931,
	274.515,
	274.1,
	273.688,
	273.277,
	272.867,
	272.459,
	272.052,
	};

	float y_validation[10] = {
	165.317,
	165.066,
	164.84,
	164.614,
	164.389,
	164.164,
	163.939,
	163.715,
	163.491,
	163.268,
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
	c1->Print("../Output_data_graph/MLP_2-20-18-15-8-2-1__10_Epochs_2025_12_30_19_33_02_Plot.c.bmp");
}