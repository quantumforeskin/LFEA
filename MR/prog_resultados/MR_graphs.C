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
#include<TText.h>
#include<TPaveText.h>
#include<fstream>


#include "TApplication.h"  //Janela

#include <algorithm>    // std::min_element, std::max_element
#include <cmath>

using namespace std;



int main(int argc, char **argv)
{


  gROOT->SetBatch(kTRUE);

  //faz aparecer o canvas
  TApplication theApp("App",&argc, argv);
  theApp.InitializeGraphics();


  static int Ngraphs=8;

  //COISAS A PREENCHER PARA CADA ANALISE!!!////////////////////////
  string plot_label[Ngraphs]; //Nome do ficheiro em que e feito o plot MR(H)
  plot_label[0] = "SV4_A_50.pdf"; 
  plot_label[1] = "SV4_A_400.pdf";
  plot_label[2] = "SV4_C_50.pdf"; 
  plot_label[3] = "SV4_C_400.pdf"; 

  plot_label[4] = "SV3_1_50.pdf";
  plot_label[5] = "SV3_1_400.pdf";
  plot_label[6] = "SV3_3_50.pdf";
  plot_label[7] = "SV3_3_400.pdf";


  string file1[Ngraphs]; //directorias dos dados do primeiro varrimento
  file1[0]="../3s/data/SV4_A_50_3a.txt";  
  file1[1]="../3s/data/SV4_A_400_2a.txt";
  file1[2]="../3s/data/SV4_C_50_3a.txt";  
  file1[3]="../3s/data/SV4_C_400_2a.txt";

  file1[4]="../4s/data/SV3_1_50_2a.txt";
  file1[5]="../4s/data/SV3_1_400_2a.txt";
  file1[6]="../4s/data/SV3_3_50_2a.txt";
  file1[7]="../4s/data/SV3_3_400_2a.txt";


  string file2[Ngraphs]; //directoria dos dados do segundo varrimento
  file2[0]="../3s/data/SV4_A_50_3b.txt"; 
  file2[1]="../3s/data/SV4_A_400_2b.txt";
  file2[2]="../3s/data/SV4_C_50_3b.txt"; 
  file2[3]="../3s/data/SV4_C_400_2b.txt";

  file2[4]="../4s/data/SV3_1_50_2b.txt";
  file2[5]="../4s/data/SV3_1_400_2b.txt";
  file2[6]="../4s/data/SV3_3_50_2b.txt";
  file2[7]="../4s/data/SV3_3_400_2b.txt"; 

  double I[Ngraphs];//corrente
  I[0]=0.0010026;
  I[1]=0.0010026;
  I[2]=0.001004;
  I[3]=0.001004;

  I[4]=0.001003;
  I[5]=0.0010029;
  I[6]=0.0010072;
  I[7]=0.0010072;


  double eI=0.0000001;//erro corrente
  double eV = 0.000001; //erro tensao
  double eh = 0.1;//erro campo !!!!! TOU A POR ASSIM PARA O FIT DAR, MAS NA VERDADE O ERRO E 0.1 !!!!!!! 


  //FIM DAS COISAS PARA PREENCHER A CADA ANALISE///////////////////


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

  double *H = new double[N];
  double *R = new double[N];
  double *eR = new double[N];


  file.close();
  file.open (file1[j].c_str());

  int i=0;
  int test=0;
  while(!file.eof() && test==0)
    {

      file >> H[i] >> R[i]; // extracts 2 floating point values seperated by whitespace
      R[i]=R[i]/I[j]; //PASSAR TENSOES PARA RESISTENCIAS
      eR[i] = eV/I[j] + R[i]/I[j]*eI; //erro resistencia
      i++; 


      if(i>=N)
	test=1;

    }




  ///////////////////Tirar os dados do file 2 - varrimento 2////////////////////////////
  ifstream file_2;
  file_2.open(file2[j].c_str());


  double *H2 = new double[N];
  double *R2 = new double[N];
  double *eR2 = new double[N];

  file_2.close();
  file_2.open (file2[j].c_str());

  i=0;
  test=0;
  while(!file_2.eof() && test==0)
    {
      file_2 >> H2[i] >> R2[i]; // extracts 2 floating point values seperated by whitespace
      R2[i]=R2[i]/I[j]; //PASSAR TENSOES PARA RESISTENCIAS
      eR2[i] = eV/I[j] + R2[i]/I[j]*eI; //erro resistencia
      i++;

      if(i>=N)
	test=1;
      // do something with them
    }


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
  MR_H->SetMarkerStyle(1);
  MR_H->SetLineColor(kBlue);


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
  MR_H2->SetLineColor(kRed);
  MR_H2->SetMarkerStyle(1);



  TCanvas *c1 = new TCanvas("c1","Nome",200,10,700,500);
  c1->SetFillColor(0);
  //c1->SetGrid();
  c1->GetFrame()->SetFillColor(21);
  c1->GetFrame()->SetBorderSize(12);




  TMultiGraph *mg = new TMultiGraph("mg","");
  mg->Add(MR_H);
  mg->Add(MR_H2);



  //Legenda///////////////////////////

  TLegend* leg;
  leg = new TLegend(0.1,0.8,0.2,0.9);//(x1,y1,x2,y2)
  
  //leg->SetHeader("Orientac#tilde{o}es");
  leg->AddEntry(MR_H,"#rightarrow","lep");
  leg->AddEntry(MR_H2,"#leftarrow","lep");



  file.close();
  file_2.close();
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
  mg->GetYaxis()->SetTitle("MR");
  mg->GetYaxis()->SetTitleOffset(1.2);

  

  //legenda
  leg->Draw();
  

  c1->Update();
  c1->Modified();
  c1->Print(plot_label[j].c_str());
  //getchar();

  }

  theApp.Terminate();
  return 0;  
}
