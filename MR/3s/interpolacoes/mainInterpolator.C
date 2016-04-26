#include "TROOT.h"  //Principal
#include "TFrame.h"  //gClient
#include"DataInterpolator.h"
#include <TAxis.h>
#include"cFCgraphics.h"
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
#include<fstream>


#include "TApplication.h"  //Janela

#include <algorithm>    // std::min_element, std::max_element
#include <cmath>

using namespace std;


int main(int argc, char **argv)
{


  //COISAS A PREENCHER PARA CADA ANALISE!!!////////////////////////
  string res_label = "resultados_SV4_D.txt";//Nome do ficheiro dos resultados
  string plot_label = "SV4_D.pdf"; //Nome do plot 
  string file1="../data/SV4_D_50_2a.txt"; //dados do primeiro varrimento 
  string file2="../data/SV4_D_50_2b.txt"; //dados do segundo varrimento

  double I=0.0010094;//corrente
  double eI=0.0000001;//erro corrente
  double eV = 0.000001; //erro tensao
  double eh = 0.0001;//erro campo VALOR ESTA MAL TEMOS DE ESTIMA-LO DEPOIS

  //Limites da curva linear --> Para fazer o fit
  double low_lim=-5;
  double high_lim=20;
  double low_lim2=-5;
  double high_lim2=20;

  //FIM DAS COISAS PARA PREENCHER A CADA ANALISE///////////////////


  /////////////////////////Tirar os dados do file 1 - varrimento 1////////////////////////////
  ifstream file;
  file.open (file1.c_str());

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
  file.open (file1.c_str());

  int i=0;
  while(!file.eof())
    {
      file >> H[i] >> R[i]; // extracts 2 floating point values seperated by whitespace
      R[i]=R[i]/I; //PASSAR TENSOES PARA RESISTENCIAS
      i++;
      // do something with them
    }


  ///////////////////Tirar os dados do file 2 - varrimento 2////////////////////////////
  ifstream file_2;
  file_2.open (file2.c_str());

  static int N2=0;

  
  char cur2 = '\0';
  char last2 = '\0';

  while (file_2.get(cur2)) {
      if (cur2 == '\n' ||
          (cur2 == '\f' && last2 == '\r'))
         N2++;
  }

  N2--;

  double *H2 = new double[N];
  double *R2 = new double[N];


  file_2.close();
  file_2.open (file2.c_str());

  i=0;
  while(!file_2.eof())
    {
      file_2 >> H2[i] >> R2[i]; // extracts 2 floating point values seperated by whitespace
      R2[i]=R2[i]/I; //PASSAR TENSOES PARA RESISTENCIAS
      i++;
      // do something with them
    }




  ///////INTERPOLACAO//////////////////////////
  /*


  TF1 *cubic;
  TGraph *g;
  double *K;

  DataInterpolator Test(N,H,R);
  cout<<"Pontos de Data"<<endl;


  for(int i=0;i<N;i++)
    cout<<H[i]<<" "<<R[i]<<endl;

  
  cubic=Test.DataInterpolator::CubicSpline(K);
  cubic->SetLineWidth(2);
  cubic->SetLineColor(kRed);
  cubic->SetTitle("Cubic Spline and Polynomial Interpolation");

  g=Test.Draw(N);
  g->SetMarkerStyle(31);
  g->SetTitle("Data Points");
  */
  

  /////////////////////////Rp e Rap////////////////////////////////////////////////

  ///Varrimento 1

  double Rp = *std::min_element(R,R+N);
  double Rap = *std::max_element(R,R+N);

  ///Varrimento 2

  double Rp2 = *std::min_element(R2,R2+N);
  double Rap2 = *std::max_element(R2,R2+N);


  //////////////Grafico MR(H) com os respectivos erros/////////////////////////

  ///Varrimento 1

  double *MR = new double[N];
  double *eR = new double[N];
  double *eH = new double[N];
  double *eMR = new double[N];
  for(int i=0;i<N;i++){

    double er = eV/I + R[i]/I*eI; //erro resistencia
    double e_mr= er/Rp + R[i]/(Rp*Rp)*er; //erro magneto-resistencia

    eR[i] = er;
    eH[i]=eh; //dado no inicio do prog
    eMR[i]=e_mr;//em percentagem
    MR[i]=(R[i]-Rp)/Rp;//em percentagem

  }
  

  TGraphErrors *MR_H = new TGraphErrors(N,H,MR,eH,eMR);
  MR_H->SetMarkerStyle(6);
  MR_H->SetMarkerColor(kBlue);
  MR_H->SetFillColor(kBlue);
  //MR_H->SetLineColor(kBlue);



  ///Varrimento 2

  double *MR2 = new double[N2];
  double *eR2 = new double[N2];
  double *eH2 = new double[N2];
  double *eMR2 = new double[N2];
  for(int i=0;i<N2;i++){

    //Os erros eV, eI e eH sao os mesmos para ambos os varrimentos
    double er2 = eV/I + R2[i]/I*eI; //erro resistencia
    double e_mr2= er2/Rp + R2[i]/(Rp2*Rp2)*er2; //erro magneto-resistencia

    eR2[i]=er2;
    eH2[i]=eh; //dado no inicio do prog
    eMR2[i]=e_mr2;//em percentagem
    MR2[i]=(R2[i]-Rp2)/Rp2;//em percentagem

  }
  

  TGraphErrors *MR_H2 = new TGraphErrors(N2,H2,MR2,eH2,eMR2);
  MR_H2->SetMarkerColor(kRed);
  MR_H2->SetMarkerStyle(7);

  /*
  //GRAFICO MR(H) COM TODOS OS DADOS

  double *Hf = new double[N+N2];
  double *MRf = new double[N+N2];
  double *eHf = new double[N+N2];
  double *eMRf = new double[N+N2];
  
  for(int i=0;i<N;i++){

    Hf[i]=H[i];
    MRf[i]=MR[i];
    eHf[i]=eH[i];
    eMRf[i]=eMR[i];

  }

  for(int i=N;i<N+N2;i++){

    Hf[i]=H2[i-N];
    MRf[i]=MR2[i-N];
    eHf[i]=eH2[i-N];
    eMRf[i]=eMR2[i-N];

  }

  int Nf=N+N2;

  TGraphErrors *MR_Hf = new TGraphErrors(Nf,Hf,MRf,eHf,eMRf); //grafico que mostra ambos os varrimentos
  */



  ////////////////////Encontrar Hc////////////////////


  double R_half = (Rap+Rp)/2; //Resistencia a meia altura par o varrimento 1
  double R_half2 = (Rap2+Rp2)/2; //Resistencia a meia altura para o varrimento 2
  double R_half_med=(R_half+R_half2)/2; //Faz-se a media para obter a resistencia a meia altura final


  //Varrimento 1
  TF1 *f1= new TF1("f1","[0]+[1]*x");//Funcao a fitar
  TGraphErrors *R_H = new TGraphErrors(N,H,R,eH,eR);//Grafico R(H) para dazer o fit
  R_H->Fit("f1","MF","",low_lim,high_lim);
  double b=f1->GetParameter(0); //ordenada na origem 
  double a=f1->GetParameter(1); //declive
  double dH1=(R_half_med-b)/a; //H correspondente a R a meia altura

  //Varrimento 2
  TF1 *f2= new TF1("f2","[0]+[1]*x");
  TGraphErrors *R_H2 = new TGraphErrors(N2,H2,R2,eH2,eR2);//grafico R(H) para fazer o fit
  R_H2->Fit("f2","MF","",low_lim2,high_lim2);
  double b2=f2->GetParameter(0); // ordenada na origem
  double a2=f2->GetParameter(1); //declive
  double dH2=(R_half_med-b2)/a2; //H correspondente a R a meia altura


  // Campo coercivo
  double Hc=TMath::Abs(dH2-dH1)/2;
  
  // Campo de offset
  double Hoff=(dH2+dH1)/2;

  //// Sensibilidade e erros
  double S1 = a/Rp*100; //Varrimento 1
  double eS1 = f1->GetParError(1); 
  double S2 = a2/Rp2*100; //Varrimento 2
  double eS2 = f2->GetParError(1);


  //Ficheiro com os resultados
  ofstream resultados;
  resultados.open (res_label.c_str());
  resultados << "Rp: " << Rp  << " Ohm" << "\n" << "Rap: " << Rap << " Ohm" << "\n" << "Hc: " << Hc << " Oe" << "\n" << "Hoff: " << Hoff << " Oe" << "\n" << "S (varrimento 1) (%) " << S1 << " +- " << eS1 << "\n" << "S (varrimento 2) (%)" << S2 << " +- " << eS2 << "\n";
  resultados.close();



  //faz aparecer o canvas
  TApplication theApp("App",&argc, argv);
  theApp.InitializeGraphics();

  TCanvas *c1 = new TCanvas("c1","Nome",200,10,700,500);
  c1->SetFillColor(0);
  //c1->SetGrid();
  c1->GetFrame()->SetFillColor(21);
  c1->GetFrame()->SetBorderSize(12);




  TMultiGraph *mg = new TMultiGraph("mg","Magnetoresistencia em funcao do campo magnetico");
  mg->Add(MR_H);
  mg->Add(MR_H2);


  file.close();
  //delete  g;
  //delete gr1; // A classe do prof deve fazer delete aos objectos, quando descomento da segmentation violation
  //delete  cubic;
  delete [] R;
  delete [] H;
  delete [] MR;
  delete [] eH;
  delete [] eMR;
  delete [] R2;
  delete [] H2;
  delete [] MR2;
  delete [] eH2;
  delete [] eMR2;
  delete [] eR;
  delete [] eR2;


  mg->Draw("AP");

  mg->GetXaxis()->SetTitle("H (Oe)");
  mg->GetYaxis()->SetTitle("MR (%)");


  c1->Update();
  c1->Modified();
  c1->Print(plot_label.c_str());
  getchar();
  theApp.Terminate();


  return 0;  
}
