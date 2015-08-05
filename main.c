#include <avr/io.h>
#include "uart.h"
#include "adc.h"
#include <util/delay.h>
#include <stdlib.h>

int main() {
	DDRD = 0xFF;
	uart_init();
	adc_init();
	char buffer[10];
	uint16_t temperature;

	while(1) {
		temperature = adc_read(0)/2;

		if(temperature < 20) {
			PORTD = 0x00;
		} else {
			PORTD = 0xFF;
		}
		uart_puts(itoa(temperature, buffer, 10));
		uart_puts("\r\n");
		_delay_ms(1000);
	}
}
