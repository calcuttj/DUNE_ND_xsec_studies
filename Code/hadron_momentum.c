#include "eff_DUNE.h"

char * fInFileName;
char * fOutFileName;
char * fEffFileName;

void lar_efficiencies(char * fInFileName,char * fOutFileName){

   TRandom * rand = new TRandom();

   TFile *fout = new TFile(fOutFileName, "RECREATE");
   TTree *out_tree;

   TFile *fin = new TFile(fInFileName, "READ");
   TTree *in_tree;
  
   for(int i = 0; i < 4; i++){
      cout<<tree_names[i]<<endl;
      fin->cd();
      in_tree = (TTree*)fin->Get(tree_names[i]);
      in_tree->SetBranchAddress("array_pmu",&array_pmu); 
      in_tree->SetBranchAddress("array_ppip",&array_ppip); 
      in_tree->SetBranchAddress("array_ppim",&array_ppim); 
      in_tree->SetBranchAddress("array_ppi0",&array_ppi0); 
      in_tree->SetBranchAddress("array_pprot",&array_pprot); 
//      in_tree->SetBranchAddress("Enu_true",&Enu_true); 
      in_tree->SetBranchAddress("Mode",&Mode);

      fout->cd();
      out_tree = new TTree(tree_names[i],tree_names[i]); 
      out_tree->Branch("Nleptons",&Nleptons_reco,"Nleptons/I");
      out_tree->Branch("Nprotons",&Nprotons_reco,"Nprotons/I");
      out_tree->Branch("Npiplus",&Npiplus_reco,"Npiplus/I");
      out_tree->Branch("Npineg",&Npineg_reco,"Npineg/I");
      out_tree->Branch("Npi0",&Npi0_reco,"Npi0/I");
      out_tree->Branch("Mode_true", &Mode, "Mode_true/I");
      out_tree->Branch("P_protons",&P_protons_reco,"P_protons/F"); 
      out_tree->Branch("P_pions",&P_pions_reco,"P_pions/F"); 


      for(int j = 0; j < in_tree->GetEntries(); j++){
//        cout<<j<<endl;


        float Px_protons = 0;
        float Py_protons = 0;
        float Pz_protons = 0;
        float Px_pions = 0;
        float Py_pions = 0;
        float Pz_pions = 0;
         

        P_protons_reco = 0;
        P_pions_reco = 0;
 
        Nleptons_reco = 0;
        Nprotons_reco = 0;
        Npiplus_reco = 0;
        Npineg_reco = 0;

        Npi0_reco = 0;
   
        in_tree->GetEntry(j);
        //Skip any mode > 30 
        //These are NC events and won't have 
        //Any leptons anyways 
        if(abs(Mode) > 30){continue;}
        for(int k = 0; k < array_pmu->GetEntries(); k++){
           //Get mu momentum
           // throw random number, check trkeff
           TLorentzVector *pmu_4mom = (TLorentzVector*)array_pmu->At(k); 
           //For cases with more than 1 lepton, want to get highest momentum 
                    
           Nleptons_reco++;
           
        }

        //Protons
        for(int k = 0; k < array_pprot->GetEntries(); k++){
           //Get prot momentum
           // throw random number, check trkeff
           TLorentzVector *pprot_4mom = (TLorentzVector*)array_pprot->At(k); 
           Px_protons += pprot_4mom->Px();
           Py_protons += pprot_4mom->Py();
           Pz_protons += pprot_4mom->Pz();            
           
           Nprotons_reco++;
          
        }
        //Pi+
        for(int k = 0; k < array_ppip->GetEntries(); k++){
           //Get pip momentum
           // throw random number, check trkeff
           TLorentzVector *ppip_4mom = (TLorentzVector*)array_ppip->At(k); 
           Px_pions += ppip_4mom->Px();
           Py_pions += ppip_4mom->Py();
           Pz_pions += ppip_4mom->Pz();            

           Npiplus_reco++;
          
        }
        //Pi-
        for(int k = 0; k < array_ppim->GetEntries(); k++){
           //Get pip momentum
           // throw random number, check trkeff
           TLorentzVector *ppim_4mom = (TLorentzVector*)array_ppim->At(k); 
           Px_pions += ppip_4mom->Px();
           Py_pions += ppip_4mom->Py();
           Pz_pions += ppip_4mom->Pz();            

           Npineg_reco++;
          
        }
        //Pi0    
/*        for(int k = 0; k < array_ppi0->GetEntries(); k++){
           //Get pip momentum
           // throw random number, check trkeff
           TLorentzVector *ppi0_4mom = (TLorentzVector*)array_ppi0->At(k); 
           Px_pions += ppip_4mom->Px();
           Py_pions += ppip_4mom->Py();
           Pz_pions += ppip_4mom->Pz();            

           Npi0_reco++;
          
        }*/

        P_protons_reco = sqrt(Px_protons*Px_protons + Py_protons*Py_protons + Pz_protons*Pz_protons);  
        P_pions_reco = sqrt(Px_pions*Px_pions + Py_pions*Py_pions + Pz_pions*Pz_pions);  

        //fout->cd();

        out_tree->Fill();
     }      
     out_tree->Write();
   } 


   //FD
/*   for(int i = 0; i < 2; i++){
      cout<<tree_names[i]<<endl;
      fin->cd();
      in_tree = (TTree*)fin->Get(tree_names[i]);

      fout->cd();
//      out_tree = (TTree*)in_tree->Clone();
//      TBranch *del_branch = out_tree->GetBranch("array_pprot");
//      out_tree->GetListOfBranches()->Remove(del_branch);
 //     out_tree->Write();

      in_tree->CloneTree()->Write();
   }*/
}
