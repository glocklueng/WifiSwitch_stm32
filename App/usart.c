#include "usart.h"

// 串口数据缓存区长度
const uint8_t BUFFERLENGTH = 80;

// 串口数据缓存区
uint8_t UsartBuffer[BUFFERLENGTH];

/**
 * [usart_Init description]
 * [串口初始化]
 * PA9  --- Tx
 * PA10 --- Rx
 */
void usart_Init(void) {
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	GPIO_InitStructure.GPIO_Mode                  = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin                   = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed                 = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode                  = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin                   = GPIO_Pin_10;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	NVIC_InitStructure.NVIC_IRQChannel            = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd         = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	USART_InitStructure.USART_BaudRate            = 115200;
	USART_InitStructure.USART_WordLength          = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits            = USART_StopBits_1;
	USART_InitStructure.USART_Parity              = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure );

	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	
	USART_Cmd(USART1, ENABLE);
}

/**
 * [USART1_IRQHandler description]
 * [串口中断服务]
 * 负责把串口接收到的uint8_t格式的数据存放到UsartBuffer中
 */
void USART1_IRQHandler(void) {
	static uint8_t p = 0;
	if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) {
		uint8_t tmp = USART_ReceiveData(USART1);
		UsartBuffer[p++] = tmp;
		if ((p > 1 && UsartBuffer[p - 2] == '\x0d' && UsartBuffer[p - 1] == '\x0a') || 
			(UsartBuffer[p - 1] == '\n')) {
			wifi_pushData();
			p = 0;
		}
		if (p >= BUFFERLENGTH) p = 0;
	}
}
