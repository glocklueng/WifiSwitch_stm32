#include "delay.h"

uint32_t relay_delay = 0;
extern uint8_t current_task;

void delay_Init(void) {
	if (SysTick_Config(SystemCoreClock / 1000)) while (1);
}

void delay_ms(uint32_t nms) {
	TimingDelay = nms;
	while (TimingDelay);
}

void TimingDelay_Decrement(void) {
	if (TimingDelay != 0) TimingDelay--;
	if (relay_delay != 0) {
		relay_delay--;
		if (relay_delay == 0) {
			if (current_task == SWITCHON) RELAY_ON();
			if (current_task == SWITCHOFF) RELAY_OFF();
		}
	}
}

void SysTick_Handler(void) {
	TimingDelay_Decrement();
}
