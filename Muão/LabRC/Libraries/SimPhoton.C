#include "SimPhoton.h"

ClassImp(SimPhoton);

SimPhoton::SimPhoton() {
  Clean();
}

void SimPhoton::Clean() {
  x_i = -1000.;
  y_i = -1000.;
  x_f = -1000.;
  y_f = -1000.;
  length = 0.;
  lambda = 0.;
  is_detected = false;
  is_sci_abs = false;
  is_alu_abs = false;
  nrefl = 0;
  nalurefl = 0;
};
