#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <utility>
#include <string>

#include "TFile.h"
#include "TH1D.h"
#include "TH2.h"
#include "TGraph.h"
#include "THStack.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TString.h"

void scale(string in_file_name, string out_file_name){


	//Open root flux input file
	TFile * inFileRoot = new TFile(in_file_name.c_str(),"READ");
	//Get unoscillated fluxes
	TH1D * numu_flux = inFileRoot->Get("numu_flux");
	TH1D * numubar_flux = inFileRoot->Get("numubar_flux");
	TH1D * nue_flux = inFileRoot->Get("nue_flux");
	TH1D * nuebar_flux = inFileRoot->Get("nuebar_flux");
	//Get oscillated fluxes
	TH1D * numu_fluxosc = inFileRoot->Get("numu_fluxosc");
	TH1D * numubar_fluxosc = inFileRoot->Get("numubar_fluxosc");
	TH1D * nue_fluxosc = inFileRoot->Get("nue_fluxosc");
	TH1D * nuebar_fluxosc = inFileRoot->Get("nuebar_fluxosc");
	

	//Open root flux output file
	TFile * outFileRoot = new TFile(out_file_name.c_str(),"RECREATE");
	//Copy unoscillated fluxes
	TH1D * numu_flux_scaled = numu_flux->Clone(); 
	TH1D * numubar_flux_scaled = numubar_flux->Clone(); 
	TH1D * nue_flux_scaled = nue_flux->Clone(); 
	TH1D * nuebar_flux_scaled = nuebar_flux->Clone(); 
	//Copy oscillated fluxes
	TH1D * numu_fluxosc_scaled = numu_fluxosc->Clone(); 
	TH1D * numubar_fluxosc_scaled = numubar_fluxosc->Clone(); 
	TH1D * nue_fluxosc_scaled = nue_fluxosc->Clone(); 
	TH1D * nuebar_fluxosc_scaled = nuebar_fluxosc->Clone(); 

	//Scaled each by the bin width
	for(int i = 1; i <= numu_flux_scaled->GetXaxis()->GetNbins(); i++){
		numu_flux_scaled->SetBinContent(i, numu_flux_scaled->GetBinContent(i)/numu_flux_scaled->GetXaxis()->GetBinWidth(i) );
		numubar_flux_scaled->SetBinContent(i, numubar_flux_scaled->GetBinContent(i)/numubar_flux_scaled->GetXaxis()->GetBinWidth(i) );
		nue_flux_scaled->SetBinContent(i, nue_flux_scaled->GetBinContent(i)/nue_flux_scaled->GetXaxis()->GetBinWidth(i) );
		nuebar_flux_scaled->SetBinContent(i, nuebar_flux_scaled->GetBinContent(i)/nuebar_flux_scaled->GetXaxis()->GetBinWidth(i) );

		numu_fluxosc_scaled->SetBinContent(i, numu_fluxosc_scaled->GetBinContent(i)/numu_fluxosc_scaled->GetXaxis()->GetBinWidth(i) );
		numubar_fluxosc_scaled->SetBinContent(i, numubar_fluxosc_scaled->GetBinContent(i)/numubar_fluxosc_scaled->GetXaxis()->GetBinWidth(i) );
		nue_fluxosc_scaled->SetBinContent(i, nue_fluxosc_scaled->GetBinContent(i)/nue_fluxosc_scaled->GetXaxis()->GetBinWidth(i) );
		nuebar_fluxosc_scaled->SetBinContent(i, nuebar_fluxosc_scaled->GetBinContent(i)/nuebar_fluxosc_scaled->GetXaxis()->GetBinWidth(i) );
	
	}

	//Rename hists
	string title;

	title = numu_flux_scaled->GetYaxis()->GetTitle();
	title.append(" / GeV");
	numu_flux_scaled->SetYTitle(title.c_str());

	title = numubar_flux_scaled->GetYaxis()->GetTitle();
	title.append(" / GeV");
	numubar_flux_scaled->SetYTitle(title.c_str());

	title = nue_flux_scaled->GetYaxis()->GetTitle();
	title.append(" / GeV");
	nue_flux_scaled->SetYTitle(title.c_str());

	title = nuebar_flux_scaled->GetYaxis()->GetTitle();
	title.append(" / GeV");
	nuebar_flux_scaled->SetYTitle(title.c_str());

	title = numu_fluxosc_scaled->GetYaxis()->GetTitle();
	title.append(" / GeV");
	numu_fluxosc_scaled->SetYTitle(title.c_str());

	title = numubar_fluxosc_scaled->GetYaxis()->GetTitle();
	title.append(" / GeV");
	numubar_fluxosc_scaled->SetYTitle(title.c_str());

	title = nue_fluxosc_scaled->GetYaxis()->GetTitle();
	title.append(" / GeV");
	nue_fluxosc_scaled->SetYTitle(title.c_str());

	title = nuebar_fluxosc_scaled->GetYaxis()->GetTitle();
	title.append(" / GeV");
	nuebar_fluxosc_scaled->SetYTitle(title.c_str());
	//Save hists to output file
	numu_flux_scaled->Write();
	numubar_flux_scaled->Write();
	nue_flux_scaled->Write();
	nuebar_flux_scaled->Write();

	numu_fluxosc_scaled->Write();
	numubar_fluxosc_scaled->Write();
	nue_fluxosc_scaled->Write();
	nuebar_fluxosc_scaled->Write();
}
