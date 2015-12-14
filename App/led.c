#include "led.h"

void LED_Init(void) {
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitStructure.GPIO_Pin   = RED | GREEN | BLUE;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	LED_OFF(RED | GREEN | BLUE);
}

void LED_ON(uint16_t GPIO_Pin) {
	GPIO_ResetBits(GPIOA, GPIO_Pin);
}

void LED_OFF(uint16_t GPIO_Pin) {
	GPIO_SetBits(GPIOA, GPIO_Pin);
}

