#include "TROOT.h"  //Principal
#include "TFrame.h"  //gClient
#include <TAxis.h>
#include<TROOT.h>
#include<TGraphErrors.h>
#include<TMultiGraph.h>
#include<TF1.h>
#include<TH1F.h>
#include<TGraph.h>
#include<TCanvas.h>
#include<TPad.h>
#include<iostream>
#include<iomanip>
#include<TLine.h>
#include<TLatex.h>
#include<TArrow.h>
#include<TLegend.h>
#include<TText.h>
#include<TPaveText.h>
#include<TStyle.h>
#include<fstream>


#include "TApplication.h"  //Janela

#include <algorithm>    // std::min_element, std::max_element
#include <cmath>

using namespace std;



int main(int argc, char **argv)
{

  string titulo = "histograma";
  //int nbins=350; nbins utilizado para o hist.pdf
  int nbins=5000;
  float low_lim=0;
  float up_lim=64;

  bool optfit=true;

  //TF1 *fit = new TF1("myfit","[0]*(0.56*exp(-x/[1])+0.44*exp(-x/[2]))+[3]", 2, 9);
  
  //fit->SetParLimits(1,1,3);
  //fit->SetParLimits(2,1,3);
  //fit->SetParLimits(0,0,10000);
  //fit->SetParLimits(3,0,2000);
  
  TF1 *fit = new TF1("myfit","[0]*exp(-x/[1])+[2]", 1.8, 9);
  fit->SetParLimits(1,1,3);
  fit->SetParLimits(0,0,2000);
  fit->SetParLimits(2,0,2000);

  if(optfit==true)
    gStyle->SetOptFit();

  //gROOT->SetBatch(kTRUE);

  //faz aparecer o canvas
  TApplication theApp("App",&argc, argv);
  theApp.InitializeGraphics();


  static int Ngraphs=1; //Nº de graficos que quero

  //COISAS A PREENCHER PARA CADA ANALISE!!!////////////////////////
  string plot_label[Ngraphs]; //Nome do ficheiro em que e feito o plot MR(H)
  plot_label[0] = "hist_latest.pdf"; 


  string file1[Ngraphs]; //directoria dos dados para plotar
  file1[0]="dados_last.txt";  


  for(int j=0;j<Ngraphs;j++){

  /////////////////////////Tirar os dados do file 1 - varrimento 1////////////////////////////
  ifstream file;
  file.open (file1[j].c_str());

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

  double *X = new double[N];


  file.close();
  file.open (file1[j].c_str());

  int i=0;
  int test=0;
  while(!file.eof() && test==0)
    {

      file >> X[i]; // extracts 2 floating point values seperated by whitespace
      X[i]=X[i]/1000;
      i++; 


      if(i>=N)
	test=1;

    }


  TH1F *hist = new TH1F("hist",titulo.c_str(),nbins,low_lim,up_lim);

  for(int i=0;i<N;i++){

    hist->Fill(X[i]);

  }

  if(optfit==true)
    hist->Fit("myfit","R");//,"",0,10);

  TCanvas *c1 = new TCanvas("c1","Nome",200,10,700,500);
  c1->SetFillColor(0);
  //c1->SetGrid();
  c1->GetFrame()->SetFillColor(21);
  c1->GetFrame()->SetBorderSize(12);


  //Legenda///////////////////////////

  //TLegend* leg;
  //leg = new TLegend(0.1,0.8,0.2,0.9);//(x1,y1,x2,y2)
  
  //leg->SetHeader("Orientac#tilde{o}es");
  //leg->AddEntry(MR_H,"#rightarrow","lep");
  //leg->AddEntry(MR_H2,"#leftarrow","lep");



  file.close();
  delete [] X;

  hist->Draw();
  if(optfit==true)
    fit->Draw("same");

  hist->GetXaxis()->SetTitle("t");
  hist->GetYaxis()->SetTitle("N");
  hist->GetYaxis()->SetTitleOffset(1.2);

  

  //legenda
  //leg->Draw();
  

  c1->Update();
  c1->Modified();
  c1->Print(plot_label[j].c_str());

  getchar();
  //getchar();

  }

  theApp.Terminate();
  return 0;  
}
