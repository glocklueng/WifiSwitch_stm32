#include "wifi.h"

uint8_t wifi_Connected = 0;

extern uint8_t UsartBuffer[];

uint8_t wifi_data[80];

uint8_t Char_ready[6]    = {'r', 'e', 'a', 'd', 'y', '\0'};
uint8_t Char_Send[2]     = {'>', '\0'};
uint8_t Char_OK[3]       = {'O', 'K', '\0'};
uint8_t Char_ERROR[6]    = {'E', 'R', 'R', 'O', 'R', '\0'};
uint8_t Char_IPD[5]      = {'+', 'I', 'P', 'D', '\0'};
uint8_t Char_CONNECT[10] = {'0', ',', 'C', 'O', 'N', 'N', 'E', 'C', 'T', '\0'};
uint8_t Char_CLOSED[9]  = {'0', ',', 'C', 'L', 'O', 'S', 'E', 'D', '\0'};

uint8_t check_char(uint8_t S[]) {
	uint8_t i = 0;
	while (S[i] != '\0') {
		if (UsartBuffer[i] != S[i]) return 0;
		i++;
	}
	return 1;
}

void wifi_pushData() {
	uint8_t ii = 0;
	uint32_t t;
	if (check_char(Char_CONNECT) == 1) {
		LED_ON(BLUE);
		wifi_Connected = 1;
	}
	if (check_char(Char_CLOSED) == 1) {
		LED_OFF(BLUE);
		wifi_Connected = 0;
	}
	if (check_char(Char_IPD) == 1) {
		while (ii < 80 && UsartBuffer[ii] != ':') ii++;
		if (ii > 20) return;
		t = UsartBuffer[ii + 2] << 24 | 
			UsartBuffer[ii + 3] << 16 | 
			UsartBuffer[ii + 4] << 8  |
			UsartBuffer[ii + 5];
		if (UsartBuffer[ii + 1] == 0x00) {
			RELAT_SETTIME(t, SWITCHOFF);
		} else {
			RELAT_SETTIME(t, SWITCHON);
		}
	}
}

void wifi_Init(void) {
	LED_ON(GREEN);
	delay_ms(1000);
	printf(" ");
	printf("AT+RST\x0d\x0a");
	while (check_char(Char_ready) == 0) delay_ms(5);
	delay_ms(10);
	printf("AT+CIPMUX=1\x0d\x0a");
	while (check_char(Char_OK) == 0) delay_ms(5);
	delay_ms(10);
	printf("AT+CIPSERVER=1,6789\x0d\x0a");
	while (check_char(Char_OK) == 0) delay_ms(5);
	LED_OFF(GREEN);
	LED_ON(RED);
}

void wifi_SendString(char* Msg, uint8_t length) {
	printf("AT+CIPSEND=0,%d\x0d\x0a", length);
	while (check_char(Char_Send) == 0) delay_ms(5);
	delay_ms(10);
	printf("%s\x0d\x0a", Msg);
}

void wifi_WaitData() {
	while (check_char(Char_IPD) == 0) delay_ms(5);

}




