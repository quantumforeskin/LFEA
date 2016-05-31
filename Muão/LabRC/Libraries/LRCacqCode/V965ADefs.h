/********************************************************************************
 * V965A: 12-bit QDC
 *
 * 8-channels
 * 2 ranges: [0-100pC], [0-900pC]
 *
 * F.Barao (Nov.08)
 *******************************************************************************/

#ifndef __CAENV965ADefs_H
#define __CAENV965ADefs_H


typedef enum V965ARegisters {
  V965AEventBufferHeader          = 0x0000,          // Output Buffer register
  V965AFirmwareRegister           = 0x1000,          // Firmware Revision register
  V965ABitSet1Register            = 0x1006,          // Bit Set 1 register
  V965ABitClear1Register          = 0x1008,          // Bit Clear 1 register
  V965AStatusRegister1            = 0x100E,          // Status Register 1
  V965AEventTriggerRegister       = 0x1020,          // Event Trigger Register
  V965AStatusRegister2            = 0x1022,          // Status Register 2
  V965AEventCounterLowRegister    = 0x1024,          // Event Counter_Low Register
  V965AEventCounterHighRegister   = 0x1026,          // Event Counter_High Register
  V965AIncrementEventRegister     = 0x1028,          // Increment Event register
  V965AIncrementOffsetRegister    = 0x102A,          // Increment Offset register
  V965ABitSet2Register            = 0x1032,          // Bit Set 2 Register
  V965ABitClear2Register          = 0x1034,          // Bit Clear 2 Register
  V965ACrateSelectRegister        = 0x103C,          // Crate Select Register
  V965ATestEventWriteRegister     = 0x103E,          //
  V965AEventCounterResetRegister  = 0x1040,          //
  V965ASlideConstantRegister      = 0x106A,          // Slide Constant Register
  V965AThresholdHighRangeCh0      = 0x1080,          // Thresholds (8-bit values)
  V965AThresholdLowRangeCh0       = 0x1084,          // 
  V965AThresholdHighRangeCh1      = 0x1088,          //
  V965AThresholdLowRangeCh1       = 0x108C,          //
  V965AThresholdHighRangeCh2      = 0x1090,          //
  V965AThresholdLowRangeCh2       = 0x1094,          //
  V965AThresholdHighRangeCh3      = 0x1098,          //
  V965AThresholdLowRangeCh3       = 0x109C,          //
  V965AThresholdHighRangeCh4      = 0x10A0,          //
  V965AThresholdLowRangeCh4       = 0x10A4,          //
  V965AThresholdHighRangeCh5      = 0x10A8,          //
  V965AThresholdLowRangeCh5       = 0x10AC,          //
  V965AThresholdHighRangeCh6      = 0x10B0,          //
  V965AThresholdLowRangeCh6       = 0x10B4,          //
  V965AThresholdHighRangeCh7      = 0x10B8,          //
  V965AThresholdLowRangeCh7       = 0x10BC           //
} V965ARegisters;

typedef enum V965ADataMasks {
  V965AMaskNumberCh  = 0x00003F00,          // number of channels (bit: 8-13)
  V965AMaskDataTag   = 0x07000000,          // Data tag (bit: 24-26)
  V965AMaskChannel   = 0x001C0000,          // Channel mask (bit: 18-20)
  V965AMaskOverflow  = 0x00001000,          // Overflow (bit 12)
  V965AMaskUnderTh   = 0x00002000,          // under threshold (bit 13)
  V965AMaskRange     = 0x00020000,          // Range mask (bit 17)
  V965AMaskCrateNb   = 0x00FF0000,          // Crate number (bit: 16-23)
  V965AMaskData      = 0x00000FFF           // Data value mask (bit: 0-11)
} V965ADataMasks;

#endif
