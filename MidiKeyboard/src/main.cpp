#include "main.h"

Gpio led = Gpio(&PORTB, 5, Gpio::Mode::OUT);

/* Multiplexer select lines */
Gpio mux_sel[MUX_SEL_N] = {Gpio(&PORTB, 5, Gpio::Mode::OUT),
						   Gpio(&PORTB, 5, Gpio::Mode::OUT),
						   Gpio(&PORTB, 5, Gpio::Mode::OUT)};

Gpio mux_read[MUX_READ_N] = {Gpio(&PORTB, 5, Gpio::Mode::OUT),
						     Gpio(&PORTB, 5, Gpio::Mode::OUT)};

UART serial = UART(9600);
MIDI_Packet midi_pack = {0};
MuxState mux_state = {0};

// Key curr_note = {0};
uint8_t curr_note = 0;
bool curr_note_state = false;
bool prev_note_state = false;

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
	midi_pack.velocity = DEFAULT_VELOCITY;
	
	int sequence[8] = {69, 71, 72, 74, 76, 77, 79, 80};

	_delay_ms(5000);

	while(1)
	{
		for (int i = 0; i < 8; i++)
		{
			mux_state = read_mux(i);
			curr_note = key_to_note(mux_to_key(mux_state))
			// midi_pack.note = sequence[i];
			// midi_pack.control = MIDI_NOTE_ON;
			// midi_send(&midi_pack);
			send(MIDI_NOTE_ON, sequence[i]);
			_delay_ms(2000);

			send(MIDI_NOTE_OFF, sequence[i]);
			_delay_ms(2000);

			led.toggle();
		}
#ifdef DEBUG
		serial.println(std::to_string(curr_note).c_str());
#endif

	}

	return 0;
}

void midi_send(MIDI_Packet *packet)
{
	serial.putc((unsigned char)packet->control);
	serial.putc((unsigned char)packet->note);
	serial.putc((unsigned char)packet->velocity);
}

MuxState read_mux(uint8_t chan)
{
	MuxState state = {0};

	for(uint8_t i = 0; i < MUX_SEL_N; ++i)
	{
		mux_sel[i] = chan & (0x01 << i);
	}

	state.a = mux_read[0].read();
	state.b = mux_read[1].read();
	state.chan = chan;

	return state;
}

uint8_t mux_to_key(MuxState mux)
{
	uint8_t key = 0;

	if(mux.a == 1){	key = mux.chan;	}
	else if(mux.b == 1)	{ key = mux.chan + 8; }

	return key;
}

uint8_t key_to_note(uint8_t key){ return key_to_note_map[key] + BASE_NOTE; }
uint8_t note_to_key(uint8_t note){ return note_to_key_map[note - BASE_NOTE]; }