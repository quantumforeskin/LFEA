#ifndef __CFCG__
#define __CFCG__

#include <string>
#include <map>
using namespace std;
#include "TApplication.h"
#include "TList.h"
#include "TObject.h"
#include "TPad.h"


class cFCgraphics {
 public:
  cFCgraphics();
  ~cFCgraphics();

  //create Pad and add objects to it
  TPad* CreatePad(string PadName);
  void AddObject(TObject *obj, string PadName);
  void AddObject(TObject *obj, string PadName, string sopt);
  void DrawPad(string PadName);
  void DumpPad(string PadName);

  //add objects to Canvas
  void AddObject(TObject *obj=NULL );
  void ListObjects();
  void Draw(string sopt="all");
  int GetNumberOfListEntries();
  void Print(string); //save to file

 private:
  TApplication *gMyRootApp;
  TList *L, *Ltmp; ///< list of user ROOT objects
  map<string,TPad*> Mpad;
  map<string,TPad*>::iterator itMpad;
  TCanvas *fCanvas;
};

#endif
