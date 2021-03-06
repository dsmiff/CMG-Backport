#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include "TFile.h"
#include "../includes/common.h"
#include "../includes/common2.h"

void prepareDatacardsFast(TString folder, TString syst_folder, TString SignalSample, int generated_PDF_set=1, int generated_PDF_member=0, TString WorZ="W"){

  TString original;
  std::vector<TString> tokenized;
  original = WorZ;
      
  TObjArray* LineColumns = original.Tokenize(",");
  
  for(int j=0;j<LineColumns->GetEntriesFast();j++)
  {
    tokenized.push_back(((TObjString *)LineColumns->At(j))->GetString());
    // cout << "tokenized["<<j<<"]= " << tokenized[j] << endl;
  }
  
  for(unsigned int itoken=0; itoken<tokenized.size(); itoken++){

    static const int Nsamples=23;
    enum                                 {  DATA, WJetsPowPlus,  WJetsPowNeg,  WJetsMadSig,  WJetsMadFake,  DYJetsPow,  DYJetsMadSig,  DYJetsMadFake,   TTJets,   ZZJets,   WWJets,  WZJets,  QCD, T_s, T_t, T_tW, Tbar_s, Tbar_t, Tbar_tW, EWK, EWKTT, MCDATALIKEPOW, MCDATALIKEMAD  };
    TString     samples_str[Nsamples]  = { "DATA" , "WJetsPowPlus", "WJetsPowNeg", "WJetsMadSig", "WJetsMadFake", "DYJetsPow", "DYJetsMadSig", "DYJetsMadFake",  "TTJets",  "ZZJets",  "WWJets", "WZJets",   "QCD", "T_s", "T_t", "T_tW", "Tbar_s", "Tbar_t", "Tbar_tW", "EWK", "EWKTT", "MCDATALIKEPOW", "MCDATALIKEMAD" };
    TString     WCharge_str[]={"Pos","Neg"};

    cout << "folder= " << folder << endl;
    cout << "SignalSample= " << SignalSample << endl;
    
    WorZ = tokenized.at(itoken); // "Z" or "W"
    TString Wlike = WorZ.Contains("W")?"":"like";
    int charges = WorZ.Contains("W")?2:1;
    double ZWmassRatio = ((float)WMass::ZMassCentral_MeV)/((float)WMass::WMassCentral_MeV);
    cout << "WorZ= " << WorZ << endl;
    
    double xmin=(30.*(1+(int)(1==1)))/(WMass::WMassCentral_MeV/1e3), xmax=(50.*(1+(int)(1==1)))/(WMass::WMassCentral_MeV/1e3);
    
    // TOKENIZE SAMPLES
    TFile* finTemplatesZ[Nsamples], *finTemplatesW[Nsamples];
    TH1D *TemplatesZ[WMass::NtoysMomCorr][WMass::PDF_members][Nsamples][WMass::etaMuonNSteps][2*WMass::WMassNSteps+1], *TemplatesZ_NonScaled[WMass::NtoysMomCorr][WMass::PDF_members][Nsamples][WMass::etaMuonNSteps][2*WMass::WMassNSteps+1];
    TH1D *TemplatesW[2][WMass::NtoysMomCorr][WMass::PDF_members][WMass::NFitVar][Nsamples][WMass::etaMuonNSteps][2*WMass::WMassNSteps+1], *TemplatesW_NonScaled[2][WMass::NtoysMomCorr][WMass::PDF_members][WMass::NFitVar][Nsamples][WMass::etaMuonNSteps][2*WMass::WMassNSteps+1];
    
    // LOAD ALL THE HISTOS FROM THE VARIOUS FILES IN MEMORY
    for(int isample=0; isample<Nsamples;isample++){
      finTemplatesW[isample] = new TFile(Form("%s/test_numbers_%s/%sanalysisOnDATA.root",folder.Data(),samples_str[isample].Data(),WorZ.Data()));
      finTemplatesW[isample]->Print();
      for(int ieta=0; ieta<WMass::etaMuonNSteps; ieta++){
        TString eta_str = Form("%.1f",WMass::etaMaxMuons[ieta]); eta_str.ReplaceAll(".","p");
        for(int jmass=0; jmass<2*WMass::WMassNSteps+1; jmass++){
          // int jWmass = WMass::WMassCentral_MeV-(WMass::WMassNSteps-jmass)*WMass::WMassStep_MeV;
          int jWmass = WorZ.Contains("Z")? WMass::Zmass_values_array[jmass] : WMass::Wmass_values_array[jmass];
          
          for(int h=0; h<WMass::PDF_members; h++){
              for(int m=0; m<WMass::NtoysMomCorr; m++){
              for(int k=0;k<3;k++){
                for(int c=0;c<charges;c++){
                  // TemplatesW[c][m][h][k][isample][ieta][jmass] = (TH1D*) finTemplatesW[isample]->Get(Form("hW%s%s_%sNonScaled_8_JetCut_pdf%d-%d%s_eta%s_%d",Wlike.Data(),WCharge_str[c].Data(),WMass::FitVar_str[k].Data(),WMass::PDF_sets<0?generated_PDF_set:WMass::PDF_sets,h, WMass::NtoysMomCorr>1?Form("_MomCorrToy%d",m):"",eta_str.Data(),jWmass));
                  
                  TemplatesW_NonScaled[c][m][h][k][isample][ieta][jmass] = (TH1D*) finTemplatesW[isample]->Get(Form("hW%s%s_%sNonScaled_8_JetCut_pdf%d-%d%s_eta%s_%d",Wlike.Data(),WCharge_str[c].Data(),WMass::FitVar_str[k].Data(),WMass::PDF_sets<0?generated_PDF_set:WMass::PDF_sets,h, WMass::NtoysMomCorr>1?Form("_MomCorrToy%d",m):"",eta_str.Data(),jWmass));
                }
              }
            }
          }
          
        }
      }
    }
    for(int isample=0; isample<Nsamples;isample++){
      for(int ieta=0; ieta<WMass::etaMuonNSteps; ieta++){
        for(int jmass=0; jmass<2*WMass::WMassNSteps+1; jmass++){
          for(int h=0; h<WMass::PDF_members; h++){
            for(int m=0; m<WMass::NtoysMomCorr; m++){
              for(int k=0;k<3;k++){
                for(int c=0;c<charges;c++){
                  
                  if(TemplatesW_NonScaled[c][m][h][k][isample][ieta][jmass]){
                    double int_hist_data = TemplatesW_NonScaled[c][0][0][k][isample][ieta][WMass::WMassNSteps]->Integral();
                    double int_hist_mcdatalike = TemplatesW_NonScaled[c][m][h][k][isample][ieta][jmass]->Integral();
                    double norm_factor_to_match_data = int_hist_mcdatalike>0 ? int_hist_data/int_hist_mcdatalike : 1;
                    
                    TemplatesW_NonScaled[c][m][h][k][isample][ieta][jmass]->Scale(norm_factor_to_match_data);
                    cout <<"c "<<c<<" m "<<m<<" h "<<" "<<h<<" k "<<k<<" isample "<<samples_str[isample]<<" ieta "<<ieta<<" jmass "<<jmass<<" norm "<<norm_factor_to_match_data<<endl;
                  }
                }
              }
            }
          }
        }
      }
    }

    // return;
    // PROCESS THE HISTOS AND STORE THEM IN A SUITABLE FILE, STORE NORMALIZATIONS IN A SEPARATE TEXT FILE
    TFile *foutDATA = new TFile(Form("%s/DataCards/datacards_DATA%s.root",folder.Data(),WorZ.Contains("W")?"":"_Wlike"),"RECREATE");
    
    for(int c=0; c<charges; c++){
      ofstream outTXTfile;
      outTXTfile.open(Form("%s/DataCards/datacard_Wmass_Mu%s%s_normalizations.txt",folder.Data(),Wlike.Data(),WCharge_str[c].Data()));
      
      // LOOP OVER MAX-ETA BINS
    
      for(int ieta=0; ieta<WMass::etaMuonNSteps; ieta++){
        TString eta_str = Form("%.1f",WMass::etaMaxMuons[ieta]); eta_str.ReplaceAll(".","p");
        outTXTfile << "-----------------------" << endl;
        outTXTfile << "-----------------------" << endl;
        outTXTfile << "Mu"<<Wlike.Data()<<WCharge_str[c].Data()<< " with |eta| < " << WMass::etaMaxMuons[ieta] << endl;
        outTXTfile << "-----------------------" << endl;
        outTXTfile << "-----------------------" << endl;
        outTXTfile << endl;
        TDirectory *channel_dir = foutDATA->mkdir(Form("Mu%s%s_eta%s",Wlike.Data(),WCharge_str[c].Data(),eta_str.Data()));
        foutDATA->cd(Form("Mu%s%s_eta%s",Wlike.Data(),WCharge_str[c].Data(),eta_str.Data()));
        
        //LOOP OVER w MASS BINS
        for(int jmass=0; jmass<2*WMass::WMassNSteps+1; jmass++){
          // int jWmass = WMass::WMassCentral_MeV-(WMass::WMassNSteps-jmass)*WMass::WMassStep_MeV;
          int jWmass = WorZ.Contains("Z")? WMass::Zmass_values_array[jmass] : WMass::Wmass_values_array[jmass];
          
          double fitrange_Scaling = 1;
          
          cout << "W"<<Wlike.Data()<<WCharge_str[c]<<" eta cut " << WMass::etaMaxMuons[ieta]<< " jWmass= " << jWmass; fflush(stdout);
          TDirectory *mass_dir = channel_dir->mkdir(Form("%d",jWmass));
          mass_dir->cd();

          for(int h=0; h<WMass::PDF_members; h++){
            cout << " PDF " << (WMass::PDF_sets<0?generated_PDF_set:WMass::PDF_sets)<<"-"<<h; fflush(stdout);
            for(int m=0; m<WMass::NtoysMomCorr; m++){
              if(WMass::NtoysMomCorr>1) cout << " MomScale toy " << m; fflush(stdout);
              // gDirectory->pwd();
              outTXTfile << "-----------------------" << endl;
              outTXTfile << "Mass hypothesis  " << jWmass << " PDF " << Form("%d-%d%s",WMass::PDF_sets<0?generated_PDF_set:WMass::PDF_sets,h,WMass::NtoysMomCorr>1?Form(" MomCorrToy%d",m):"") << endl;
              outTXTfile << "-----------------------" << endl;
              outTXTfile << endl;

              TString Z_histoname[2*Nsamples], W_histoname[2*Nsamples];
              TString Z_histoname_NonScaled[2*Nsamples], W_histoname_NonScaled[2*Nsamples];
              double Z_integrals[2*Nsamples], W_integrals[2*Nsamples];
              
              //LOOP OVER THE SAMPLES
              for(int isample=0; isample<Nsamples;isample++){
                for(int k=0;k<3;k++){
                
                  if(!TemplatesW_NonScaled[c][m][h][k][isample][ieta][jmass]) continue;
                
                  // DECLARE NEW HISTOS
                  TH1D*Ztempl,*Wtempl;
                  TH1D*Ztempl_NonScaled, *Wtempl_NonScaled;
                  // To BE CHECKED
                  // W_histoname[isample] = samples_str[isample] == "DATA" ? Form("data_obs_W%s%s_%s",Wlike.Data(),WCharge_str[c].Data(),WMass::FitVar_str[k].Data()) : Form("W%s%s_%s_%s_pdf%d-%d%s",Wlike.Data(),WCharge_str[c].Data(),samples_str[isample].Data(),WMass::FitVar_str[k].Data(),WMass::PDF_sets<0?generated_PDF_set:WMass::PDF_sets,h, WMass::NtoysMomCorr>1?Form("_MomCorrToy%d",m):"");
                  // Wtempl=new TH1D(W_histoname[isample],W_histoname[isample],TemplatesW[c][m][h][k][isample][ieta][jmass]->GetXaxis()->FindBin(xmax*fitrange_Scaling)-TemplatesW[c][m][h][k][isample][ieta][jmass]->GetXaxis()->FindBin(xmin*fitrange_Scaling),xmin*fitrange_Scaling,xmax*fitrange_Scaling);
                  W_histoname_NonScaled[isample] = samples_str[isample] == "DATA" ? Form("data_obs_W%s%s_%sNonScaled",Wlike.Data(),WCharge_str[c].Data(),WMass::FitVar_str[k].Data()) : Form("W%s%s_%s_%sNonScaled_pdf%d-%d%s",Wlike.Data(),WCharge_str[c].Data(),samples_str[isample].Data(),WMass::FitVar_str[k].Data(),WMass::PDF_sets<0?generated_PDF_set:WMass::PDF_sets,h, WMass::NtoysMomCorr>1?Form("_MomCorrToy%d",m):"");
                  // Wtempl_NonScaled=new TH1D(W_histoname_NonScaled[isample],W_histoname_NonScaled[isample],50, WMass::fit_xmin[k],WMass::fit_xmax[k]);
                  Wtempl_NonScaled=(TH1D*)TemplatesW_NonScaled[c][m][h][k][isample][ieta][jmass]->Clone(W_histoname_NonScaled[isample]);
                  Wtempl_NonScaled->SetName(W_histoname_NonScaled[isample]);
                  Wtempl_NonScaled->SetTitle(W_histoname_NonScaled[isample]);
                  
                  int ibin=1;      
                  double z_templ_sign = 1 /* -1 */;
                  int start_bin=1, end_bin=2;
                  
                  // if(TemplatesW_NonScaled[c][m][h][k][isample][ieta][jmass]){
                    // start_bin = TemplatesW_NonScaled[c][m][h][k][isample][ieta][jmass]->GetXaxis()->FindBin(WMass::fit_xmin[k]/* /(WMass::WMassCentral_MeV/1e3) */);
                    // end_bin = TemplatesW_NonScaled[c][m][h][k][isample][ieta][jmass]->GetXaxis()->FindBin(WMass::fit_xmax[k]/* /(WMass::WMassCentral_MeV/1e3) */-1e-10);
                  // }
                  
                  // for(int ibinhisto=start_bin; ibinhisto<end_bin; ibinhisto++){
                    // if(TemplatesW_NonScaled[c][m][h][k][isample][ieta][jmass]){
                      // // Wtempl->SetBinContent(ibin,TemplatesW[c][m][h][k][isample][ieta][jmass]->Integral(ibinhisto,ibinhisto));
                      // Wtempl_NonScaled->SetBinContent(ibin,TemplatesW_NonScaled[c][m][h][k][isample][ieta][jmass]->Integral(ibinhisto,ibinhisto));
                    // }
                    // ibin++;
                  // }

                  // if(!TemplatesW_NonScaled[c][m][h][k][isample][ieta][jmass]){
                    Wtempl_NonScaled->Write();
                  // }
                  
                  // if(!(samples_str[isample].Contains(WorZ.Contains("W")?"WJetsSig":"DYJetsSig") || samples_str[isample].Contains(WorZ.Contains("W")?"DYJetsSig":"WJetsSig") || samples_str[isample].Contains(WorZ.Contains("W")?"DYJetsFake":"WJetsFake") || samples_str[isample].Contains("QCD"))){

                    int nspaces1 = 15 - W_histoname[isample].Length();
                    // outTXTfile << Wtempl->GetName();
                    outTXTfile << Wtempl_NonScaled->GetName();
                    for(int ispace=0;ispace<nspaces1;ispace++) outTXTfile << " ";
                    // W_integrals[isample] = Wtempl->Integral();
                    W_integrals[isample] = Wtempl_NonScaled->Integral();
                    outTXTfile << W_integrals[isample] << endl;
                  // }

                  // if(!TemplatesW_NonScaled[c][m][h][k][isample][ieta][jmass]){
                    // Wtempl->Delete();
                    Wtempl_NonScaled->Delete();
                  // }
                }
              }
              outTXTfile << endl;
              
            }
          }
          cout << endl;
        }
        cout << endl;
        outTXTfile << endl;
        outTXTfile << endl;
      }
      
      
      for(int ieta=0; ieta<WMass::etaMuonNSteps; ieta++){
        TString eta_str = Form("%.1f",WMass::etaMaxMuons[ieta]); eta_str.ReplaceAll(".","p");
        for(int jmass=0; jmass<2*WMass2::WMassNSteps+1; jmass++){
          // int jWmass = WMass2::WMassCentral_MeV-(WMass2::WMassNSteps-jmass)*WMass2::WMassStep_MeV;
          int jWmass = WorZ.Contains("Z")? WMass2::Zmass_values_array[jmass] : WMass2::Wmass_values_array[jmass];
          for(int h=0; h<WMass::PDF_members; h++){
            for(int m=0; m<WMass::NtoysMomCorr; m++){
                
              // // PREPARE DUMMY DATACARD
              TString SigSample_str = "MadSig";
              // PowPlus,  PowNeg,  MadSig,  Pow,  MadSig
              if(SignalSample.Contains("POWHEG")){
                SigSample_str = "Pow";
                  if(WorZ.Contains("W")) SigSample_str+=WCharge_str[c];
              }

              // PREPARE DUMMY DATACARD NON SCALED WITH BACKGROUND WITHOUT Z DATADRIVEN
              for(int k=0;k<3;k++){

                ofstream DummyDatacard;
                DummyDatacard.open(Form("%s/DataCards/dummy_datacard_Wmass_Mu%s%s_pdf%d-%d%s_eta%s_%d_%sNonScaled.txt",folder.Data(),Wlike.Data(),WCharge_str[c].Data(),WMass::PDF_sets<0?generated_PDF_set:WMass::PDF_sets,h, WMass::NtoysMomCorr>1?Form("_MomCorrToy%d",m):"",eta_str.Data(),jWmass,WMass::FitVar_str[k].Data()));
                
                if(syst_folder.Length()<15){
                  DummyDatacard << "shapes   *          *   datacards_DATA"<<(WorZ.Contains("W")?"":"_Wlike")<<".root $CHANNEL/$MASS/$PROCESS $CHANNEL/$MASS/$PROCESS_$SYSTEMATIC" << endl;
                }else{
                  DummyDatacard << "shapes   *          *   "<<Form("../../%s/DataCards/datacards_DATA%s.root",syst_folder.Data(),WorZ.Contains("W")?"":"_Wlike") << " $CHANNEL/$MASS/$PROCESS $CHANNEL/$MASS/$PROCESS_$SYSTEMATIC" << endl;
                }
                
                  // DummyDatacard << "shapes   data_obs   *   datacards_DATA"<<(WorZ.Contains("W")?"":"_Wlike")<<".root $CHANNEL/"<<(WMass2::WMassCentral_MeV)<<Form("/W%s%s_MCDATALIKE%s_%sNonScaled_pdf%d-%d%s",Wlike.Data(),WCharge_str[c].Data(),SignalSample.Contains("POWHEG")?"POW":"MAD",WMass::FitVar_str[k].Data(),WMass::PDF_sets<0?generated_PDF_set:WMass::PDF_sets,h, WMass::NtoysMomCorr>1?Form("_MomCorrToy%d",0):"") << endl;
                  DummyDatacard << "shapes   data_obs   *   datacards_DATA"<<(WorZ.Contains("W")?"":"_Wlike")<<".root $CHANNEL/"<<(WorZ.Contains("W") ? WMass2::WMassCentral_MeV : WMass2::ZMassCentral_MeV)<<Form("/W%s%s_MCDATALIKE%s_%sNonScaled_pdf%d-%d%s",Wlike.Data(),WCharge_str[c].Data(),SignalSample.Contains("POWHEG")?"POW":"MAD",WMass::FitVar_str[k].Data(),WMass::PDF_sets<0?generated_PDF_set:WMass::PDF_sets,h, WMass::NtoysMomCorr>1?Form("_MomCorrToy%d",0):"") << endl;
                
                if(syst_folder.Length()<15){
                  // DummyDatacard << Form("shapes   W%s%s_%sJets%s_%sNonScaled_ALT   *   datacards_DATA%s.root $CHANNEL/",Wlike.Data(),WCharge_str[c].Data(),WorZ.Contains("W")?"W":"DY",SigSample_str.Data(),WMass::FitVar_str[k].Data(),WorZ.Contains("W")?"":"_Wlike")<<(WMass2::WMassCentral_MeV-WMass2::WMassNSteps*WMass2::WMassStep_MeV)<<Form("/W%s%s_%sJets%s_%sNonScaled_pdf%d-%d%s",Wlike.Data(),WCharge_str[c].Data(),WorZ.Contains("W")?"W":"DY",SigSample_str.Data(),WMass::FitVar_str[k].Data(),WMass::PDF_sets<0?generated_PDF_set:WMass::PDF_sets,0, WMass::NtoysMomCorr>1?Form("_MomCorrToy%d",m):"") << endl;
                  DummyDatacard << Form("shapes   W%s%s_%sJets%s_%sNonScaled_ALT   *   datacards_DATA%s.root $CHANNEL/",Wlike.Data(),WCharge_str[c].Data(),WorZ.Contains("W")?"W":"DY",SigSample_str.Data(),WMass::FitVar_str[k].Data(),WorZ.Contains("W")?"":"_Wlike")<<(WorZ.Contains("Z")? WMass::Zmass_values_array[0] : WMass::Wmass_values_array[0])<<Form("/W%s%s_%sJets%s_%sNonScaled_pdf%d-%d%s",Wlike.Data(),WCharge_str[c].Data(),WorZ.Contains("W")?"W":"DY",SigSample_str.Data(),WMass::FitVar_str[k].Data(),WMass::PDF_sets<0?generated_PDF_set:WMass::PDF_sets,0, WMass::NtoysMomCorr>1?Form("_MomCorrToy%d",m):"") << endl;
                }else{
                  // DummyDatacard << Form("shapes   W%s%s_%sJets%s_%sNonScaled_ALT   *   ../../%s/DataCards/datacards_DATA%s.root $CHANNEL/",Wlike.Data(),WCharge_str[c].Data(),WorZ.Contains("W")?"W":"DY",SigSample_str.Data(),WMass::FitVar_str[k].Data(),syst_folder.Data(),WorZ.Contains("W")?"":"_Wlike")<<(WMass2::WMassCentral_MeV-WMass2::WMassNSteps*WMass2::WMassStep_MeV)<<Form("/W%s%s_%sJets%s_%sNonScaled_pdf%d-%d%s",Wlike.Data(),WCharge_str[c].Data(),WorZ.Contains("W")?"W":"DY",SigSample_str.Data(),WMass::FitVar_str[k].Data(),WMass::PDF_sets<0?generated_PDF_set:WMass::PDF_sets,0, WMass::NtoysMomCorr>1?Form("_MomCorrToy%d",m):"") << endl;
                  DummyDatacard << Form("shapes   W%s%s_%sJets%s_%sNonScaled_ALT   *   ../../%s/DataCards/datacards_DATA%s.root $CHANNEL/",Wlike.Data(),WCharge_str[c].Data(),WorZ.Contains("W")?"W":"DY",SigSample_str.Data(),WMass::FitVar_str[k].Data(),syst_folder.Data(),WorZ.Contains("W")?"":"_Wlike")<<(WorZ.Contains("Z")? WMass::Zmass_values_array[0] : WMass::Wmass_values_array[0])<<Form("/W%s%s_%sJets%s_%sNonScaled_pdf%d-%d%s",Wlike.Data(),WCharge_str[c].Data(),WorZ.Contains("W")?"W":"DY",SigSample_str.Data(),WMass::FitVar_str[k].Data(),WMass::PDF_sets<0?generated_PDF_set:WMass::PDF_sets,0, WMass::NtoysMomCorr>1?Form("_MomCorrToy%d",m):"") << endl;
                  
                }
                
                DummyDatacard << "----------------------------------------" << endl;
                DummyDatacard << "bin                 Mu"<<Wlike.Data()<<WCharge_str[c].Data()<<"_eta"<<eta_str<< endl;
                DummyDatacard << "observation              -1 " << endl;
                DummyDatacard << "----------------------------------------" << endl;
                DummyDatacard << "bin            Mu"<<Wlike.Data()<<WCharge_str[c].Data()<<"_eta"<<eta_str<<"          Mu"<<Wlike.Data()<<WCharge_str[c].Data()<<"_eta"<<eta_str<<"         Mu"<<Wlike.Data()<<WCharge_str[c].Data()<<"_eta"<<eta_str<< endl;
                DummyDatacard << Form("process        W%s%s_%sJets%s_%sNonScaled_pdf%d-%d%s        W%s%s_%sJets%s_%sNonScaled_ALT        W%s%s_EWKTT_%sNonScaled_pdf%d-%d%s        ",Wlike.Data(),WCharge_str[c].Data(),WorZ.Contains("W")?"W":"DY",SigSample_str.Data(),WMass::FitVar_str[k].Data(),WMass::PDF_sets<0?generated_PDF_set:WMass::PDF_sets,0, WMass::NtoysMomCorr>1?Form("_MomCorrToy%d",m):"",Wlike.Data(),WCharge_str[c].Data(),WorZ.Contains("W")?"W":"DY",SigSample_str.Data(),WMass::FitVar_str[k].Data(),Wlike.Data(),WCharge_str[c].Data(),WMass::FitVar_str[k].Data(),WMass::PDF_sets<0?generated_PDF_set:WMass::PDF_sets,0, WMass::NtoysMomCorr>1?Form("_MomCorrToy%d",m):"") << endl;   
                DummyDatacard << "process               -1                             0                            1   " << endl;
                DummyDatacard << "rate                 -1                             -1                            -1  " << endl;
                DummyDatacard << "--------------------------------------------------------------------------------" << endl;
                DummyDatacard << "lumi    lnN    1.001    1.001   1.001 " << endl;
                DummyDatacard.close();
              }
                
                
            }
          }
        }
      }
    // }

      outTXTfile.close();
    }
    
    foutDATA->Write();
    foutDATA->Close();
    foutDATA->Delete();
    
    cout << "program ended..." << endl;
    
  }
}




// bin              1     1     1     1
// process         ggH  qqWW  ggWW  others
// process          0     1     2     3
// rate           1.47  0.63  0.06  0.22
// ------------
// # then we list the independent sources of uncertainties, and give their effect (syst. error)
// # on each process and bin
// lumi    lnN    1.11    -   1.11    -    lumi affects both signal and gg->WW (mc-driven). lnN = lognormal
// xs_ggH  lnN    1.16    -     -     -    gg->H cross section double sf_WDATA = signal efficiency double sf_WDATA = other minor ones.
// WW_norm gmN 4    -   0.16    -     -    WW estimate of 0.64 comes from sidebands: 4 events in sideband times 0.16 (=> ~50% statistical uncertainty)
// xs_ggWW lnN      -     -   1.50    -    50% uncertainty on gg->WW cross section
// bg_others lnN    -     -     -   1.30   30% uncertainty on the rest of the backgrounds
