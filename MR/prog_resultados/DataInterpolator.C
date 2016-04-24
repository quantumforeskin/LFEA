#ifndef __DataInterpolator__
#include"DataInterpolator.h"
#define __DataInterpolator__ 1
#endif
#include"cFCgraphics.h"
#include<TGraph.h>
#include<TF1.h>
#include<iostream>
#include<cstdlib>
#include<sstream>
#include<cmath>
#include<TMath.h>
#include"EqSolver.h"
using namespace std;


double h=0.00000813;//variavel global, passo das derivadas numericas

/*
void DataInterpolator::LUdecomposition3(double *a3,double *b3, double *c3, int n){

  //Transformacao dos elementos a_k e b_k
  for(int k=1;k<n;k++){
    b3[k] = b3[k] -  a3[k-1]/b3[k-1]*c3[k-1];

    a3[k-1] = a3[k-1]/b3[k-1];

    }
  //Os elementos c_k permanecem inalterados
}

double* DataInterpolator::TridiagonalSolve(double *a3,double *b3, double *c3, double *B, int n){

  double* y = new double [n];
  double* x = new double [n];

   LUdecomposition3(a3,b3,c3,n);

  y[0] = B[0];

  for(int k=1;k<n;k++)
    y[k] = B[k] - a3[k-1]*y[k-1];
  
  x[n-1] = y[n-1]/b3[n-1];

  for(int k=n-2;k>=0;k--)
    x[k] = (y[k] - c3[k]*x[k+1])/b3[k];
 
  delete [] y;
  return x;
}
*/
DataInterpolator::DataInterpolator(int iN, double* ix, double* iy)
{
  N=iN;
  x=new double[N];
  y=new double[N];
  for(int i=0;i<N;i++){
    x[i]=ix[i];
    y[i]=iy[i];
  }
  cout<<endl;
  double s,d;
  int tester=0;
  for(int j=0;j<N;j++)//ordenar
    {
      s=x[j];
      for(int i=j;i<N;i++)
	if(s>x[i])
	  {
	    tester=1;
	    s=x[i];
	    x[i]=x[j];
	    x[j]=s;
	    d=y[j];
	    y[j]=y[i];
	    y[i]=d;	  
	      }
      if(tester==0)
	break;
      tester=0;  
    } 
}

TGraph* DataInterpolator::Draw(int N)
{
  TGraph *g=new TGraph(N,x,y);
  return g;
}
double* DataInterpolator::CubicSplineCurvatures(int N)//calcular K's, segundas derivadas
{
  double* K=new double[N];  
  K[0]=0.;
  K[N-1]=0.;
  
  double *a,*b,*c,*B;
  a=new double[N-3];
  b= new double[N-2];
  c=new double[N-3];
  B=new double[N-2];
  
  //coeficientes da matriz tridiagonal//
  for(int i=0;i<N-2;i++)
    b[i]=(x[i+1]-x[i]+(x[i+2]-x[i+1]))*2;

  for(int i=1;i<N-2;i++)
    a[i-1]=-(x[i]-x[i+1]);

  for(int i=0;i<N-2;i++)
    c[i]=-(x[i]-x[i+1]);
  /////////////////////////////////////
  for(int i=0;i<N-2;i++)
    B[i]=-6*((y[i+1]-y[i])/(x[i+1]-x[i])-(y[i+2]-y[i+1])/(x[i+2]-x[i+1]));
 
  EqSolver::LUdecomposition3(a,b,c,N-2);
  double *solution=EqSolver::LUsolve3(a,b,c,B,N-2);//resolver sistema linear de matriz tridiagonal
  for(int i=1;i<N-1;i++)
    K[i]=solution[i-1];

  for(int i=0;i<N;i++)
    cout<<"K["<<i<<"]="<<K[i]<<endl;
  
  delete [] a;
  delete [] b;
  delete [] c;
  delete [] B;
  return K;
}

double DataInterpolator::CubicSplineEvaluate(double *x, double *par)//funcao auxiliar de DataInterpolator::CubicSpline()
{
  double xx = x[0];
  int segment=0;
  int N=par[0];
  for(int i=0;i<N;i++)//descobrir segmento
    {
      if(xx>=par[i+1])
	if(xx<=par[i+2])
	  break;
      segment ++;
    } 
 
  double yi=par[N+segment+1];
  double yi1=par[N+segment+2];
  double xi=par[segment+1];
  double xi1=par[segment+2];
  double Ki=par[2*N+segment+1];
  double Ki1=par[2*N+segment+2];

  double A=yi/(xi-xi1)-Ki/6*(xi-xi1);
  double B=yi1/(xi-xi1)-Ki1/6*(xi-xi1);
  double f=1/((xi)-(xi1))*((Ki)/6*TMath::Power((xx-(xi1)),3)-(Ki1)/6*TMath::Power((xx-(xi)),3))+(A)*(xx-(xi1))-(B)*(xx-(xi));
  return f;
}
double DataInterpolator::CubicSplineEvaluate(double a, double *par)//funcao auxiliar de DataInterpolator::CubicSpline()
{
  double xx = a;
  int segment=0;
  int N=par[0];
  for(int i=0;i<N;i++)//descobrir segmento
    {
      if(xx>=par[i+1])
	if(xx<=par[i+2])
	  break;
      segment ++;
    } 
 
  double yi=par[N+segment+1];
  double yi1=par[N+segment+2];
  double xi=par[segment+1];
  double xi1=par[segment+2];
  double Ki=par[2*N+segment+1];
  double Ki1=par[2*N+segment+2];

  double A=yi/(xi-xi1)-Ki/6*(xi-xi1);
  double B=yi1/(xi-xi1)-Ki1/6*(xi-xi1);
  double f=1/((xi)-(xi1))*((Ki)/6*TMath::Power((xx-(xi1)),3)-(Ki1)/6*TMath::Power((xx-(xi)),3))+(A)*(xx-(xi1))-(B)*(xx-(xi));
  return f;
}

TF1* DataInterpolator::CubicSpline(double* K)//interpolaçao integra Cubic Spline em formato TF1
{
  
  TF1 *CS=new TF1("Testf",DataInterpolator::CubicSplineEvaluate,x[0],x[N-1],3*N+2);
  //colocaçao de parametros
  CS->SetParameter(0,N);
  for(int i=1;i<=N+1;i++)
    CS->SetParameter(i,x[i-1]);
  for(int i=N+1;i<=2*N+1;i++)
    CS->SetParameter(i,y[i-(N+1)]);
  for(int i=2*N+1;i<=3*N+1;i++)
    CS->SetParameter(i,K[i-(2*N+1)]);

  return CS;
}

TF1* DataInterpolator::CubicSplineSegment(double* K, double X)//retorna TF1 inicializado a partir da expressao
{
  TF1 *fs;
  int i;
  for(i=0;i<N-1;i++)//Descobrir segmento em causa
    if(X>=x[i])
      if(X<=x[i+1])
	break;
  string A;
  string B;
  string func;
  string xi,yi,xi1,yi1,Ki,Ki1;


  stringstream strs;

  strs<<y[i]/(x[i]-x[i+1])-K[i]/6*(x[i]-x[i+1]);
  A=strs.str();
  strs.str(string());
  strs.clear();

  strs<<y[i+1]/(x[i]-x[i+1])-K[i+1]/6*(x[i]-x[i+1]);
  B=strs.str();
  strs.str(string());
  strs.clear();

  strs<<x[i];
  xi=strs.str();
  strs.str(string());
  strs.clear();

  strs<<y[i];
  yi=strs.str();
  strs.str(string());
  strs.clear();

  strs<<y[i+1];
  yi1=strs.str();
  strs.str(string());
  strs.clear();

  strs<<x[i+1];
  xi1=strs.str();
  strs.str(string());
  strs.clear();

  strs<<K[i];
  Ki=strs.str();
  strs.str(string());
  strs.clear();

  strs<<K[i+1];
  Ki1=strs.str();
  strs.str(string());
  strs.clear();

  func="1/(("+xi+")-("+xi1+"))*(("+Ki+")/6*(x-("+xi1+"))^3-("+Ki1+")/6*(x-("+xi+"))^3)+("+A+")*(x-("+xi1+"))-("+B+")*(x-("+xi+"))";//expressao do segmento
  
  fs=new TF1("Segment",func.c_str(),x[i],x[i+1]);

  return fs;
}
double DataInterpolator::CubicSplineDeriv(double* K, double a)//returns CS'(a)
{
  int i=0;
  for(i=0;i<N-1;i++)//descobrir segmento
    if(a>=x[i])
      if(a<=x[i+1])
	break;

  double A=y[i]/(x[i]-x[i+1])-K[i]/6*(x[i]-x[i+1]);
  double B=y[i+1]/(x[i]-x[i+1])-K[i+1]/6*(x[i]-x[i+1]);
  return (1/(x[i]-x[i+1])*(K[i]/2*pow((a-x[i+1]),2)-K[i+1]/2*pow((a-x[i]),2))+A-B);
}

double DataInterpolator::CubicSplineDeriv(double a,double *par)//(static) returns CS'(a)
{
  int N=par[0];
  int segment=0;
  for(segment=0;segment<N-1;segment++)//descobrir segmento
    if(a>=par[1+segment])
      if(a<=par[2+segment])
	break;
  double yi=par[N+segment+1];
  double yi1=par[N+segment+2];
  double xi=par[segment+1];
  double xi1=par[segment+2];
  double Ki=par[2*N+segment+1];
  double Ki1=par[2*N+segment+2];
  double A=yi/(xi-xi1)-Ki/6*(xi-xi1);
  double B=yi1/(xi-xi1)-Ki1/6*(xi-xi1);

  return (1/(xi-xi1)*(Ki/2*pow((a-xi1),2)-Ki1/2*pow((a-xi),2))+A-B);
}

double DataInterpolator::CubicSplineEvaluate(double* K,double a)//returns CS(a)
{
  int i;
  for(i=0;i<N-1;i++)
    if(a>=x[i])
      if(a<=x[i+1])
	break;
  double A=y[i]/(x[i]-x[i+1])-K[i]/6*(x[i]-x[i+1]);
  double B=y[i+1]/(x[i]-x[i+1])-K[i+1]/6*(x[i]-x[i+1]);

  return 1/((x[i])-(x[i+1]))*((K[i])/6*pow((a-(x[i+1])),3)-(K[i+1])/6*pow((a-(x[i])),3))+(A)*(a-(x[i+1]))-(B)*(a-(x[i]));
}

double DataInterpolator::CubicSplineDerivN(double* K, double a)//returns numerical CS'(a)
{
  double deriv;
 
  int i=0;
  for(i=0;i<N-1;i++)
    if(a>=x[i])
      if(a<=x[i+1])
	break;
  
  deriv=1/(12*h)*((CubicSplineEvaluate(K,a-2*h)+8*CubicSplineEvaluate(K,a+h))-(8*CubicSplineEvaluate(K,a-h)+CubicSplineEvaluate(K,a+2*h)));  
  return deriv;
}

double DataInterpolator::CubicSplineDerivN(double a, double *par)//(static) returns numerical CS'(a)
{
 
  return 1/(12*h)*((CubicSplineEvaluate(a-2*h,par)+8*CubicSplineEvaluate(a+h,par))-(8*CubicSplineEvaluate(a-h,par)+CubicSplineEvaluate(a+2*h,par)));
}

TF1* DataInterpolator::Polynomial()//TF1 inicializado a partir da expressao do polinomio
{
  stringstream strs;//necessario para a passagem double->string
  string *li=new string[N+1];//array de strings 
  string *xs=new string[N];//array de string x[i]
  string *ys=new string[N];//array de strings y[i]
  string expression;//expressao final
  for(int i=0;i<N;i++)
    {
      strs<<y[i];
      ys[i]=strs.str();
      strs.str(string());
      strs.clear();

      strs<<x[i];
      xs[i]=strs.str();
      strs.str(string());
      strs.clear();
    }
  //escrever numerador de li
  for(int i=0;i<N;i++)
    {
      for(int j=0;j<N;j++){
	if(xs[j][0] =='-' && j!=i){
	  li[i]+="*(x";
	  string a=xs[j];
	  a[0]='+';
	  li[i]+=a;
	  li[i]+=")";
	}
	else if(j!=i){
	  li[i]+="*(x-";
	  li[i]+=xs[j];
	  li[i]+=")";
	}
      }
    }
  //escrever denominador de li
  for(int i=0;i<N;i++)
    {
      for(int j=0;j<N;j++){
	if(xs[j][0] =='-' && j!=i){
	  li[i]+="/(";	  

	  string a=xs[j];
	  if(xs[i]!="0"){
	    li[i]+=xs[i];
	    a[0]='+';
	  }
	  else 
	    a.erase(0,1);
	  if(xs[j]!="0")
	    li[i]+=a;
	  li[i]+=")";
	}
	else if(j!=i){
	  li[i]+="/(";
	  if(xs[i]!="0")
	    li[i]+=xs[i];
	  if(xs[j]!="0"){
	    li[i]+='-';
	    li[i]+=xs[j];
	  }
	  li[i]+=")";
	}
      }
    }
  //expressao final
  expression+=ys[0];
  expression+=li[0];
  for(int i=1;i<N;i++){
    expression+="+";
    expression+=ys[i];
    expression+=li[i];
  }
  delete [] li;
  delete [] xs;
  delete [] ys;

  return new TF1("LagrangeInterpolation",expression.c_str(),x[0],x[N-1]);
}

double DataInterpolator::PolynomialEvaluate(double a)//returns P(a)
{
  double l[N];
  for(int i=0;i<N;i++)
    {
      l[i]=1;
      //calcular numeradores de li 
      for(int j=0;j<N;j++)
	{
	  if(j!=i)
	    l[i]*=a-x[j];
	}
      //calcular denominadores
      for(int j=0;j<N;j++)
	{
	  if(j!=i)
	    l[i]/=x[i]-x[j];
	}
    }
  double total=0;
  for(int i=0;i<N;i++)
    total+=y[i]*l[i];

  return total;
}
double DataInterpolator::PolynomialEvaluate(double a,double *par)//returns P(a)
{
  int N=par[0];
  double l[N];
  for(int i=0;i<N;i++)
    {
      l[i]=1;
      //calcular numeradores de li 
      for(int j=0;j<N;j++)
	{
	  if(j!=i)
	    l[i]*=a-par[1+j];
	}
      //calcular denominadores
      for(int j=0;j<N;j++)
	{
	  if(j!=i)
	    l[i]/=par[1+i]-par[1+j];
	}
    }
  double total=0;
  for(int i=0;i<N;i++)
    total+=par[N+1+i]*l[i];

  return total;

}


double DataInterpolator::PolynomialDerivN(double X)
{
  return 1/(12*h)*((PolynomialEvaluate(X-2*h)+8*PolynomialEvaluate(X+h))-(8*PolynomialEvaluate(X-h)+PolynomialEvaluate(X+2*h)));
}

double DataInterpolator::PolynomialDerivN(double a, double *par)
{
  return 1/(12*h)*((PolynomialEvaluate(a-2*h,par)+8*PolynomialEvaluate(a+h,par))-(8*PolynomialEvaluate(a-h,par)+PolynomialEvaluate(a+2*h,par)));
}

double DataInterpolator::DifCubicPolynomial(double x[], double par[])//funcao auxiliar de DifCP()
{
  return CubicSplineEvaluate(x[0],par)-PolynomialEvaluate(x[0],par);;
}

TF1* DataInterpolator::DifCubicPolynomial(double *K)
{
 TF1 *CP=new TF1("DifCP",DifCubicPolynomial,x[0],x[N-1],3*N+2);
  CP->SetParameter(0,N);
  for(int i=1;i<=N+1;i++)
    CP->SetParameter(i,x[i-1]);
  for(int i=N+1;i<=2*N+1;i++)
    CP->SetParameter(i,y[i-(N+1)]);
  for(int i=2*N+1;i<=3*N+1;i++)
    CP->SetParameter(i,K[i-(2*N+1)]);

  return CP;
}

Double_t DataInterpolator::DifCubicDeriv(Double_t x[], Double_t par[])//funcao auxiliar de DataInterpolator::CubicSpline()
{
  double a=x[0];
  return CubicSplineDeriv(a,par)-CubicSplineDerivN(a,par);
}



TF1* DataInterpolator::DifCubicDeriv(double *K)
{
  TF1 *CD;
  CD=new TF1("DifCubicDeriv",DifCubicDeriv,x[0],x[N-1],3*N+2);
  CD->SetParameter(0,N);
  for(int i=1;i<=N+1;i++)
    CD->SetParameter(i,x[i-1]);
  for(int i=N+1;i<=2*N+1;i++)
    CD->SetParameter(i,y[i-(N+1)]);
  for(int i=2*N+1;i<=3*N+1;i++)
    CD->SetParameter(i,K[i-(2*N+1)]);
  return CD;
}

double DataInterpolator::DifCubicPolynomialDeriv(double x[], double par[])
{
  return CubicSplineDerivN(x[0],par)-PolynomialDerivN(x[0],par);
}

TF1* DataInterpolator::DifCubicPolynomialDeriv(double *K)
{
  TF1 *CPD;
  CPD=new TF1("DifCubicDeriv",DifCubicPolynomialDeriv,x[0],x[N-1],3*N+2);
  CPD->SetParameter(0,N);
  for(int i=1;i<=N+1;i++)
    CPD->SetParameter(i,x[i-1]);
  for(int i=N+1;i<=2*N+1;i++)
    CPD->SetParameter(i,y[i-(N+1)]);
  for(int i=2*N+1;i<=3*N+1;i++)
    CPD->SetParameter(i,K[i-(2*N+1)]);
  return CPD;
}
