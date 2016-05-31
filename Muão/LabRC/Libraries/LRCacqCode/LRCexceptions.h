#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

class Exception {
 public:
  virtual const char* what() = 0;
  virtual const char* details() = 0;
};

#include <CAENVMElib.h>

/////////////////////////////////////////////////////////////////////////////7
class VME_Exception: public Exception {
 public:
 VME_Exception(const char* c, CVErrorCodes e): error(e), context(c) {};
  virtual const char* details() { return context; };
  virtual const char* what();
  
 private:
  CVErrorCodes error;
  const char* context;
};

/////////////////////////////////////////////////////////////////////////////7
class LipPad_Exception: public Exception {
 public:
 LipPad_Exception(const char* c,int e): error(e), context(c) {};
  virtual const char* details() { return context; };
  virtual const char* what();
  
 private:
  int error;
  const char* context;
};

#endif
