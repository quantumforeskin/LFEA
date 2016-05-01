#include "EqSolver.h"
#include <cmath>
#include <iostream>
#include <cstdio>

using namespace std;


EqSolver::EqSolver(){

  dim = 0;

  mexist = 0;
  bexist = 0;
  Uexist = 0;
  Lexist = 0; //Ainda nao foi alocado espaco para a matriz m e para o vetor b, por isso esse espaco pode ser alocado na primeira funcao que for utilizada*/


}

void EqSolver::SwapRows(int row1, int row2, double **M,int n){

  double a;

  //Aqui estou a admitir que o utilizador poe a ordem da linha a partir de 1 e nao de 0.

  if(row1 < n+1 && row1 > 0 && row2 < n+1 && row2 > 0){
    for (int i=0;i<n;i++){

      a = M[row1-1][i];
      M[row1-1][i] = M[row2-1][i];
      M[row2-1][i] = a;

    }

  }else{
    cout << "As linhas que pretende trocar nao existem na matriz" << endl;
  }


}

void EqSolver::GaussElimination(double **M, double *B, int n){

  int j, rvalor;
  double rteste;
  double a;
  double saux;
  double *s = new double [n];
  double r[n];

  //Criacao da matriz m cujos valores vao ser iguais aos da matriz M. Nao basta fazer simplesmente m = M pois o objetivo e nao alterar o conteudo da matriz M

  if(mexist == 0){
    m = new double *[n];

    for(int i=0;i<n;i++)
      m[i] = new double [n];

    mexist = 1;
  }

  for(int i=0;i<n;i++)
    for(int it=0;it<n;it++)
      m[i][it] = M[i][it];

  //O mesmo para o array b

  if(bexist == 0){
    b = new double [n];
    bexist = 1;
  }

  for(int i=0;i<n;i++)
    b[i] = B[i];

  dim = n;
  decision = 0;//Queremos apenas fazer o delete da matriz m e do vetor b


  for(int i=0;i<n;i++)
    r[i] = 0;

   ////// Vetor s
    j = 0;
  for(int i=0; i<n; i++){
    saux = m[i][j];

   for(j=0;j<n-1;j++){
     if(saux < m[i][j+1]){
       saux = m[i][j+1];
     }else{
       //o a mantem-se
     }

   }

   s[i] = saux;
  
   }

  /////////////////////////////////////////////////////////
  
  ///////Inicio do loop

  for(int t=0;t < n-1; t++){

    ////////////Pesos relativos
    rteste = 0;
    for(int j=t;j < n; j++){

      r[j] = abs(m[j][t]/s[j]);

      if(rteste >= r[j]){
	//nao faz nada pois o rteste e rvalor se mantem
      }else{
	rteste = r[j];
	rvalor = j;
      }

    }

    ////Se todos os pesos forem muito pequenos a matriz e praticamente nao singular
    if(rteste < 0.0001){
      cout << "A matriz e singular" << rteste << endl;
      break;
    }//O rteste ja esta em modulo. VER DEPOIS A TOLERANCIA!


    //Trocas na matriz:
    //So queremos que hajam trocas de linhas se o elemento de maior peso nao for o pivot
  
    EqSolver Sl;

    if(rvalor != t)
      Sl.SwapRows(t+1,rvalor+1,m,n);

    //Trocas no vetor b:

    double troca = b[t];//Nao esquecer que e DOUBLE E NAO INT!!!
    b[t] = b[rvalor];
    b[rvalor] = troca;


    ///Fase da eliminacao
    //////////////////////////////////////////

    for(int j=t+1;j<n;j++){
  
      //if (matrix.mvec[t].entries[t]==0)  
      a = m[j][t]/m[t][t];

      b[j] = b[j] - b[t]*a;//operacoes no vetor b

      for(int i=t;i<n;i++){

        m[j][i] = m[j][i] - m[t][i]*a;

       }

    }

  }

  delete [] s;



}

double* EqSolver::GaussEliminationSolver(){

  double *x = new double [dim];
  double sum;

  x[dim-1] = b[dim-1]/m[dim-1][dim-1];

  for(int k=dim-1;k>=0;k--){
    sum = 0;
    for(int j=k+1;j<dim;j++)
      sum += m[k][j] * x[j];

    x[k] = (b[k] - sum)/m[k][k];
  }
  /////Temos a nossa solucao - o vetor x

  return x;

}

void EqSolver::LUdecomposition3(double *a3,double *b3, double *c3, int n){

  //Transformacao dos elementos a_k e b_k
  for(int k=1;k<n;k++){
    b3[k] = b3[k] -  a3[k-1]/b3[k-1]*c3[k-1];

    a3[k-1] = a3[k-1]/b3[k-1];

    }
  //Os elementos c_k permanecem inalterados
}
void EqSolver::LUdecomposition3(float *a3,float *b3, float *c3, int n){

  //Transformacao dos elementos a_k e b_k
  for(int k=1;k<n;k++){
    b3[k] = b3[k] -  a3[k-1]/b3[k-1]*c3[k-1];

    a3[k-1] = a3[k-1]/b3[k-1];

    }
  //Os elementos c_k permanecem inalterados
}


double* EqSolver::LUsolve3(double *a3,double *b3, double *c3, double *B, int n){

  double* y = new double [n];
  double* x = new double [n];

  y[0] = B[0];

  for(int k=1;k<n;k++)
    y[k] = B[k] - a3[k-1]*y[k-1];
  

  x[n-1] = y[n-1]/b3[n-1];

  for(int k=n-2;k>=0;k--)
    x[k] = (y[k] - c3[k]*x[k+1])/b3[k];
  


  delete [] y;

  return x;

}
float* EqSolver::LUsolve3(float *a3,float *b3, float *c3, float *B, int n){

  float* y = new float [n];
  float* x = new float [n];

  y[0] = B[0];

  for(int k=1;k<n;k++)
    y[k] = B[k] - a3[k-1]*y[k-1];
  

  x[n-1] = y[n-1]/b3[n-1];

  for(int k=n-2;k>=0;k--)
    x[k] = (y[k] - c3[k]*x[k+1])/b3[k];
  


  delete [] y;

  return x;

}
EqSolver::~EqSolver(){

  for (int i=0;i<dim;i++)//a matriz m e utilizada em todas as funcoes
    delete [] m[i];

  if(decision==1){  
    for (int i=0;i<dim;i++)
      delete [] L[i];

    for (int i=0;i<dim;i++)
      delete [] U[i];
  }

  if(dim!=0 && decision==1)
    delete [] b;

}
