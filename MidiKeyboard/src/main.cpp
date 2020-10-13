#include "main.h"

Gpio led = Gpio(&PORTB, 5, Gpio::Mode::OUT);

/* Multiplexer select lines */
// Gpio mux_sel[MUX_SEL_N] = {Gpio(&PORTD, 4, Gpio::Mode::OUT),
// 						   Gpio(&PORTD, 3, Gpio::Mode::OUT),
// 						   Gpio(&PORTD, 2, Gpio::Mode::OUT)};

// Gpio mux_read[MUX_READ_N] = {Gpio(&PORTD, 5, Gpio::Mode::IN),
// 						     Gpio(&PORTD, 6, Gpio::Mode::IN)};

Gpio btns[4] = {Gpio(&PORTD, 2, Gpio::Mode::IN),
						Gpio(&PORTD, 3, Gpio::Mode::IN),
						Gpio(&PORTD, 4, Gpio::Mode::IN),
						Gpio(&PORTD, 5, Gpio::Mode::IN)};

UART serial = UART(9600);
MIDI_Packet midi_pack = {0};
MuxState mux_state = {0};

// Key curr_note = {0};
uint8_t curr_note = 0;
uint8_t prev_note = 0;
int curr_note_state = 0;
int prev_note_state = 0;

int btn_val[8] = {0,0,0,0,0,0,0,0};
int prev_btn_val[8] = {0,0,0,0,0,0,0,0};

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
	midi_pack.control = MIDI_NOTE_ON;
	
	int sequence[8] = {69, 71, 72, 74, 76, 77, 79, 80};

	// _delay_ms(5000);

	while(1)
	{
		for(uint8_t i = 0; i < 4; ++i)
		{
			btn_val[i] = btns[i].read();

			if(btn_val[i] != prev_btn_val[i])
			{
				if(btn_val[i])
				{
					midi_pack.note = i + BASE_NOTE;
					midi_pack.control = MIDI_NOTE_ON;
					// serial.println("Pressed");
					midi_send(&midi_pack);
					_delay_ms(200);	
				}
				else
				{
					midi_pack.note = i + BASE_NOTE;
					midi_pack.control = MIDI_NOTE_OFF;
					// serial.println("Pressed");
					midi_send(&midi_pack);
					_delay_ms(200);						
				}
			}
			prev_btn_val[i] = btn_val [i];

		}

		// for(int chan = 0; chan< 8; ++chan)
		// {
		// 	/* Set mux channel */
		// 	for(uint8_t s = 0; s < MUX_SEL_N; ++s)
		// 	{
		// 		if(chan & (0x01 << s))
		// 		{
		// 			mux_sel[s].set();
		// 		}
		// 		else
		// 		{
		// 			mux_sel[s].clear();
		// 		}
		// 	}

		// 	btn_val[chan] = mux_read[0].read();

		// 	if(btn_val[chan] == 0 && prev_btn_val[chan] == 1)
		// 	{
		// 		// char* st = "HI\n";
		// 		serial.println(chan);
		// 	}
		// 	if(btn_val[chan] == 1 && prev_btn_val[chan] == 0)
		// 	{
		// 		// char* st = "LO\n";
		// 		serial.println(chan);
		// 	}

		// 	prev_btn_val[chan] = btn_val[chan];
		// }


	}

	return 0;
}

void midi_send(MIDI_Packet *packet)
{
	serial.putc((unsigned char)packet->control);
	serial.putc((unsigned char)packet->note);
	serial.putc((unsigned char)packet->velocity);
// #ifdef DEBUG
// 	serial.putc("\n");
// #endif
}

// MuxState read_mux(uint8_t chan)
// {
// 	MuxState state = {0};

// 	for(uint8_t i = 0; i < MUX_SEL_N; ++i)
// 	{
// 		if(chan & (0x01 << i))
// 		{
// 			mux_sel[i].set();
// 		}
// 		else
// 		{
// 			mux_sel[i].clear();
// 		}
// 	}

// 	state.a = mux_read[0].read();
// 	state.b = mux_read[1].read();
// 	state.chan = chan;

// 	return state;
// }

// bool btns_pressed(MuxState state)
// {
// 	return (state.a == 1 || state.b == 1) ? true : false;
// }

// uint8_t mux_to_key(MuxState mux)
// {
// 	uint8_t key = 0;

// 	if(mux.a == 1){	key = mux.chan;	}
// 	else if(mux.b == 1)	{ key = mux.chan + 8; }

// 	return key;
// }

// uint8_t key_to_note(uint8_t key){ return key_to_note_map[key] + BASE_NOTE; }
// uint8_t note_to_key(uint8_t note){ return note_to_key_map[note - BASE_NOTE]; }