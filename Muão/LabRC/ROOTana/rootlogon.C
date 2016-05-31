void rootlogon() {
  gInterpreter->AddIncludePath("/RAID5/LabRC/Libraries");
  gInterpreter->AddIncludePath("/RAID5/LabRC/Libraries/LRCacqCode");
  gSystem->CompileMacro("/RAID5/LabRC/Libraries/uLRCtreeSIM.C");
  gSystem->CompileMacro("/RAID5/LabRC/Libraries/uLRCtreeACQ.C");
  gSystem->Load("/RAID5/LabRC/Libraries/libLFEA.so");
}
