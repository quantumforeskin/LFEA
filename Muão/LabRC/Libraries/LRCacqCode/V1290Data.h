#ifndef __CAENV1290DATA_H
#define __CAENV1290DATA_H

#ifndef __STL_STRING
#include <string>
#endif

#include <stdint.h>

namespace V1290Data {

  // Definitions of bits that appear in all data words:

  const uint32_t TYPE_MASK        (0xf8000000); // Data type field
  const uint32_t GLOBAL_HEADER    (0x40000000); // GBL header type fld
  const uint32_t TDC_HEADER       (0x08000000); // TDC header
  const uint32_t TDC_TRAILER      (0x18000000); // TDC Trailer
  const uint32_t TDC_MEASUREMENT  (0x00000000); // TDC Measurement
  const uint32_t TDC_ERROR        (0x20000000); // TDC Error flag.
  const uint32_t TRIGGER_TIME     (0x88000000); // Trigger time tag.
  const uint32_t GLOBAL_TRAILER   (0x80000000); // Global trailer.
  const uint32_t FILLER_LONG      (0xc0000000); // Filler longs.

  // Definitions in the global header only:

  const uint32_t EVENTCOUNT_MASK  (0x07ffffe0);
  const uint32_t EVENT_RSHIFT     (0x5);
  const uint32_t GEO_MASK         (0x0000001f);

  // Definitions in the TDC header longword:

  const uint32_t TDC_MASK           (0x03000000);
  const uint32_t TDC_RSHIFT         (24);
  const uint32_t TDC_EVENTID_MASK   (0x007ff800);
  const uint32_t TDC_EVENTID_RSHIFT (12);
  const uint32_t TDC_BUNCHID_MASK   (0x000007ff);
  const uint32_t TDC_WORDCOUNT_MASK (0x000007ff);

  // Definitions in the TDC measurement word:

  const uint32_t TDC_TRAILING_BIT      (0x04000000);
  const uint32_t TDC_TYPE_RSHIFT       (27);
  const uint32_t TDC_CHANNEL_MASK      (0x03e00000);
  const uint32_t TDC_CHANNEL_RSHIFT    (21);
  const uint32_t TDC_DATA_MASK         (0x001fffff);

  const uint16_t TDCERR_HITLOST_0_FIFO  (0x0001); // hits lost group 0 FIFO overflow
  const uint16_t TDCERR_HITLOST_0_L1    (0x0002); // hits lost group 0 L1 overflow
  const uint16_t TDCERR_HITERROR_0      (0x0004); // hit error in group 0.'
  const uint16_t TDCERR_HITLOST_1_FIFO  (0x0008); // hits lost group 1 FIFO overflow
  const uint16_t TDCERR_HITLOST_1_L1    (0x0010); // hits lost group 1 L1 overflow
  const uint16_t TDCERR_HITERROR_1      (0x0020); // hit error in group 1.
  const uint16_t TDCERR_HITLOST_2_FIFO  (0x0040); // hits lost group 2 FIFO overflow
  const uint16_t TDCERR_HITLOST_2_L1    (0x0080); // hits lost group 2 L1 overflow
  const uint16_t TDCERR_HITERROR_2      (0x0100); // hit error in group 2.
  const uint16_t TDCERR_HITLOST_3_FIFO  (0x0200); // hits lost group 3 FIFO overflow
  const uint16_t TDCERR_HITLOST_3_L1    (0x0400); // hits lost group 3 L1 overflow
  const uint16_t TDCERR_HITERROR_3      (0x0800); // hit error in group 3.
  const uint16_t TDCERR_HITS_EXCEEDED   (0x1000); // Hits lost, size limit exceeded.
  const uint16_t TDCERR_EVENTLOST_FIFO  (0x2000); // Event lost due to trigger fifo overflow.
  const uint16_t TDCERR_FATALCHIP_ERROR (0x4000); // fatal chip error detected.
  const uint16_t TDCERR_ERROR_MASK      (0x7fff); // All bits.

  // Extended trigger time:

  const uint32_t TRIGGERTIME_MASK       (0x07ffffff);

  // Global trailer:

  const uint32_t TRIGGERLOST_MASK       (0x04000000);
  const uint32_t TDCERROR_MASK          (0x02000000);
  const uint32_t OVERFLOW_MASK          (0x01000000);
  const uint32_t WORDCOUNT_MASK         (0x001fffe0);
  const uint32_t WORDCOUNT_RSHIFT       (5);

} 

#endif

