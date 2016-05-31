
#include <TH1F.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "uLRCtreeACQ.h"
#include <TMath.h>
#include <TChain.h>
#include <TF1.h>
#include <iostream>

ClassImp(uLRCtreeACQ);

///////////////////////////////////////////////////////////////////////////////////////////////////

uLRCtreeACQ::uLRCtreeACQ(string filename, string treename) : fChain(0) {
  TTree* tree;
  TFile *f = new TFile(filename.c_str(), "READ");
  if (!f || !f->IsOpen()) {
    std::cout << Form("[uLRCtreeACQ::uLRCtreeACQ] User tried to open %s but file doesn't seem to exist.", filename.c_str()) << std::endl;
  } else if (treename == "") {
    f->GetObject("LRCTree",tree);
    Init(tree);
  } else { 
    f->GetObject(treename.c_str(),tree);
    Init(tree);
  }

  ph = new TH1F*[6];

  for (int n=0; n<6; n++) {
    ph[n] =  new TH1F(Form("LIPPAD-%d",n), Form("LIPPAD channel %d",n), 256, 0., 256.);
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////

uLRCtreeACQ::~uLRCtreeACQ() {
  if (!fChain) return;
  delete fChain->GetCurrentFile();
  delete[] ph;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void uLRCtreeACQ::Init(TTree *tree) {
  if (!tree) return;
  fChain = tree;
  fCurrent = -1;
  fChain->SetMakeClass(1);

  fChain->SetBranchAddress("fUniqueID", &fUniqueID, &b_LRCevent_fUniqueID);
  fChain->SetBranchAddress("fBits", &fBits, &b_LRCevent_fBits);
  fChain->SetBranchAddress("EventSize", &EventSize, &b_LRCevent_EventSize);
  fChain->SetBranchAddress("RunNumber", &RunNumber, &b_LRCevent_RunNumber);
  fChain->SetBranchAddress("EventNumber", &EventNumber, &b_LRCevent_EventNumber);
  fChain->SetBranchAddress("EventType", &EventType, &b_LRCevent_EventType);
  fChain->SetBranchAddress("CrateNumber", &CrateNumber, &b_LRCevent_CrateNumber);
  fChain->SetBranchAddress("ModuleId", &ModuleId, &b_LRCevent_ModuleId);
  fChain->SetBranchAddress("EvTime_sec", &EvTime_sec, &b_LRCevent_EvTime_sec);
  fChain->SetBranchAddress("EvTime_usec", &EvTime_usec, &b_LRCevent_EvTime_usec);
  fChain->SetBranchAddress("EventTag", &EventTag, &b_LRCevent_EventTag);
  fChain->SetBranchAddress("ModuleEvent", &ModuleEvent, &b_LRCevent_ModuleEvent);
  Notify();
}

///////////////////////////////////////////////////////////////////////////////////////////////////

Bool_t uLRCtreeACQ::Notify() {
  return kTRUE;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void uLRCtreeACQ::Show(Long64_t entry) {
  if (!fChain) return;
  fChain->Show(entry);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

Int_t uLRCtreeACQ::Cut(Long64_t entry) {
  entry = 0;
  return 1;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

void uLRCtreeACQ::Loop() {
  if (fChain == 0) return;

  Long64_t nentries = fChain->GetEntriesFast();
  Long64_t nbytes = 0, nb = 0;

  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////

Int_t uLRCtreeACQ::GetEntry(Long64_t entry) {
  // Read contents of entry.
  if (!fChain) return 0;
  return fChain->GetEntry(entry);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

Long64_t uLRCtreeACQ::LoadTree(Long64_t entry) {
  // Set the environment to read one entry
  if (!fChain) return -5;
  Long64_t centry = fChain->LoadTree(entry);
  if (centry < 0) return centry;
  if (fChain->GetTreeNumber() != fCurrent) {
    fCurrent = fChain->GetTreeNumber();
    Notify();
  }
  return centry;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<int> uLRCtreeACQ::GetChannel(int evt, int n) {
  int ip = 256*n; // 256 words per channel
  vector<int> c;
  if (evt < 0 || evt > GetNEvents()) return c;
  for (int i=ip; i<ip+256; i++) {
    c.push_back((int)ModuleEvent[i]);
  }
  return c;
}

//////////////////////////////////////////////////////////////////////////////////////////////////

TH1F** uLRCtreeACQ::GetAllChannels(int evt) {
  if (evt < 0 || evt > GetNEvents()) return 0;
  LIPPAD_WORD w;
  for (int n=0; n<6; n++) {
     int ip = 256*n; // 256 words per channel
     for (int i=0; i<256; i++) {
       w.word32=ModuleEvent[ip+i];
       int adc = (int)w.bit_field.adc_value;
       ph[n]->SetBinContent(i+1,adc);
     }
   }
   return ph;
 }
