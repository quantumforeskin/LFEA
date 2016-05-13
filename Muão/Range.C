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


  float R=10;//Range em g/(cm2) 
  double density=1.03; // g/(cm3)
  double x_range=R/density; // range em cm
  float m=105.65837;//energia em repouso do muao
  float E_R = x_range*g/4*(1+sqrt(1+4*m/(x_range*g)))*(1+sqrt(1+4*m/(x_range*g)));


  cout << E_R << endl;


  //Stopping time


  float f = sqrt((E_R/m)*(E_R/m)-1);

  float t=m/(c*g)*(f + atan(1/f) - M_PI/2);

  cout << t << endl;




} 
