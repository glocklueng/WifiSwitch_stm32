#ifndef __DELAY_H
#define __DELAY_H

#include "context.h"

static volatile uint32_t TimingDelay;

void delay_Init(void);
void delay_ms(uint32_t);
void TimingDelay_Decrement(void);

#endif
