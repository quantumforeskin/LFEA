#include<TGraph.h>
#include<TF1.h>
#ifndef __DataInterpolator__
#define __DataInterpolator__ 1
#endif
#include<iostream>
using namespace std;

class DataInterpolator {
 public:
  // N data points
  DataInterpolator(int iN, double* ix, double* iy);

  TGraph* Draw(int); //draw points
  
  static void LUdecomposition3(double *,double *,double *,int);//funcao auxiliar de TridiagonalSolve
  static double* TridiagonalSolve(double *,double *,double *,double* ,int);//resolve sistema de matriz tridiagonal
  double* CubicSplineCurvatures(int); // return k’s

  static double CubicSplineEvaluate(double *xins, double *par);//funçao auxiliar, retorna valor num ponto 
  static double CubicSplineEvaluate(double a, double *par);
  double CubicSplineEvaluate(double* K, double a);//valor no ponto a

  TF1* CubicSpline(double* k); // k=input curvatureclass 
 
  TF1* CubicSplineSegment(double* k, double x); // retorna segmento de Splines Cubicos

  double CubicSplineDeriv(double* k, double a); // Derivada exacta no ponto a
  static double CubicSplineDeriv(double a,double *par);//x,array de parametros com p[0]=N
  double CubicSplineDerivN(double* k, double a);//Derivada numerica no ponto a, h=10e-6
  static double CubicSplineDerivN(double a,double *par);//x, array de parametros com p[0]=N,h=10e-6
 
  
  //polynomial
  TF1* Polynomial();//retorna interpolaçao polinomial P(x) pelo metodo de Lagrange
  double PolynomialEvaluate(double a);//retorna P(a)
  static double PolynomialEvaluate(double a,double *par);//funçao auxiliar, retorna P(a)
  double PolynomialDerivN(double a);//retorna derivada numerica P'(a)
  static double PolynomialDerivN(double a,double *par);//funçao auxiliar, retorna derivada numerica P'(a)

  //metodos extra ultimas alineas
  static double DifCubicPolynomial(double *,double*);//funçao auxiliar
  TF1* DifCubicPolynomial(double *K);//retorna funcao diferenca Cubicspline-Polynomial



  TF1* DifCubicDeriv(double *K);//retorna funçao diferenca da derivada numerica vs derivada exacta da Interpolaçao por Splines Cubicos
  static double DifCubicDeriv(double *functorx,double *par);//funçao auxiliar, valor da diferença num ponto a


  TF1* DifCubicPolynomialDeriv(double *K);//retorna funçao diferença da funçao cubic Spline vs interpolacao polinomial
  static double DifCubicPolynomialDeriv(double *,double *);
 

  //destructor
  ~DataInterpolator(){delete []x;delete[] y;};

 private:
  double *x;
  double *y;
  int N;
};
