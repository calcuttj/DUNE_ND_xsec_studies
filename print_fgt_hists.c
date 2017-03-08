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

void print_fgt_hists(){
  TFile *fgt_file = new TFile("fgt_hists.root", "READ");
  
  char * particle[4];
  particle[0] = "muon";
  particle[1] = "proton";
  particle[2] = "electron";
  particle[3] = "pion";

  for(int i = 0; i < 4; i++){
    TH1 *h1 = (TH1*)fgt_file->Get(Form("trkeff_%s",particle[i]));
    TH1 *h2 = (TH1*)fgt_file->Get(Form("pideff_%s",particle[i]));

    h1->GetXaxis()->SetTitleOffset(1);
    h1->GetYaxis()->SetTitleOffset(1);
    h1->SetTitle(Form("FGT tracking efficiency - %ss",particle[i]));

    TCanvas * c1 = new TCanvas("c1","c1",700,550);
    h1->Draw();
    c1->SaveAs(Form("eff_plots/fgt_trkeff_%s.png",particle[i]));    

    h2->GetXaxis()->SetTitleOffset(1);
    h2->GetYaxis()->SetTitleOffset(1);
    h2->SetTitle(Form("FGT particle ID efficiency - %ss",particle[i]));

    TCanvas * c1 = new TCanvas("c1","c1",700,550);
    h2->Draw();
    c1->SaveAs(Form("eff_plots/fgt_pideff_%s.png",particle[i]));    

  }

}
