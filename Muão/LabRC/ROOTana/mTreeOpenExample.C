void mTreeOpenExample() {
  TFile* file = new TFile("/RAID5/LabRC/EXPsci.simulations/Scintillator_simulation.root");
  TTree* tree = dynamic_cast<TTree*> (file->Get("tLRCsim"));

  if (tree) {
    std::cout << Form("[mTreeOpenExample] Tree found with %lld events.", tree->GetEntries()) << std::endl;
  }
}
