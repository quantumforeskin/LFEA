//C
#include <stdint.h> //data types

//C++
#include <string>
#include <iostream>
using namespace std;

//LipPad driver
#include "pciLip_Pad_struct.h"

//MY
#include "LRCConfigLipPad.h"
#include "LRCbuffer.h"

//ROOT
#include "TROOT.h"
#include "TBufferFile.h"
// ClassImp(LRCConfigLipPad);

////////////////////////////////////////////////////////////////////////////////////////
LRCConfigLipPad::LRCConfigLipPad() {
  //init config register
  ConfigReg=0;
  //init delay register
  DelayReg=0;
  // Initializate Thresholds
  for (int i=0; i<6; i++) {
    Threshold[i] = 0;
  }
}

////////////////////////////////////////////////////////////////////////////////////////
LRCConfigLipPad::~LRCConfigLipPad() {;}

////////////////////////////////////////////////////////////////////////////////////////
void LRCConfigLipPad::SetActiveInputChannels(int Active) {
  CONFIG_REG tConfigReg;
  tConfigReg.reg32 = ConfigReg;
  tConfigReg.cfgFlds.actv_input_chnls = (0x3F)&Active;
  ConfigReg = tConfigReg.reg32;
}
int  LRCConfigLipPad::GetActiveInputChannels() {
  CONFIG_REG tConfigReg;
  tConfigReg.reg32 = ConfigReg;
  return (int)tConfigReg.cfgFlds.actv_input_chnls;
}

////////////////////////////////////////////////////////////////////////////////////////
void LRCConfigLipPad::SetTriggerType(int value) {
  CONFIG_REG tConfigReg;
  tConfigReg.reg32 = ConfigReg;
  tConfigReg.cfgFlds.trigger_type = (0x3)&value;
  ConfigReg = tConfigReg.reg32;
}
int  LRCConfigLipPad::GetTriggerType() {
  CONFIG_REG tConfigReg;
  tConfigReg.reg32 = ConfigReg;
  return (int)tConfigReg.cfgFlds.trigger_type;
}

////////////////////////////////////////////////////////////////////////////////////////
void LRCConfigLipPad::SetStatus(int value) {
  CONFIG_REG tConfigReg;
  tConfigReg.reg32 = ConfigReg;
  tConfigReg.cfgFlds.status = (0xF)&value;
  ConfigReg = tConfigReg.reg32;
}
int  LRCConfigLipPad::GetStatus() {
  CONFIG_REG tConfigReg;
  tConfigReg.reg32 = ConfigReg;
  return (int)tConfigReg.cfgFlds.status;
}

////////////////////////////////////////////////////////////////////////////////////////
void LRCConfigLipPad::SetTriggerPosition(int value) {
  TRIGDELAY_REG tDelayReg;
  tDelayReg.reg32 = DelayReg;
  tDelayReg.trgDlyFlds.trig_pos = (0xFF)&value;
  DelayReg = tDelayReg.reg32;
}
int  LRCConfigLipPad::GetTriggerPosition() {
  TRIGDELAY_REG tDelayReg;
  tDelayReg.reg32 = DelayReg;
  return (int)tDelayReg.trgDlyFlds.trig_pos;
}

////////////////////////////////////////////////////////////////////////////////////////
void LRCConfigLipPad::SetInhibitTime(int value) {
  TRIGDELAY_REG tDelayReg;
  tDelayReg.reg32 = DelayReg;
  tDelayReg.trgDlyFlds.d = (0xFF)&value;
  DelayReg = tDelayReg.reg32;
}
int  LRCConfigLipPad::GetInhibitTime() {
  TRIGDELAY_REG tDelayReg;
  tDelayReg.reg32 = DelayReg;
  return (int)tDelayReg.trgDlyFlds.d;
}

////////////////////////////////////////////////////////////////////////////////////////
void LRCConfigLipPad::SetWindowTime(int value) {
  TRIGDELAY_REG tDelayReg;
  tDelayReg.reg32 = DelayReg;
  tDelayReg.trgDlyFlds.t = (0xFF)&value;
  DelayReg = tDelayReg.reg32;
}
int  LRCConfigLipPad::GetWindowTime() {
  TRIGDELAY_REG tDelayReg;
  tDelayReg.reg32 = DelayReg;
  return (int)tDelayReg.trgDlyFlds.t;
}

////////////////////////////////////////////////////////////////////////////////////////
void LRCConfigLipPad::SetThresholds(int *p) {
  for (int i=0; i<6; i++) {Threshold[i] = p[i];}
}
void LRCConfigLipPad::GetThresholds(int *&p) {
  for (int i=0; i<6; i++) {p[i] = Threshold[i];}
}

////////////////////////////////////////////////////////////////////////////////////////
void LRCConfigLipPad::SetConfigRegister(uint32_t a) {ConfigReg = a;}
int  LRCConfigLipPad::GetConfigRegister() {return (int)ConfigReg;}

////////////////////////////////////////////////////////////////////////////////////////
void LRCConfigLipPad::SetDelayRegister(uint32_t a) {DelayReg = a;}
int  LRCConfigLipPad::GetDelayRegister() {return (int)DelayReg;}

////////////////////////////////////////////////////////////////////////////////////////
void LRCConfigLipPad::PrintOut() {
  TRIGDELAY_REG tDelayReg;
  tDelayReg.reg32 = DelayReg;
  CONFIG_REG tConfigReg;
  tConfigReg.reg32 = ConfigReg;

  cout <<"[LRCConfigLipPad::PrintOut] **************************************************" << endl;
  cout << "Active Input Channels: " << hex << tConfigReg.cfgFlds.actv_input_chnls <<dec << endl;
  cout << "Trigger Type         : " << hex << tConfigReg.cfgFlds.trigger_type << dec << endl;
  cout << "Status               : " << hex << tConfigReg.cfgFlds.status << dec << endl;
  cout << "Trigger Position     : " << tDelayReg.trgDlyFlds.trig_pos << endl;
  cout << "Inhibit Time[0...256]: " << tDelayReg.trgDlyFlds.d << endl;
  cout << "Window Time[0...256] : " << tDelayReg.trgDlyFlds.t << endl;
  cout << "Threshold            : " << flush;
  for (int i=0; i<6; i++) {
    cout << "(" << i << ")" << Threshold[i] << " " << flush;
  }
  cout <<"[LRCConfigLipPad::PrintOut] END ***********************************************" << endl;
}


//////////////////////////////////////////////////////////////////////
int LRCConfigLipPad::Serialize(LRCbuffer*& pbuf) {
  pbuf->ResetBuffer();
  TBufferFile btemp(TBuffer::kWrite);
  btemp.WriteObject(this);
  int bsize = btemp.Length();
  byte *pchar = new byte[bsize];
  memcpy(pchar,btemp.Buffer(),bsize);
  for (int i=0; i<bsize; i++) {
    pbuf->write(pchar[i]);
  }
  return bsize;
}
void LRCConfigLipPad::DeSerialize(LRCbuffer*& pbuf) {
  TBufferFile btemp(TBuffer::kRead);
  int bsize = (int)pbuf->GetBufferSize();
  byte *pchar = new byte[bsize];
  for (int i=0; i<bsize; i++) {
    pbuf->read(pchar[i]);
  }
  btemp.SetBuffer(pchar,bsize,kFALSE);
  LRCConfigLipPad *a = dynamic_cast<LRCConfigLipPad *>(btemp.ReadObject(gROOT->GetClass("LRCConfigLipPad")));
  this->SetConfigRegister(a->GetConfigRegister());
  this->SetDelayRegister(a->GetDelayRegister());
  int *th = new int[6];
  a->GetThresholds(th);
  this->SetThresholds(th);
  delete []th;
}
