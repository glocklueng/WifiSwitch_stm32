#include "context.h"

/**
 * [ALL_Init description]
 * [全局初始化]
 * 负责初始化所有要用到的驱动
 */
void ALL_Init(void) {
	LED_Init();
	RELAY_Init();
}

/**
 * [fputc description]
 * [printf转usart]
 * 可以利用printf把数据输出到串口
 */
int fputc(int ch, FILE *f) {
	USART_SendData(USART1, (uint8_t) ch);
	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
	return ch;
}
