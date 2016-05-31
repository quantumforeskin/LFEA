#include "uLRCtreeSIM.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TString.h>
#include <iostream>

////////////////////////////////////////////////////////////////////////////////
uLRCtreeSIM::uLRCtreeSIM(TString treename) : fChain(0) {
  TTree* tree;
  TFile *f = new TFile(treename.Data(), "READ");
  if (!f || !f->IsOpen()) {
    std::cout << Form("[uLRCtreeSIM::uLRCtreeSIM] User tried to open %s but file doesn't seem to exist.", treename.Data()) << std::endl;
  } else {
    f->GetObject("tLRCsim",tree);
    Init(tree);
  }
}

////////////////////////////////////////////////////////////////////////////////
void uLRCtreeSIM::Init(TTree *tree) {
  if (!tree) return;
  fChain = tree;
  fCurrent = -1;
  fChain->SetMakeClass(1);

  fChain->SetBranchAddress("fUniqueID", &fUniqueID, &b_SimEvent_fUniqueID);
  fChain->SetBranchAddress("fBits", &fBits, &b_SimEvent_fBits);
  fChain->SetBranchAddress("pid", &pid, &b_SimEvent_pid);
  fChain->SetBranchAddress("x_imp", &x_imp, &b_SimEvent_x_imp);
  fChain->SetBranchAddress("y_imp", &y_imp, &b_SimEvent_y_imp);
  fChain->SetBranchAddress("energy", &energy, &b_SimEvent_energy);
  fChain->SetBranchAddress("nsci", &nsci, &b_SimEvent_nsci);
  fChain->SetBranchAddress("ndet", &ndet, &b_SimEvent_ndet);
  fChain->SetBranchAddress("vphotons", &vphotons_, &b_SimEvent_vphotons_);
  fChain->SetBranchAddress("vphotons.fUniqueID", vphotons_fUniqueID, &b_vphotons_fUniqueID);
  fChain->SetBranchAddress("vphotons.fBits", vphotons_fBits, &b_vphotons_fBits);
  fChain->SetBranchAddress("vphotons.x_i", vphotons_x_i, &b_vphotons_x_i);
  fChain->SetBranchAddress("vphotons.y_i", vphotons_y_i, &b_vphotons_y_i);
  fChain->SetBranchAddress("vphotons.x_f", vphotons_x_f, &b_vphotons_x_f);
  fChain->SetBranchAddress("vphotons.y_f", vphotons_y_f, &b_vphotons_y_f);
  fChain->SetBranchAddress("vphotons.length", vphotons_length, &b_vphotons_length);
  fChain->SetBranchAddress("vphotons.lambda", vphotons_lambda, &b_vphotons_lambda);
  fChain->SetBranchAddress("vphotons.is_detected", vphotons_is_detected, &b_vphotons_is_detected);
  fChain->SetBranchAddress("vphotons.is_sci_abs", vphotons_is_sci_abs, &b_vphotons_is_sci_abs);
  fChain->SetBranchAddress("vphotons.is_alu_abs", vphotons_is_alu_abs, &b_vphotons_is_alu_abs);
  fChain->SetBranchAddress("vphotons.nrefl", vphotons_nrefl, &b_vphotons_nrefl);
  fChain->SetBranchAddress("vphotons.nalurefl", vphotons_nalurefl, &b_vphotons_nalurefl);
  Notify();
}

////////////////////////////////////////////////////////////////////////////////
uLRCtreeSIM::~uLRCtreeSIM() {
  if (!fChain) return;
  delete fChain->GetCurrentFile();
}

////////////////////////////////////////////////////////////////////////////////
void uLRCtreeSIM::Loop() {
  if (fChain == 0) return;
  Long64_t nentries = fChain->GetEntriesFast();
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
  }
}

////////////////////////////////////////////////////////////////////////////////
Int_t uLRCtreeSIM::GetEntry(Long64_t entry) {
  // Read contents of entry.
  if (!fChain) return 0;
  return fChain->GetEntry(entry);
}

////////////////////////////////////////////////////////////////////////////////
Long64_t uLRCtreeSIM::LoadTree(Long64_t entry) {
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

////////////////////////////////////////////////////////////////////////////////
Bool_t uLRCtreeSIM::Notify() {
  return kTRUE;
}

////////////////////////////////////////////////////////////////////////////////
void uLRCtreeSIM::Show(Long64_t entry) {
  if (!fChain) return;
  fChain->Show(entry);
}

////////////////////////////////////////////////////////////////////////////////
Int_t uLRCtreeSIM::Cut(Long64_t entry) {
  entry = 0;
  return 1;
}
