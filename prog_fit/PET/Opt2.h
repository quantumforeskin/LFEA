#include "TGraphErrors.h"
#include "TGraphPolar.h" 
#include "TH1F.h"
#include "TNamed.h"
#include <vector>
#include <cstdlib>

#include <string>
#include <iostream>

using namespace std;

class Opt
{
  public:
    Opt(string, string);
    vector<string> Escolher();
    TH1F* Histograma();
    void Ajuste(TGraphErrors* gr);
    TGraphPolar* GraficoPolar(int);
    TGraphPolar* GraficoPolarArea(int);
    TGraphErrors* Grafico(int color);
    vector<double> Return_dims();

  private:
    string ficheiro;
    string dados;
    string opcao;
    string func;
    string titulo;
    vector<double> dim;
    vector<string> mainsender;
    string numbin;
};
