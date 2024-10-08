{
	double x[5] = {1, 2, 3, 4, 5};
	double y[5] = {1, 4, 9, 16, 5};

	TGraph gr(5, x, y);

	TCanvas c1;
	gr.Draw("Ac*");
}