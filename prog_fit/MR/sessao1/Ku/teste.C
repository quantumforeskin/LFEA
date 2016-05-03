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
#include<TArrow.h>
#include<TLegend.h>
#include "TStyle.h"  //Caixa do fit
#include<TText.h>
#include<TPaveText.h>
#include<fstream>


#include "TApplication.h"  //Janela

#include <algorithm>    // std::min_element, std::max_element
#include <cmath>

using namespace std;


int main(int argc, char **argv)
{


  //COISAS A PREENCHER PARA CADA ANALISE!!!////////////////////////
  string res_label = "resultados_SV3_4.txt";//Nome do ficheiro onde sao apresentados os resultados
  string plot_label = "SV3_4.pdf"; //Nome do ficheiro em que e feito o plot MR(H) 
  string file1="../4s/data/SV3_4_50_2a.txt"; //directoria dos dados do primeiro varrimento 
  string file2="../4s/data/SV3_4_50_2b.txt"; //directoria dos dados do segundo varrimento

  double I=0.0010094;//corrente
  double eI=0.0000001;//erro corrente
  double eV = 0.000001; //erro tensao
  double eh = 0.1;//erro campo !!!!! TOU A POR ASSIM PARA O FIT DAR, MAS NA VERDADE O ERRO E 0.1 !!!!!!! 

  //Limites da curva linear --> Para fazer o fit
  double low_lim=-15;
  double high_lim=6;
  double low_lim2=-15;
  double high_lim2=6;

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

  //N--;
  
  cout << N << endl;

  double *H = new double[N];
  double *R = new double[N];
  double *eR = new double[N];


  file.close();
  file.open (file1.c_str());

  int i=0;
  int test=0;
  while(!file.eof() && test==0)
    {

      file >> H[i] >> R[i]; // extracts 2 floating point values seperated by whitespace
      R[i]=R[i]/I; //PASSAR TENSOES PARA RESISTENCIAS
      eR[i] = eV/I + R[i]/I*eI; //erro resistencia
      i++; 


      if(i>=N)
	test=1;

    }

  file.close();




  ///////////////////Tirar os dados do file 2 - varrimento 2////////////////////////////
  ifstream file_2;
  file_2.open(file2.c_str());


  double *H2 = new double[N];
  double *R2 = new double[N];
  double *eR2 = new double[N];

  file_2.close();
  file_2.open (file2.c_str());

  i=0;
  test=0;
  while(!file_2.eof() && test==0)
    {
      file_2 >> H2[i] >> R2[i]; // extracts 2 floating point values seperated by whitespace
      R2[i]=R2[i]/I; //PASSAR TENSOES PARA RESISTENCIAS
      eR2[i] = eV/I + R2[i]/I*eI; //erro resistencia
      i++;

      if(i>=N)
	test=1;
      // do something with them
    }

  file_2.close();


  /////////////////////////Rp e Rap////////////////////////////////////////////////

  ///Varrimento 1

  double Rp = *std::min_element(R,R+N);
  double eRp = *std::min_element(eR,eR+N); //Quanto maior a resistencia maior o seu erro, ver formula de erro
  double Rap = *std::max_element(R,R+N);
  double eRap = *std::max_element(eR,eR+N);

  ///Varrimento 2

  double Rp2 = *std::min_element(R2,R2+N);
  double eRp2 = *std::min_element(eR2,eR2+N);
  double Rap2 = *std::max_element(R2,R2+N);
  double eRap2 = *std::max_element(eR2,eR2+N);


  // Media do Rp e Rap
  double Rp_med = (Rp+Rp2)/2;
  double eRp_med = (eRp+eRp2)/2;
  double Rap_med = (Rap+Rap2)/2;
  double eRap_med = (eRap+eRap2)/2;



  //////////////Grafico MR(H) com os respectivos erros/////////////////////////

  ///Varrimento 1

  double *MR = new double[N];
  double *eH = new double[N];
  double *eMR = new double[N];
  for(int i=0;i<N;i++){

    double e_mr= eR[i]/Rp + R[i]/(Rp*Rp)*eRp; //erro magneto-resistencia

    eH[i]=eh; //dado no inicio do prog
    eMR[i]=e_mr;
    MR[i]=(R[i]-Rp)/Rp;

  }

  

  
  

  TGraphErrors *MR_H = new TGraphErrors(N,H,MR,eH,eMR);
  MR_H->SetMarkerStyle(6);
  MR_H->SetMarkerColor(kBlue);
  MR_H->SetFillColor(kBlue);


  ///Varrimento 2

  double *MR2 = new double[N];
  double *eH2 = new double[N];
  double *eMR2 = new double[N];
  for(int i=0;i<N;i++){

    //Os erros eV, eI e eH sao os mesmos para ambos os varrimentos
    double e_mr2= eR2[i]/Rp2 + R2[i]/(Rp2*Rp2)*eRp2; //erro magneto-resistencia

    eH2[i]=eh; //dado no inicio do prog
    eMR2[i]=e_mr2;//em percentagem
    MR2[i]=(R2[i]-Rp2)/Rp2;//em percentagem

  }
  

  TGraphErrors *MR_H2 = new TGraphErrors(N,H2,MR2,eH2,eMR2);
  MR_H2->SetMarkerColor(kRed);
  MR_H2->SetMarkerStyle(7);




  ////////////////////Encontrar Hc e Hoff////////////////////


  double R_half = (Rap+Rp)/2; //Resistencia a meia altura para o varrimento 1
  double eR_half = (eRap+eRp)/2; //Erro
  double R_half2 = (Rap2+Rp2)/2; //Resistencia a meia altura para o varrimento 2
  double eR_half2 = (eRap2+eRp2)/2; //Erro
  double R_half_med=(R_half+R_half2)/2; //Faz-se a media para obter a resistencia a meia altura final
  double eR_half_med=(eR_half+eR_half2)/2;//Erro


  //Varrimento 1
  TF1 *f1= new TF1("f1","[0]+[1]*x");//Funcao a fitar
  TGraphErrors *R_H = new TGraphErrors(N,H,R,eH,eR);//Grafico R(H) para dazer o fit
  R_H->Fit("f1","","",low_lim,high_lim);
  double b=f1->GetParameter(0); //ordenada na origem 
  double eb =  f1->GetParError(0); // erro da ordenada na origem 
  double a=f1->GetParameter(1); //declive
  double ea =  f1->GetParError(0); //erro do declive 

  double dH1=(R_half_med-b)/a; //H correspondente a R a meia altura
  double edH1=(eR_half_med+eb)/a + TMath::Abs(R_half_med-b)/(a*a)*ea;

  for(i=0;i<N;i++)
    cout << "H " << H[i] << " eH " << eH[i] << " R " << R[i] << " eR " << eR[i] << endl;

  //Varrimento 2
  TF1 *f2= new TF1("f2","[0]+[1]*x");
  TGraphErrors *R_H2 = new TGraphErrors(N,H2,R2,eH2,eR2);//grafico R(H) para fazer o fit
  R_H2->Fit("f2","","",low_lim2,high_lim2);
  double b2=f2->GetParameter(0); // ordenada na origem
  double eb2 =  f2->GetParError(0); // erro da ordenada na origem 
  double a2=f2->GetParameter(1); //declive
  double ea2 =  f2->GetParError(0); //erro do declive 


  //faz aparecer o canvas
  TApplication theApp("App",&argc, argv);
  theApp.InitializeGraphics();



  TCanvas *c1 = new TCanvas("c1","Nome",200,10,700,500);
  c1->SetFillColor(0);
  //c1->SetGrid();
  c1->GetFrame()->SetFillColor(21);
  c1->GetFrame()->SetBorderSize(12);


  //TMultiGraph *mg = new TMultiGraph("mg","");
  //mg->Add(R_H);
  //mg->Add(R_H2);

  R_H->Draw("AP");



  //file.close();
  //file_2.close();


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

  gStyle->SetOptFit();
  

  c1->Update();
  c1->Modified();
  c1->Print(plot_label.c_str());
  getchar();
  theApp.Terminate();


  return 0;  
}
