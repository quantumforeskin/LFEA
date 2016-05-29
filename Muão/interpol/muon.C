#include<fstream>
#include "TROOT.h"
#include "TFrame.h" //gClient
#include "TCanvas.h"
#include "TPad.h"
#include "TSystem.h"
#include <TList.h>
#include "TApplication.h"
#include "TVirtualX.h"
#include "TF1.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include <cmath>
#include <iostream>
#include "TPaveStats.h"
#include "TStyle.h"
#include "TLegend.h"
#include "TAxis.h"
#include "TH1F.h"
#include "TLatex.h"
using namespace std;
#include <unistd.h>
#include<fstream>

  void intSimpson(TF1 *f, int n,double a, double b, double *x, double*y, double *e){
    x[0]=a;
    double M,m;
    double h=(b-a)/n;//  Width of each slice
    for(int i=0;i<n;++i){
      M+=2*h*f->GetMaximum(x[i],x[i]+2*h);
      m+=2*h*f->GetMinimum(x[i],x[i]+2*h);
      if( i==0){
      y[i]=h/3*(f->Eval(x[i])+4*f->Eval(x[i]+h)+f->Eval(x[i]+2*h));
      x[i+1]=x[0]+h;
      }
   
      if(i!=0){
      y[i]=y[i-1]+h/3*(f->Eval(x[i])+4*f->Eval(x[i]+h)+f->Eval(x[i]+2*h));
      x[i]=x[i-1]+h; 
      cout << x[i] << "p " << y[i] << endl;
}
      e[i]=(M-m)/2;//  Integral error
    }
  }



void intTrap(TF1 *f, int n, double a, double b, double *x, double *y,double *e){
  double h=(b-a)/n;
  for(int i=0;i<n;++i){
    if (i==0)
    y[i]=h/2*(f->Eval(a+i*h)+f->Eval(a+(i+1)*h));
    else
    y[i]=y[i-1]+h/2*(f->Eval(a+i*h)+f->Eval(a+(i+1)*h));
    x[i]=a+h*(i+1);
  e[i]=(b-a)*(b-a)/12/n/n*fabs(f->Derivative(b)-f->Derivative(a));
  }
}







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

  //Definir multiplos graficos num canvas
  TMultiGraph *mg = new TMultiGraph("mg","mg");
  mg->SetTitle("Stopping Time;#Energy(MeV);time(s)");
 
  //range
  TF1* func=new TF1("Func","(   1/ (0.307075*0.56*( (log(2/0.0000784*0.511/(sqrt(1+2*0.511*x/(105.658*105.658)))*          (1-(105.68/x)*(105.658/x))))/((1-(105.68/x)*(105.658/x))) -1)))",110,1000);
 
  //stopping time
  //TF1* func=new TF1("Func","(1/(3e8*sqrt(1-(105.658/x)*(105.658/x))))*(   1/ (0.307075*0.56*( (log(2/0.0000784*0.511/(sqrt(1+2*0.511*x/(105.658*105.658)))*          (1-(105.68/x)*(105.658/x))))/((1-(105.68/x)*(105.658/x))) -1)))",110,1000);
  func->SetLineColor(kBlue);
 

  double a=105.658+1; //muon mass GeV
  double b = 1000; //1 TeV
  int n =200; //divisions must be even
double x [n]; 
double y[n];
  double e[n];
  intTrap(func,n,a,b,x,y,e);


  ofstream file;

  file.open("range.txt");


  for (int i=0; i<n;++i) {
    cout << x[i] << " " << y[i] << endl;
    file << x[i]  << " " << y[i] << "\n";
  } 
 

  file.close();
  //grafico 1
   
  TGraph *gr1 = new TGraph(n,x,y);
  gr1->SetName("gr1");
  gr1->SetTitle("graph 1");
  gr1->SetMarkerStyle(5);
  gr1->SetMarkerColor(kBlue);
  mg->SetMaximum(2e-6);

  //por L e comentar o fit e o stat do fit correspondete -> pa desenhar linha a unir pontos
  gr1->SetDrawOption("ALP");
  //Com opçao L define a cor da linha que une os pontos, e a cor das barras de erro
  gr1->SetLineColor(1);
  gr1->SetLineWidth(2);
  gr1->SetFillStyle(0);
  //funcao a fittar
  // TF1 *f1 = new TF1("f1", "[1] * x  + [0]");
  // f1->SetLineColor(kBlue);
  // gr1->Fit("f1","EMF");
  mg->Add(gr1);

  mg->Draw("AP");

 
  //func->Draw("AP");
   
  c1->Update();

  c1->Modified();
 

  c1->Print("plot.pdf");
  getchar();
return 0;

  }
