#include "SimEvent.h"

ClassImp(SimEvent);

SimEvent::SimEvent() {
  Clean();
}

void SimEvent::Clean() {
  pid = -1;
  x_imp = -1000.;
  y_imp = -1000.;
  energy = 0.;
  nsci = 0;
  ndet = 0;
  vphotons.clear();
};
