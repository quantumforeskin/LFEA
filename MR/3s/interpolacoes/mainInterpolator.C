#include"DataInterpolator.h"
#include"cFCgraphics.h"
#include<TROOT.h>
#include<TGraphErrors.h>
#include<TF1.h>
#include<TGraph.h>
#include<TCanvas.h>
#include<TPad.h>
#include<iostream>
#include<iomanip>
#include<TLine.h>
#include<TLatex.h>
#include<fstream>

#include <algorithm>    // std::min_element, std::max_element


using namespace std;


int main()
{


  double I=0.0010094;//corrente
  double eI=0.0000001;//erro corrente
  double eV = 0.000001; //erro tensao
  double eh = 0.0001;//erro campo VALOR ESTA MAL TEMOS DE ESTIMA-LO DEPOIS
 

  TF1 *cubic;
  TGraph *g;
  double *K;


  ifstream file;
  file.open ("../data/SV4_B_50_2a.txt");

  static int N=0;

  
  char cur = '\0';
  char last = '\0';

  while (file.get(cur)) {
      if (cur == '\n' ||
          (cur == '\f' && last == '\r'))
         N++;
  }

  N--;
  
  cout << N << endl;

  double *H = new double[N];
  double *R = new double[N];


  file.close();
  file.open ("../data/SV4_B_50_2a.txt");

  int i=0;
  while(!file.eof())
    {
      file >> H[i] >> R[i]; // extracts 2 floating point values seperated by whitespace
      R[i]=R[i]/I; //PASSAR TENSOES PARA RESISTENCIAS
      i++;
      // do something with them
    }

  DataInterpolator Test(N,H,R);
  cout<<"Pontos de Data"<<endl;


  for(int i=0;i<N;i++)
    cout<<H[i]<<" "<<R[i]<<endl;

  
  //cubic=Test.DataInterpolator::CubicSpline(K);
  //cubic->SetLineWidth(2);
  //cubic->SetLineColor(kRed);
  //cubic->SetTitle("Cubic Spline and Polynomial Interpolation");

  g=Test.Draw(N);
  g->SetMarkerStyle(31);
  g->SetTitle("Data Points");
  

  
  
  //Rp e Rap

  double Rp = *std::min_element(R,R+N);
  double Rap = *std::max_element(R,R+N);

  // Grafico MR(H) com os respectivos erros

  

  double *MR = new double[N];
  double *eH = new double[N];
  double *eMR = new double[N];
  for(int i=0;i<N;i++){

    double eR = eV/I + R[i]/I*eI; //erro resistencia
    double e_mr= eR/Rp + R[i]/(Rp*Rp)*eR; //erro magneto-resistencia

    eH[i]=eh; //dado no inicio do prog
    eMR[i]=e_mr;
    MR[i]=(R[i]-Rp)/Rp;

  }
  

  TGraphErrors *MR_H = new TGraphErrors(N,H,MR,eH,eMR);

  ////Encontrar Hc
  TF1 *f1= new TF1("f1","[0]+[1]*x");
  MR_H->Fit("f1","MF","",-5,18);

  R_half = (Rap-Rp)/2;
  b=f1->GetParameter(0);
  a=f1->GetParameter(1);
  dH1=(R_half-b)/a;

  
  
  cFCgraphics br;//criar um objecto cFCgraphics

  //br.AddObject(cubic);
  br.AddObject(MR_H);
  //br.AddObject(fg);
  br.Draw("all"); //draw canvas
  

  file.close();
  delete  g;
  //delete gr1; // A classe do prof deve fazer delete aos objectos, quando descomento da segmentation violation
  //delete  cubic;
  delete [] R;
  delete [] H;
  //delete [] MR;
  //delete [] eH;
  //delete [] eMR;

  return 0;  
}
