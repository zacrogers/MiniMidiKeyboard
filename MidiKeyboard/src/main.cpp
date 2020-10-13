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

int sequence[8] = {69, 71, 72, 74, 76, 77, 79, 80};

int main(void)
{
	midi_pack.velocity = DEFAULT_VELOCITY;
	midi_pack.control = MIDI_NOTE_ON;

	_delay_ms(2000);
	while(1)
	{
		// poll_buttons();
		play_loop();
	}

	return 0;
}

void poll_buttons()
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
				midi_send(&midi_pack);
				_delay_ms(200);	
			}
			else
			{
				midi_pack.note = i + BASE_NOTE;
				midi_pack.control = MIDI_NOTE_OFF;
				midi_send(&midi_pack);
				_delay_ms(200);						
			}
		}
		prev_btn_val[i] = btn_val [i];

	}	
}

void play_loop()
{
	for(int i = 0; i < 8; ++i)
	{
		midi_pack.note = sequence[i];
		midi_pack.control = MIDI_NOTE_ON;
		midi_send(&midi_pack);
		_delay_ms(1000);

		midi_pack.note = sequence[i];
		midi_pack.control = MIDI_NOTE_OFF;
		midi_send(&midi_pack);
		_delay_ms(1000);	
	}

}

void midi_send(MIDI_Packet *packet)
{
	serial.putc((unsigned char)packet->control);
	serial.putc((unsigned char)packet->note);
	serial.putc((unsigned char)packet->velocity);
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