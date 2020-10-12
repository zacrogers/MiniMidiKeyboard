#include "main.h"

Gpio led = {&PORTB, 5, Gpio::Mode::OUT};

UART serial(9600);

void send(int ctrl, int note)
{
	serial.putc((unsigned char)ctrl);
	serial.putc((unsigned char)note);
	serial.putc((unsigned char)100);
}

int main(void)
{
	// char test_str[] = "Hello\n";
	// midi_pack.channel = 0;
	// midi_pack.note = 90;
	// midi_pack.velocity = 90;
	MIDI_Packet midi_pack = {0};
	int sequence[8] = {69, 71, 72, 74, 76, 77, 79, 80};

	_delay_ms(5000);

	while(1)
	{
		for (int i = 0; i < 8; i++)
		{
			// midi_pack.note = sequence[i];
			// midi_pack.control = MIDI_NOTE_ON;
			// midi_send(&midi_pack);
			send(MIDI_NOTE_ON, sequence[i]);
			_delay_ms(2000);

			send(MIDI_NOTE_OFF, sequence[i]);
			_delay_ms(2000);

			led.toggle();
		}
	}

	return 0;
}

void midi_send(MIDI_Packet *packet)
{
	serial.putc((unsigned char)packet->control);
	serial.putc((unsigned char)packet->note);
	serial.putc((unsigned char)packet->velocity);
}