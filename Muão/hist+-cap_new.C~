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

  ///////Neste momento o limite inferior do fit esta em 1.35 porque e o q da melhor, mas o grafico q ta no relatorio e para 1.16!!!!!


  string titulo = "Tempo de vida m#acute{e}dia - mu#tilde{o}es + e -";
  //int nbins=350; nbins utilizado para o hist.pdf
  int nbins=1500;
  float low_lim=0;
  float up_lim=63;

  bool optfit=true;
  bool stdfit=false;
  bool subregion=false;//fitar subregiao
  float fit_ul=63;//no standart e isto, se subregion=True e o lim superior da subregion

  static int Ngraphs=1; //Nº de graficos que quero
  string plot_label[Ngraphs]; //Nome do ficheiro em que e feito o plot MR(H)

  TF1 *fit;
  if(stdfit==true){//1.16
    fit = new TF1("myfit","[0]*exp(-x/[1])+[2]", 1.16, 63);
    fit->SetParLimits(1,1,3);
    fit->SetParLimits(0,0,50000);
    fit->SetParLimits(2,0,2200);

    //COISAS A PREENCHER PARA CADA ANALISE!!!////////////////////////

    plot_label[0] = "hist_std.pdf"; 
  }


  if(stdfit==false){
    fit = new TF1("myfit","[0]*exp(-x*[1])*(0.55+0.45*exp(-x*0.0379))+[2]", 1.16, fit_ul);
  
    fit->SetParLimits(1,0.1,3);
    fit->SetParLimits(0,0,100000);
    fit->SetParLimits(2,0,2200);

    plot_label[0] = "hist_+-cap.pdf"; 

  }

  if(subregion==true){
    fit_ul=10;
    fit = new TF1("myfit","[0]*exp(-x/[1])+[2]", 1.16, fit_ul);
    fit->SetParLimits(1,1,3);
    fit->SetParLimits(0,0,50000);
    fit->SetParLimits(2,0,2200);

    plot_label[0] = "hist_std_sub.pdf"; 
  }
  

  if(optfit==true)
    gStyle->SetOptFit();

  //gROOT->SetBatch(kTRUE);

  //faz aparecer o canvas
  TApplication theApp("App",&argc, argv);
  theApp.InitializeGraphics();



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
  double *delta = new double[N];


  file.close();
  file.open (file1[j].c_str());

  int i=0;
  int test=0;
  while(!file.eof() && test==0)
    {

      file >> X[i] >> delta[i]; // extracts 2 floating point values seperated by whitespace
      X[i]=(X[i]-delta[i])/1000;
      i++; 


      if(i>=N)
	test=1;

    }


  TH1F *hist = new TH1F("Par#hat{a}metros estat#acute{i}sticos e do ajuste",titulo.c_str(),nbins,low_lim,up_lim);

  for(int i=0;i<N;i++){

    hist->Fill(X[i]);

  }

  for(int i=0;i<200;i++)
    cout << 63./1500.*i << "  " << hist->GetBinContent(i) << endl;

  if(optfit==true)
    hist->Fit("myfit","R");//,"",0,10);

  TCanvas *c1 = new TCanvas("c1","Nome",200,10,700,500);
  c1->SetFillColor(0);
  //c1->SetGrid();
  c1->GetFrame()->SetFillColor(21);
  c1->GetFrame()->SetBorderSize(12);

  c1->SetLogy();


  //Legenda///////////////////////////

  //TLegend* leg;
  //leg = new TLegend(0.1,0.8,0.2,0.9);//(x1,y1,x2,y2)
  
  //leg->SetHeader("Orientac#tilde{o}es");
  //leg->AddEntry(MR_H,"#rightarrow","lep");
  //leg->AddEntry(MR_H2,"#leftarrow","lep");



  file.close();
  delete [] X;
  delete [] delta;

  hist->Draw();
  hist->SetMinimum(90);
  //hist->SetMaximum(10000);
  hist->SetTitleOffset(15);
  gStyle->SetTitleY(1.01);
  if(optfit==true){
    fit->Draw("same");
    TF1* fit2;
    if(stdfit==true)
      fit2 = new TF1("fit2","[0]*exp(-x/[1])+[2]", 0, fit_ul);
    else
    fit2 = new TF1("myfit","[0]*exp(-x*[1])*(0.55+0.45*exp(-x*0.0376))+[2]", 0, fit_ul);
    fit2->SetParameter(0,fit->GetParameter(0));
    fit2->SetParameter(1,fit->GetParameter(1));
    fit2->SetParameter(2,fit->GetParameter(2));
    fit2->Draw("same");
    }

  hist->GetXaxis()->SetTitle("t (#mu s)");
  hist->GetYaxis()->SetTitle("N (conts)");
  hist->GetYaxis()->SetTitleOffset(1.2);
  hist->GetXaxis()->SetTitleOffset(1);

  

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
