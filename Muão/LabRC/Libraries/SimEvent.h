#ifndef _SimEvent_
#define _SimEvent_

/**
 * \author F. Barao, M. Orcinha - May 2016
 * \class SimEvent
 *
 * Storage classes for a physical event.
 */

#include "SimPhoton.h"
#include "TObject.h"
#include <vector>
using namespace std;

class SimEvent: public TObject {

 public:
  SimEvent();

  void Clean();

  ClassDef(SimEvent,1);

  int pid;                     //Número de partícula segundo o Particle Data Group
  double x_imp, y_imp;         //Ponto de impacto do raio cósmico no detector [cm]
  double energy;               //Energia do raio cósmico [GeV]
  int nsci;                    //Número de fotões cintilados
  int ndet;                    //Número de fotões detectados
  vector <SimPhoton> vphotons; //Vector de SimPhotons(classe que contém informação relativa fotão a fotão.)

};

#endif
