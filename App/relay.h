#ifndef __RELAY_H
#define __RELAY_H

#include "context.h"

#define SWITCHOFF 0
#define SWITCHON  1

void RELAY_Init(void);
void RELAY_ON(void);
void RELAY_OFF(void);
void RELAT_SETTIME(uint32_t, uint8_t);

#endif
