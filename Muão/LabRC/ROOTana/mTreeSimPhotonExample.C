void mTreeSimPhotonExample() {
  uLRCtreeSIM* tree_ana = new uLRCtreeSIM("/RAID5/LabRC/EXPsci.simulations/Scintillator_simulation.root");

  TH1D* hlength = new TH1D("hlength", "hlength", 1000, 0., 5000.);

  Long64_t N = tree_ana->fChain->GetEntries();
  for (Long64_t i = 0; i < 10; i++) {
    tree_ana->GetEntry(i);
    int nphot = tree_ana->vphotons_;

    for (int j = 0; j < nphot; j++) {
      double length = tree_ana->vphotons_length[j];
      hlength->Fill(length, 1.);
    }
  }

  TCanvas *c = new TCanvas("c", "c", 1200, 800);
  c->SetLogx();
  hlength->Draw();
}
