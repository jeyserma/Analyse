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

TString double2str(Double_t t) {
    TString str; 
    str.Form("%f", t);
    return str;
} 

void plotFile_timing() {

	// Data file
	TString input = "data/SingleGEM/time_0.0.root";
	
	// Output filename
	TString output = "data/SingleGEM/time_0.0.pdf";	
	
	// Settings
	TString title = "";
	TString xaxis = "Time [ns]";
	TString yaxis = "signal [fC / ns]";
	

	TFile *File = new TFile(input, "READ");
	if(!File->IsOpen()) {
		std::cout << "Problem while opening the file" << std::endl;
		exit();
	}

	File->ls(); // List root file contents
	

	TCanvas *c1 = (TCanvas *)File->Get("c1");
	TH1D *h1= (TH1D*)c1->FindObject("hSignal");
	

	
	TCanvas *c2 = new TCanvas("c1", "plot", 750, 500);
	c2->cd();
	h1->GetXaxis()->SetTitle(xaxis);
	h1->GetYaxis()->SetTitle(yaxis);
	TString rmstitle;
	rmstitle = "RMS: " + double2str(h1->GetRMS());
	h1->SetTitle(rmstitle);
	h1->Scale(-1);
	h1->GetXaxis()->SetRange(0., 300.);

	
	// Style
	h1->SetLineColor(kRed);
	h1->SetLabelSize(0.04, "xyz");
	h1->SetTitleSize(0.04, "xyz");
	h1->SetTitleOffset(1.6, "y");
	
	gStyle->SetPadLeftMargin(0.12);
	gStyle->SetOptStat(0);
	gStyle->SetTitleAlign(33);
	gStyle->SetTitleX(0.925);
	gStyle->SetTitleY(0.95);

	
	h1->Draw();

	
	c2->Update();
	c2->SaveAs(output);
	
	
	//File->Close();


	
}
