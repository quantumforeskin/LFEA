/**
 * \file    LRCevent.C
 * \authors F.Barao, M.Jordao
 * \date    Jul.08 (last update: Nov.08)
 *
 */


//C+
#include <iostream>
#include <string>

//C
#include <sys/time.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>    /* data types */

//my classes
#include "LRCtime.h"
#include "LRCevent.h"
#include "V965ADefs.h"
#include "V1290Data.h"
#include "LRCLipPad.h"

using namespace std;

//ROOT
ClassImp(LRCevent);

///////////////////////////////////////////////////////////////////////
LRCevent::LRCevent() {
  //event variables
  EventSize        = 0;
  RunNumber        = 0;
  EventNumber      = 0;
  EventType        = (uint8_t)LRC_EVENT;
  ModuleId         = "";
  EvTime_sec       = 0;
  EvTime_usec      = 0;
  EventTag         = "";
}

LRCevent::LRCevent(int r, int e) {
  //event variables
  EventSize        = 0;
  RunNumber        = (uint32_t)r;
  EventNumber      = (uint32_t)e;
  EventType        = (uint8_t)LRC_EVENT;
  ModuleId         = "";
  EvTime_sec       = 0;
  EvTime_usec      = 0;
  EventTag         = "";
}

///////////////////////////////////////////////////////////////////////
LRCevent::~LRCevent() {
  ModuleEvent.clear();
}

///////////////////////////////////////////////////////////////////////
void LRCevent::ResetEvent() {
  ModuleEvent.clear();
  EventSize   = 0;
  EventType   = (uint8_t)LRC_EVENT;
  ModuleId    = "";
  EvTime_sec  = 0;
  EvTime_usec = 0;
  EventTag    = "";
}

///////////////////////////////////////////////////////////////////////
void LRCevent::ResetModuleEvent() {
  ModuleEvent.clear();
}

///////////////////////////////////////////////////////////////////////
int LRCevent::GetEventSize() {return (int)EventSize;}

///////////////////////////////////////////////////////////////////////
void LRCevent::SetEventTime() {
  ///set event time
  LRCtime t;
  EvTime_sec = (uint32_t)t.GetTime1970sec();
  EvTime_usec = (uint32_t)t.GetTime1970usec();
}
int    LRCevent::GetEventTimeSec()  { return (int)EvTime_sec;}
int    LRCevent::GetEventTimeuSec() { return (int)EvTime_usec;}
double LRCevent::GetEventTimefull() { return (double)EvTime_sec + 1.0E-6*(double)EvTime_usec;}

///////////////////////////////////////////////////////////////////////
void   LRCevent::SetModuleId(string Module) {ModuleId = Module;}
string LRCevent::GetModuleId() {return ModuleId;}

///////////////////////////////////////////////////////////////////////
void   LRCevent::SetEventTag(string Tag) {EventTag = Tag;}
string LRCevent::GetEventTag() {return EventTag;}

///////////////////////////////////////////////////////////////////////
void   LRCevent::SetCrateNumber(int cnb) {CrateNumber = (uint8_t)cnb;}
int    LRCevent::GetCrateNumber() {return static_cast<int>(CrateNumber);}

///////////////////////////////////////////////////////////////////////
void LRCevent::SetEventDataWord(uint32_t data) {ModuleEvent.push_back(data);}

///////////////////////////////////////////////////////////////////////
int LRCevent::GetNumberDataWords() {return (int)ModuleEvent.size();}

///////////////////////////////////////////////////////////////////////
int LRCevent::GetDataValue(uint32_t ch) {
#ifdef DEBUG
  cout << "(LRCevent::GetDataValue) get value for channel..." << ch << endl;
#endif
  uint32_t range, channel, adc;
  int adcv = -9999;
  for (size_t i=0; i<ModuleEvent.size(); i++) {
    int DataTag = ModuleEvent[i]&V965AMaskDataTag;
    if (DataTag == 0) { //data word found
      range   = (ModuleEvent[i]&V965AMaskRange)>>17;
      channel = (ModuleEvent[i]&V965AMaskChannel)>>18;
      adc     = ModuleEvent[i]&V965AMaskData;
#ifdef DEBUG
      cout << "(LRCevent::GetDataValue) data word: range=" << range
           << " channel= " << channel << "  adc=" << adc << endl;
#endif
      if (channel == ch) {
	adcv = adc;
#ifdef DEBUG
	cout << "(LRCevent::GetDataValue) FOUND adc value = " << adcv << "  for channel " << ch << endl;
#endif
      }
    }
  }
  return adcv;
}

///////////////////////////////////////////////////////////////////////
uint32_t LRCevent::GetDataWord(int index) {
#ifdef DEBUG
  cout << "(LRCevent::GetDataWord) get data word at position..." << index << endl;
#endif
  return ModuleEvent.at(index);
}

///////////////////////////////////////////////////////////////////////
void LRCevent::SetEventNumber(int n) {EventNumber = (uint32_t)n;}

///////////////////////////////////////////////////////////////////////
int LRCevent::GetEventNumber() {return (int)EventNumber;}

///////////////////////////////////////////////////////////////////////
// DATA Streaming
///////////////////////////////////////////////////////////////////////
//
// Event format streamer
// ---------------------
// Event size (int)
// Run number (uint32_t)
// Event Number (uint32_t)
// Crate Number (int)
// Event Type (EventObjectType)
// Event tag (string)
// Nb of Acq Module data words (uint32_t)
// Data words (uint32_t)
// ...
// Module identifier (string)
// Event time sec (float)
// Event time usec (float)

//
//////////////////////////////////////////////////////////////////////
//bool LRCevent::IsSerialized() {return EventSerialized;}

//////////////////////////////////////////////////////////////////////
//void LRCevent::SetFlagSerialized() {EventSerialized = 1;}

/// Event serialization
/// Format: Event Size in bytes (2 bytes)
///         Run Number          (4 bytes)
///         Event Number        (4 bytes)
///         Crate Number        (4 bytes)
///         Event Type          (1 byte )
///         Event Tag           (? bytes)
///         Module Id
///         Nb of Module words following
///         Module words data
///         ...
///         Event Time (sec)
///         Event Time (microsec)

//////////////////////////////////////////////////////////////////////
int LRCevent::Serialize(LRCbuffer*& pbuf) {
#ifdef PRINT
  cout << "(LRCevent::Serialize) Serialize event... " << flush;
#endif
  //reset buffer
  pbuf->ResetBuffer();
  //dump LRCevent data (order is important!)
  pbuf->write(RunNumber);
  pbuf->write(EventNumber);
  pbuf->write(EventType);
  pbuf->write(CrateNumber);
  pbuf->write(EventTag);
  pbuf->write(ModuleId);
  uint32_t ModuleEventSize = ModuleEvent.size();
  pbuf->write(ModuleEventSize);
  for (size_t i=0; i<ModuleEvent.size(); ++i) {pbuf->write(ModuleEvent[i]);}
  pbuf->write(EvTime_sec);
  pbuf->write(EvTime_usec);
  //last...add the event size and return it
  size_t nbytes = pbuf->AddEventSize();
  //flag it
  //  EventSerialized = true;

  //event size read from buffer
  EventSize = pbuf->GetEventSize();

#ifdef PRINT
  cout << "event size [ = " << nbytes << "] bytes, DONE!" << endl;
#endif
#ifdef DEBUG
  pbuf->PrintOut();
#endif

  //return
  return (int)nbytes;
}

///////////////////////////////////////////////////////////////////////
void LRCevent::DeSerialize(LRCbuffer*& pbuf) {

#ifdef PRINT
    cout << "[LRCevent::DeSerialize] Recover event from stream... " << endl;
#endif

#ifdef DEBUG
    pbuf->PrintOut();
#endif

    cout << "[(LRCevent::DeSerialize) "<< flush;

    //init event
    ModuleEvent.clear();
    EventSize = pbuf->GetEventSize(); //passive method for getting event size

    //LRCevent RECOVERING from buffer
    uint16_t nbytes=0;
    pbuf->read(nbytes);
    cout << "event size=" << dec << (int)nbytes << " bytes " << flush;
    //recover data
    pbuf->read(RunNumber); //cout << RunNumber << endl;
    pbuf->read(EventNumber); //cout << EventNumber << endl;
    pbuf->read(EventType); //cout << ObjectType << endl;
    pbuf->read(CrateNumber);
    pbuf->read(EventTag); //cout << EventTag << endl;
    pbuf->read(ModuleId);
    uint32_t ModuleEventSize = 0;
    pbuf->read(ModuleEventSize);
    cout << " | ModuleEventSize=" << dec << ModuleEventSize << flush;
    for (uint32_t i=0; i<ModuleEventSize; ++i) {
      uint32_t aux = 0;
      pbuf->read(aux);
      ModuleEvent.push_back(aux);
    }
    pbuf->read(EvTime_sec);
    pbuf->read(EvTime_usec);

    //end cout
    cout << "]" << endl;
}

///////////////////////////////////////////////////////////////////////
void LRCevent::PrintOut() {

  cout << "(LRCevent::PrintOut) ======================================" << endl;

  cout << " ---> Event number      : " << dec << EventNumber << endl;
  cout << " ---> Event Size [bytes]: " << dec << EventSize << " (" << sizeof(*this) << ")" << endl;
  cout << " ---> Run number        : " << dec << RunNumber << endl;
  cout << " ---> Crate number      : " << dec << RunNumber << endl;
  cout << " ---> ModuleId          : " << dec << ModuleId << endl;
  cout << " ---> EventTag          : " << EventTag << endl;
  cout << " ---> Module Nb of words: " << ModuleEvent.size()  << endl;

  if (ModuleId == "V965A" || ModuleId == "DUMMY") {

    for (size_t i=0; i<ModuleEvent.size(); i++) {
      cout << " ..... ModuleEvent (hex): " << hex << ModuleEvent[i]
	   << " (" << dec << ModuleEvent[i] << ")"
	   << " [WordTag=" << (int)((ModuleEvent[i]&V965AMaskDataTag)>>24) << "]"
	   << " [Ch="      << (int)((ModuleEvent[i]&V965AMaskChannel)>>18) << "]"
	   << " [Un="      << (int)((ModuleEvent[i]&V965AMaskUnderTh)>>13) << "]"
	   << " [Ov="      << (int)((ModuleEvent[i]&V965AMaskOverflow)>>12) << "]"
	   << " [Rg="      << (int)((ModuleEvent[i]&V965AMaskRange)>>17) << "]"
	   << " [adc="     << (int)(ModuleEvent[i]&V965AMaskData) << "]" << endl;
    }

  } else if (ModuleId == "V1290N") {

    for (size_t i=0; i<ModuleEvent.size(); i++) {
      cout << " ..... ModuleEvent (hex): " << hex << ModuleEvent[i]
	   << " (" << dec << ModuleEvent[i] << ")"
	   << " [Tag =" << (int)((ModuleEvent[i]&V1290Data::TYPE_MASK)>>V1290Data::TDC_TYPE_RSHIFT) << "]"
	   << " [Ch  =" << (int)((ModuleEvent[i]&V1290Data::TDC_CHANNEL_MASK)>>V1290Data::TDC_CHANNEL_RSHIFT) << "]"
	   << " [tdc =" << (int)(ModuleEvent[i]&V1290Data::TDC_DATA_MASK)
	   << "(" <<  (int)(ModuleEvent[i]&V1290Data::TDC_DATA_MASK)*25 << "psec | "
  	   << "(" <<  (int)(ModuleEvent[i]&V1290Data::TDC_DATA_MASK)*25*1.E-12 << "sec ) " << " ]"
	   << " [trailing =" << (int)((ModuleEvent[i]&V1290Data::TDC_TRAILING_BIT)>>26) << "]" << endl;
    }

  } else if (ModuleId == "LipPad") {

    LIPPAD_WORD LipPadData;
    for (size_t i=0; i<ModuleEvent.size(); i++) {
      LipPadData.word32 = ModuleEvent[i];
       if ((int)LipPadData.bit_field.adc_value) {
 	cout << " ..... ModuleEvent (hex): " << hex << ModuleEvent[i]
 	     << " (" << dec << ModuleEvent[i] << ")"
 	     << " [Channel=" << (int)LipPadData.bit_field.channel_number << "]"
 	     << " [ActiveFlag=" << (int)LipPadData.bit_field.active_channel << "]"
 	     << " [" << (int)LipPadData.bit_field.sampling_number << "]"
 	     << " [ADC value =" << (int)LipPadData.bit_field.adc_value << "]" << endl;
       }
    }
  }

  cout << "(LRCevent::PrintOut) ======================================" << endl;

}
