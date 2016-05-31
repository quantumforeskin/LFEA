#ifndef uLRCtreeSIM_h
#define uLRCtreeSIM_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "TObject.h"

class uLRCtreeSIM {
 public:
  uLRCtreeSIM(TString treename);               //Constructor que faz load da tree contida no ficheiro "treename"
  virtual ~uLRCtreeSIM();
  virtual Int_t    Cut(Long64_t entry);        //Método para selecção de eventos
  virtual Int_t    GetEntry(Long64_t entry);   //Load do evento número entry
  virtual Long64_t LoadTree(Long64_t entry);   //Localização do evento na chain
  virtual void     Loop();                     //Loop sobre todos os eventos
  virtual Bool_t   Notify();                   //Output standard
  virtual void     Show(Long64_t entry = -1);  //Mostra informação sobre o evento
  virtual void     Init(TTree *tree);          //Inicialização da tree

  TTree          *fChain;   //!pointer to the analyzed TTree or TChain
  Int_t           fCurrent; //!current Tree number in a TChain

  // Fixed size dimensions of array or collections stored in the TTree if any.
  static const Int_t kMaxvphotons = 55118;

  // Declaration of leaf types
  //SimEvent        *SimEvent;
  UInt_t          fUniqueID;
  UInt_t          fBits;
  Int_t           pid;
  Double_t        x_imp;
  Double_t        y_imp;
  Double_t        energy;
  Int_t           nsci;
  Int_t           ndet;
  Int_t           vphotons_;
  UInt_t          vphotons_fUniqueID[kMaxvphotons];   //[vphotons_]
  UInt_t          vphotons_fBits[kMaxvphotons];   //[vphotons_]
  Double_t        vphotons_x_i[kMaxvphotons];   //[vphotons_]
  Double_t        vphotons_y_i[kMaxvphotons];   //[vphotons_]
  Double_t        vphotons_x_f[kMaxvphotons];   //[vphotons_]
  Double_t        vphotons_y_f[kMaxvphotons];   //[vphotons_]
  Double_t        vphotons_length[kMaxvphotons];   //[vphotons_]
  Double_t        vphotons_lambda[kMaxvphotons];   //[vphotons_]
  Bool_t          vphotons_is_detected[kMaxvphotons];   //[vphotons_]
  Bool_t          vphotons_is_sci_abs[kMaxvphotons];   //[vphotons_]
  Bool_t          vphotons_is_alu_abs[kMaxvphotons];   //[vphotons_]
  Int_t           vphotons_nrefl[kMaxvphotons];   //[vphotons_]
  Int_t           vphotons_nalurefl[kMaxvphotons];   //[vphotons_]

  // List of branches
  TBranch        *b_SimEvent_fUniqueID;   //!
  TBranch        *b_SimEvent_fBits;   //!
  TBranch        *b_SimEvent_pid;   //!
  TBranch        *b_SimEvent_x_imp;   //!
  TBranch        *b_SimEvent_y_imp;   //!
  TBranch        *b_SimEvent_energy;   //!
  TBranch        *b_SimEvent_nsci;   //!
  TBranch        *b_SimEvent_ndet;   //!
  TBranch        *b_SimEvent_vphotons_;   //!
  TBranch        *b_vphotons_fUniqueID;   //!
  TBranch        *b_vphotons_fBits;   //!
  TBranch        *b_vphotons_x_i;   //!
  TBranch        *b_vphotons_y_i;   //!
  TBranch        *b_vphotons_x_f;   //!
  TBranch        *b_vphotons_y_f;   //!
  TBranch        *b_vphotons_length;   //!
  TBranch        *b_vphotons_lambda;   //!
  TBranch        *b_vphotons_is_detected;   //!
  TBranch        *b_vphotons_is_sci_abs;   //!
  TBranch        *b_vphotons_is_alu_abs;   //!
  TBranch        *b_vphotons_nrefl;   //!
  TBranch        *b_vphotons_nalurefl;   //!

};

#endif
