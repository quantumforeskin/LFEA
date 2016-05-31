void mTreeACQExample() {
  uLRCtreeACQ* tree_ana = new uLRCtreeACQ("/RAID5/LabRC/DATA/Scintillator.root");

  tree_ana->GetEntry(5);
  tree_ana->Show();
  tree_ana->Show(10);
}
