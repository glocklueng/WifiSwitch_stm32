#include "delay.h"

uint32_t TimingDelay;

void delay_Init(void) {
	if (SysTick_Config(SystemCoreClock / 1000)) while (1);
}

void delay_ms(uint32_t nms) {
	TimingDelay = nms;
	while (TimingDelay);
}

void TimingDelay_Decrement(void) {
	if (TimingDelay != 0x00) TimingDelay--;
}

void SysTick_Handler(void) {
	TimingDelay_Decrement();
}
