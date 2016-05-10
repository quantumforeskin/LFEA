#include "TROOT.h"
#include "TFrame.h" //gClient
#include "TCanvas.h"
#include "TPad.h"
#include "TSystem.h"
#include <TList.h>
#include "TApplication.h"
#include "TVirtualX.h"
#include "TF1.h"
#include "TGraphErrors.h"
#include "TMultiGraph.h"
#include <cmath>
#include <iostream>
#include "TPaveStats.h"
#include "TStyle.h"
#include "TLegend.h"
#include "TAxis.h"
#include "TH1F.h"
#include "TLatex.h"
using namespace std;
#include <unistd.h>

int main(int argc, char **argv) {
  //faz aparecer o canvas
  TApplication theApp("App", &argc, argv);
 
  //box com resultados do fit
  gStyle->SetOptFit();
  //settings do canvas  
  TCanvas *c1 = new TCanvas("c1","Nome",200,10,700,500);
  c1->SetFillColor(0);
  c1->SetGrid();
  c1->GetFrame()->SetFillColor(21);
  c1->GetFrame()->SetBorderSize(12);

  //Definir multiplos graficos num canvas
  TMultiGraph *mg = new TMultiGraph("mg","mg");
   mg->SetTitle(";H(Oe);R(#Omega)");
 
 
 
 
  //grafico 1
  TGraphErrors *gr1 = new TGraphErrors("data1.txt","%lg %lg %lg");
  gr1->SetName("gr1");
  gr1->SetTitle("graph 1");
  gr1->SetMarkerStyle(1);
  gr1->SetLineColor(kPink+10);

  //por L e comentar o fit e o stat do fit correspondete -> pa desenhar linha a unir pontos
  gr1->SetDrawOption("AP");
  //Com opçao L define a cor da linha que une os pontos, e a cor das barras de erro
  gr1->SetLineWidth(1);
  gr1->SetFillStyle(0);
  //funcao a fittar
  // TF1 *f1 = new TF1("f1", "[1] * x  + [0]");
  // f1->SetLineColor(kBlue);
  // gr1->Fit("f1","EMF");
   mg->Add(gr1);

 TGraphErrors *gr2 = new TGraphErrors("data2.txt"," %lg %lg %lg");
  gr2->SetName("gr2");
  gr2->SetTitle("graph 2");
  gr2->SetMarkerStyle(1);
  gr2->SetLineColor(kRed);

  //por L e comentar o fit e o stat do fit correspondete -> pa desenhar linha a unir pontos
  gr2->SetDrawOption("AP");
  //Com opçao L define a cor da linha que une os pontos, e a cor das barras de erro
  gr2->SetLineWidth(1);
  gr2->SetFillStyle(0);
  //funcao a fittar
  // TF1 *f1 = new TF1("f1", "[1] * x  + [0]");
  // f1->SetLineColor(kBlue);
  // gr1->Fit("f1","EMF");
   mg->Add(gr2);

    TGraphErrors *gr3 = new TGraphErrors("data3.txt","%lg %lg %lg");
  gr3->SetName("gr3");
  gr3->SetTitle("graph 3");
  gr3->SetMarkerStyle(1);
  gr3->SetLineColor(kOrange+10);

  //por L e comentar o fit e o stat do fit correspondete -> pa desenhar linha a unir pontos
  gr3->SetDrawOption("AP");
  //Com opçao L define a cor da linha que une os pontos, e a cor das barras de erro
  gr3->SetLineWidth(1);
  gr3->SetFillStyle(0);
  //funcao a fittar
  // TF1 *f1 = new TF1("f1", "[1] * x  + [0]");
  // f1->SetLineColor(kBlue);
  // gr1->Fit("f1","EMF");
   mg->Add(gr3);

   TGraphErrors *gr4 = new TGraphErrors("data4.txt"," %lg %lg %lg");
  gr4->SetName("gr4");
  gr4->SetTitle("graph 4");
  gr4->SetMarkerStyle(1);
  gr4->SetLineColor(kOrange+4);

  //por L e comentar o fit e o stat do fit correspondete -> pa desenhar linha a unir pontos
  gr4->SetDrawOption("AP");
  //Com opçao L define a cor da linha que une os pontos, e a cor das barras de erro
  gr4->SetLineWidth(1);
  gr4->SetFillStyle(0);
  //funcao a fittar
  // TF1 *f1 = new TF1("f1", "[1] * x  + [0]");
  // f1->SetLineColor(kBlue);
  // gr1->Fit("f1","EMF");
   mg->Add(gr4);

   TGraphErrors *gr5 = new TGraphErrors("data5.txt"," %lg %lg %lg");
  gr5->SetName("gr5");
  gr5->SetTitle("graph 5");
  gr5->SetMarkerStyle(1);
  gr5->SetLineColor(kYellow);

  //por L e comentar o fit e o stat do fit correspondete -> pa desenhar linha a unir pontos
  gr5->SetDrawOption("AP");
  //Com opçao L define a cor da linha que une os pontos, e a cor das barras de erro
  gr5->SetLineWidth(1);
  gr5->SetFillStyle(0);
  //funcao a fittar
  // TF1 *f1 = new TF1("f1", "[1] * x  + [0]");
  // f1->SetLineColor(kBlue);
  // gr1->Fit("f1","EMF");
   mg->Add(gr5);

      TGraphErrors *gr6 = new TGraphErrors("data6.txt"," %lg %lg %lg");
  gr6->SetName("gr6");
  gr6->SetTitle("graph 6");
  gr6->SetMarkerStyle(1);
  gr6->SetLineColor(kYellow+3);

  //por L e comentar o fit e o stat do fit correspondete -> pa desenhar linha a unir pontos
  gr6->SetDrawOption("AP");
  //Com opçao L define a cor da linha que une os pontos, e a cor das barras de erro
  gr6->SetLineWidth(1);
  gr6->SetFillStyle(0);
  //funcao a fittar
  // TF1 *f1 = new TF1("f1", "[1] * x  + [0]");
  // f1->SetLineColor(kBlue);
  // gr1->Fit("f1","EMF");
   mg->Add(gr6);

   TGraphErrors *gr7 = new TGraphErrors("data7.txt"," %lg %lg %lg");
  gr7->SetName("gr7");
  gr7->SetTitle("graph 7");
  gr7->SetMarkerStyle(1);
  gr7->SetLineColor(kSpring);

  //por L e comentar o fit e o stat do fit correspondete -> pa desenhar linha a unir pontos
  gr7->SetDrawOption("AP");
  //Com opçao L define a cor da linha que une os pontos, e a cor das barras de erro
  gr7->SetLineWidth(1);
  gr7->SetFillStyle(0);
  //funcao a fittar
  // TF1 *f1 = new TF1("f1", "[1] * x  + [0]");
  // f1->SetLineColor(kBlue);
  // gr1->Fit("f1","EMF");
   mg->Add(gr7);

   TGraphErrors *gr8 = new TGraphErrors("data8.txt"," %lg %lg %lg");
  gr8->SetName("gr8");
  gr8->SetTitle("graph 8");
  gr8->SetMarkerStyle(1);
  gr8->SetLineColor(kGreen+3);

  //por L e comentar o fit e o stat do fit correspondete -> pa desenhar linha a unir pontos
  gr8->SetDrawOption("AP");
  //Com opçao L define a cor da linha que une os pontos, e a cor das barras de erro
  gr8->SetLineWidth(1);
  gr8->SetFillStyle(0);
  //funcao a fittar
  // TF1 *f1 = new TF1("f1", "[1] * x  + [0]");
  // f1->SetLineColor(kBlue);
  // gr1->Fit("f1","EMF");
   mg->Add(gr8);




 
  //Draws, prints e updates no canvas
  mg->Draw("AP");

 
 c1->Update();

  //legenda
  // posiçao legenda (x,y) -> primeiro argumento x, ultimo argumento y
     TLegend *leg = new TLegend(0.9,0.75,0.75,0.9);
  //argumentos add entry 
  //  L: draw line associated with TAttLine if obj inherits from TAttLine
  // P: draw polymarker associated with TAttMarker if obj inherits from TAttMarker
  // F: draw a box with fill associated wit TAttFill if obj inherits TAttFill
  //  E: draw vertical error bar 

 //   leg->SetHeader("Legenda");
  leg->AddEntry("gr1","FA d=0cm #rightarrow ","lep");
  leg->AddEntry("gr2","FA d=2cm  #leftarrow","lep");
 leg->AddEntry("gr3","FA d=3cm #rightarrow","lep");
 leg->AddEntry("gr4","FA d=4cm #leftarrow","lep");
   leg->AddEntry("gr5","FB d=0cm #rightarrow ","lep");
  leg->AddEntry("gr6","FB d=2cm  #rightarrow","lep");
 leg->AddEntry("gr7","FB d=3cm #rightarrow","lep");
 leg->AddEntry("gr8","FB d=4cm #leftarrow","lep");
 
 
    leg->Draw();

  //box com resultados do fit
  // TPaveStats *stats1 = (TPaveStats*)gr1->GetListOfFunctions()->FindObject("stats");
  //  TPaveStats *stats2 = (TPaveStats*)gr2->GetListOfFunctions()->FindObject("stats");
  //stats1->SetTextColor(kBlue); 
  // stats2->SetTextColor(kRed); 
  // stats1->SetX1NDC(0.12); stats1->SetX2NDC(0.32); stats1->SetY1NDC(0.75);
  // stats2->SetX1NDC(0.52); stats2->SetX2NDC(0.72); stats2->SetY1NDC(0.78);
  c1->Modified();
 

  c1->Print("plot.pdf");
  getchar();
  return 0;
}
