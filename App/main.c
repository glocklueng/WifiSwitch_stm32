#include "main.h"

void ALL_Init() {
	LED_Init();
	RELAY_Init();
}

int main() {
	ALL_Init();
	RELAY_ON();
	while(1);
	
	
}
