void mTreeSimExample() {
  uLRCtreeSIM* tree_ana = new uLRCtreeSIM("/RAID5/LabRC/EXPsci.simulations/Scintillator_simulation.root");

  tree_ana->GetEntry(5);
  tree_ana->Show();
  tree_ana->Show(10);
}
