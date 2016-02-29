#include "Opt.h"
#include "fstream"
#include "TF1.h"
#include "TStyle.h"
#include <cstdlib>
#include <iostream>

using namespace std;
//merdas

//Construtor
Opt::Opt(string fparam, string fdados)
{
  string dim1,dim2,dim3,dim4;
  ficheiro = fparam;
  dados = fdados;
  ifstream det(fparam.c_str());
  if (det.is_open())
  {
    det.ignore(256,':');
    getline(det,opcao);
    det.ignore(256,':');
    getline(det,titulo);
    det.ignore(256,':');
    getline(det,func);
    det.ignore(256,':');
    getline(det,dim1);
    det.ignore(256,':');
    getline(det,dim2);
    det.ignore(256,':');
    getline(det,dim3);
    det.ignore(256,':');
    getline(det,dim4);
    det.ignore(256,':');
    getline(det,numbin);
  }
  cout << opcao << "  BATATA" << endl;

  det.close();
  dim.push_back(atof(dim1.c_str()));
  dim.push_back(atof(dim2.c_str()));
  dim.push_back(atof(dim3.c_str()));
  dim.push_back(atof(dim4.c_str()));

  cout << "O ficheiro de parametros e " << ficheiro << " e a opcao e " << opcao << endl;
}


//Decide, baseado na opcao, que grafico fazer; Chama funcao adequada
vector<string> Opt::Escolher()
{
  cout << opcao << endl;
  if ( (opcao!="fit") & (opcao!="grafico") & (opcao!="histograma") )
  {
    opcao.clear();
    cout << "opcao invalida. adeus" << endl;
  }

  mainsender.push_back(opcao);
  mainsender.push_back(titulo);
  return mainsender;
}


//Faz um ajuste
TGraphErrors* Opt::Ajuste(TGraphErrors* gr1)
{
  cout << "Eu quero fazer um ajuste e jame deixam." << endl;

  TF1 *f1 = new TF1("f1",func.c_str());
  f1->SetLineColor(kBlue);
  f1->SetLineWidth(2);

  f1->SetParameters(-0.001,-0.5);
  //f1->SetParameters(1,0.001,8000,118.,10);
  //f1->SetParLimits(4,0,100000);
  //f1->SetParLimits(3,95.,110.);
  //gr1->Fit("f1","MF","",110.,121.);
  gr1->Fit("f1","MF");

  gr1->SetMarkerColor(kRed);
  gr1->SetMarkerStyle(7);
  gr1->SetLineColor(kBlack);

  cout << gr1->GetErrorY(0) << " " << gr1->GetErrorY(1) << " " << gr1->GetErrorY(2) << " " << gr1->GetErrorY(3) << endl;
  cout << gr1->GetErrorX(0) << " " << gr1->GetErrorX(1) << " " << gr1->GetErrorX(2) << " " << gr1->GetErrorX(3) << endl;

 
 
}


//Faz um grafico
TGraphErrors* Opt::Grafico()
{
  cout << "Eu quero fazer um grafico e ja consigo!" << endl;
  //int n=5;
  TGraphErrors *gr1 = new TGraphErrors(dados.c_str(),"%lg %lg %lg %lg");
  //Double_t x[n] = {1,2,3,4,5};
  //Double_t y[n] = {2,3,1,5,4};
  //Double_t ex[n] = {0.1,0.2,0.3,0.4,0.5};
  //Double_t ey[n] = {0.1,0.2,0.3,0.4,0.5};

  //TGraphErrors *gr1 = new TGraphErrors(n,x,y,ex,ey);

  gr1->SetName("gr1");
  gr1->SetTitle("graph 1");
  gr1->SetMarkerStyle(6);
  gr1->SetMarkerColor(kBlack);
  gr1->SetLineWidth(3);

  gr1->SetLineColor(1);
  gr1->SetLineWidth(0.5);
  gr1->SetFillStyle(1);

  gr1->SetFillColor(kBlack);

  gr1->GetXaxis()->SetLimits(dim[0],dim[1]);
  gr1->GetYaxis()->SetLimits(dim[2],dim[3]);
  //gr1->SetMinimum(dim[2]);
  //gr1->SetMaximum(dim[3]);


  return gr1;
}


//Faz um histograma
TH1F* Opt::Histograma()
{
  ifstream data(dados.c_str());
  cout << "Eu quero fazer um histograma e ja me deixam." << endl;
  TH1F *hist = new TH1F("Stats",titulo.c_str(),atof(numbin.c_str()),dim[0],dim[1]);
  
  vector<double> erros;
  //while(data.eof()==false)
  for (int i=0; i<50;i++)
  {
    string point;
    getline(data,point);
    hist->Fill(atof(point.c_str()));
    cout << point << endl;
  }

  for (int i=0; i<atof(numbin.c_str()); i++)
  {
    erros.push_back(hist->GetBinError(i));
  }

  cout << hist->Integral() << endl;
  //hist->Scale(1/hist->Integral());
  hist->Scale(1/25.);
  TF1 *f1 = new TF1("f1",func.c_str());
  f1->SetParameters(1,0.01);
  //hist->Fit("f1","EMF");
  for (int i=0; i<atof(numbin.c_str()); i++)
  {
    cout << "Erros" << endl;
    cout << erros[i] << " " << hist->GetBinError(i) << " " << erros[i]/25. << endl;
    hist->SetBinError(i,erros[i]/25.);
  }
  hist->Fit("f1","EMF");
  //gfit->GetNDF();
  //cout << "Qui-quadrado: " << hist->Chisqdf(f1) << endl;

  data.close();

  return hist;


}


vector<double> Opt::Return_dims()
{
  return dim;
}
