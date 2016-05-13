#include <iostream>
#include <cmath>

using namespace std;

int main(){

  float k=0.307075;
  float q=1;
  float ZA = 0.56;
  float me=511;//eV
  float I=78.4;//eV
  float c = 300000000;

  float g=k*q*q*ZA*log(2*me/I);


  double density=1.032; // g/(cm3), densidade do plastico do cintilador
  double x_range=300; // range em cm
  double R=density*x_range; //Range em g/(cm2) 
  float m=105.65837;//energia em repouso do muao
  float E_R = R*g/4*(1+sqrt(1+4*m/(R*g)))*(1+sqrt(1+4*m/(R*g)));


  cout << E_R << endl;


  //Stopping time


  float f = sqrt((E_R/m)*(E_R/m)-1);

  float t=m/(c*g)*(f + atan(1/f) - M_PI/2);

  cout << t << endl;




} 
