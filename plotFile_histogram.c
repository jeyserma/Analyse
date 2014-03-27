#include <sstream>                  // class for parsing strings  
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cmath>

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1F.h>
#include <TH1D.h>
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


void plotFile_histogram() {

	TH1F *t = new TH1F("", "tt", 10, 0., 10.);

	// Data file
	TString input = "data/poisson.root";
	
	// Output filename
	TString output = "data/SingleGEM/inization-poisson.pdf";	
	
	// Settings
	TString title = "Ionization distribution";
	TString xaxis = "Time [ns]";
	TString yaxis = "";
	
	// Graphical styles
	gROOT->ProcessLine(".x rootstyle.c");
	gROOT->SetStyle("newStyle");
	
	TFile *File = new TFile(input, "READ");
	if(!File->IsOpen()) {
		std::cout << "Problem while opening the file" << std::endl;
		exit();
	}
	File->cd("data/SingleGEM/");

	File->ls(); // List root file contents

	
	//TH1F *h1= (TH1F *)File->Get("energy");
	//TH1F *h1 = new TH1F("h1", "title", 20, 0., 20.);

	TH1F *h1;
	File->GetObject("Poisson", h1);
	h1->Draw();
	/*
	TCanvas *c1 = new TCanvas("c1", "plot", 750, 500);
	c1->cd();
	
	//h1->GetXaxis()->SetTitle(xaxis);
	std::cout << h1->GetMean() << std::endl;
	//h1->GetXaxis()->SetTitle(xaxis);
	//h1->GetYaxis()->SetTitle(yaxis);
	h1->SetTitle(title);
	h1->GetXaxis()->SetLimits(0., 20.);
	
	
	
	//c1->Update();
	//c1->SaveAs(output);
	
	//

*/
	File->Close();
}
