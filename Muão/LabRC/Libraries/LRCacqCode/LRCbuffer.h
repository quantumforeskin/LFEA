#ifndef __LRCbuffer__
#define __LRCbuffer__

//STL
#include <vector>

//C
#include <stdint.h> /* type declarations */
#include <cstring>

//C++
#include <string>

//ROOT
#include <TObject.h>

/**
 * \file LRCbuffer.h
 * \author F.Barao
 * \date July 08
 *
 * Events (\file LRCevent.C) read from the acquisition crates are temporarily stored
 * in a shareable memory (\file LRCCirMem.C).
 * For that, the events have to be serialized in a buffer.
 * This class implements methods for stripping variables into bytes streams.
 */

////////////////////////////////////////////////////////////////////

typedef char byte;

/// Object type

enum EventObjectType {
  LRC_FLOAT = 1,
  LRC_EVENT = 2
};

///

class LRCbuffer: public TObject {

 public:
  LRCbuffer();                     ///< constructor
  ~LRCbuffer();                    ///< destructor
  byte*  GetBuffer();              ///< get buffer pointer
  size_t GetBufferSize();          ///< get buffer size
  void   SetBuffer(byte*,int);     ///< set buffer with contents of an array
  size_t AddEventSize();           ///< add event size in bytes to stream; to be called at end of data dumping
  size_t GetEventSize();           ///< get event size (bytes)
  int    GetEventType();           ///< get event type
  void   ResetBuffer();            ///< reset buffer
  void   PrintOut();               ///< printout buffer information

  void write(byte);
  void write(const byte*, size_t); ///< stripping methods for writing into buffer
  void write(const std::string&);
  void write(uint32_t);
  void write(uint16_t);
  void write(uint8_t);
  void write(float);

  void read(byte&);                ///< stripping methods for reading from buffer
  void read(std::string&);
  void read(uint32_t&);
  void read(uint16_t&);
  void read(uint8_t&);
  void read(float&);

  // ClassDef(LRCbuffer,1);           ///< declaration for producing root dictionary

 protected:
  std::vector<byte> buffer;        ///< stl vector: buffer

};

#endif
