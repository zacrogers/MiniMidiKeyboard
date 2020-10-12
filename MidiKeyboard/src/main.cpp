#include "main.h"

Gpio led = {&PORTB, 5, Gpio::Mode::OUT};

int main(void)
{
	init_uart(9600);
	char test_str[] = "Hello\n";

	while(1)
	{
		uart_puts(test_str);
		led.toggle();
		_delay_ms(1000);
	}

	return 0;
}