{
	float x[1] = {
	1,
	};

	float y_training[1] = {
	3.17341,
	};

	float y_validation[1] = {
	1.56685,
	};

	TMultiGraph *mg = new TMultiGraph();
	TGraph* gr1 = new TGraph(1, x, y_training);
	gr1->SetName("gr1");
	gr1->SetMarkerColor(1);
	gr1->SetMarkerSize(0.05);
	gr1->SetMarkerStyle(7);
	gr1->SetLineColor(kGreen);
	gr1->SetLineWidth(5);
	TGraph* gr2 = new TGraph(1, x, y_validation);
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
	c1->Print("../Output_data_graph/MLP_2-1-1__1_Epochs_2026_01_18_14_19_47_Plot.c.bmp");
}