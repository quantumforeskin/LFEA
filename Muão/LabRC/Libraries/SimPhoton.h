#ifndef _SimPhoton_
#define _SimPhoton_

/**
 * \author F. Barao, M. Orcinha - May 2016
 * \class SimPhoton
 *
 * Storage classes for a physical event.
 */

#include "TObject.h"
using namespace std;

class SimPhoton: public TObject {

 public:
  SimPhoton();

  void Clean();

  ClassDef(SimPhoton,1);

  double x_i, y_i;  //ponto de geração do fotão (x,y) [cm]
  double x_f, y_f;  //ponto de absorção do fotão (x,y) [cm]
  double length;    //comprimento total percorrido pelo fotão [cm]
  double lambda;    //comprimento de onda [nm]
  bool is_detected; //se o fotão foi detectado pelo PMT
  bool is_sci_abs;  //se o fotão foi absorvido no cintilador
  bool is_alu_abs;  //se o fotão foi absorvido no alumínio
  int nrefl;        //número de reflexões feitos pelo fotão
  int nalurefl;     //número de reflexões no alumínio feitos pelo fotão
};

#endif
