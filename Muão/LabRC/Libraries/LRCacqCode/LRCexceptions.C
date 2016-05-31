#include <iostream>
#include "LRCexceptions.h"
using namespace std;


const char* VME_Exception::what() { 
    return CAENVME_DecodeError(error);
}

const char* LipPad_Exception::what() { 
  //LipPad errors:
  // 1 = no device
  switch (error) {
  case 1:
    return(context);
  }
  
}
