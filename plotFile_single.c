#include <sstream>                  // class for parsing strings  
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cmath>

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1F.h>
#include <TCanvas.h>
#include <TPaveStats.h>
#include <TPad.h>
#include <TMath.h>
#include <TStyle.h>
#include <TSystem.h>
#include <TLegend.h>
#include <TString.h>
#include <TGraph.h>
#include <TLatex.h>
#include <TMultiGraph.h>


void plotFile_single() {

	// Data file
	TString input = "data/SingleGEM/gain_energy/results.txt";

	// Output filename
	TString output = "data/SingleGEM/gain_energy/results.pdf";	
	
	// Settings
	TString title = "";
	TString xaxis = "primary electron energy [eV]";
	TString yaxis = "effective gain";
	TString data = "Experiment";


	// Graphical styles
	gROOT->ProcessLine(".x rootstyle.c");
	gROOT->SetStyle("newStyle");


	TGraph *plot = new TGraph();
	Int_t i = 0;

	ifstream inp;
	string line;
	inp.open(input);
	
	Double_t x, y;
	
	// Read first line
	getline(inp,line);

	while(getline(inp,line)) {
		
		stringstream ss(line);
		//cout << line << endl;
		ss >> x >> y;
		plot->SetPoint(i, x, y);

		i++;		
	}
	
	TCanvas *c1 = new TCanvas("c1", "plot", 750, 500);
	c1->cd();
	
	TLegend *legend = new TLegend(0.2, 0.7, 0.4, 0.85);
	legend->AddEntry(plot, data, "p");
	
	
	plot->GetXaxis()->SetTitle(xaxis);
	plot->GetYaxis()->SetTitle(yaxis);
	
	plot->GetXaxis()->SetLimits(-5., 100.);
	//plot->GetYaxis()->SetLimits(rangeLeft, rangeRight);
	
	
	plot->Draw("AP");
	plot->SetMarkerColor(kRed);
	plot->SetMarkerSize(1.);
	
	legend->Draw("SAME");
	c1->Update();
	c1->SaveAs(output);
}
