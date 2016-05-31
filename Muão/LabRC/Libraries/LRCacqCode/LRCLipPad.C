//linux
#include <sys/ioctl.h>

//C
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdint.h> //types
#include <math.h>
#ifdef __APPLE__
#include "unistd.h"
#endif

//C++
#include <string>
#include <iostream>
#include <vector>
using namespace std;

//LipPad driver
#include <pciLip_Pad_struct.h> 
#include <pciLip_Pad_ioctl.h>

//MY
#include "LRCexceptions.h"
#include "LRCConfigLipPad.h"
#include "LRCLipPad.h"
#include "LRCevent.h"


//////////////////////////////////////////////////////////////////////////////
LRCLipPad::LRCLipPad() {

  //open device
  DeviceName = "/dev/pciLipPad0";
  int flags = 0 | O_RDONLY;
  fd = open(DeviceName.c_str(),flags); // Opening the device  */
  if (fd==-1) { 
    throw LipPad_Exception("Error: cannot open device /dev/pciLipPad0",1);
  }
 
  // .......... create buffers for reading fifos

  FIFO1Buffer = new uint32_t[256];
  FIFO2Buffer = new uint32_t[256];

  //event number
  EventNumber = 0;
}

//////////////////////////////////////////////////////////////////////////////
LRCLipPad::~LRCLipPad() {
  //delete fifos buffers
  delete [] FIFO1Buffer;
  delete [] FIFO2Buffer;
  FIFO1Buffer = NULL;
  FIFO2Buffer = NULL;
  //stop card
  int rc = 0;
  rc = ioctl(fd, PCI_LIP_PAD_IOCT_STOP);
  //close device
  close(fd);  
}

//////////////////////////////////////////////////////////////////////////////
void LRCLipPad::Start() {
  cout << "[LRCLipPad::Start] Starting LipPad card..." << endl;  
  int rc=0;
  rc = ioctl(fd, PCI_LIP_PAD_IOCT_START);
}

//////////////////////////////////////////////////////////////////////////////
void LRCLipPad::Stop() {
  cout << "[LRCLipPad::Stop] Stopping LipPad card..." << endl;  
  int rc=0;
  rc = ioctl(fd, PCI_LIP_PAD_IOCT_STOP);
}

//////////////////////////////////////////////////////////////////////////////
void LRCLipPad::GenerateTestPulse() { 
  cout << "[LRCLipPad::GenerateTestPulse] Generating test pulse..." << flush;  
  int dummy = 0;
  int rc=0;
  rc = ioctl(fd, PCI_LIP_PAD_IOCS_TEST_PULSE, &dummy);
  cout << "done!" << endl;
}

//////////////////////////////////////////////////////////////////////////////
void LRCLipPad::SetConfig(LRCConfigLipPad *pconfig) {
  int value = 0;
  //trigger type
  value = pconfig->GetTriggerType();
  SetTriggerType(value);
  //active channels
  value = pconfig->GetActiveInputChannels();
  SetActiveChannels(value);
  //trigger position
  value = pconfig->GetTriggerPosition();
  SetTriggerPosition(value);
  //inhibit time
  value = pconfig->GetInhibitTime();
  SetInhibitTime(value);
  //window time
  value = pconfig->GetWindowTime();
  SetWindowTime(value);
  //Threshols
  int *pvalue = new int[6];
  pconfig->GetThresholds(pvalue);
  for (int i=0; i<6; i++) {
    SetThreshold(i,pvalue[i]);
  }
  delete [] pvalue;
}

//////////////////////////////////////////////////////////////////////////////
void LRCLipPad::GetConfig(LRCConfigLipPad *&pconfig) {
  int value = 0;

  //trigger type
  value = GetTriggerType();
  pconfig->SetTriggerType(value);

  //active channels
  value = GetActiveChannels();
  if (value > 0) {
    pconfig->SetActiveInputChannels(value);
  } else {
    cout << "[LRCLipPad::GetConfig] Error on getting active channels!!!" << endl;
    pconfig->SetActiveInputChannels(0);
  }    

  //trigger position
  value = GetTriggerPosition();
  pconfig->SetTriggerPosition(value);

  //inhibit time
  value = GetInhibitTime();
  pconfig->SetInhibitTime(value);

  //window time
  value = GetWindowTime();
  pconfig->SetWindowTime(value);

  //status
  value = GetStatus();
  pconfig->SetStatus(value);

  //Threshols
  int *pvalue = new int[6];
  for (int i=0; i<6; i++) {
    pvalue[i] = GetThreshold(i);
  }
  pconfig->SetThresholds(pvalue);
  delete [] pvalue;
}

//////////////////////////////////////////////////////////////////////////////
int LRCLipPad::GetEvent(LRCevent *pevent) {
  // ret = 0: no event found
  //     = 1: event found

  //  while ( !(0x2&GetStatus()) ) {;} //spinlock waiting for data

  int ret = 1;

  //check LipPad status (is there event?)
  //  cout << "[LRCLipPad::GetEvent] LipPad Status = " << GetStatus() << endl;
  if ((0x2)&GetStatus()) { //event found!
  
    EventNumber++;

    std::cout << "[LRCLipPad::GetEvent] Getting event..." << std::flush;
    pevent->ResetEvent();

    //get LipPad active channels
    int ActiveCh = GetActiveChannels();
    if (ActiveCh < 0) {
      cout << "[LRCLipPad::GetEvent] Error on getting active channels = " << ActiveCh << endl;
      getchar(); 
    }

    //set event data
    vector<uint32_t> EventBuffer;
    LIPPAD_WORD LipPadData;

    vector<int*> pch = ReadChannels(); //read LipPad channels
    for (int i=0; i<6; i++) {
      LipPadData.word32 = 0;
      LipPadData.bit_field.channel_number = i;
      if ((int)pow(2.,i)&ActiveCh) {
	LipPadData.bit_field.active_channel = 1;
      } else {
	LipPadData.bit_field.active_channel = 0;
      }
      for (int j=0; j<256; j++) {
	LipPadData.bit_field.sampling_number = j;
	LipPadData.bit_field.adc_value = pch[i][j];
	EventBuffer.push_back(LipPadData.word32);      
      }
      delete [] pch[i];
    }
    int EventBufferSize = (int)EventBuffer.size();
    //set event structure
    pevent->SetModuleId("LipPad");
    pevent->SetEventTag("LipPad");
    pevent->SetEventTime();
    pevent->SetCrateNumber(0);
    pevent->SetEventNumber(EventNumber);
    for (int i=0; i<EventBufferSize; i++) { pevent->SetEventDataWord(EventBuffer[i]);} 
    EventBuffer.clear();
  } else {
    ret = 0;
  }
  //  cout << " ...DONE!]" << endl;
  return ret;
}

//////////////////////////////////////////////////////////////////////////////
// Getting
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
int LRCLipPad::GetStatus() {
  //bit 0 set = empty FIFO
  //    1     = FIFO full
  //    2     = running
  //    3     = idle
  //  cout << "[LRCLipPad::GetStatus] Status =" << flush;  
  CONFIG_REG config;
  config.reg32 =0;
  int rc=0;
  rc = ioctl(fd, PCI_LIP_PAD_IOCG_READ_CONFIG, &config);
  int ret = (int)config.cfgFlds.status;
  return ret;
}

//////////////////////////////////////////////////////////////////////////////
int LRCLipPad::GetTriggerType() {
  cout << "[LRCLipPad::GetTriggerType] Trigger Type..." << flush;  
  CONFIG_REG config;
  int rc=0;
  rc = ioctl(fd, PCI_LIP_PAD_IOCG_READ_CONFIG, &config);
  int ret = (int)config.cfgFlds.trigger_type;
  return ret;
}

//////////////////////////////////////////////////////////////////////////////
int LRCLipPad::GetActiveChannels() {
  cout << "[LRCLipPad::GetActiveChannels] " << flush;  
  CONFIG_REG config;
  int ret = -1;
  if ( ioctl(fd, PCI_LIP_PAD_IOCG_READ_CONFIG, &config) == 0) {
      ret = config.cfgFlds.actv_input_chnls;
  } 
  cout << "[ret = " << ret << " ]" << flush;
  return ret;
}

//////////////////////////////////////////////////////////////////////////////
int LRCLipPad::GetTriggerPosition() {
  cout << "[LRCLipPad::GetTriggerPosition] trigger position... " << flush;  
  TRIGDELAY_REG trigDelay;
  int rc=0;
  rc = ioctl(fd, PCI_LIP_PAD_IOCG_READ_TRIGDELAY, &trigDelay);
  int ret = (int)trigDelay.trgDlyFlds.trig_pos;
  cout << hex << ret << dec << endl; 
  return ret;
}

//////////////////////////////////////////////////////////////////////////////
int LRCLipPad::GetInhibitTime() {
  cout << "[LRCLipPad::GetInhibitTime] inhibit time... " << flush;  
  TRIGDELAY_REG trigDelay;
  int rc=0;
  rc = ioctl(fd, PCI_LIP_PAD_IOCG_READ_TRIGDELAY, &trigDelay);
  int ret = (int)trigDelay.trgDlyFlds.d;
  cout << hex << ret << dec << endl; 
  return ret;
}

//////////////////////////////////////////////////////////////////////////////
int LRCLipPad::GetWindowTime() {
  cout << "[LRCLipPad::GetWindowTime] window time... " << flush;  
  TRIGDELAY_REG trigDelay;
  int rc=0;
  rc = ioctl(fd, PCI_LIP_PAD_IOCG_READ_TRIGDELAY, &trigDelay);
  int ret = (int)trigDelay.trgDlyFlds.t;
  cout << hex << ret << dec << endl; 
  return ret;
}

//////////////////////////////////////////////////////////////////////////////
int LRCLipPad::GetThreshold(int ch) {
  cout << "[LRCLipPad::GetThreshold] Get threshold for channel ... " << ch << flush;  
  if (ch>5) {cout << "[LRCLipPad::GetThreshold] channel number wrong..." << ch << endl;} 
  int rc=0;
  int thr;
  switch (ch) {
  case 0:
    rc = ioctl(fd, PCI_LIP_PAD_IOCG_READ_THR1, &thr); break;
  case 1:
    rc = ioctl(fd, PCI_LIP_PAD_IOCG_READ_THR2, &thr); break;
  case 2:
    rc = ioctl(fd, PCI_LIP_PAD_IOCG_READ_THR3, &thr); break;
  case 3:
    rc = ioctl(fd, PCI_LIP_PAD_IOCG_READ_THR4, &thr); break;
  case 4:
    rc = ioctl(fd, PCI_LIP_PAD_IOCG_READ_THR5, &thr); break;
  case 5:
    rc = ioctl(fd, PCI_LIP_PAD_IOCG_READ_THR6, &thr); break;
  }
  cout << " = " << thr << endl;
  return thr;
}

//////////////////////////////////////////////////////////////////////////////
vector<int*> LRCLipPad::ReadChannels() {
  // array of pointers to channels data
  vector<int*> pc;
  //init
  int rc=0;
  int nbytes = 256 * sizeof(int);
  //read fifo 1
  rc = ioctl(fd, PCI_LIP_PAD_IOCT_FIFO1); /*point read to fifo 1*/
  rc = read(fd, FIFO1Buffer, nbytes);
  //read fifo 2
  rc = ioctl(fd, PCI_LIP_PAD_IOCT_FIFO2); /*point read to fifo 2*/
  rc = read(fd, FIFO2Buffer, nbytes);
  //get channel arrays with contents
  DATA_REG *pData1 = (DATA_REG *) FIFO1Buffer; 
  DATA_REG *pData2 = (DATA_REG *) FIFO2Buffer;
  //...read channels 
  pc.push_back(new int[256]);
  for (int j=0; j<256; j++) { pc[0][j] = pData1[j].channel1; }
  pc.push_back(new int[256]);
  for (int j=0; j<256; j++) { pc[1][j] = pData1[j].channel2; }
  pc.push_back(new int[256]);
  for (int j=0; j<256; j++) { pc[2][j] = pData1[j].channel3; }
  pc.push_back(new int[256]);
  for (int j=0; j<256; j++) { pc[3][j] = pData2[j].channel1; }
  pc.push_back(new int[256]);
  for (int j=0; j<256; j++) { pc[4][j] = pData2[j].channel2; }
  pc.push_back(new int[256]);
  for (int j=0; j<256; j++) { pc[5][j] = pData2[j].channel3; }
#ifdef DEBUG
  cout << " [LRCLipPad::ReadChannels] ch.0 = " << flush;
  for (int i=0; i<256; i++) {cout << " " << pc[0][i] << flush;}; cout << endl; 
  cout << " [LRCLipPad::ReadChannels] ch.1 = " << flush;
  for (int i=0; i<256; i++) {cout << " " << pc[1][i] << flush;}; cout << endl; 
#endif
  //return array of pointers
  return pc;
}

//////////////////////////////////////////////////////////////////////////////
// Setting
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
void LRCLipPad::SetTriggerType(int trig) {
  CONFIG_REG config;
  int rc=0;
  //read config
  //...read config
  rc = ioctl(fd, PCI_LIP_PAD_IOCG_READ_CONFIG, &config);
  //set trigger type
  config.cfgFlds.trigger_type = (0x3)&trig;
  rc = ioctl(fd, PCI_LIP_PAD_IOCS_WRITE_CONFIG, &config);
}

//////////////////////////////////////////////////////////////////////////////
void LRCLipPad::SetActiveChannels(int chan) {
  //chan: bit word [0...5] with active channels 
  CONFIG_REG config;
  int rc=0;
  //read config
  rc = ioctl(fd, PCI_LIP_PAD_IOCG_READ_CONFIG, &config);
  //set active channels
  config.cfgFlds.actv_input_chnls = (0x3F)&chan;
  rc = ioctl(fd, PCI_LIP_PAD_IOCS_WRITE_CONFIG, &config);
}

//////////////////////////////////////////////////////////////////////////////
void LRCLipPad::SetTriggerPosition(int value) {
  cout << "[LRCLipPad::SetTriggerPosition] " << endl;  
  TRIGDELAY_REG trigDelay;
  int rc=0;
  //read register
  rc = ioctl(fd, PCI_LIP_PAD_IOCG_READ_TRIGDELAY, &trigDelay);
  //set register with trigger position
  trigDelay.trgDlyFlds.trig_pos = (0xFF)&value;
  rc = ioctl(fd, PCI_LIP_PAD_IOCS_WRITE_TRIGDELAY, &trigDelay);
}

//////////////////////////////////////////////////////////////////////////////
void LRCLipPad::SetInhibitTime(int value) {
  cout << "[LRCLipPad::SetInhibitTime]" << endl;  
  TRIGDELAY_REG trigDelay;
  int rc=0;
  //read register
  rc = ioctl(fd, PCI_LIP_PAD_IOCG_READ_TRIGDELAY, &trigDelay);
  //set register with trigger inhibit time
  trigDelay.trgDlyFlds.d = (0xFF)&value;
  rc = ioctl(fd, PCI_LIP_PAD_IOCS_WRITE_TRIGDELAY, &trigDelay);
}

//////////////////////////////////////////////////////////////////////////////
void LRCLipPad::SetWindowTime(int value) {
  cout << "[LRCLipPad::SetWindowTime]" << endl;  
  TRIGDELAY_REG trigDelay;
  int rc=0;
  //read register
  rc = ioctl(fd, PCI_LIP_PAD_IOCG_READ_TRIGDELAY, &trigDelay);
  //set register with window time
  trigDelay.trgDlyFlds.t = (0xFF)&value;
  rc = ioctl(fd, PCI_LIP_PAD_IOCS_WRITE_TRIGDELAY, &trigDelay);
}

//////////////////////////////////////////////////////////////////////////////
void LRCLipPad::SetThreshold(int ch, int value) { 
  cout << "[LRCLipPad::SetThreshold] Setting threshold for channel... " << ch << flush;  
  if (ch>5) {cout << "[LRCLipPad::SetThreshold] Channel number wrong..." << ch << endl;}
  int rc=0;
  int thr = value;
  switch (ch) {
  case 0:
    rc = ioctl(fd, PCI_LIP_PAD_IOCS_WRITE_THR1, &thr); break;
  case 1:
    rc = ioctl(fd, PCI_LIP_PAD_IOCS_WRITE_THR2, &thr); break;
  case 2:
    rc = ioctl(fd, PCI_LIP_PAD_IOCS_WRITE_THR3, &thr); break;
  case 3:
    rc = ioctl(fd, PCI_LIP_PAD_IOCS_WRITE_THR4, &thr); break;
  case 4:
    rc = ioctl(fd, PCI_LIP_PAD_IOCS_WRITE_THR5, &thr); break;
  case 5:
    rc = ioctl(fd, PCI_LIP_PAD_IOCS_WRITE_THR6, &thr); break;
  }
  cout << " value = " << thr << endl;
}
