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


  double g=k*q*q*ZA*log(2*me/I);

  static int N=200;

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
  st[i]=t;


  cout << E_R << "              " << t << endl;
  //cout << E_R << endl << t << endl;

  //cout << t << endl;
  }

  TCanvas *c1 = new TCanvas("c1","Nome",200,10,700,500);
  c1->SetFillColor(0);
  //c1->SetGrid();
  c1->GetFrame()->SetFillColor(21);
  c1->GetFrame()->SetBorderSize(12);

TGraph *gr = new TGraph(N,E,st);

gr->Draw("AL");


delete [] st;
delete [] E;


  c1->Update();
  c1->Modified();
  c1->Print("Range_aprox.pdf");


  theApp.Terminate();



} 
