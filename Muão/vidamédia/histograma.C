
void histograma(){

  double n1=0;


  TH1F* hist=new TH1F("h1", "Histogram muon decay", 100, 0, 64);



  ifstream file("delta_t.txt", std::ios::in);
  if(file.is_open())
   {

      while(!file.eof()){
	file >> n1;

  hist->Fill(n1);   


      }

    }

   hist->Draw();

   f1 = ROOT.TF1("f1", "[0]*TMath::Power(([1]/[2]),(x/[2]))*(TMath::Exp( ([1]/[2])))/TMath::Gamma((x/[2])+1)", 0, 5);
   f1.SetParameters(1, 1, 1);
        hist.Fit('f1', 'R');
        fit = hist.GetFunction('f1');
        fit.Draw('same');
}