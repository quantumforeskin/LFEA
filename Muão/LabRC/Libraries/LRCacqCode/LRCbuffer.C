//C
#include <stdint.h>

//C++
#include <iostream>
#include <string>


//STL
#include <vector>

//My
#include "LRCbuffer.h"

//ROOT
// ClassImp(LRCbuffer);

///////////////////////////////////////////////////////////////////////////////////
LRCbuffer::LRCbuffer() {
#ifdef DEBUG
  std::cout << "(LRCbuffer::LRCbuffer) constructor..." << std::endl;
#endif
  buffer.clear();
}

///////////////////////////////////////////////////////////////////////////////////
LRCbuffer::~LRCbuffer() {buffer.clear();}

///////////////////////////////////////////////////////////////////////////////////
void LRCbuffer::ResetBuffer() {buffer.clear();}

////////////////////////////////////////////////////////////////////////////////////
size_t LRCbuffer::GetBufferSize() { return buffer.size();}

////////////////////////////////////////////////////////////////////////////////////
byte* LRCbuffer::GetBuffer() {
#ifdef PRINT
      std::cout << "[(LRCbuffer::GetBuffer) " << std::flush;
#endif
  size_t numCopied = 0;
  byte *pc;
  if (buffer.size() != 0) {
    pc = new byte[buffer.size()];
    // copy from internal to external buffer
    for (size_t i = 0; i < buffer.size(); i++) {
      pc[i] = buffer[i];
      numCopied++;
#ifdef PRINT
      std::cout << " " << (int)pc[i] << "(" << (int)buffer[i] << ")" << std::flush;
#endif
    }
  }

#ifdef PRINT
  std::cout << " buffersize = " << std::dec << buffer.size() << " numCopied = " << numCopied << std::endl;
#endif

  return pc;
}

///////////////////////////////////////////////////////////////////////////////////////
// Set buffer
void LRCbuffer::SetBuffer(byte *pc, int ObjectSize) {
  for (int i=0; i<ObjectSize; i++) {
    buffer.push_back(pc[i]);
  }
}

///////////////////////////////////////////////////////////////////////////////////////
// Write event size (bytes) at first
size_t LRCbuffer::AddEventSize() {

  uint16_t EventSize = buffer.size();
  EventSize += 2; //add 2 bytes for EventSize word
  byte a[2];
  a[0] = (EventSize&0xFF00)>>8;
  a[1] = (EventSize&0x00FF)>>0;
  buffer.insert(buffer.begin(),a,a+2);

  return (size_t)EventSize;
}

///////////////////////////////////////////////////////////////////////////////////////
size_t LRCbuffer::GetEventSize() {
  uint16_t evsize =0;
  evsize = (
            ((static_cast<uint16_t>(buffer[0]) << 8) & 0xFF00) |
	    ((static_cast<uint16_t>(buffer[1]) << 0) & 0x00FF)
	     );
    return (size_t)evsize;
}

///////////////////////////////////////////////////////////////////////////////////////
int LRCbuffer::GetEventType() { //WRONG now??????!!!! it depends on order of writing...changed!
  uint32_t Type = 0;
  Type =  ( (static_cast<uint32_t>(buffer[1]) << 24) & 0xff000000 )
        | ( (static_cast<uint32_t>(buffer[2]) << 16) & 0x00ff0000 )
        | ( (static_cast<uint32_t>(buffer[3]) << 8) & 0x0000ff00 )
        | (  static_cast<uint32_t>(buffer[4]) & 0x000000ff );
  return (int)Type;
}

///////////////////////////////////////////////////////////////////////////////////////
void LRCbuffer::PrintOut() {
  std::cout << "[LRCbuffer::PrintOut] Number of bytes stored = " << std::dec << buffer.size() << std::endl;
  for (size_t i = 0; i < buffer.size(); i++) {
    std::cout << std::dec << ".... byte[" << i << "]  "
              << (int)buffer[i]
      //  << "  ( " << buffer[i] << ")";
      //    std::cout.setf(std::ios::hex | std::ios::showbase | std::ios::uppercase);
	      << " (" << std::hex << (int)(uint8_t)buffer[i] << ")" << std::endl;
  }
}

/////////////////////////////////////////////////////////////////////
// WRITE and READ methods
/////////////////////////////////////////////////////////////////////

/********************************************************************
 *
 * Write methods on buffer of bytes
 *
 *******************************************************************/

void LRCbuffer::write(byte byte) {buffer.push_back(byte);}

void LRCbuffer::write(const byte* data, size_t size) {
  // copy from external to internal buffer
  for (size_t i = 0; i < size; ++i) {
    buffer.push_back(data[i]);
  }
}

void LRCbuffer::write(const std::string& s) {write(s.c_str() + '\0', s.length()+1);}

void LRCbuffer::write(uint32_t i) {
  byte aux[4];
  aux[0] = static_cast<char>((i >> 24) & 0xff);
  aux[1] = static_cast<char>((i >> 16) & 0xff);
  aux[2] = static_cast<char>((i >> 8) & 0xff);
  aux[3] = static_cast<char>((i >> 0) & 0xff);
  write(aux, 4);
}

void LRCbuffer::write(uint16_t i) {
  byte aux[2];
  aux[0] = static_cast<char>((i >> 8) & 0xff);
  aux[1] = static_cast<char>((i >> 0) & 0xff);
  write(aux, 2);
}

void LRCbuffer::write(uint8_t i) {
  byte aux;
  aux = static_cast<char>(i);
  write(aux);
}

void LRCbuffer::write(float f) {write(*(uint32_t*)&f);}

/********************************************************************
 *
 * Read methods
 *
 *******************************************************************/

void LRCbuffer::read(byte& byte)
{
  byte = buffer[0];
  buffer.erase(buffer.begin());
}

void LRCbuffer::read(std::string& s)
{
  s.clear();
  byte aux;
  while (true) {
    read(aux);
    if (aux == '\0')
      return;
    else
      s.push_back(aux);
  }
}

void LRCbuffer::read(uint8_t& i)
{
  char c;
  read(c);
  i =  static_cast<uint8_t>(c);
}

void LRCbuffer::read(uint16_t& i)
{
  char c0, c1;
  read(c0); read(c1);
  i = ( (static_cast<uint32_t>(c0) << 8) & 0x0000ff00 )
      | (static_cast<uint32_t>(c1)       & 0x000000ff );
}

void LRCbuffer::read(uint32_t& i)
{
  char c0, c1, c2, c3;
  read(c0); read(c1); read(c2); read(c3);
  i = ( (static_cast<uint32_t>(c0) << 24) & 0xff000000 )
    | ( (static_cast<uint32_t>(c1) << 16) & 0x00ff0000 )
    | ( (static_cast<uint32_t>(c2) << 8)  & 0x0000ff00 )
    | ( static_cast<uint32_t>(c3)         & 0x000000ff );
}

void LRCbuffer::read(float& f) {
  uint32_t aux;
  read(aux);
  f = *(float*)&aux;
}
