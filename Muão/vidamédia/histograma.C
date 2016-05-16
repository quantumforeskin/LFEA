
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
}