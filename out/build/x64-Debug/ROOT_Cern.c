{	
	TGraph *gr = new TGraph();
	
	gr->SetMarkerStyle(kFullCircle);
	
	fstream file;
	file.open("Out_date.txt", ios::in);
	
	while(1)
	{
		double x, y;
		file >> x >> y;
		gr->SetPoint(gr->GetN(), x, y);
		if(file.eof()) break;
	}
	
	file.close();
	
	TCanvas *c1 = new TCanvas();
	gr->Draw("ALP");
}