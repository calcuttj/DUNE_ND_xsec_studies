#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <utility> 

#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TGraph.h"
#include "THStack.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TTree.h"
#include "TLine.h"
#include "TTree.h"
#include "TPaveText.h"
#include "TMath.h"

using std::cout;
using std::cerr;
using std::endl;
using namespace std;

void print_DUNE_flux(){

  char * files[4];
  files[0] = "Dune_Flux/CDR_FHC_FD_flux_scaled.root";
  files[1] = "Dune_Flux/CDR_RHC_FD_flux_scaled.root";
  files[2] = "Dune_Flux/CDR_FHC_ND_flux_scaled.root";
  files[3] = "Dune_Flux/CDR_RHC_ND_flux_scaled.root";

  char * hists[4];
  hists[0] = "numu_fluxosc";
  hists[1] = "numubar_fluxosc";
  hists[2] = "numu_flux";
  hists[3] = "numubar_flux";
 
  char * names[4];
  names[0] = "Dune_Flux/numu_FD_flux.png";
  names[1] = "Dune_Flux/numubar_FD_flux.png";
  names[2] = "Dune_Flux/numu_ND_flux.png";
  names[3] = "Dune_Flux/numubar_ND_flux.png";

  char * titles[4];
  titles[0] = "#nu_{#mu} Flux - DUNE Far Detector";
  titles[1] = "#bar{#nu_{#mu}} Flux - DUNE Far Detector";
  titles[2] = "#nu_{#mu} Flux - DUNE Near Detector";
  titles[3] = "#bar{#nu_{#mu}} Flux - DUNE Near Detector";

  for(int i = 0; i < 4; i++){
    TFile *f = new TFile(files[i],"READ");
    
    TH1 *h = (TH1*)f->Get(hists[i]);

    TCanvas * c1 = new TCanvas("c1","c1",700,550);
    gStyle->SetOptStat(kFALSE);
 
    h->GetXaxis()->SetRangeUser(0,10);
    h->SetLineWidth(2);
    h->SetTitle(titles[i]);
    h->Draw("chist");
    
    c1->SaveAs(names[i]); 
  }

}
