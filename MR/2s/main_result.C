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
#include<TStyle.h>


#include "TApplication.h"  //Janela

#include <algorithm>    // std::min_element, std::max_element
#include <cmath>

using namespace std;



int main(int argc, char **argv)
{


  //COISAS A PREENCHER PARA CADA ANALISE!!!////////////////////////
  string res_label = "res1.txt";//Nome do ficheiro onde sao apresentados os resultados
  string plot_label = "coco1.pdf"; //Nome do ficheiro em que e feito o plot MR(H) 
  string file1="../2s/data_SV2_100.txt"; //directoria dos dados do primeiro varrimento 
  string file2="../2s/data_SV2_100_2.txt"; //directoria dos dados do segundo varrimento

  double I=0.0010082;//corrente
  double eI=0.0000001;//erro corrente
  double eV = 0.000001; //erro tensao
  double eh = 0.1;//erro campo !!!!! TOU A POR ASSIM PARA O FIT DAR, MAS NA VERDADE O ERRO E 0.1 !!!!!!! 

  //Limites da curva linear --> Para fazer o fit
  double low_lim=-13;
  double high_lim=-5;
  double low_lim2=-20;
  double high_lim2=-11;

  //FIM DAS 3OISAS PARA PREENCHER A CADA ANALISE///////////////////


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
  //MR_H->SetFillColor(kBlue);


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
  //f1->FitParLimits(0,vmáx,vmin);
  R_H->Fit("f1","","",low_lim,high_lim);
  double b=f1->GetParameter(0); //ordenada na origem 
  double eb =  f1->GetParError(0); // erro da ordenada na origem 
  double a=f1->GetParameter(1); //declive
  double ea =  f1->GetParError(0); //erro do declive 

  double dH1=(R_half_med-b)/a; //H correspondente a R a meia altura
  double edH1=(eR_half_med+eb)/a + TMath::Abs(R_half_med-b)/(a*a)*ea;

  //Varrimento 2
  TF1 *f2= new TF1("f2","[0]+[1]*x");
  TGraphErrors *R_H2 = new TGraphErrors(N,H2,R2,eH2,eR2);//grafico R(H) para fazer o fit
  R_H2->Fit("f2","","",low_lim2,high_lim2);
  double b2=f2->GetParameter(0); // ordenada na origem
  double eb2 =  f2->GetParError(0); // erro da ordenada na origem 
  double a2=f2->GetParameter(1); //declive
  double ea2 =  f2->GetParError(0); //erro do declive 

  double dH2=(R_half_med-b2)/a2; //H correspondente a R a meia altura
  double edH2=(eR_half_med+eb2)/a2 + TMath::Abs(R_half_med-b2)/(a2*a2)*ea2;


  // Campo coercivo
  double Hc=TMath::Abs(dH2-dH1)/2;
  double eHc = (edH1+edH2)/2; //erro
  
  // Campo de offset
  double Hoff=(dH2+dH1)/2;
  double eHoff = (edH1+edH2)/2; //erro

  //// Sensibilidade e erros (em percentagem)
  double S1 = a/Rp*100; //Varrimento 1
  double eS1 = (ea/Rp + a/(Rp*Rp)*eRp)*100; 
  double S2 = a2/Rp2*100; //Varrimento 2
  double eS2 = (ea2/Rp2 + a2/(Rp2*Rp2)*eRp2)*100;

 double ab=low_lim;
 double bc=high_lim;
 double ba=high_lim2;
 double cb=low_lim2;
  //Ficheiro com os resultados
  ofstream resultados;
  resultados.open (res_label.c_str());
  resultados << "------ Varrimento 1 ------ " << "\n" <<"Rp: " << Rp  << " +- " << eRp << " Ohm" << "\n" << "Rap: " << Rap << " +- " << eRap << " Ohm" << "\n" << "------ Varrimento 2 ------ " << "\n" << "Rp: " << Rp2  << " +- " << eRp2 << " Ohm" << "\n" << "Rap: " << Rap2 << " +- " << eRap2 << " Ohm" << "\n" << "------ Media ------ " << "\n" << "Rp: " << Rp_med  << " +- " << eRp_med << " Ohm" << "\n" << "Rap: " << Rap_med << " +- " << eRap_med << " Ohm" << "\n" <<  "---------------------" << "\n" << "Hc: " << Hc  << " +- " << eHc << " Oe" << "\n" << "Hoff: " << Hoff << " +- " << eHoff << " Oe" << "\n" << "S (varrimento 1) (%) " << S1 << " +- " << eS1 << "\n" << "S (varrimento 2) (%)" << S2 << " +- " << eS2 << "\n" <<"Intervalo 1: ["  << bc << " ;  " << ab << "]  Intervalo 2:  [" << ba << " ;  " << cb << "] " << "\n";
  resultados.close();



  //faz aparecer o canvas
  TApplication theApp("App",&argc, argv);
  theApp.InitializeGraphics();

  TCanvas *c1 = new TCanvas("c1","Nome",200,10,700,500);
  c1->SetFillColor(0);
  //c1->SetGrid();
  c1->GetFrame()->SetFillColor(21);
  c1->GetFrame()->SetBorderSize(12);




  TMultiGraph *mg = new TMultiGraph("mg","");
  mg->Add(MR_H);
  mg->Add(MR_H2);



 /////////////////// ARROWS PARA AS ORIENTACOES /////////////////////////////////////////////////////////////////////////////
  float arrow_step = 0.0025;//Distancia entre arrows
  float arrow_offset = 0.0035;//Distancia do arrow mais proximo do grafico ao grafico


  //Regiao 1/////////////////////////

  float ax1 = -98;
  float ay1 = 0.035;

  // H 
  TArrow *r1ar1 = new TArrow(ax1,ay1+arrow_offset,ax1+15,ay1+arrow_offset,0.02,"<|");
  r1ar1->SetLineColor(1);
  r1ar1->SetFillColor(1);

  // Mpl
  TArrow *r1ar2 = new TArrow(ax1,ay1+arrow_offset-arrow_step,ax1+15,ay1+arrow_offset-arrow_step,0.02,"|>");
  r1ar2->SetLineColor(8);
  r1ar2->SetFillColor(8);


  // Mfl
  TArrow *r1ar3 = new TArrow(ax1,ay1+arrow_offset-2*arrow_step,ax1+15,ay1+arrow_offset-2*arrow_step,0.02,"<|");
  r1ar3->SetLineColor(9);
  r1ar3->SetFillColor(9);

  /*
  // J
  float axj=40;
  float ayj=0;
  TArrow *arj = new TArrow(axj,ayj,axj+10,ayj,0.02,"|>");
  arj->SetLineColor(49);
  arj->SetFillColor(49);
  TPaveText *text_j = new TPaveText(axj,ayj+5,axj+10,ayj+5);
  text_j->SetLabel("J");
  */

  // Ku
  float axku=-60;
  float ayku=0.002;
  TArrow *arku = new TArrow(axku,ayku,axku+30,ayku,0.02,"<|>");
  arku->SetLineColor(49);
  arku->SetFillColor(49);
  TText *text_ku = new TText(axku+10, ayku+0.002, "Ku");
  text_ku->SetTextSize(0.04);


  //Regiao 2///////
/*
  float ax2 = -5;
  float ay2 = 0.021;

  // H 
  TText *text_H = new TText(ax2, ay2+arrow_offset+arrow_step/2-0.0045, "H = 0");
  text_H->SetTextSize(0.04);


  // M pl
  TArrow *r2ar2 = new TArrow(ax2+1,ay2+arrow_offset+2*arrow_step-0.005,ax2+15,ay2+arrow_offset+2*arrow_step-0.005,0.02,"|>");
  r2ar2->SetLineColor(8);
  r2ar2->SetFillColor(8);

  // M fl
  TArrow *r2ar3 = new TArrow(ax2-1,ay2+arrow_offset,ax2-1,ay2+arrow_offset+0.004,0.02,"|>");
  r2ar3->SetLineColor(9);
  r2ar3->SetFillColor(9);
 */

 //   REGIAO 2.3 ////////////////////////////////

/*
  float ax23 = -130;
  float ay23 = 0.035;

  // H 
  TArrow *r23ar1 = new TArrow(ax23,ay23+arrow_offset,ax23+45,ay23+arrow_offset,0.02,"<|");
  r23ar1->SetLineColor(1);
  r23ar1->SetFillColor(1);

  // Mpl
  TArrow *r23ar2 = new TArrow(ax23,ay23+arrow_offset-arrow_step,ax23+45,ay23+arrow_offset-arrow_step,0.02,"|>");
  r23ar2->SetLineColor(8);
  r23ar2->SetFillColor(8);


  // Mfl
  TArrow *r23ar3 = new TArrow(ax23,ay23+arrow_offset-2*arrow_step,ax23+45,ay23+arrow_offset-2*arrow_step,0.02,"<|");
  r23ar3->SetLineColor(9);
  r23ar3->SetFillColor(9); 
*/

 //REGIAO 2.5 ////////////////////////////
/*

  float ax25 = 60;
  float ay25 = 0.065;

  // H 
  TArrow *r25ar1 = new TArrow(ax25,ay25+arrow_offset,ax25+25,ay25+arrow_offset,0.02,"|>");
  r25ar1->SetLineColor(1);
  r25ar1->SetFillColor(1);

  // Mpl
  TArrow *r25ar2 = new TArrow(ax25,ay25+arrow_offset-arrow_step,ax25+25,ay25+arrow_offset-arrow_step,0.02,"<|");
  r25ar2->SetLineColor(8);
  r25ar2->SetFillColor(8);


  // Mfl
  TArrow *r25ar3 = new TArrow(ax25,ay25+arrow_offset-2*arrow_step,ax25+25,ay25+arrow_offset-2*arrow_step,0.02,"|>");
  r25ar3->SetLineColor(9);
  r25ar3->SetFillColor(9);
*/

  //Regiao 3///////

  float ax3 = 82;
  float ay3 = 0.011;

  // H 
  TArrow *r3ar1 = new TArrow(ax3,ay3-arrow_offset,ax3+15,ay3-arrow_offset,0.02,"|>");
  r3ar1->SetLineColor(1);
  r3ar1->SetFillColor(1);

  // M pl 
  TArrow *r3ar2 = new TArrow(ax3,ay3-arrow_offset-arrow_step,ax3+15,ay3-arrow_offset-arrow_step,0.02,"|>");
  r3ar2->SetLineColor(8);
  r3ar2->SetFillColor(8);

  // M fl
  TArrow *r3ar3 = new TArrow(ax3,ay3-arrow_offset-2*arrow_step,ax3+15,ay3-arrow_offset-2*arrow_step,0.02,"|>");
  r3ar3->SetLineColor(9);
  r3ar3->SetFillColor(9);


  //Legenda///////////////////////////
/*
  TLegend* leg;
 
  //Usa-se a condicao para nao por a legenda em cima dos dados
  if(S1<0){
    leg = new TLegend(0.65,0.55,0.9,0.9);//(x1,y1,x2,y2
   
      }else{
    leg = new TLegend(0.1,0.6,0.27,0.9);//(x1,y1,x2,y2)
  }
  //leg->SetHeader("Orientac#tilde{o}es");
  leg->AddEntry(MR_H,"#rightarrow","lep");
  leg->AddEntry(MR_H2,"#leftarrow","lep");

  leg->AddEntry(r1ar1,"H","l");
  leg->AddEntry(r1ar2,"M Pl","l");
  leg->AddEntry(r1ar3,"M Fl","l");
  //leg->AddEntry(arj,"J","l");
*/



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
 R_H->Draw("AP");
 //R_H2->Draw("AP");
  gStyle->SetOptFit(1);
  /*
  //arrows
  r1ar1->Draw();
  //r2ar1->Draw(); Basta por um texto a dizer que H=0
  //text_H->Draw();
 //  r23ar1->Draw(); //
 // r25ar1->Draw(); //
  r3ar1->Draw();

  r1ar2->Draw();
 // r2ar2->Draw();
 // r23ar2->Draw(); //
 // r25ar2->Draw(); //
  r3ar2->Draw();

  r1ar3->Draw();
 // r2ar3->Draw();
 //  r23ar3->Draw(); //
 // r25ar3->Draw(); //
  r3ar3->Draw();

  arku->Draw();
  text_ku -> Draw(); */

  //arj->Draw();
  //text_j->Draw();


  

  //legenda
 // leg->Draw();
  



  c1->Update();
  c1->Modified();
  c1->Print(plot_label.c_str());
  getchar();
  theApp.Terminate();


  return 0;  
}
