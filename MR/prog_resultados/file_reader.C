#include "file_reader.h"
#include<iostream>
#include<fstream>

using namespace std;


int fr::getN(string file1){


  ifstream file;
  file.open (file1.c_str());

  N=0;
  
  char cur = '\0';
  char last = '\0';

  while (file.get(cur)) {
      if (cur == '\n' ||
          (cur == '\f' && last == '\r'))
         N++;
  }

  return N;

}



double* fr::getH(string file1, double I){

  double eI=0.0000001;//erro corrente
  double eV = 0.000001; //erro tensao
  double eh = 0.1;//erro campo

  ifstream file;
  file.open (file1.c_str());

  
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

  delete [] R;
  delete [] eR;

  return H;

}

double* fr::getR(string file1, double I){

  double eI=0.0000001;//erro corrente
  double eV = 0.000001; //erro tensao
  double eh = 0.1;//erro campo

  ifstream file;
  file.open (file1.c_str());

  
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
      i++; 


      if(i>=N)
	test=1;

    }

  delete [] H;
  delete [] eR;

  return R;

}

double* fr::get_eR(string file1, double I){

  double eI=0.0000001;//erro corrente
  double eV = 0.000001; //erro tensao
  double eh = 0.1;//erro campo

  ifstream file;
  file.open (file1.c_str());

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
      i++; 


      if(i>=N)
	test=1;

    }

  delete [] R;
  delete [] H;

  return eR;

}
