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


using namespace TMath;

void plotFile_comparison() {

	// Data file
	TString input = "data/SingleGEM/gain1.txt";

	// Output filename
	TString output = "data/SingleGEM/gain1.pdf";	
	
	// Settings
	TString title = "effective gain vs GEM voltage";
	TString xaxis = "V_{GEM} [V]";
	TString yaxis = "effective gain";
	TString data1 = "Experiment";
	TString data2 = "Simulation";

	// Graphical styles
	gROOT->ProcessLine(".x rootstyle.c");
	gROOT->SetStyle("newStyle");


	TGraph *plot1 = new TGraph();
	TGraph *plot2 = new TGraph();
	Int_t i = 0;

	ifstream inp;
	string line;
	inp.open(input);
	
	Double_t x, y1, y2;
	
	// Read first line
	getline(inp,line);

	while(getline(inp,line)) {
		
		stringstream ss(line);
		//cout << line << endl;
		ss >> x >> y1 >> y2;
		plot1->SetPoint(i, x, y1);
		plot2->SetPoint(i, x, y2);

		i++;		
	}
	
	TCanvas *c1 = new TCanvas("c1", "plot", 750, 500);
	c1->cd();
	
	TLegend *legend = new TLegend(0.2, 0.7, 0.4, 0.85);
	legend->AddEntry(plot1, data1, "p");
	legend->AddEntry(plot2, data2, "p");
	
	
	plot1->GetXaxis()->SetTitle(xaxis);
	plot1->GetYaxis()->SetTitle(yaxis);
	
	plot1->GetXaxis()->SetRange(400., 530.);	
	plot1->SetMinimum(20.);
	plot1->SetMaximum(620.);
	
	
	plot1->Draw("AP");
	plot1->SetMarkerColor(kRed);
	plot1->SetMarkerSize(1.);
	
	plot2->Draw("P");
	plot2->SetMarkerColor(kBlue);
	plot2->SetMarkerSize(1.);
	
	legend->Draw("SAME");
	c1->Update();
	c1->SaveAs(output);
	

}
