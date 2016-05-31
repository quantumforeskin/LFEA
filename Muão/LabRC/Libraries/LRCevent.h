/**
 * \file LRCevent.h
 * \authors F.Barao, M.Jordao
 * 
 * 
 */

//STL
#include <vector>
using std::vector;

//C
#include <stdint.h> //data types

//C++
#include <string>
using std::string;

//ROOT
#include <TObject.h> 

//forward
#include "LRCbuffer.h"

/////////////////////////////////////////////////////////////////////////

class LRCevent: public TObject {
 
 public:
  LRCevent();
  LRCevent(int,int); //run and event number
  ~LRCevent();

  void   ResetEvent();
  void   ResetModuleEvent();

  void   SetModuleId(string);
  string GetModuleId(); 
 
  void   SetEventTime();
  int    GetEventTimeSec();           ///< get event time in seconds (since jan 1, 1970) 
  int    GetEventTimeuSec();          ///< get event time in microseconds (since event time in seconds) 
  double GetEventTimefull();          ///< get event full time adding seconds+microseconds (double) 

  void   SetEventTag(string);
  string GetEventTag();  

  int    GetEventNumber();
  void   SetEventNumber(int);

  int    GetCrateNumber();
  void   SetCrateNumber(int);

  int    GetEventSize();
  int    GetNumberDataWords();

  void   SetEventDataWord(uint32_t);
  int    GetDataValue(uint32_t);      /// get data value for a given channel (VME)
  uint32_t GetDataWord(int);          /// get full word for a given channel

  int    Serialize(LRCbuffer*&);      /// get event serialized into buffer
  void   DeSerialize(LRCbuffer*&);    /// get event deserialized from buffer

  void   PrintOut();

  ClassDef(LRCevent,1);

 private:
  int      EventSize;              /// event size in bytes

  uint32_t RunNumber;              /// run number
  uint32_t EventNumber;            /// event number
  uint8_t  EventType;              /// see LRCbuffer.h
  uint8_t  CrateNumber;            /// crate number
  string   ModuleId;               /// Module Id
  uint32_t EvTime_sec;             /// time in seconds since January 1, 1970
  uint32_t EvTime_usec;            /// aditional micro-seconds time (for sec)
  string   EventTag;               /// module tag (ADC, QDC, TDC)
  vector<uint32_t> ModuleEvent;    /// Event data words from acqusition modules (vme, lippad, ...)
};


