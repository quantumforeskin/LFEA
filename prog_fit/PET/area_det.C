#include <iostream> 
#include <fstream>  
#include <cmath>

using namespace std;

double to_rad(double a){

  return a*3.14159265359/180;

}

int main(){

  double r1=2.54;
  double r2=3.81;

  //Recta 1
  double a1u=to_rad(170.6);
  double a2u=to_rad(141.7);

  //declive da reta  y = mu*x + c
  double mu=(r2*sin(a2u) - r1*sin(a1u))/(r2*cos(a2u) - r1*cos(a1u));
  double cu = r2*sin(a2u) - mu*r2*cos(a2u);

  cout << "declive " << mu << endl;
  cout << "ordenada " << cu << endl;

  //Para coord polares
  double x0 = -cu/mu; //interseccao da reta com y=0
  double theta_x0 = atan(mu);//angulo da reta em relacao ao ponto x0

  static int N=10;
  double theta[N];
  double r[N];

  theta[0]=0;
  r[0]=x0;

  int i=1;
  double dx=0;
  while(i<10){
    dx+=0.02;
    double y=mu*(x0+dx)+cu;
    double theta_0 = atan(y/(x0+y/tan(theta_x0))); //angulo da reta em relacao a origem do ref polar
    double r_0 = y/sin(theta_0);
    theta[i] = theta_0;
    r[i] = r_0;
    //cout << theta[i] << endl;
    //cout << r[i] << endl;
    i++;
  }

  //Recta 2
  double a1l=to_rad(-10);
  double a2l=to_rad(-30);

  //declive da reta  y = mu*x + c
  double ml=(r2*sin(a2l) - r1*sin(a1l))/(r2*cos(a2l) - r1*cos(a1l));
  double cl = r2*sin(a2l) - ml*r2*cos(a2l);

  //interseccao 
  double x_int = (cl-cu)/(mu-ml);
  double y_int = x_int*mu + cu;


  return 0;



}
