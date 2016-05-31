#ifndef LIPPAD_STRUCT
#define LIPPAD_STRUCT

//structures declaration for accessing LipPad registers and FIFOs data


typedef struct _CONFIG_REG {
    union{
        uint32_t reg32;
		struct {
			unsigned int actv_input_chnls:6,
			                 trigger_type:2,
			               trigger_in_ext:1,
			                    input_pol:1,
			                          rsv:18,
			                       status:4;
		} cfgFlds;
    };    
} CONFIG_REG;


/**
  32 bit reg **/
typedef struct _TRIGDELAY_REG {
    union{
        uint32_t reg32;
		struct {
			unsigned int trig_pos:8,
			                    d:8,
			                    t:8,
			                  rsv:8;
		} trgDlyFlds;
    };    
} TRIGDELAY_REG;

typedef struct _DATA_REG {
      unsigned int channel1:10,
	           channel2:10,
		   channel3:10,
		       _rsv:2;
} DATA_REG;

#endif
