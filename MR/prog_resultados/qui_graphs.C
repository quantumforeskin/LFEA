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


  static int Ngraphs=12;

  //COISAS A PREENCHER PARA CADA ANALISE!!!////////////////////////
  string plot_label[Ngraphs]; //Nome do ficheiro em que e feito o plot MR(H)
  plot_label[0] = "qui2/SV3_4_inf_1.pdf"; 
  plot_label[1] = "qui2/SV3_4_sup_1.pdf"; 
  plot_label[2] = "qui2/SV3_4_inf_2.pdf"; 
  plot_label[3] = "qui2/SV3_4_sup_2.pdf"; 
  plot_label[4] = "qui2/SV3_2_inf_1.pdf"; 
  plot_label[5] = "qui2/SV3_2_sup_1.pdf"; 
  plot_label[6] = "qui2/SV3_2_inf_2.pdf"; 
  plot_label[7] = "qui2/SV3_2_sup_2.pdf"; 
  plot_label[8] = "qui2/SV4B_inf_1.pdf"; 
  plot_label[9] = "qui2/SV4B_sup_1.pdf"; 
  plot_label[10] = "qui2/SV4B_inf_2.pdf"; 
  plot_label[11] = "qui2/SV4B_sup_2.pdf"; 

  /*
  plot_label[1] = "SV4_A_400.pdf";
  plot_label[2] = "SV4_C_50.pdf"; 
  plot_label[3] = "SV4_C_400.pdf"; 

  plot_label[4] = "SV3_1_50.pdf";
  plot_label[5] = "SV3_1_400.pdf";
  plot_label[6] = "SV3_3_50.pdf";
  plot_label[7] = "SV3_3_400.pdf";
  */


  string file1[Ngraphs]; //directorias dos dados do primeiro varrimento
  file1[0]="qui2/SV3_4_inf_1.txt";  
  file1[1]="qui2/SV3_4_sup_1.txt";
  file1[2]="qui2/SV3_4_inf_2.txt";
  file1[3]="qui2/SV3_4_sup_2.txt";
  file1[4]="qui2/SV3_2_inf_1.txt";  
  file1[5]="qui2/SV3_2_sup_1.txt";
  file1[6]="qui2/SV3_2_inf_2.txt";
  file1[7]="qui2/SV3_2_sup_2.txt";
  file1[8]="qui2/SV4B_inf_1.txt";  
  file1[9]="qui2/SV4B_sup_1.txt";
  file1[10]="qui2/SV4B_inf_2.txt";
  file1[11]="qui2/SV4B_sup_2.txt";
  /*
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
  */
  //double eh = 0.1;//erro campo !!!!! TOU A POR ASSIM PARA O FIT DAR, MAS NA VERDADE O ERRO E 0.1 !!!!!!! 


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
  double *qui = new double[N];


  file.close();
  file.open (file1[j].c_str());

  int i=0;
  int test=0;
  while(!file.eof() && test==0)
    {

      file >> H[i] >> qui[i]; // extracts 2 floating point values seperated by whitespace
      i++; 


      if(i>=N)
	test=1;

    }

  TGraph *graph = new TGraph(N,H,qui);
  graph->SetMarkerStyle(7);
  graph->SetLineColor(kBlue);


  TCanvas *c1 = new TCanvas("c1","Nome",200,10,700,500);
  c1->SetFillColor(0);
  //c1->SetGrid();
  c1->GetFrame()->SetFillColor(21);
  c1->GetFrame()->SetBorderSize(12);




  TMultiGraph *mg = new TMultiGraph("mg","");
  mg->Add(graph);



  file.close();

  delete [] qui;
  delete [] H;


  mg->Draw("AP");
  mg->GetXaxis()->SetTitle("H (Oe)");
  mg->GetYaxis()->SetTitle("#chi2");
  mg->GetYaxis()->SetTitleOffset(1.2);

  
  

  c1->Update();
  c1->Modified();
  c1->Print(plot_label[j].c_str());
  //getchar();

  }

  theApp.Terminate();
  return 0;  
}
