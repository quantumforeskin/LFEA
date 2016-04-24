// see: http://root.cern.ch/drupal/content/how-embed-tcanvas-external-applications

#include "TROOT.h"
#include <TGFrame.h> //gClient
#include "TCanvas.h"
#include "TPad.h"
#include "TSystem.h"
#include <TList.h>
#include "TApplication.h"
#include "TVirtualX.h"
#include "TF1.h"
#include "TGraph.h"

#include <iostream>
using namespace std;
#include <unistd.h>
#include "cFCgraphics.h" 

cFCgraphics::cFCgraphics () {
  cout << Form("[cFCgraphics::cFCgraphics] default constructor called...)\n");
  //create TList
  L = new TList();
  Ltmp = new TList();
  //create application
  int argc = 0;
  char **argv = NULL;
  gMyRootApp = new TApplication("Comput Phys Application", &argc, argv);
  gMyRootApp->SetReturnFromRun(true);
  gROOT->SetStyle("Plain");

  //canvas
  fCanvas = new TCanvas("FC_canvas","Canvas - Fis Computacional", 400, 100, 900, 700);
}

cFCgraphics::~cFCgraphics () {
  cout << Form("[cFCgraphics::~cFCgraphics] destructor called...)\n");
  TListIter next(L);
  TObject *to;
  cout << Form("[Destructor] delete objects... (Total nb objects=%d)\n", GetNumberOfListEntries());
  while ((to=next())) {
    cout<< Form("delete %s [%s] \n",to->GetName(), to->ClassName());
    delete to;
  }
  cout<< endl;

  //  delete gMyRootApp;
  delete L;
  delete Ltmp;
  delete fCanvas;
}

void cFCgraphics::AddObject(TObject *obj) {
  if (obj) {
    L->Add(obj);
    if (obj->InheritsFrom("TF1") | obj->InheritsFrom("TH1")  ) { 
      cout << Form("[cFCgraphics::AddObject] %s added.. .(Total nb objects=%d)\n", obj->GetName(), GetNumberOfListEntries());
    }
  }
}

void cFCgraphics::ListObjects() {
  TListIter next(L);
  TObject *to;
  cout << Form("[cFCgraphics::ListObjects] (Total nb objects=%d)\n", GetNumberOfListEntries());
  while ((to=next())) {
    cout<< Form("%s ---> %s \n",to->ClassName(),to->GetName());
  }
  cout<< endl;
}

void cFCgraphics::Draw(string sopt) {
  cout<< Form("[cFCgraphics::Draw] Drawing objects...[%s]\n",sopt.c_str());
  //new canvas
  //  fCanvas->SetFillColor(19);
  //  fCanvas->SetFrameFillColor(50);
  //all or only one object
  if (sopt == "all") {
    // ... get number of list entries
    int count = GetNumberOfListEntries();
    int nlines = count/3;
    int ncolus = count%3;
    if (count < 3) {
      fCanvas->Divide(ncolus,nlines+1);
    } else {
      fCanvas->Divide(3,(count-1)/3 + 1);
    }
    TListIter next(L);
    TObject *to;
    int n = 0;
    printf("Drawing... ");
    while ((to=next())) {
      printf(" [%s:%s] ",to->ClassName(),to->GetDrawOption());
      n++;
      fCanvas->cd(n);
      string gopt="";
      if (to->InheritsFrom("TF1")) { 
	((TF1*)to)->SetLineWidth(4); 
	((TF1*)to)->SetLineColor(kBlue+2);   
      } else if (to->InheritsFrom("TGraph")) { 
	//         ((TGraph*)to)->SetMarkerColor(kRed+3); 
	 //         ((TGraph*)to)->SetMarkerStyle(22); 
	 //         ((TGraph*)to)->SetMarkerSize(0.5); 
        gopt="AP";
      }
      to->Draw(gopt.c_str());
    }
  } else {
    TObject *o = L->FindObject(sopt.c_str());
    if (o) o->Draw();
  }
  fCanvas->Update();
  //  Ltmp->Add(fCanvas);
  //  gMyRootApp->Run(kTRUE);
  //  sleep(10);
  cout << Form("\n\033[1;31m Hit any key or double-click mouse  \033[0m\n") << flush;
  cout << Form("\033[1;31m to LEAVE graphics windows!!! \033[0m") << flush;
  fCanvas->WaitPrimitive(); //double-click or hit key to leave
}

int cFCgraphics::GetNumberOfListEntries() {
  TListIter next(L);
  TObject *to;
  int count=0;
  while ((to=next())) {count++;}
  return count;
}

void cFCgraphics::Print(string OutFilename) {
  //    TListIter next(Ltmp);
  //    TCanvas *pcanvas = (TCanvas*)next();
  fCanvas->Modified();
  fCanvas->SaveAs(OutFilename.c_str());
}

TPad* cFCgraphics::CreatePad(string PadName) {
  Mpad[PadName] = new TPad(PadName.c_str(),PadName.c_str(), 0.01,0.01,0.98,0.98);
  return Mpad[PadName];  
}

void cFCgraphics::AddObject(TObject *obj, string PadName) {
  if (obj->InheritsFrom("TF1") | obj->InheritsFrom("TH1")  ) { 
    cout << Form("[cFCgraphics::AddObject] %s added to Pad %s...\n", obj->GetName(), PadName.c_str());
  }
  itMpad = Mpad.find(PadName);
  if (itMpad != Mpad.end()) {
    itMpad->second->cd();
    //    obj->AppendPad();
    TList *li = itMpad->second->GetListOfPrimitives();
    if (!li->GetSize()) {
      obj->Draw();
    } else {
      obj->Draw("same");
    }
  }
}

void cFCgraphics::AddObject(TObject *obj, string PadName, string sopt) {
  if (obj->InheritsFrom("TF1") | obj->InheritsFrom("TH1")  ) { 
    cout << Form("[cFCgraphics::AddObject] %s added to Pad %s...\n", obj->GetName(), PadName.c_str());
  }
  itMpad = Mpad.find(PadName);
  if (itMpad != Mpad.end()) {
    itMpad->second->cd();
    //    obj->AppendPad();
    obj->Draw(sopt.c_str());
  }
  itMpad->second->Update();
}


void cFCgraphics::DrawPad(string PadName) {
  //new canvas
  itMpad = Mpad.find(PadName);
  if (itMpad != Mpad.end()) {
    fCanvas->cd();
    fCanvas->GetListOfPrimitives()->Add(itMpad->second);
    //    itMpad->second->AppendPad();
  }
  fCanvas->Modified();
  fCanvas->Update();
  fCanvas->Draw();
  cout << Form("\033[1;31m Hit any key or double-click mouse  \033[0m\n") << flush;
  cout << Form("\033[1;31m to LEAVE graphics windows!!! \033[0m") << flush;
  fCanvas->WaitPrimitive(); //double-click or hit key to leave

}

void cFCgraphics::DumpPad(string PadName) {
  TList *tl;
  itMpad = Mpad.find(PadName);
  if (itMpad != Mpad.end()) {
    tl = itMpad->second->GetListOfPrimitives();
    if (!tl) return;
    TListIter next(tl);
    TObject *to;
    while ((to=next())) {
      cout << to->GetName() << endl;
    }
  }
}

