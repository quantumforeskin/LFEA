#include <iostream>
#include <cmath>


#include "TROOT.h"  //Principal
#include "TFrame.h"  //gClient
#include <TAxis.h>
#include<TROOT.h>
#include<TGraphErrors.h>
#include<TMultiGraph.h>
#include<TF1.h>
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

#include "TApplication.h"  //Janela


using namespace std;

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




int main(int argc, char **argv){


  //faz aparecer o canvas
  TApplication theApp("App",&argc, argv);
  theApp.InitializeGraphics();


  double k=0.307075;
  double q=1;
  double ZA = 0.56;
  double me=511;//eV
  double I=78.4;//eV
  double c = 300000000;
  double t;
  double density; // g/(cm3), densidade do plastico do cintilador
  double x_range; // range em cm
  double R; //Range em g/(cm2) 
  double m;//energia em repouso do muao
  double E_R;


  bool stop_time=true;

  double g=k*q*q*ZA*log(2*me/I);

  static int N=2000;

  double *E = new double[N];
  double* st= new double[N];


  for(int i=0;i<N;i++){

  density=1.032; // g/(cm3), densidade do plastico do cintilador
  x_range=(double)(i+1)/2; // range em cm
  R=density*x_range; //Range em g/(cm2) 
  m=105.65837;//energia em repouso do muao
  E_R = R*g/4*(1+sqrt(1+4*m/(R*g)))*(1+sqrt(1+4*m/(R*g)));


//cout << E_R << endl;


  //Stopping time


  double f = sqrt((E_R/m)*(E_R/m)-1);

  t=m/(c*g)*(f + atan(1/f) - M_PI/2);

  E[i]=E_R;
  if(stop_time==false)
    st[i]=R;
  else
    st[i]=t;


  }


  //PARTE DO PEDRO


  //range
  //TF1* func=new TF1("Func","(   1/ (0.307075*0.56*( (log(x/(105.658)*x/(105.658)*2/0.0000784*0.511/(sqrt(1+2*0.511*x/(105.658*105.658)))*          (1-(105.658/x)*(105.658/x))))/((1-(105.68/x)*(105.658/x))) -1)))",110,1000);
 
  //stopping time
  TF1* func=new TF1("Func","(1/(3e8*sqrt(1-(105.658/x)*(105.658/x))))*(   1/ (0.307075*0.56*( (log(x/(105.658)*x/(105.658)*2/0.0000784*0.511/(sqrt(1+2*0.511*x/(105.658*105.658)))*          (1-(105.68/x)*(105.658/x))))/((1-(105.658/x)*(105.658/x))) -1)))",110,1000);
  func->SetLineColor(kBlue);
 

  double a=105.658+1; //muon mass GeV
  double b = 1000; //1 TeV
  int n =200; //divisions must be even
double x [n]; 
double y[n];
  double e[n];
  intTrap(func,n,a,b,x,y,e);

  for (int i=0; i<n;++i) {
    cout << x[i] << " " << y[i] << endl;
  } 
 
  //grafico 1
   



  TCanvas *c1 = new TCanvas("c1","Nome",200,10,700,500);
  c1->SetFillColor(0);
  //c1->SetGrid();
  c1->GetFrame()->SetFillColor(21);
  c1->GetFrame()->SetBorderSize(12);

  TGraph *gr1 = new TGraph(n,x,y);
  gr1->SetName("gr1");
  gr1->SetTitle("graph 1");
  gr1->SetMarkerStyle(5);
  gr1->SetMarkerColor(kBlue);
  //mg->SetMaximum(2e-6);

  gr1->SetLineColor(4);
  gr1->SetLineWidth(2);
  gr1->SetFillStyle(0);


TGraph *gr = new TGraph(N,E,st);

  gr->SetLineColor(2);
  gr->SetLineWidth(2);
  gr->SetFillStyle(0);

 gr->GetXaxis()->SetTitle("E[MeV]");

  TLegend* leg;
  leg = new TLegend(0.65,0.75,0.9,0.9);//(x1,y1,x2,y2)
  leg->AddEntry(gr,"Aproximado","lep");
  leg->AddEntry(gr1,"Calculo numerico","lep");


 if(stop_time==false){
   gr->GetYaxis()->SetTitle("R[g/cm2]");
   gr->SetTitle("Alcance em func#tilde{a}o da energia do mu#tilde{a}o");
 }
  else
   gr->GetYaxis()->SetTitle("t[s]");
   gr->SetTitle("Stopping time em func#tilde{a}o da energia do mu#tilde{a}o");



  gr->Draw("AL");
  //gr1->Draw("same");

  //leg->Draw();


delete [] st;
delete [] E;


  c1->Update();
  c1->Modified();
  if(stop_time==false)
    c1->Print("Range_aprox.pdf");
  else
    c1->Print("Stoppingtime_aprox.pdf");


  theApp.Terminate();



} 
