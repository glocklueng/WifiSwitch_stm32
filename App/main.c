#include "context.h"

extern uint8_t wifi_Connected;
uint8_t old_wifi_Connected = 0;

extern uint8_t relay_status;
uint8_t old_relay_status = 0;

extern uint8_t recievetask;

int main() {
	ALL_Init();
	old_wifi_Connected = wifi_Connected;
	old_relay_status = relay_status;
	// RELAY_ON();
	while(1) {
		if (old_wifi_Connected == 0 && wifi_Connected == 1) {
			wifi_SendString("hello\n", 6);
		}
		if (old_relay_status == 0 && relay_status == 1) {
			wifi_SendString("ON\n", 3);
		}
		if (old_relay_status == 1 && relay_status == 0) {
			wifi_SendString("OFF\n", 4);
		}
		if (recievetask == 1) {
			wifi_SendString("GET\n", 4);
			recievetask = 0;
		}
		old_wifi_Connected = wifi_Connected;
		old_relay_status = relay_status;
		delay_ms(100);
	}
}

