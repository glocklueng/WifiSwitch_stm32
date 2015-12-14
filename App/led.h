#ifndef __LED_H
#define __LED_H

#include "main.h"


#define RED 	GPIO_Pin_5
#define GREEN 	GPIO_Pin_6
#define BLUE 	GPIO_Pin_7


void LED_Init(void);
void LED_ON(uint16_t);
void LED_OFF(uint16_t);



#endif
