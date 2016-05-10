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

#include "file_reader.h"

using namespace std;


int main(int argc, char **argv)
{

  //COISAS A PREENCHER PARA CADA ANALISE!!!////////////////////////

  bool fit=true;//Opcao de fazer os graficos dos fits R(H) ou fazer a analise de resultados normal com o grafico MR(H)

  string res_label="";
  string plot_label="";
  string plot_label2="";

  if(fit==false){
    res_label = "resultados_SV3_2.txt";//Nome do ficheiro onde sao apresentados os resultados
    plot_label = "SV3_2.pdf"; //Nome do ficheiro em que e feito o plot MR(H) 
  }else{
    res_label = "resultados_SV3_2.txt";//Nome do ficheiro onde sao apresentados os resultados
    plot_label = "fits/fit_SV3_2a.pdf"; //Nome do ficheiro em que e feito o plot MR(H) 
    plot_label2 = "fits/fit_SV3_2b.pdf"; //Nome do ficheiro em que e feito o plot MR(H) 
  }



  string file1="../4s/data/SV3_2_50_3a.txt"; //directoria dos dados do primeiro varrimento 
  string file2="../4s/data/SV3_2_50_3b.txt"; //directoria dos dados do segundo varrimento

  double I=0.0010038;//corrente
  double eI=0.0000001;//erro corrente
  double eV = 0.000001; //erro tensao
  double eh = 0.1;//erro campo !!!!! TOU A POR ASSIM PARA O FIT DAR, MAS NA VERDADE O ERRO E 0.1 !!!!!!! 


  //Limites da curva linear --> Para fazer o fit
  double low_lim=-10;
  double high_lim=40;
  double low_lim2=-10;
  double high_lim2=40;

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

      //cout << "i " << i << "  H " << H[i] << "  R " << R[i] << endl;

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

  //Tirar os dados dos ficheiros de -400 a 400 para obter os valores minimo e maximo de R que correspondem a Rp e Rap
  string f1_400="../4s/data/SV3_2_400_2a.txt";  


  string f2_400="../4s/data/SV3_2_400_2b.txt"; 

  double I_400=0.0010072;

  fr rd; //objecto file reader

  int N_400 = rd.getN(f1_400);
  double* H_400=rd.getH(f1_400,I_400);
  double* R_400=rd.getR(f1_400,I_400);
  double* eR_400=rd.get_eR(f1_400,I_400);
  double* H2_400=rd.getH(f2_400,I_400);
  double* R2_400=rd.getR(f2_400,I_400);
  double* eR2_400=rd.get_eR(f2_400,I_400);



  ///Varrimento 1

  double Rp = *std::min_element(R_400,R_400+N_400);
  double eRp = *std::min_element(eR_400,eR_400+N_400); //Quanto maior a resistencia maior o seu erro, ver formula de erro
  double Rap = *std::max_element(R_400,R_400+N_400);
  double eRap = *std::max_element(eR_400,eR_400+N_400);


  /// MR max /////////
  double MRmax=(Rap-Rp)/Rp;
  double eMRmax=(eRap+eRp)/Rp + (Rap-Rp)*eRp/(Rp*Rp);



  ///Varrimento 2

  double Rp2 = *std::min_element(R2_400,R2_400+N_400);
  double eRp2 = *std::min_element(eR2_400,eR2_400+N_400);
  double Rap2 = *std::max_element(R2_400,R2_400+N_400);
  double eRap2 = *std::max_element(eR2_400,eR2_400+N_400);

  cout << Rap << endl ;

  /// MR max /////////
  double MRmax2=(Rap2-Rp2)/Rp2;
  double eMRmax2=(eRap2+eRp2)/Rp2 + (Rap2-Rp2)*eRp2/(Rp2*Rp2);

  cout << MRmax << endl;

  // Media do Rp e Rap
  double Rp_med = (Rp+Rp2)/2;
  double eRp_med = (eRp+eRp2)/2;
  double Rap_med = (Rap+Rap2)/2;
  double eRap_med = (eRap+eRap2)/2;

  /// MR max /////////
  double MRmax_med=(Rap_med-Rp_med)/Rp_med;
  double eMRmax_med=(eRap_med+eRp_med)/Rp_med + (Rap_med-Rp_med)*eRp_med/(Rp_med*Rp_med);




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




  ////////////////////Encontrar Hc e Hoff////////////////////



  ///Uma vez que a saturacao nao e simetrica em relacao ao centro da zonna linear, e necessario ter descernimento e considerar um intervalo de campos adequado para obter o ponto central da zona linear. As resistencias correspondentes aos limites dessa regiao sao estimadas como sendo Ru (resistencia maxima na regiao considerada) e Rl(resistencia minima na regiao considerada)


 ///Varrimento 1

  double Rl = *std::min_element(R,R+N);
  double eRl = *std::min_element(eR,eR+N); 
  double Ru = *std::max_element(R,R+N);
  double eRu = *std::max_element(eR,eR+N);

  

  ///Varrimento 2

  double Rl2 = *std::min_element(R2,R2+N);
  double eRl2 = *std::min_element(eR2,eR2+N);
  double Ru2 = *std::max_element(R2,R2+N);
  double eRu2 = *std::max_element(eR2,eR2+N);


  double R_half = (Ru+Rl)/2; //Resistencia a meia altura para o varrimento 1
  double eR_half = (eRu+eRl)/2; //Erro
  double R_half2 = (Ru2+Rl2)/2; //Resistencia a meia altura para o varrimento 2
  double eR_half2 = (eRu2+eRl2)/2; //Erro
  double R_half_med=(R_half+R_half2)/2; //Faz-se a media para obter a resistencia a meia altura final
  double eR_half_med=(eR_half+eR_half2)/2;//Erro


  //Varrimento 1
  TF1 *f1= new TF1("f1","[0]+[1]*x");//Funcao a fitar
  f1->SetParLimits(1,-1,-0.1);
  TGraphErrors *R_H = new TGraphErrors(N,H,R,eH,eR);//Grafico R(H) para dazer o fit
  R_H->SetMarkerStyle(1);
  R_H->SetLineColor(kBlue);
  R_H->Fit("f1","","",low_lim,high_lim);

  double a_sens=f1->GetParameter(1); //declive para o calculo da sensibilidade
  double ea_sens =  f1->GetParError(1); //erro do declive 
  double b_sens=f1->GetParameter(0);
  double eb_sens = f1->GetParError(0);


  //Calculo de Hsat(varrimento 1)


  double Hsat1 = (Rp - b_sens)/a_sens;//Campo de saturacao que surge da interseccao da reta com a resistencia minima
  double Hsat2 = (Rap - b_sens)/a_sens;//Campo de saturacao que surge da interseccao da reta com a resistencia maxima
  double eHsat1 = TMath::Abs((eRp + eb_sens)/a_sens) + TMath::Abs((Rp - b_sens)*ea_sens/(a_sens*a_sens));
  double eHsat2 = TMath::Abs((eRap + eb_sens)/a_sens) + TMath::Abs((Rap - b_sens)*ea_sens/(a_sens*a_sens));



  //Fit para os calculos de Hc e Hoff - MAIS LOCALIZADO!
  TF1 *faux= new TF1("faux","[0]+[1]*x");//Funcao a fitar
  faux->SetParLimits(1,-1,-0.1);
  TGraphErrors *R_Haux = new TGraphErrors(N,H,R,eH,eR);//Grafico R(H) para dazer o fit
  R_Haux->SetMarkerStyle(1);
  R_Haux->SetLineColor(kBlue);
  R_Haux->Fit("faux","","",5,20);

  double b=faux->GetParameter(0); //ordenada na origem 
  double eb =  faux->GetParError(0); // erro da ordenada na origem 
  double a=faux->GetParameter(1); //declive
  double ea =  faux->GetParError(1); //erro do declive 
 

  double dH1=(R_half_med-b)/a; //H correspondente a R a meia altura
  double edH1=(eR_half_med+eb)/TMath::Abs(a) + TMath::Abs(R_half_med-b)/(a*a)*ea;



  //Varrimento 2
  TF1 *f2= new TF1("f2","[0]+[1]*x");
  f2->SetParLimits(1,-1,0);
  TGraphErrors *R_H2 = new TGraphErrors(N,H2,R2,eH2,eR2);//grafico R(H) para fazer o fit
  R_H2->SetMarkerStyle(1);
  R_H2->SetLineColor(kBlue);
  R_H2->Fit("f2","","",low_lim2,high_lim2);

  double a_sens2=f2->GetParameter(1); //declive para o calculo da sensibilidade
  double ea_sens2=f2->GetParError(1); //erro do declive 
  double b_sens2=f2->GetParameter(0);
  double eb_sens2 = f2->GetParError(0);


  //Calculo de Hsat(varrimento 2)


  double Hsat1_2 = (Rp2 - b_sens2)/a_sens2;//Campo de saturacao que surge da interseccao da reta com a resistencia minima
  double Hsat2_2 = (Rap2 - b_sens2)/a_sens2;//Campo de saturacao que surge da interseccao da reta com a resistencia maxima
  double eHsat1_2 = TMath::Abs((eRp2 + eb_sens2)/a_sens2) + TMath::Abs((Rp2 - b_sens2)*ea_sens2/(a_sens2*a_sens2));
  double eHsat2_2 = TMath::Abs((eRap2 + eb_sens2)/a_sens2) + TMath::Abs((Rap2 - b_sens2)*ea_sens2/(a_sens2*a_sens2));


  //Media de Hsat

  double Hsat1_med = (Hsat1+Hsat1_2)/2;
  double Hsat2_med = (Hsat2+Hsat2_2)/2;
  double eHsat1_med = (eHsat1+eHsat1_2)/2;
  double eHsat2_med = (eHsat2+eHsat2_2)/2;

  double DHsat = TMath::Abs(Hsat1_med) + TMath::Abs(Hsat2_med);
  double eDHsat = eHsat1_med + eHsat2_med;




  //Fit para os calculos de Hc e Hoff - MAIS LOCALIZADO!
  TF1 *faux2= new TF1("faux2","[0]+[1]*x");//Funcao a fitar
  faux2->SetParLimits(1,-1,-0.1);
  TGraphErrors *R_Haux2 = new TGraphErrors(N,H2,R2,eH2,eR2);//Grafico R(H) para dazer o fit
  R_Haux2->SetMarkerStyle(1);
  R_Haux2->SetLineColor(kBlue);
  R_Haux2->Fit("faux2","","",5,20);

  double b2=faux2->GetParameter(0); // ordenada na origem
  double eb2 =  faux2->GetParError(0); // erro da ordenada na origem 
  double a2=faux2->GetParameter(1); //declive
  double ea2 =  faux2->GetParError(1); //erro do declive 

  double dH2=(R_half_med-b2)/a2; //H correspondente a R a meia altura
  double edH2=(eR_half_med+eb2)/TMath::Abs(a2) + TMath::Abs(R_half_med-b2)/(a2*a2)*ea2;


  
  // Campo coercivo
  double Hc=TMath::Abs(dH2-dH1)/2;
  double eHc = (edH1+edH2)/2; //erro
  
  // Campo de offset
  double Hoff=(dH2+dH1)/2;
  double eHoff = (edH1+edH2)/2; //erro

  //// Sensibilidade e erros (em percentagem)
  double S1 = a_sens/Rp*100; //Varrimento 1
  double eS1 = (ea_sens/Rp + a_sens/(Rp*Rp)*eRp)*100; 
  double S2 = a_sens2/Rp2*100; //Varrimento 2
  double eS2 = (ea_sens2/Rp2 + a_sens2/(Rp2*Rp2)*eRp2)*100;
  double Smed = (S1+S2)/2;//media
  double eSmed = (eS1+eS2)/2;


  //Ficheiro com os resultados
  ofstream resultados;
  resultados.open (res_label.c_str());
  resultados << "------ Varrimento 1 ------ " << "\n" <<"Rp: " << Rp  << " +- " << eRp << " Ohm" << "\n" << "Rap: " << Rap << " +- " << eRap << " Ohm" << "\n" << "MR max: " << MRmax << " +- " << eMRmax << "\n" << "------ Varrimento 2 ------ " << "\n" << "Rp: " << Rp2  << " +- " << eRp2 << " Ohm" << "\n" << "Rap: " << Rap2 << " +- " << eRap2 << " Ohm" << "\n" << "MR max: " << MRmax2 << " +- " << eMRmax2 << "\n" << "------ Media ------ " << "\n" << "Rp: " << Rp_med  << " +- " << eRp_med << " Ohm" << "\n" << "Rap: " << Rap_med << " +- " << eRap_med << " Ohm" << "\n "<<  "---------------------" << "\n"<< "MR max: " << MRmax_med << " +- " << eMRmax_med <<"\n" << "H sat1: " << Hsat1_med << " +- "  << eHsat1_med << " Oe" << "\n" << "H sat2: " << Hsat2_med << " +- "  << eHsat2_med << " Oe"  << "\n " << "Delta Hsat " << DHsat << " +- " << eDHsat << " Oe " <<  "\n" <<  "---------------------" << "\n"<< "Hc: " << Hc  << " +- " << eHc << " Oe" << "\n" << "Hoff: " << Hoff << " +- " << eHoff << " Oe" << "\n" << "S (varrimento 1) (%) " << S1 << " +- " << eS1 << "\n" << "S (varrimento 2) (%)" << S2 << " +- " << eS2 << "\n" << "S media (%) " << Smed << " +- " << eSmed << "\n";
  resultados.close();
 
  //faz aparecer o canvas
  TApplication theApp("App",&argc, argv);
  theApp.InitializeGraphics();

  TCanvas *c1 = new TCanvas("c1","Nome",200,10,700,500);
  c1->SetFillColor(0);
  //c1->SetGrid();
  c1->GetFrame()->SetFillColor(21);
  c1->GetFrame()->SetBorderSize(12);



  //TGraphErrors *R_H400 = new TGraphErrors(N_400,H_400,R_400,eH,eR_400);
  //R_H400->SetMarkerColor(kBlue);

  TMultiGraph *mg = new TMultiGraph("mg","");
  if(fit==false){
    mg->Add(MR_H);
    mg->Add(MR_H2);
    
    mg->Draw("AP");
    mg->GetXaxis()->SetTitle("H (Oe)");
    mg->GetYaxis()->SetTitle("MR");
    mg->GetYaxis()->SetTitleOffset(1.2);
  }else{
    mg->Add(R_H);
    gStyle->SetOptFit();

    mg->Draw("AP");
    mg->GetXaxis()->SetTitle("H (Oe)");
    mg->GetYaxis()->SetTitle("R (#Omega)");
  }

 /////////////////// Arrows para as orientacoes /////////////////////////////////////////////////////////////////////////////
  float arrow_step = 0.0020;//Distancia entre arrows
  float arrow_offset = 0.0025;//Distancia do arrow mais proximo do grafico ao grafico


  //Regiao 1/////////////////////////

  float ax1 = -40;
  float ay1 = 0.033;

  // H 
  TArrow *r1ar1 = new TArrow(ax1,ay1,ax1+10,ay1,0.02,"<|");
  r1ar1->SetLineColor(1);
  r1ar1->SetFillColor(1);

  // M pl 
  TArrow *r1ar2 = new TArrow(ax1,ay1-arrow_step,ax1+10,ay1-arrow_step,0.02,"|>");
  r1ar2->SetLineColor(8);
  r1ar2->SetFillColor(8);

  // M fl
  TArrow *r1ar3 = new TArrow(ax1,ay1-2*arrow_step,ax1+10,ay1-2*arrow_step,0.02,"<|");
  r1ar3->SetLineColor(9);
  r1ar3->SetFillColor(9);

  // Ku
  float axku=-50;
  float ayku=0.008;
  TArrow *arku = new TArrow(axku,ayku,axku+10,ayku,0.02,"<|>");
  arku->SetLineColor(49);
  arku->SetFillColor(49);
  TText *text_ku = new TText(axku+3, ayku+0.001, "Ku");
  text_ku->SetTextSize(0.03);


  //Regiao 2///////

  float ax2 = 5;
  float ay2 = 0.018;

  // H
  TText *text_H = new TText(ax2-arrow_step, ay2-arrow_step, "H = 0");
  text_H->SetTextSize(0.04);


  // M pl
  TArrow *r2ar2 = new TArrow(ax2,ay2,ax2+10,ay2,0.02,"|>");
  r2ar2->SetLineColor(8);
  r2ar2->SetFillColor(8);

  // M fl
  TArrow *r2ar3 = new TArrow(ax2-2,ay2-arrow_step,ax2-2,ay2-arrow_step+0.004,0.02,"|>");
  r2ar3->SetLineColor(9);
  r2ar3->SetFillColor(9);



  //Regiao 3///////

  float ax3 = 65;
  float ay3 = 0.015;

  // H 
  TArrow *r3ar1 = new TArrow(ax3,ay3,ax3+10,ay3,0.02,"|>");
  r3ar1->SetLineColor(1);
  r3ar1->SetFillColor(1);

  // Mpl
  TArrow *r3ar2 = new TArrow(ax3,ay3-arrow_step,ax3+10,ay3-arrow_step,0.02,"|>");
  r3ar2->SetLineColor(8);
  r3ar2->SetFillColor(8);


  // Mfl
  TArrow *r3ar3 = new TArrow(ax3,ay3-2*arrow_step,ax3+10,ay3-2*arrow_step,0.02,"|>");
  r3ar3->SetLineColor(9);
  r3ar3->SetFillColor(9);


  //Legenda///////////////////////////

  TLegend* leg;

  //Usa-se a condicao para nao por a legenda em cima dos dados
  if(S1<0){
    leg = new TLegend(0.8,0.7,0.9,0.9);//(x1,y1,x2,y2)
  }else{
    leg = new TLegend(0.1,0.7,0.2,0.9);//(x1,y1,x2,y2)
  }
  //leg->SetHeader("Orientac#tilde{o}es");
  leg->AddEntry(MR_H,"#rightarrow","p");
  leg->AddEntry(MR_H2,"#leftarrow","p");

  leg->AddEntry(r1ar1,"H","l");
  leg->AddEntry(r1ar2,"M pl","l");
  leg->AddEntry(r1ar3,"M fl","l");
  //leg->AddEntry(arj,"J","l");




  //////DRAWs
  
  //arrows
  r1ar1->Draw();
  //r2ar1->Draw(); Basta por um texto a dizer que H=0
  text_H->Draw();
  r3ar1->Draw();

  r1ar2->Draw();
  r2ar2->Draw();
  r3ar2->Draw();

  r1ar3->Draw();
  r2ar3->Draw();
  r3ar3->Draw();

  arku->Draw();
  text_ku -> Draw();

  //arj->Draw();
  //text_j->Draw();


  


  if(fit==false){

    //legenda
    leg->Draw();

    c1->Update();
    c1->Modified();
    c1->Print(plot_label.c_str());
    getchar();


  }else{

    //Desenhar fit varrimento 1
    c1->Update();
    c1->Modified();
    c1->Print(plot_label.c_str());


    //Desenhar fit varrimento 2
    TMultiGraph *mg2 = new TMultiGraph("mg2","");
    mg2->Add(R_H2);
    gStyle->SetOptFit();


    c1->Clear();
    mg2->Draw("AP");
    mg2->GetXaxis()->SetTitle("H (Oe)");
    mg2->GetYaxis()->SetTitle("R (#Omega)");

    c1->Update();
    c1->Modified();
    c1->Print(plot_label2.c_str());
  }

  
  
  file.close();
  file_2.close();
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

  
  theApp.Terminate();
  



  return 0;  
}
