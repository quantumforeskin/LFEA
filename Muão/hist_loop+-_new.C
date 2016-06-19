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
#include<TGaxis.h>
#include<fstream>


#include "TApplication.h"  //Janela

#include <algorithm>    // std::min_element, std::max_element
#include <cmath>

using namespace std;



int main(int argc, char **argv)
{

  string titulo = "Tempo de vida m#acute{e}dia do mu#tilde{a}o";
  //int nbins=150; //nbins utilizado para o hist.pdf
  //int nbins=630;//Para cada bin ter 0.1 micros  //5000; 
  float low_lim=0;
  float up_lim=63;

  bool optfit=true;
  bool stdfit=true;
  bool subregion=false;//fitar subregiao
  float fit_ul=63;//no standart e isto, se subregion=True e o lim superior da subregion

  TF1 *fit;
  if(stdfit==true){//1.16
    fit = new TF1("myfit","[0]*exp(-x*[1])*(0.55+0.45*exp(-x*0.0379))+[2]", 1.16, fit_ul);
  
    fit->SetParLimits(1,0,3);
    fit->SetParLimits(0,0,10000);
    fit->SetParLimits(2,0,100);
  }


  if(stdfit==false){//1.35 da bue bom!
    fit = new TF1("myfit","[0]*(0.55*exp(-x/[1])+0.45*exp(-x/[2]))+[3]", 1.16, fit_ul);
  
    fit->SetParLimits(1,1,3);
    fit->SetParLimits(2,1,3);
    fit->SetParLimits(0,0,100000);
    fit->SetParLimits(3,0,2200);

  }

  if(subregion==true){
    fit_ul=10;
    fit = new TF1("myfit","[0]*exp(-x/[1])+[2]", 1.16, fit_ul);
    fit->SetParLimits(1,1,10);
    fit->SetParLimits(0,0,50000);
    fit->SetParLimits(2,0,2200);
  }
  

  if(optfit==true)
    gStyle->SetOptFit();

  //gROOT->SetBatch(kTRUE);


  static int Ngraphs=1; //Nº de graficos que quero

  //COISAS A PREENCHER PARA CADA ANALISE!!!////////////////////////
  string plot_label[Ngraphs]; //Nome do ficheiro em que e feito o plot MR(H)
  plot_label[0] = "hist_loop+-_new.pdf"; 


  string file1[Ngraphs]; //directoria dos dados para plotar
  file1[0]="new.txt";  


  /////////////////////////Tirar os dados do file 1 - varrimento 1////////////////////////////
  ifstream file;
  file.open (file1[0].c_str());

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


  double *X = new double[N];
  double *delta = new double[N];


  file.close();
  file.open (file1[0].c_str());

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










  int nbins=100;
  static int Nit=200;
  double bins[Nit];
  double param[Nit];
  double param2[Nit];
  double chi[Nit];


  TH1F *hist;

  for(int j=0;j<Nit;j++){

  hist = new TH1F("Par#hat{a}metros estat#acute{i}sticos e do ajuste",titulo.c_str(),nbins,low_lim,up_lim);

  for(int i=0;i<N;i++){

    hist->Fill(X[i]);

  }


  if(optfit==true)
    hist->Fit("myfit","R");//,"",0,10);

  bins[j]=nbins;
  param[j]=fit->GetParameter(1);
  param2[j]=fit->GetParameter(2);
  chi[j] =fit->GetChisquare()/fit->GetNDF();


  //bins[i]=nbins;
  //param[i]=fit->GetParameter(1);

  cout << nbins << endl;

  nbins+=1;

  //cout << fit->GetParameter(1) << endl;


  }

  int count1=0;
  int count2=0;
  double media=0;
  double media2=0;
  double lim=0.05;
  for(int j=34;j<66;j++){

    if(param[j]<param[j+1]+lim && param[j]>param[j+1]-lim){
      media+=param[j];
      count1++;
    }


    if(param2[j]<param2[j+1]+lim && param2[j]>param2[j+1]-lim){
      media2+=param2[j];
      count2++;
    }


  }

  media=media/count1;
  media2=media2/count2;


  cout << "media p1 " << media << endl;
  cout << "media p2 " << media2 << endl;
  cout << count1 << endl;
  cout << count2 << endl;






  //faz aparecer o canvas
  TApplication theApp("App",&argc, argv);
  theApp.InitializeGraphics();


  TCanvas *c1 = new TCanvas("c1","Nome",200,10,700,500);
  c1->SetFillColor(0);
  c1->SetGrid();
  c1->GetFrame()->SetFillColor(21);
  c1->GetFrame()->SetBorderSize(12);


  TGraph * gr = new TGraph(Nit,bins,param);
  gr->SetMinimum(0);
  gr->SetMaximum(6);
  gr->Draw("AC");
  gr->SetLineColor(4);
  gr->SetTitle("Variac#tilde{a}o do #chi^{2}/ndf e #tau com o n#circ de bins");

  TGraph * gr2 = new TGraph(Nit,bins,param2);
  gr2->Draw("same");
  gr2->SetLineColor(8);

  TGraph * gr3 = new TGraph(Nit,bins,chi);
  gr3->Draw("same");
  gr3->SetLineColor(2);



  double nn[1];
  double tt[1];
  nn[0]=9200;
  tt[0]=2.272;
  TGraph * gr4 = new TGraph(1,nn,tt);
  gr4->Draw("same,*");
  gr4->SetLineColor(6);

  TLegend* leg;
  leg = new TLegend(0.65,0.75,0.9,0.9);//(x1,y1,x2,y2)
  leg->AddEntry(gr,"#tau+ (#mu s)","lep");
  leg->AddEntry(gr2,"#tau- (#mu s)","lep");
  leg->AddEntry(gr3,"#chi^{2}/ndf","lep");
  //leg->AddEntry(gr4,"n#circ bins escolhido","ep");

  leg->Draw();

  gr->GetYaxis()->SetTitle("t (#mu s) / #frac{#chi^{2}}{ndf}");
  gr->GetXaxis()->SetTitle("n#circ bins");
  //gr->GetYaxis()->SetTitleOffset(1.2);



  c1->Update();
  c1->Modified();
  c1->Print(plot_label[0].c_str());

  getchar();



  file.close();
  delete [] X;
  delete [] delta;


  theApp.Terminate();
  return 0;  
}
