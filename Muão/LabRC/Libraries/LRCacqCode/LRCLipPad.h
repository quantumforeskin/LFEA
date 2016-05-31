//C
#include <stdint.h> //data types

//STL
#include <string>
#include <vector>
using std::vector;
using std::string;

//forward declaration
class LRCConfigLipPad;
class LRCevent;

///////////////////////////////////////////////////////////////////////////////////

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

///////////////////////////////////////////////////////////////////////////////////

class LRCLipPad {

 public:
  LRCLipPad();
  ~LRCLipPad();

  void Start();
  void Stop(); 
  void GenerateTestPulse();
  void SetConfig(LRCConfigLipPad *);
  void GetConfig(LRCConfigLipPad *&);
  int  GetEvent(LRCevent *);

  int    GetStatus();
  int    GetTriggerType();
  int    GetActiveChannels();
  int    GetTriggerPosition();
  int    GetInhibitTime();
  int    GetWindowTime();
  int    GetThreshold(int);
  vector<int*> ReadChannels();

  void   SetTriggerType(int);
  void   SetActiveChannels(int);  ///bitted word with active channels
  void   SetTriggerPosition(int);
  void   SetInhibitTime(int);
  void   SetWindowTime(int);
  void   SetThreshold(int,int);

 private:
  string   DeviceName;      ///< device name
  int      fd;              ///< file descriptor
  uint32_t *FIFO1Buffer;    ///< fifo 1 buffer
  uint32_t *FIFO2Buffer;    ///< fifo 2 buffer
  int      EventNumber;     ///< event number
};
