#ifndef __SOUND_H
#define __SOUND_H
#include "stdlib.h"

extern uint16_t msg[8];
extern uint16_t score;

void enable_ports(void);
void setup_dma(void);
void enable_dma(void);
void init_tim1(void);
void init_tim15(void);
void setup_adc(void);
void init_tim2(void);
void init_wavetable(void);
void set_freq(int chan, float f);
void setup_dac(void);
void init_tim6(void);

#endif