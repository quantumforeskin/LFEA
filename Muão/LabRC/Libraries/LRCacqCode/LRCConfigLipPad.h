//C
#include <stdint.h> //data types

//C++
#include <string>
using namespace std;

//ROOT
#include "TObject.h"

//LipPad driver
//#include "pciLip_Pad_struct.h"

//forward
#include "LRCbuffer.h"

////////////////////////////////////////////////////////////////////////////////////////

class LRCConfigLipPad: public TObject {
  public:
    LRCConfigLipPad();
    ~LRCConfigLipPad();

    void PrintOut();

    void SetActiveInputChannels(int);
    void SetTriggerType(int);
    void SetTriggerPosition(int);
    void SetInhibitTime(int);
    void SetWindowTime(int);
    void SetStatus(int);

    void SetConfigRegister(uint32_t);
    void SetDelayRegister(uint32_t);
    void SetThresholds(int*);

    int  GetActiveInputChannels();
    int  GetTriggerType();
    int  GetTriggerPosition();
    int  GetInhibitTime();
    int  GetWindowTime();
    int  GetStatus();

    void GetThresholds(int*&);
    int  GetConfigRegister();
    int  GetDelayRegister();

    int    Serialize(LRCbuffer*&);    //get event serialized into buffer
    void   DeSerialize(LRCbuffer*&);  //get event deserialized from buffer

    // ClassDef(LRCConfigLipPad,1);

  private:
    uint32_t ConfigReg;     /// Configuration register
    uint32_t DelayReg;   /// Delay register
    int      Threshold[6]; /// threshold values for 6 channels
};
