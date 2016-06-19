#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;


int main(){


  ///Definem-se todas as unidades em cm


  float Lx=55.4;//comprimento de S1
  float Ly=43.9;//largura de S1
  float lx=41; //largura do bloco
  float ly=40.9; //comprimento do bloco
  float eS1=2.05; //espessura de S1
  float eB=9.7; // espessura do bloco 
  float dz = 56.6;//distancia entre S1 e o bloco


 srand (time(NULL));





  vector<double> d_travel_S1B;  
  vector<double> d_travel_S1;  
  vector<double> d_travel_B;  


for(int j=0;j<1;j++){

  int totalevents=100000000;
  int events=0;

  for(int i=0;i<totalevents;i++){

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

  
  float t=dz/cos(th); // parametro da parametrizacao


  x = x + t*v[0]; //Abcissa do ponto a altura de S1 que segue a direçao de v
  y = y + t*v[1];

  if(x>-Lx/2 && x<Lx/2 && y>-Ly/2 && y<Ly/2){
    d_travel_S1B.push_back((eB+eS1)*cos(th)); //distancia percorrida em S1 e B 
    d_travel_S1.push_back(eS1*cos(th)); //distancia percorrida em S1 
    events++;
  }else{
    d_travel_B.push_back(eB*cos(th));  // distancia percorrida em B
  }



  //(th,fi) da-me info sobre a direccao de propagaçao do muao
  //(x,y) da-me info sobre o ponto do bloco que este vai atingir


  }

  float events1 = (float)totalevents - (float)events; //eventos q passam so em B
  float events2 = (float)events;// eventos q passam em S1 e B
  float total=(float)totalevents;

  float ratio1=events1/total;
  float eratio1=sqrt((sqrt(events1)/total)*(sqrt(events1)/total)+(events1/(total*total))*(events1/(total*total))*sqrt(total)*sqrt(total));

  float ratio2=events2/total;
  float eratio2=sqrt((sqrt(events2)/total)*(sqrt(events2)/total)+(events2/(total*total))*(events2/(total*total))*sqrt(total)*sqrt(total));


  cout << ratio1 << "   " << eratio1 << endl;
  cout << ratio2 << "   " << eratio2 << endl;


}


//Distancia media percorrida quando passa em B apenas
 double d_Bmed=0;
 for(int t=0;t<d_travel_B.size();t++){
   d_Bmed+=d_travel_B[t];
 }

 d_Bmed=d_Bmed/d_travel_B.size();

 cout << "distancia B " << d_Bmed << endl;


//Distancia media percorrida quando passa em S1 
 double d_S1med=0;
 for(int t=0;t<d_travel_S1.size();t++){
   d_S1med+=d_travel_S1[t];
 }

 d_S1med=d_S1med/d_travel_S1.size();

 cout << "distancia S1 " << d_S1med << endl;



//Distancia media percorrida quando passa em S1 e B
 double d_S1Bmed=0;
 for(int t=0;t<d_travel_S1B.size();t++){
   d_S1Bmed+=d_travel_S1B[t];
 }

 d_S1Bmed=d_S1Bmed/d_travel_S1B.size();

 cout << "distancia S1B " << d_S1Bmed << endl;


  return 0;






}
