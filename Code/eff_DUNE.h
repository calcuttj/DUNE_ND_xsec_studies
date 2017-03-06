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
#include "TRandom.h"

using std::cout;
using std::cerr;
using std::endl;
using namespace std;


float muon_thresh_lar = 0;
float muon_thresh_gar = 0;
float proton_thresh_lar = 200; 
float proton_thresh_gar = 100; 
float pion_thresh_lar = 0; 
float pion_thresh_gar = 0; 


char* tree_names[4];
tree_names[0] = "GenericFlux_FHC_FD_numu_osc_VARS";
tree_names[1] = "GenericFlux_RHC_FD_numub_osc_VARS";
tree_names[2] = "GenericFlux_FHC_ND_numu_VARS";
tree_names[3] = "GenericFlux_RHC_ND_numub_VARS";

TObjArray *array_pmu;
TObjArray *array_pprot;
TObjArray *array_pneut;
TObjArray *array_ppip;
TObjArray *array_ppim;
TObjArray *array_ppi0;

int Mode;

float Ereco;

int Nleptons_reco;
float ELep_reco;

int Nprotons_reco;
float EPr_reco;

int Npiplus_reco;
float EPiP_reco;

int Npineg_reco;
float EPiN_reco;

int Npi0_reco;
float EPi0_reco;

float Enu_true;
float q0_reco;
float q3_reco;
float Q2_reco;

float Px_total_reco;
float Py_total_reco;
float Pz_total_reco;

float Px_Lep_reco;
float Py_Lep_reco;
float Pz_Lep_reco;

//float Px;
//float Py;
//float Pz;

float delta_Px;
float delta_Py;
float delta_Pz;

float P_protons_reco;
float P_pions_reco;

