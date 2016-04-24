//Header's de ROOT
#include "TROOT.h"  //Principal
#include "TFrame.h"  //gClient
#include "TCanvas.h"  //Ecra principal dos graficos
#include "TPad.h"  //"Subcanvas"
#include "TSystem.h"  //Nao faco ideia
#include "TApplication.h"  //Janela
#include "TAxis.h"  //Eixos dos graficos
#include "TMultiGraph.h"  //Varios graficos sobrepostos
#include "TGraphPolar.h" //grafico polar
#include "TStyle.h"  //Caixa do fit
#include "TF1.h"  //Funcoes
#include "TPaveStats.h"  //Customizacao da caixa de parametros do fit
#include <TList.h>  //Nao sei, alguem diga alguma coisa
#include <TPad.h>  //Quem e que pos isto aqui, esta la em cima...
#include <TH1.h>  //Classe base dos histogramas
#include "TLatex.h"

//Header's nao de ROOT
#include <iostream>  //Porque razoes
#include <fstream>  //Ficheiros
#include <sstream> //para passar int para string
#include <string>
#include "Opt2.h"  //Classe que faz coisas

using namespace std;

int main(int argc, char **argv)
{
  
  cout << "Hail Eris! All hail Discordia!" << endl;

  //const int N = 1; //nr de ficheiros de dados que se pretende plotar 
  const int N = 1;
  if (argc != N+2)
  {
    cout << "Faltam argumentos. Ler manual." << endl;
    return 0;
  }

  const char* paramf = argv[1];

  
  const char* dados[N];

  for(int i=0; i<N; i++){

    dados[i] = argv[i+2];

  }
  

  ifstream det(paramf);
  if(det.is_open())
    cout << "Ficheiro aberto com sucesso" << endl;
  else
    cout << "Erro. Nao foi possivel abrir o ficheiro" << endl;
  det.close();

  //faz aparecer o canvas
  TApplication theApp("App", &argc, argv);
  theApp.InitializeGraphics();

  TCanvas *c1 = new TCanvas("c1","Nome",200,10,700,500);
  c1->SetFillColor(0);
  //c1->SetGrid();
  c1->GetFrame()->SetFillColor(21);
  c1->GetFrame()->SetBorderSize(12);


  
  Opt *Decisao[N];

  for(int i=0;i<N;i++){

    Decisao[i] = new Opt(paramf,dados[i]);

  }
  

  vector<string> cenas = Decisao[0]->Escolher(); //os paramf sao os msmos para todas por isso e indiferente
  TMultiGraph *mg = new TMultiGraph("mg","mg"); 
  mg->SetTitle(cenas[1].c_str());


  
  string escolha = cenas[0];  
  cout << escolha << endl;

  //Para por aqui os titulos que quisermos dar
  string title[N];
  title[0]="x = -3.81cm";
  title[1]="x = -2.54cm";
  title[2]="x = -1.27cm";
  title[3]="x = 0 cm";
  title[4]="x = 1.27 cm";
  title[5]="x = 2.54cm";
  title[6]="x = 3.81 cm";
  //for(int i=0;i<N;i++)
  //title[i] = "POE UM TITULO!!!";


  if (escolha == "grafico")
  {
    
    for(int i=0;i<N;i++){

      TGraphErrors* gr;
      if(i!=3){
	gr = Decisao[i]->Grafico(i+2);//mando a cor como argumento
      }else{
	gr = Decisao[i]->Grafico(12);
      }

      //Para criar legenda automaticamente com as varias posicoes 

      //float d = -3.81+i*1.27;
      //string d_string = static_cast<ostringstream*>( &(ostringstream() << d) )->str();
      //string title="x = " + d_string + " cm";
      //const char* c_title = title.c_str();


      const char* c_title = title[i].c_str();
      gr->SetTitle(c_title);

      mg->Add(gr);


    }
    
  }

  else if (escolha == "polar"){

    for(int i=0;i<N;i++){


      TGraphPolar* gr = Decisao[i]->GraficoPolar(i+2);//mando a cor como argumento
      float d = -3.81+i*1.27;
      string d_string = static_cast<ostringstream*>( &(ostringstream() << d) )->str();
      string title= " ";//"d = " + d_string + "cm";
      const char* c_title = title.c_str();
      gr->SetTitle(c_title);
      mg->Add(gr);


    }


  }


  else if (escolha == "polar_area"){

    for(int i=0;i<N;i++){


      TGraphPolar* gr = Decisao[i]->GraficoPolarArea(i+2);//mando a cor como argumento
      mg->Add(gr);


    }


  }

  /*
  else if (escolha == "histograma")
  {
    TH1F* hist=Decisao->Histograma();
    hist->Draw("EHISTSAME");
    //hist->Draw("BE1");
    c1->Update();
    //for (int i=0; i<100; i++)
    //{
    //  cout << hist->GetBinError(i) << endl;
    //}
  }
  else if (escolha == "fit")
  {
    TGraphErrors* gr = Decisao->Grafico(1);
    gStyle->SetOptFit();
    for(int i=0; i<=19; i++)
      //cout << "erro de x:" << gr->GetErrorX(i) << " erro de y:" << gr->GetErrorY(i) << endl;
    Decisao->Ajuste(gr);
    gr->Draw();
    mg->Add(gr);

    gPad->Update();

    TPaveStats *stats1 = (TPaveStats*)gr->GetListOfFunctions()->FindObject("stats");
    stats1->SetX1NDC(.6); 
    stats1->SetX2NDC(.85);
    stats1->SetY1NDC(0.7);
    stats1->SetY2NDC(0.4);

  }


  */



  if (escolha !="histograma") {


    //mg->Draw("PE"); // para plot polar
    mg->Draw("AC*"); //para plot normal

    if(escolha!="polar" && escolha!="polar_area"){
      vector<double> dim = Decisao[0]->Return_dims();
      mg->GetXaxis()->SetLimits(dim[0],dim[1]);
      mg->SetMinimum(dim[2]);
      mg->SetMaximum(dim[3]);

      c1->BuildLegend();//Legenda
    }
    c1->Update();
  }

  c1->Modified();
  c1->Print("plot.pdf");
  getchar();

  theApp.Terminate();

  
  for(int i=0;i<N;i++){
    delete Decisao[i];
    delete dados[i];
  }
  

  return 0;
}
