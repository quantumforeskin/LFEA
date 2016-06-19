#include "TROOT.h"
#include "TFrame.h" //gClient
#include "TCanvas.h"
#include "TPad.h"
#include "TSystem.h"
#include <TList.h>
#include "TApplication.h"
#include "TVirtualX.h"
#include "TF1.h"
#include "TGraphErrors.h"
#include "TMultiGraph.h"
#include <cmath>
#include <iostream>
#include "TPaveStats.h"
#include "TStyle.h"
#include "TLegend.h"
#include "TAxis.h"
#include "TH1.h"
#include<fstream>
#include <time.h>
using namespace std;
#include <unistd.h>

int main(int argc, char **argv) {
  //faz aparecer o canvas
  TApplication theApp("App", &argc, argv);
 
  //box com resultados do fit
  gStyle->SetOptFit();
  //settings do canvas  
  TCanvas *c1 = new TCanvas("c1","Nome",200,10,700,500);
  c1->SetFillColor(0);
  c1->SetGrid();
  c1->GetFrame()->SetFillColor(21);
  c1->GetFrame()->SetBorderSize(12);

  string file1="data1.txt";  



  double er=0.000000000001;//erro rate


  /////////////////////////Tirar os dados do file 1 - varrimento 1////////////////////////////
  ifstream file;
  file.open (file1.c_str());

  static int N=0;

  N=0;
  char cur = '\0';
  char last = '\0';

  while (file.get(cur)) {
      if (cur == '\n' ||
          (cur == '\f' && last == '\r')){
         N++;
      }
  }

  //N--;
  
  cout << N << endl;

  double *D = new double[N];
  double *R = new double[N];
  double *eR = new double[N];
  double *eD = new double[N];


  file.close();
  file.open (file1.c_str());

  int i=0;
  int test=0;
  while(!file.eof() && test==0)
    {
      double a=0; //dummy variable para colunas q n interessam
      double b=0; //dummy variable para colunas q n interessam
      file >> a >>  D[i] >> b >> R[i]; // extracts 2 floating point values seperated by whitespace
      eR[i] = er; //erro rate
      eD[i]=0;
       D[i]=((D[i]-1463097600)/3600);
      i++; 


      if(i>=N)
	test=1;

    }

  /*
  TH1F *h1 = new TH1F("h2", "h2", 40, 0, 25);
  h1->SetTitle("Evoluc#tilde{a}o das Contagens");
  h1->GetXaxis()->SetTitle("t (h)");
  h1->GetYaxis()->SetTitle("Counts");
  i=0;
  while( i<N) {
  h1->Fill(D[i]);
  ++i; }
  */
  
  //grafico 1
   TGraphErrors *gr1 = new TGraphErrors(N,D,R,eD,eR);
 gr1->SetTitle("Evoluc#tilde{a}o Rate Eventos  13/05/2016 a 18/05/2016; Tempo(h);Rate(Hz);");
  gr1->SetName("gr1");
  gr1->SetMarkerStyle(20);
  gr1->SetMarkerColor(kBlue);
  gr1->GetXaxis()->SetRangeUser(0,120);
  gr1->GetYaxis()->SetRangeUser(0.015,0.03);
  //por L e comentar o fit e o stat do fit correspondete -> pa desenhar linha a unir pontos
  gr1->SetDrawOption("AP");
  //Com opçao L define a cor da linha que une os pontos, e a cor das barras de erro
  gr1->SetLineColor(1);
  gr1->SetLineWidth(1);
  gr1->SetFillStyle(0);
  //funcao a fittar
   // TF1 *f1 = new TF1("f1", "[1] * x  + [0]");
   // f1->SetLineColor(kBlue);
   // gr1->Fit("f1","EMF");
   
   
  time_t raw=(D[0]-1463011200)*1;
  //time(&raw);
  printf ("The current local time is: %s", ctime (&raw));;

  


  //Draws, prints e updates no canvas
  gr1->Draw("AP");
  //h1->Draw();
  c1->Update();

  //legenda
  // posiçao legenda (x,y) -> primeiro argumento x, ultimo argumento y
  // TLegend *leg = new TLegend(0.1,0.2,0.3,0.1);
  //argumentos add entry 
  //  L: draw line associated with TAttLine if obj inherits from TAttLine
  // P: draw polymarker associated with TAttMarker if obj inherits from TAttMarker
  // F: draw a box with fill associated wit TAttFill if obj inherits TAttFill
  //  E: draw vertical error bar 

   // leg->SetHeader("Legenda");
   // leg->AddEntry("gr1","R= 598 ohm","lep");
   // leg->Draw();

  //box com resultados do fit
  //TPaveStats *stats1 = (TPaveStats*)gr1->GetListOfFunctions()->FindObject("stats");
  //  TPaveStats *stats2 = (TPaveStats*)gr2->GetListOfFunctions()->FindObject("stats");
  //stats1->SetTextColor(kBlue); 
  // stats2->SetTextColor(kRed); 
  // stats1->SetX1NDC(0.7); stats1->SetX2NDC(0.9); stats1->SetY1NDC(0.8);
  // stats2->SetX1NDC(0.52); stats2->SetX2NDC(0.72); stats2->SetY1NDC(0.78);
  c1->Modified();
 

  c1->Print("plot.pdf");
  getchar();
  return 0;
}
