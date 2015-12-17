#include "relay.h"

extern uint32_t relay_delay;
uint8_t current_task;
uint8_t relay_status = 0;
uint8_t recievetask = 0;

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
	relay_status = 1;
}

void RELAY_OFF(void) {
	GPIO_ResetBits(GPIOB, GPIO_Pin_11);
	relay_status = 0;
}

void RELAT_SETTIME(uint32_t t, uint8_t task) {
	relay_delay = t + 200;
	current_task = task;
	recievetask = 1;
}
