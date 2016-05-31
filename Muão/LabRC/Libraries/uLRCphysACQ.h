#ifndef _uLRCphys_
#define _uLRCphys_

#include "TObject.h"
#include "TF1.h"
#include "TF2.h"
//class TF1;

/////////////////////////////////////////////////////////////////////////////////////////////////////////
class uLRCphys: public TObject {
 public :
   uLRCphys();
   ~uLRCphys();

  
   
   TF1* GetL() {return fL;}
   
   TF1* GetdEW() {return fdEW;}
   
  
 
   TF1* GetLandauLRC() {return fLandauLRC;}
   
   TF1* GetLandauLRCSimple(){return fLandauLRCSimple;}

   TF1* GetLandauMpv() {return fLandauMpv;}

   TF1* GetLambdaSignal() {return fLambdaSignal;}

   TF1* GetSigmadEFromMom(){return fSigmadEFromMom;}

   TF1* GetSigmadEFromCosTheta(){return fSigmadEFromCosTheta;}
   
   TF2* Getepsilon(){return fepsilon;}

   TF1* Getdelta() {return fdelta;}
   
   TF1* GetGausXadc(){return fGausXadc;}
   
   TF1 *GetFitSumLandau(){return fFitSumLandau;}

   TF1 *GetFitSumLandauLRC(){return fFitSumLandauLRC;}

   TF1 *GetFitGausLandauChann1(){return fFitGausLandauChann1;}

   TF1 *GetFitGausLandauChann2(){return fFitGausLandauChann2;}
   
   TF1* GetMuonSpectraTheta(){return fMuonSpectraTheta;}
   
   TF1* GetMuonSpectraMomentum(){return fMuonSpectraMomentum;}
   
   TF1* GetBetheBloch(){return fBetheBloch;}
 
   TF1* GetRatioMuonVertical(){return fRatioMuonVertical;}
   
   TF1* Getkindabsorber(){return fkindabsorber;}
  
   double LandauMPV(double mom, double costheta);

   double LandauFWHM(double mom, double costheta);

   double LandauError(double mom, double costheta);


   ClassDef(uLRCphys,1);
   
 private:
   double MASS; //GeV/c^2
   double MASSELEC;
   double ZA;
   double DENSITY; //gr/cm^3
   double L0; //cm
   double IONIZ; //GeV  
   double kappa;


 
   TF1 *fL;    double L  (double *x, double *p);
   
   TF1 *fdEW;  double dEW(double *x, double *p);
 
   TF1 *fSigmadEFromMom; double SigmadEFromMom(double *x,double *p);
   TF1 *fSigmadEFromCosTheta; double SigmadEFromCosTheta(double *x,double *p);

   TF1 *fLandauLRCSimple; double LandauLRCSimple(double *x, double *p);

   TF1 *fLandauLRC; double LandauLRC(double *x, double *p);
   TF1 *fLandauMpv; double LandauMpv(double *x, double *p);
   TF1 *fLambdaSignal; double LambdaSignal(double *x, double *p);
   TF2 *fepsilon;   double epsilon (double *x, double *p);
   
   TF1 *fFitSumLandau; double FitSumLandau(double *x, double *p);
   TF1 *fFitSumLandauLRC; double FitSumLandauLRC(double *x, double *p);
  
   TF1 *fFitGausLandauChann1; double FitGausLandauChann1(double *x, double *p);
   TF1 *fFitGausLandauChann2; double FitGausLandauChann2(double *x, double *p);
   
   TF1 *fdelta;   double delta (double *x, double *p);
   TF1 *fGausXadc; double GausXadc(double *x, double *p);
   
   TF1* fMuonSpectraTheta; double MuonSpectraTheta(double *x, double *p);
   TF1* fMuonSpectraMomentum; double MuonSpectraMomentum(double *x, double *p);
  
   TF1* fRatioMuonVertical; double RatioMuonVertical(double *x, double *p);
  
   TF1* fBetheBloch; double BetheBloch(double *x, double *p);
   TF1* fkindabsorber;double kindabsorber(double *x, double *p);
  
  
 



};

#endif
