#include "eff_DUNE.h"

char * fInFileName;
char * fOutFileName;
char * fEffFileName;

void lar_efficiencies(char * fInFileName, /*char * fEffFileName*, */char * fOutFileName){

   TRandom * rand = new TRandom();

   TFile *fout = new TFile(fOutFileName, "RECREATE");
   TTree *out_tree;

   TFile *fin = new TFile(fInFileName, "READ");
   TTree *in_tree;
/*
   TFile *feff = new TFile(fEffFileName, "READ");

   TH1D * trkeff_muon = (TH1D*)feff->Get("trkeff_muon"); 
   TH1D * trkeff_electron = (TH1D*)feff->Get("trkeff_electron"); 
   TH1D * trkeff_pion = (TH1D*)feff->Get("trkeff_pion"); 
   TH1D * trkeff_proton = (TH1D*)feff->Get("trkeff_proton"); 

   TH1D * pideff_muon = (TH1D*)feff->Get("pideff_muon"); 
   TH1D * pideff_electron = (TH1D*)feff->Get("pideff_electron"); 
   TH1D * pideff_pion = (TH1D*)feff->Get("pideff_pion"); 
   TH1D * pideff_proton = (TH1D*)feff->Get("pideff_proton"); 
*/
  
   for(int i = 0; i < 4; i++){
      cout<<tree_names[i]<<endl;
      fin->cd();
      in_tree = (TTree*)fin->Get(tree_names[i]);
      in_tree->SetBranchAddress("array_pmu",&array_pmu); 
      in_tree->SetBranchAddress("array_ppip",&array_ppip); 
      in_tree->SetBranchAddress("array_ppim",&array_ppim); 
      in_tree->SetBranchAddress("array_ppi0",&array_ppi0); 
      in_tree->SetBranchAddress("array_pprot",&array_pprot); 
      in_tree->SetBranchAddress("Enu_true",&Enu_true); 
      in_tree->SetBranchAddress("Mode",&Mode);

      fout->cd();
      out_tree = new TTree(tree_names[i],tree_names[i]); 
      out_tree->Branch("Ereco",&Ereco,"Ereco/F");
      out_tree->Branch("Nleptons_reco",&Nleptons_reco,"Nleptons_reco/I");
      out_tree->Branch("ELep_reco",&ELep_reco,"ELep_reco/F");
      out_tree->Branch("Nprotons_reco",&Nprotons_reco,"Nprotons_reco/I");
      out_tree->Branch("EPr_reco",&EPr_reco,"EPr_reco/F");
      out_tree->Branch("Npiplus_reco",&Npiplus_reco,"Npiplus_reco/I");
      out_tree->Branch("EPiP_reco",&EPiP_reco,"EPiP_reco/F");
      out_tree->Branch("Npineg_reco",&Npineg_reco,"Npineg_reco/I");
      out_tree->Branch("EPiN_reco",&EPiN_reco,"EPiN_reco/F");
      out_tree->Branch("Npi0_reco",&Npi0_reco,"Npi0_reco/I");
      out_tree->Branch("EPi0_reco",&EPi0_reco,"EPi0_reco/F");
      out_tree->Branch("Enu_true", &Enu_true, "Enu_true/F");
      out_tree->Branch("Mode_true", &Mode, "Mode_true/I");
      out_tree->Branch("q0_reco", &q0_reco, "q0_reco/F");
      out_tree->Branch("q3_reco", &q3_reco, "q3_reco/F");
      out_tree->Branch("Q2_reco", &Q2_reco, "Q2_reco/F");
      out_tree->Branch("P_protons_reco",&P_protons_reco,"P_protons_reco/F"); 
      out_tree->Branch("P_pions_reco",&P_pions_reco,"P_pions_reco/F"); 


      for(int j = 0; j < in_tree->GetEntries(); j++){
//        cout<<j<<endl;

        float Px_protons = 0;
        float Py_protons = 0;
        float Pz_protons = 0;
        float Px_pions = 0;
        float Py_pions = 0;
        float Pz_pions = 0;
 
        Ereco = 0;
        q0_reco = -999.99;
        q3_reco = -999.99;
        Q2_reco = -999.99;

        delta_Px = -999.99;
        delta_Py = -999.99;
        delta_Pz = -999.99;

        P_protons_reco = 0;
        P_pions_reco = 0;
 
        Nleptons_reco = 0;
        ELep_reco = 0;
        Nprotons_reco = 0;
        EPr_reco = 0;
        Npiplus_reco = 0;
        EPiP_reco = 0;
        Npineg_reco = 0;
        EPiN_reco = 0;

        Npi0_reco = 0;
        EPi0_reco = 0;
   
        Px_total_reco = 0;
        Py_total_reco = 0;
        Pz_total_reco = 0;       

        Px_Lep_reco = 0;
        Py_Lep_reco = 0;
        Pz_Lep_reco = 0;       

        in_tree->GetEntry(j);
        //Skip any mode > 30 
        //These are NC events and won't have 
        //Any leptons anyways 
        if(abs(Mode) > 30){continue;}
        for(int k = 0; k < array_pmu->GetEntries(); k++){
           //Get mu momentum
           // throw random number, check trkeff
           TLorentzVector *pmu_4mom = (TLorentzVector*)array_pmu->At(k); 
           float Px = pmu_4mom->Px();
           float Py = pmu_4mom->Py();
           float Pz = pmu_4mom->Pz();            
 
           float P = sqrt(Px*Px + Py*Py + Pz*Pz);

           if(i < 2){//FD FHC,RHC
             if (P < muon_thresh_lar)continue;
           }
           else{//ND FHC,RHC
             if (P < muon_thresh_lar)continue;
           }
           Px_total_reco += Px;
           Py_total_reco += Py;
           Pz_total_reco += Pz;       
    
           //For cases with more than 1 lepton, want to get highest momentum 
           if(Nleptons_reco > 0){
             if(P*P > Px_Lep_reco*Px_Lep_reco + Py_Lep_reco*Py_Lep_reco + Pz_Lep_reco*Pz_Lep_reco){
               Px_Lep_reco = Px;
               Py_Lep_reco = Py;
               Pz_Lep_reco = Pz;       
               ELep_reco = pmu_4mom->E();
             }
          }
          else{
             Px_Lep_reco = Px;
             Py_Lep_reco = Py;
             Pz_Lep_reco = Pz;       
             ELep_reco = pmu_4mom->E();
           }
                    
           Nleptons_reco++;
           Ereco += pmu_4mom->E();
           
        }

        //Protons
        for(int k = 0; k < array_pprot->GetEntries(); k++){
           //Get prot momentum
           // throw random number, check trkeff
           TLorentzVector *pprot_4mom = (TLorentzVector*)array_pprot->At(k); 
           float Px = pprot_4mom->Px();
           float Py = pprot_4mom->Py();
           float Pz = pprot_4mom->Pz();            
           float P = sqrt(Px*Px + Py*Py + Pz*Pz);

           if(i < 2){//FD FHC,RHC
             if (P < proton_thresh_lar)continue;
           }
           else{
             if (P < proton_thresh_lar)continue;
           }
           
           Px_protons += Px;
           Py_protons += Py;
           Pz_protons += Pz; 
  
           Px_total_reco += Px;
           Py_total_reco += Py;
           Pz_total_reco += Pz;       
           Nprotons_reco++;
           EPr_reco += pprot_4mom->E();
           Ereco += pprot_4mom->E() - pprot_4mom->Mag();
           
        }
        //Pi+
        for(int k = 0; k < array_ppip->GetEntries(); k++){
           //Get pip momentum
           // throw random number, check trkeff
           TLorentzVector *ppip_4mom = (TLorentzVector*)array_ppip->At(k); 
           float Px = ppip_4mom->Px();
           float Py = ppip_4mom->Py();
           float Pz = ppip_4mom->Pz();            
           float P = sqrt(Px*Px + Py*Py + Pz*Pz);

           if(i < 2){//FD FHC,RHC
             if (P < pion_thresh_lar)continue;
           }
           else{     
             if (P < pion_thresh_lar)continue;
           }
           
           Px_pions += Px;
           Py_pions += Py;
           Pz_pions += Pz; 

           Px_total_reco += Px;
           Py_total_reco += Py;
           Pz_total_reco += Pz;       
           Npiplus_reco++;
           EPiP_reco += ppip_4mom->E();
           Ereco += ppip_4mom->E();
           
        }
        //Pi-
        for(int k = 0; k < array_ppim->GetEntries(); k++){
           //Get pip momentum
           // throw random number, check trkeff
           TLorentzVector *ppim_4mom = (TLorentzVector*)array_ppim->At(k); 
           float Px = ppim_4mom->Px();
           float Py = ppim_4mom->Py();
           float Pz = ppim_4mom->Pz();            
           float P = sqrt(Px*Px + Py*Py + Pz*Pz);
           if(i < 2){//FD FHC,RHC
             if (P < pion_thresh_lar)continue;
           }
           else{     
             if (P < pion_thresh_lar)continue;
           }
           
           Px_pions += Px;
           Py_pions += Py;
           Pz_pions += Pz; 
        
           Px_total_reco += Px;
           Py_total_reco += Py;
           Pz_total_reco += Pz;       
           Npineg_reco++;
           EPiN_reco += ppim_4mom->E();
           Ereco += ppim_4mom->E();
           
        }
        //Pi0    
        for(int k = 0; k < array_ppi0->GetEntries(); k++){
           //Get pip momentum
           // throw random number, check trkeff
           TLorentzVector *ppi0_4mom = (TLorentzVector*)array_ppi0->At(k); 
           float Px = ppi0_4mom->Px();
           float Py = ppi0_4mom->Py();
           float Pz = ppi0_4mom->Pz();            
           float P = sqrt(Px*Px + Py*Py + Pz*Pz);
/*           if(i < 2){//FD FHC,RHC
             if (P < pion_thresh_lar)continue;
           }
           else{     
             if (P < pion_thresh_lar)continue;
           }*/
           Px_total_reco += Px;
           Py_total_reco += Py;
           Pz_total_reco += Pz;       
           Npi0_reco++;
           EPi0_reco += ppi0_4mom->E();
           Ereco += ppi0_4mom->E();
           
        }
        //fout->cd();

        P_protons_reco = sqrt(Px_protons*Px_protons + Py_protons*Py_protons + Pz_protons*Pz_protons);  
        P_pions_reco = sqrt(Px_pions*Px_pions + Py_pions*Py_pions + Pz_pions*Pz_pions);  

        q0_reco = ELep_reco - Ereco;
         
        delta_Px = Px_total_reco - Px_Lep_reco;                
        delta_Py = Py_total_reco - Py_Lep_reco;                
        delta_Pz = Pz_total_reco - Pz_Lep_reco;                

        q3_reco = sqrt(delta_Px*delta_Px + delta_Py*delta_Py +  delta_Pz*delta_Pz );

        Q2_reco = q3_reco*q3_reco - q0_reco*q0_reco;

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
