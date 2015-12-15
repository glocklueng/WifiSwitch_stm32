#include "timer.h"

uint8_t b = 0;

void Timer_Init(void) {
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;  

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	NVIC_InitStructure.NVIC_IRQChannel              = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd           = ENABLE;                //使能TIM2中断  
	NVIC_InitStructure.NVIC_IRQChannelPriority      = 0;                //优先级为0  
	NVIC_Init(&NVIC_InitStructure); 
	
	TIM_DeInit(TIM3);
	TIM_TimeBaseStructInit(&TIM_TimeBaseInitStructure);
	TIM_TimeBaseInitStructure.TIM_ClockDivision     = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode       = TIM_CounterMode_Up;//向上计数模式
	TIM_TimeBaseInitStructure.TIM_Period            = 999;//从0~999计数，定时周期为1000次
	TIM_TimeBaseInitStructure.TIM_Prescaler         = 48000 - 1;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0x00; 
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);

	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE); 

	TIM_Cmd(TIM3, ENABLE);
}


void TIM3_IRQHandler(void) {
	if(TIM_GetITStatus(TIM3, TIM_IT_Update)) {  
        TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
        if (b == 0) {
        	b = 1;
        	LED_ON();
        } else {
        	b = 0 ;
        	LED_OFF();
        }
    }  
}
