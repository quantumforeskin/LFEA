#include <iostream>
#include <cmath>

using namespace std;

int main(){



  float L=4; //comprimento de S2
  float l=2; //comprimento do bloco
  float d=0.5; //distancia entre S2 e bloco
  float t=0.1; //espessura do bloco

  float th1 = atan((L-l)/2/(d+t));
  float th2 = atan((L+l)/2/d);

  float prob = pow(cos(th1),4)-pow(cos(th2),4);

  cout << prob << endl;


}
