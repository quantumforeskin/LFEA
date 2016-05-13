#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;


int main(){


  ///Definem-se todas as unidades em cm


  float Lx=55.4;//comprimento de S1
  float Ly=43.9;//largura de S1
  float lx=41; //largura do bloco
  float ly=40.9; //comprimento do bloco
  float eS1=2.05; //espessura de S1
  float eB=9.7; // espessura do bloco 


 srand (time(NULL));



for(int j=0;j<1;j++){

  int events=0;
  int totalevents=0;

  for(int i=0;i<1000;i++){

  float u = ((double) rand() / (RAND_MAX));


  float th = acos(pow(1-u,1/3.));



  ///Gero aleatorios segundo pdf para theta e em distribuicao uniforme para fi e (x,y)

  //Fixo a altura do bloco em z=0



  //Gerar ponto (x,y,0) arbitrario na superficie do bloco
  float x = ((double) rand() / (RAND_MAX))*lx - lx/2;
  float y = ((double) rand() / (RAND_MAX))*ly - ly/2;



  //Gerar angulo fi para obter direccao completa do muao (th,fi)
  float fi = ((double) rand() / (RAND_MAX))*2*M_PI;

  //gero agora vetor unitario segundo a direcao (th,fi)

  float v[2];

  v[0] = cos(fi)*sin(th);
  v[1] = sin(fi)*sin(th);


  float s = 56.6;//posiçao z de S2

  
  float t=s/cos(th); // parametro da parametrizacao


  x = x + t*v[0]; //Abcissa do ponto a altura de S1 que segue a direçao de v
  y = y + t*v[1];

  if(x>-Lx/2 && x<Lx/2 && y>-Ly/2 && y<Ly/2)
    events++;


  totalevents++;

  //(th,fi) da-me info sobre a direccao de propagaçao do muao
  //(x,y) da-me info sobre o ponto do bloco que este vai atingir


  }


  float ratio=(float)events/totalevents;

  cout << ratio << endl;

}



  return 0;






}
