#include "Opt2.h"
#include "fstream"
#include "TF1.h"
#include "TStyle.h"
#include "TMath.h"
#include <cstdlib>
#include <iostream>

using namespace std;
//merdas



double to_rad(double a){

  return a*3.14159265359/180;

}//da jeito


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
  if ( (opcao!="fit") & (opcao!="grafico") & (opcao!="histograma")&(opcao!="polar") & (opcao!="polar_area") )
  {
    opcao.clear();
    cout << "opcao invalida. adeus" << endl;
  }

  mainsender.push_back(opcao);
  mainsender.push_back(titulo);
  return mainsender;
}


TGraphPolar* Opt::GraficoPolar(int color){


	string data_array[37][4]; //You can make it dynamic to handle as much as the file has
	ifstream in_file(dados.c_str(), ios::binary);
	//Check if the file is open
	if(!in_file.is_open()){
		cout << "File not opened..." << endl;
	}
	//read the file (two columns) to the array
	for(int i=0; !in_file.eof(); i++){
		in_file >> data_array[i][0];
		in_file >> data_array[i][1];
		in_file >> data_array[i][2];
		in_file >> data_array[i][3];
	}
	
	//Display the array
	static int N=36;
	double col1[N];
	double col2[N];
	double col3[N];
	double col4[N];
	for(Int_t i=0; i<N; i++){
	  col1[i]=atof(data_array[i][0].c_str())*TMath::Pi()/180;
	  col2[i]=atof(data_array[i][1].c_str());
	  //<< col1[i] << "  " << col2[i] << endl;
	  col3[i]=atof(data_array[i][2].c_str())*TMath::Pi()/180;
	  col4[i]=atof(data_array[i][3].c_str());
	}
    TGraphPolar * grP1 = new TGraphPolar(N,col1,col2,col3,col4);
    grP1->SetLineColor(2);
    grP1->SetMarkerStyle(20);
    grP1->SetMarkerSize(0.75);
    grP1->SetMarkerColor(color+2);
    grP1->SetLineWidth(2);
    grP1->SetMaximum(10);
    return grP1;

}

//Faz um ajuste
void Opt::Ajuste(TGraphErrors* gr1)
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
TGraphErrors* Opt::Grafico(int color)
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

  gr1->SetLineColor(color);
  gr1->SetLineWidth(0.5);
  gr1->SetFillStyle(1);

  gr1->SetFillColor(kBlack);

  gr1->GetXaxis()->SetLimits(dim[0],dim[1]);
  gr1->GetYaxis()->SetLimits(dim[2],dim[3]);
  //gr1->SetMinimum(dim[2]);
  //gr1->SetMaximum(dim[3]);


  return gr1;

  /*
  ////////Grafico Polar//////////////////////////////
   Double_t rmin=0;
   Double_t rmax=3.1415*2;
   Double_t r[1000];
   Double_t theta[1000];
   TF1 * fp1 = new TF1("fplot","cos(x)",rmin,rmax);
   for (Int_t ipt = 0; ipt < 1000; ipt++) {
      r[ipt] = ipt*(rmax-rmin)/1000+rmin;
      theta[ipt] = fp1->Eval(r[ipt]);
   }
   TGraphPolar * grP1 = new TGraphPolar(1000,r,theta);
   cout << dados.c_str(), "%lg " << endl;
   grP1->SetLineColor(color);
   return grP1;
  */

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


TGraphPolar* Opt::GraficoPolarArea(int color){

  double r1=2.54;
  double r2=3.81;

  //Recta 1
  double a1u=to_rad(10);
  double a2u=to_rad(30);

  //declive da reta  y = mu*x + c
  double mu=(r2*sin(a2u) - r1*sin(a1u))/(r2*cos(a2u) - r1*cos(a1u));
  double cu = r2*sin(a2u) - mu*r2*cos(a2u);

  //Para coord polares
  double x0 = -cu/mu; //interseccao da reta com y=0
  double theta_x0 = atan(mu);//angulo da reta em relacao ao ponto x0

  static int N=10;
  Double_t theta[N];
  Double_t r[N];
  Double_t etheta[N];
  Double_t er[N];

  theta[0]=0;
  r[0]=x0;
  etheta[0]=0;
  r[0]=x0/10;

  int i=1;
  double dx=0;
  while(i<N){
    dx+=0.1;
    double x = x0+dx;
    double y = mu*x+cu;
    double theta_0 = atan(y/(x0+y/tan(theta_x0))); //angulo da reta em relacao a origem do ref polar
    double r_0 = y/sin(theta_0);
    theta[i] = theta_0;
    etheta[i] = theta_0/10;
    cout << theta[i] << endl;
    r[i] = r_0;
    er[i] = r_0/100;
    i++;
  }
  TGraphPolar * grP1 = new TGraphPolar(N,theta,r,etheta,er);
    grP1->SetLineColor(2);
    grP1->SetMarkerStyle(8);
    grP1->SetMarkerSize(0.45);
    grP1->SetMarkerColor(color+2);
    grP1->SetLineWidth(2);
    return grP1;

}
