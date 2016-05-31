//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Mar  7 13:11:50 2013 by ROOT version 5.34/02
// from TTree LRCTree/LRC Event Tree
// found on file: acq_muon_cint1_06Nov2013.root
//////////////////////////////////////////////////////////

#ifndef uLRCTree_h
#define uLRCTree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1F.h>
#include <TObject.h>

#include <string>
#include <vector>
using namespace std;

#ifdef __APPLE__
#include <_types/_uint8_t.h>
#include <_types/_uint32_t.h>
#else
#include <stdint.h>
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////
class uLRCtreeACQ: public TObject {

 public:

  uLRCtreeACQ(string filename, string treename = "LRCtree");               //Constructor que faz load da tree contida no ficheiro "treename"
  virtual ~uLRCtreeACQ();

  virtual Int_t    Cut(Long64_t entry);        //Método para selecção de eventos
  virtual Int_t    GetEntry(Long64_t entry);   //Load do evento número entry
  virtual Long64_t LoadTree(Long64_t entry);   //Localização do evento na chain
  virtual void     Loop();                     //Loop sobre todos os eventos
  virtual Bool_t   Notify();                   //Output standard
  virtual void     Show(Long64_t entry = -1);  //Mostra informação sobre o evento
  virtual void     Init(TTree *tree);          //Inicialização da tree

  int GetNEvents() {return fChain->GetEntries();}

  vector<int> GetChannel(int evt, int channel = 0);             //Vector com os 256 canais relativos a um canal da LIPPAD
  TH1F** GetAllChannels(int evt);                     //Array de histogramas com os 6 canais da LIPPAD

  ClassDef(uLRCtreeACQ,1);

  TTree          *fChain;   //!pointer to the analyzed TTree or TChain
  Int_t           fCurrent; //!current Tree number in a TChain

  // Declaration of leaf types
  // LRCevent        *LRCevent;
  UInt_t          fUniqueID;
  UInt_t          fBits;
  Int_t           EventSize;
  UInt_t          RunNumber;
  UInt_t          EventNumber;
  UChar_t         EventType;
  UChar_t         CrateNumber;
  string          ModuleId;
  UInt_t          EvTime_sec;
  UInt_t          EvTime_usec;
  string          EventTag;
  vector<unsigned int> ModuleEvent;

   // List of branches
   TBranch        *b_LRCevent_fUniqueID;   //!
   TBranch        *b_LRCevent_fBits;   //!
   TBranch        *b_LRCevent_EventSize;   //!
   TBranch        *b_LRCevent_RunNumber;   //!
   TBranch        *b_LRCevent_EventNumber;   //!
   TBranch        *b_LRCevent_EventType;   //!
   TBranch        *b_LRCevent_CrateNumber;   //!
   TBranch        *b_LRCevent_ModuleId;   //!
   TBranch        *b_LRCevent_EvTime_sec;   //!
   TBranch        *b_LRCevent_EvTime_usec;   //!
   TBranch        *b_LRCevent_EventTag;   //!
   TBranch        *b_LRCevent_ModuleEvent;   //!

 private:
   TH1F **ph;

};

typedef struct _LIPPAD_WORD {
    union{
        uint32_t word32;
    struct {
      unsigned int active_channel:1,
        channel_number:3,
        dummy1:4,
        sampling_number:8,
        adc_value:10,
        dummy2:6;
    } bit_field;
    };
} LIPPAD_WORD;

#endif
