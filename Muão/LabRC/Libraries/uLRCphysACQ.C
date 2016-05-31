#include "uGenFunctor.h"
#include "uLRCphys.h"
#include "TF1.h"
#include "TMath.h"

#include <iostream>
#include <cmath>
using namespace std;

ClassImp(uLRCphys);

uLRCphys::uLRCphys() {

  MASS = 0.1097; //GeV/c^2
  ZA = 0.54141;
  DENSITY = 1.023; //gr/cm^3
  L0 = 1.; //cm
  IONIZ = 94.e-9; //GeV  
  MASSELEC = 0.511E-3;//GeV/c^2
  kappa = 0.00008507326;


  

  fFitSumLandau = new TF1("FitSumLandau", this, &uLRCphys::FitSumLandau, 0., 2000., 3, "uLRCphys","FitSumLandau");
  fFitSumLandauLRC = new TF1("FitSumLandauLRC", this, &uLRCphys::FitSumLandauLRC, 0., 2000., 2, "uLRCphys","FitSumLandauLRC");
  fLandauLRCSimple = new TF1("LandauLRCSimple", this, &uLRCphys::LandauLRCSimple, 0., 2000., 3, "uLRCphys","LandauLRCSimple");
  fSigmadEFromMom = new TF1("SigmadEFromMom", this, &uLRCphys::SigmadEFromMom, 0.5,10. , 1, "uLRCphys","SigmadEFromMom");
  fSigmadEFromCosTheta = new TF1("SigmadEFromCosTheta", this, &uLRCphys::SigmadEFromCosTheta, 0.,1. , 1, "uLRCphys","SigmadEFromCosTheta");
  fFitGausLandauChann1 = new TF1("FitGausLandauChann1", this, &uLRCphys::FitGausLandauChann1, 300., 3000., 5, "uLRCphys","FitGausLandauChann1");
  fFitGausLandauChann2 = new TF1("FitGausLandauChann2", this, &uLRCphys::FitGausLandauChann2, 0., 600., 5, "uLRCphys","FitGausLandauChann2");
  fGausXadc = new TF1("GausXadc",this, &uLRCphys::GausXadc,0.,2000.,3,"uLRCphys","GausXadc");
  
  fL = new TF1("L", this, &uLRCphys::L, -10., 300., 0, "uLRCphys","L");

  fLandauLRC = new TF1("LandauLRC", this, &uLRCphys::LandauLRC, 0., 0.01, 2, "uLRCphys","LandauLRC");
 
  fLambdaSignal = new TF1("LambdaSignal", this, &uLRCphys::LambdaSignal, 0., 0.01, 4, "uLRCphys","LambdaSignal");
  
  
  fepsilon = new TF2("epsilon", this, &uLRCphys::epsilon, 0.1, 10.,0.01,1.,0, "uLRCphys","epsilon"); 
  fdEW = new TF1("dEW", this, &uLRCphys::dEW, 0., 1E-3, 2, "uLRCphys","dEW"); 
  fdelta = new TF1("delta", this, &uLRCphys::delta, 0.1, 100., 2, "uLRCphys","delta"); 
  
  
  fBetheBloch = new TF1("BetheBloch",this,&uLRCphys::BetheBloch,0.001,100.,1,"uLRCphys","BetheBloch");
  
  fkindabsorber = new TF1("kindabsorber",this,&uLRCphys::kindabsorber,0.001,100.,4,"uLRCphys","kindabsorber");

 
  fMuonSpectraMomentum = new TF1("MuonSpectraMomentum",this,&uLRCphys::MuonSpectraMomentum,0.5,100000.,1,"uLRCphys","MuonSpectraMomentum");
  fMuonSpectraTheta = new TF1("MuonSpectraTheta",this,&uLRCphys::MuonSpectraTheta,0.,1.,0,"uLRCphys","MuonSpectraTheta");
  fRatioMuonVertical = new TF1("RatioMuonVertical",this,&uLRCphys::RatioMuonVertical,0.1,100,1,"uLRCphys","RatioMuonVertical");

}

uLRCphys::~uLRCphys() {
 


  delete fL;
  delete fGausXadc;
  delete fepsilon;
  delete fLandauLRCSimple;
  delete fSigmadEFromMom;
  delete fSigmadEFromCosTheta;
  
  delete fdEW;
  delete fFitSumLandau;
  
  delete fRatioMuonVertical;
  delete fLandauLRC;
 
  delete fLambdaSignal;
  delete fFitGausLandauChann1;
  delete fFitGausLandauChann2;
  
  delete fkindabsorber;
  delete fdelta;
 
  delete fBetheBloch;
  delete fMuonSpectraMomentum;
 
  delete fMuonSpectraTheta;
 
 

 
 
 
 
}

// ---------------------- new ------------------------------------------------------------




double uLRCphys::GausXadc(double *x, double *p){

  double Xadcmean = p[0];
  double C= p[1];
  double Eff = p[2];
  double sigma = Xadcmean/sqrt((Xadcmean*1e7*Eff)/C);
  cout<<"sigma ="<<sigma<<endl;
  double ProbX =  TMath::Gaus(x[0],Xadcmean,sigma,kTRUE);
  cout<<"ProbX ="<<ProbX<<endl;
  return ProbX;

}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Funcao para somar varias distribuicoes de Landau, para várias energias e angulos da particula incidente
 
double uLRCphys::FitSumLandau(double *x, double *p) {
  /*Parameters:
    dEW0, Parameter that exprime the vertical energy (GeV)deposited by a muon with betamip
    C = G*KAdc, G -> Gain of the PMT, KAdc->Conversion from Charge to ADC channels
    N, Normalization of the function
    Eff, efficience in the photons recoil
  */  
  
  double dEW0 = p[0];
  double C = p[1]; //adc/GeV
  double N = p[2];
  // double Eff = p[3];
  
  double Xadc = x[0];
  
  double stepCT = 0.1;
  
  double stepMOM = 1.; 
  
  double gammabetamip = 3.5;
  
  double mom_mip = gammabetamip*MASS;

  double betamipinv2 = 1. + pow(MASS/mom_mip,2.);

  double epsilon0 = fepsilon->Eval(mom_mip,2.);
  
 

  double dEdxmip = TMath::Log(2*MASSELEC*epsilon0*pow(gammabetamip/IONIZ,2.)) - pow(betamipinv2,-1.) + 0.422785;
  
  double LF = 0.;
  
  for (double ct=1.; ct>0.1; ct-=stepCT) {
    
    fMuonSpectraMomentum->SetParameter(0,ct);
    double ProbCT = fMuonSpectraTheta->Eval(ct)*stepCT;
    
    for (double mom=0.5; mom<30.; mom+=stepMOM) {
      double epsilon = fepsilon->Eval(mom,ct);
      fLambdaSignal->SetParameters(dEW0, mom,ct,dEdxmip);
      double ProbMOM = fMuonSpectraMomentum->Eval(mom)*stepMOM;
      double lambda = fLambdaSignal->Eval((Xadc*1.E-7)/C);
      LF += (fL->Eval(lambda)*ProbMOM*ProbCT)/epsilon;
      
    }
  }
  
  return N*LF;
  
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Funcao igual a anterior mas que utiliza a funcao fLandauLRC para a distribuicao de Landau 

double uLRCphys::FitSumLandauLRC(double *x, double *p) {
  /*Parameters:
    dEW0, Parameter that exprime the vertical energy (GeV)deposited by a muon with betamip
    C = G*KAdc, G -> Gain of the PMT, KAdc->Conversion from Charge to ADC channels
    N, Normalization of the function
    Eff, efficience in the photons recoil
  */  
  
  double C = p[0]; //adc/GeV
  double N = p[1];
  
  double Xadc = x[0];
  
  double stepCT = 0.1;
  
  double stepMOM = 1.; 
  
  double LF = 0.;
  
  for (double ct=1.; ct>0.1; ct-=stepCT) {
    
    fMuonSpectraMomentum->SetParameter(0,ct);
    double ProbCT = fMuonSpectraTheta->Eval(ct)*stepCT;
    
    for (double mom=0.5; mom<30.; mom+=stepMOM) {
      
      fLandauLRC->SetParameters(mom,ct);
      double ProbMOM = fMuonSpectraMomentum->Eval(mom)*stepMOM;
     
      LF += fLandauLRC->Eval((Xadc*1.E-7)/C)*ProbMOM*ProbCT;
    }
  }
  
  return N*LF;
  
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Funcao de Conversao para o cintilador pequeno

double uLRCphys::FitGausLandauChann1(double *x, double *p) {
  /*Parameters:
     dEW0, Parameter that exprime the vertical energy (GeV)deposited by a muon with betamip
    C = G*KAdc, G -> Gain of the PMT, KAdc->Conversion from Charge to ADC channels
    N, Normalization of the function
    Eff, efficience in the photons recoil
  */  
  
  double dEW0 = p[0];
  double C = p[1]; //adc/GeV
  double N = p[2];
  double Eff = p[3];
  double sigmape = p[4];
  
  double Xadc = x[0];
  
  double stepCT = 0.1;
  
  double stepMOM = 1.; 
  
  double gammabetamip = 3.5;
  
  double mom_mip = MASS*gammabetamip;
  
  double epsilon0 = fepsilon->Eval(mom_mip,1.);
  
  double betamipinv2 = 1.+ pow(MASS/mom_mip,2.);
  
  double dE0mip = TMath::Log(2*MASSELEC*pow((gammabetamip/IONIZ),2.)*epsilon0) - pow(betamipinv2,-1.) + 0.422785;
  
  double LF = 0.;
  
  double stepX = 10.;

  
  for (double X = 450.;X<2000.;X+=stepX) {
    
    if(X >= 650. && X < 1200.){stepX = 20.;}
    if(X >= 1200.){stepX = 50.;}
    
    double ProbX = TMath::Gaus(Xadc, X, sqrt(X*(1.+pow(C*sigmape,2.))), kTRUE)*stepX;
    
    for (double ct=1.; ct>0.1; ct-=stepCT) {
      
      fMuonSpectraMomentum->SetParameter(0,ct);
      double ProbCT = fMuonSpectraTheta->Eval(ct)*stepCT;
      
      for (double mom=0.5; mom<10.; mom+=stepMOM) {
	
	fLambdaSignal->SetParameters(dEW0,mom,ct,dE0mip);
	double ProbMOM = fMuonSpectraMomentum->Eval(mom)*stepMOM;
	double lambda = fLambdaSignal->Eval((X*1.E-7)/(Eff*C));
	LF += fL->Eval(lambda)*ProbMOM*ProbCT*ProbX;
	
      }
    }
  }
  return N*LF;
  
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Funcao de Conversao para o cintilador grande

double uLRCphys::FitGausLandauChann2(double *x, double *p) {
  /*Parameters:
    dEW0, Parameter that exprime the vertical energy (GeV)deposited by a muon with betamip
    C = G*KAdc, G -> Gain of the PMT, KAdc->Conversion from Charge to ADC channels
    N, Normalization of the function
    Eff, efficience in the photons recoil
  */  
  
  double dEW0 = p[0];
  double C = p[1]; //adc/GeV
  double N = p[2];
  double Eff = p[3];
  double sigmape = p[4];
  double Xadc = x[0];
  
  double stepCT = 0.1;
  
  double stepMOM = 1.; 
  
  double gammabetamip = 3.5;

  double mom_mip = gammabetamip*MASS;
  
  double epsilon0 = fepsilon->Eval(mom_mip,1.);

  double betamipinv2 = 1.+ pow(MASS/mom_mip,2.);

  double dE0mip = TMath::Log(2*MASSELEC*pow((gammabetamip/IONIZ),2.)*epsilon0) - pow(betamipinv2,-1.) + 0.422785;
  
  double LF = 0.;
  
  double stepX = 10.;
  
  
  for (double X = 80.; X < 500.; X+=stepX) {
    
    if(X >= 180. && X < 350.){stepX = 10.;}
    if(X >= 350.){stepX = 20.;}
    stepX = 10.;
    
    double ProbX = TMath::Gaus(Xadc, X, sqrt(X*(1. + pow(C*sigmape,2.))), kTRUE)*stepX;
    
    for (double ct=1.; ct>0.1; ct-=stepCT) {
      
      fMuonSpectraMomentum->SetParameter(0,ct);
      double ProbCT = fMuonSpectraTheta->Eval(ct)*stepCT;
      
      for (double mom=0.5; mom<10.; mom+=stepMOM) {
	//	double epsilon = fepsilon->Eval(mom,ct);
	fLambdaSignal->SetParameters(dEW0,mom,ct,dE0mip);
	double ProbMOM = fMuonSpectraMomentum->Eval(mom)*stepMOM;
	double lambda = fLambdaSignal->Eval((X*1.E-7)/(Eff*C));
	LF += fL->Eval(lambda)*ProbMOM*ProbX*ProbCT;
	
      }
    }
  }
  return N*LF;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Implementacao do parametro lambda da distribuicao de Landau Simplificada 


double uLRCphys::LambdaSignal(double *x, double *p) {
  //lambda(dE; p, theta)
  double EW0 = p[0];
  double mom = p[1];//GeV
  
  double costheta = p[2];
  
  double EW0Mip = p[3]; 
  double dE= x[0];//GeV
  double gammabetamip = 3.5;
  
  double mom_mip = gammabetamip*MASS;

  
  double betamipinv2 = 1.+ pow(MASS/mom_mip,2.);
  
  double betainv2 = 1.+pow(MASS/mom,2.);
  
  double gammabeta = mom/MASS;
  
  double epsilon = fepsilon->Eval(mom,costheta);
  
  double epsilon0 = fepsilon->Eval(mom_mip,1.);
  
  double dEW = TMath::Log(2*MASSELEC*epsilon*pow(gammabeta/IONIZ,2.)) - pow(betainv2,-1.) + 0.422785;
   
  double lambda = dE/epsilon - (EW0*dEW)/(epsilon0*EW0Mip);
  
  return lambda;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Distribuicao de Landau simplificada em funcao do parametro lambda, que pode ser calculado na funcao fLambdaSignal

double uLRCphys::L(double *x, double *p) {
  //L(lambda)
  return pow(sqrt(2.*TMath::Pi()),-1.)*(TMath::Exp(-0.5*(x[0] + TMath::Exp(-x[0]) ))); 
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Distribuicao de Landau simplificada, onde se calcula o parametro lambda, substituindo-o na distribuicao de landau (fL)  

double uLRCphys::LandauLRC(double *x, double *p) {
  //lambda(dE; p, theta)
 
  double mom = p[0];//GeV
  
  double costheta = p[1];

  double dE= x[0];//GeV
  
  double betainv2 = 1.+pow(MASS/mom,2.);
  
  double gammabeta = mom/MASS;
  
  double epsilon = fepsilon->Eval(mom,costheta);
  
  double dEdw = epsilon*(TMath::Log(2*MASSELEC*pow(gammabeta/IONIZ,2.)*epsilon) - pow(betainv2,-1.) + 0.422785);
  
  double lambda = (dE-dEdw)/epsilon;
  
  double LV = (fL->Eval(lambda))/epsilon;
  
  return LV;

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Distribuicao de Landau em que se parameteriza a largura a meia altura e o valor mais provavel


double uLRCphys::LandauLRCSimple(double *x, double *p) {

  double dE = x[0];

  double mpv = p[0];

  double width = p[1];

  double N = p[2];

  double lambda = 4.02*(dE - mpv + (width/4)*(-0.229))/width;

  double LP = fL->Eval(lambda);

  return (4.02*N*LP)/width;

}
  
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Largura a meia altura da distribuicao de Landau simplificada


double uLRCphys::LandauFWHM(double mom, double costheta){


  double epsilon = fepsilon->Eval(mom,costheta);

  double FWHM = 4.02*epsilon;
  
  return FWHM;
  
  
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Valor mais provavel da distribuicao de Landau simplificada

double uLRCphys::LandauMPV(double mom, double costheta){

 
  double gammabeta = mom/MASS;
  
  double betainv2 = 1.+pow(MASS/mom,2.);

  double epsilon = fepsilon->Eval(mom,costheta);

  double Mpv = epsilon*(TMath::Log(2*MASSELEC*pow(gammabeta/IONIZ,2.)*epsilon) - pow(betainv2,-1.) + 0.422785 - 0.229 - fdelta->Eval(mom));

  return Mpv;

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Funcao que calcula o erro relativo da distribuicao de Landau


double uLRCphys::LandauError(double mom, double costheta){

  double sigma = LandauFWHM(mom,costheta)/2.355;

  double MPV = LandauMPV(mom, costheta);

  double error = sigma/MPV;

  return error;

}



double uLRCphys::SigmadEFromMom(double *x, double *p){

  double costheta = p[0];
  double mom = x[0];

  return LandauError(mom,costheta);

}

double uLRCphys::SigmadEFromCosTheta(double *x, double *p){

  double costheta = x[0];
  double mom = p[0];

  return LandauError(mom,costheta);

}



double uLRCphys::epsilon(double *x, double *p) {
 
  double mom = x[0];
  double costheta = x[1];
  double betainv2 = 1.+pow(MASS/mom,2.);
  return (0.1536E-3*ZA*betainv2*DENSITY*L0)/costheta;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Funcao Bethe Bloch que caracteriza os cintilazadores

double uLRCphys::dEW(double *x, double *p) {
  double mom = p[0];
  double costheta = p[1];
  double dEW0 = x[0];
  double betainv2 = 1.+pow(MASS/mom,2.);
  double gammabeta = mom/MASS;
  double betamip = 0.961524;
  double gammabetamip = 3.5;
  

  double A = TMath::Log(2*MASSELEC*pow(gammabeta,2.)/IONIZ) - pow(betainv2,-1.) - fdelta->Eval(mom)/2.;   
  double B = TMath::Log(2*MASSELEC/IONIZ)+2*TMath::Log(gammabetamip)-TMath::Power(betamip,2.)-  fdelta->Eval(mom)/2.;
  double dEvert = (dEW0*TMath::Power(betamip,2)*betainv2*A)/(B*costheta);
 
  return dEvert;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Correcao densidade na curva de perda de energia ( bethe bloch)


double uLRCphys::delta(double *x, double *p) {
  const Double_t X0 = 0.1464;
  const Double_t X1 = 2.49;
  const Double_t C = -3.20;
  const Double_t a = 0.1610;
  const Double_t m = 3.24;
  
  double mom = x[0];
  double gammabeta = mom/MASS;
  Double_t X = TMath::Log10(gammabeta);
  Double_t D;
  
  if (X<X0){ D = 0.;}
  if (X>X0 && X<X1){ D = 4.6052*X + C + 0.1610*pow((X1-X),m);}
  if (X>X1){D = 4.6052 * X + C;}

  return D;
}



double uLRCphys::kindabsorber(double *x, double *p) {
  //parameters:  p[0] = Z/A material
  //             p[1] = material density [g/cm^3]
  //             p[2] = particle mass [GeV]
  //             p[3] = material thickness [cm]
  //variable:    x[0] = momentum [GeV]
  const Double_t e_m    = 0.510998e-3; //GeV
  Double_t gammabeta = x[0]/p[2];
  Double_t Tmax = 2*e_m*pow(gammabeta,2.);                     
  fBetheBloch->SetParameters(p[0],p[1],p[2]); 
  double k = fBetheBloch->Eval(x[0])*p[3]*p[1]/Tmax;
  return k;
}

double uLRCphys::BetheBloch(double *x, double *p) {
  // returns: dE/dx in MeV/(gr/cm^2)
  // parameters: p[0] = Z/A material
  //             p[1] = material density [g/cm^3]
  //             p[2] = particle mass [GeV]
  // variable:   x[0] = momentum [GeV]  

  //material

  Double_t gammabeta = x[0]/MASS;
  
  Double_t thickness = p[0];


  
  //constantes do plastico cintilador
  
  
  Double_t betasq = pow(x[0],2.)/(pow(MASS,2.)+pow(x[0],2.)); 
  
  Double_t Tmax = 2*MASSELEC*pow(gammabeta,2.);
  
  //Compute dEdx
  
  Double_t dEdx = (DENSITY*ZA*0.1536/betasq)*(2*TMath::Log(Tmax/IONIZ) - 2*betasq - fdelta->Eval(x[0])/2.);
  
  

  return dEdx; //return GeV/cm
  
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Espectro da energia de uma particula ao nivel do mar

double uLRCphys::MuonSpectraMomentum(double *x, double *p){
  double mom = x[0];
  double costheta = p[0];
  return (18./(mom*costheta + 145.))*TMath::Power(mom + 2.7*(1./costheta),-2.7)*(mom+5.)/(mom + 5.*(1./costheta));
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Espectro do angulo de incidencia

double uLRCphys::MuonSpectraTheta(double *x, double *p){
  double costheta = x[0];
  return (1./3)*pow(costheta,2.);  
}

double uLRCphys::RatioMuonVertical(double *x, double *p){

  double mom = x[0];
  double theta = p[0];
  double costheta = TMath::Cos(theta);
  double verticalspectra = (18./(mom + 145.))*TMath::Power((mom + 2.7),-2.7)*(mom+5)/(mom + 5)*TMath::Power(costheta,2);
  double thetaspectra = (18./(mom*costheta + 145.))*TMath::Power((mom + 2.7*(1./costheta)),-2.7)*(mom+5)/(mom + 5*(1./costheta));
  double ratio = thetaspectra/verticalspectra;
  
  return ratio;

}





  

