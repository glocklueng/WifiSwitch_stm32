#include "relay.h"

void RELAY_Init(void) {
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	RELAY_OFF();
}

void RELAY_ON(void) {
	GPIO_SetBits(GPIOB, GPIO_Pin_11);
}

void RELAY_OFF(void) {
	GPIO_ResetBits(GPIOB, GPIO_Pin_11);
}
