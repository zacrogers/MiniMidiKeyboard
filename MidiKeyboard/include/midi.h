/*
 * midi.h
 *
 *  Created on: Oct 12, 2020
 *      Author: Zac
 */

#ifndef INC_MIDI_H_
#define INC_MIDI_H_

#include <stdint.h>
#include <math.h>

#define MIDI_PACKET_SIZE   (uint8_t)3

#define MIDI_NOTE_OFF      (uint8_t)0x80
#define MIDI_NOTE_ON       (uint8_t)0x90
#define MIDI_AFTERTOUCH    (uint8_t)0xA0
#define MIDI_CC_MESSAGE    (uint8_t)0xB0
#define MIDI_PATCH_CHANGE  (uint8_t)0xC0
#define MIDI_CHAN_PRESSURE (uint8_t)0xD0
#define MIDI_PITCH_BEND    (uint8_t)0xE0


typedef struct
{
	uint8_t control;
	uint8_t channel;
	uint8_t note;
	uint8_t velocity;
}MIDI_Packet;


float midi_to_freq(int note)
{
	return (440.0 / 32.0) * pow(2, ((note - 9.0) / 12.0));
}

MIDI_Packet midi_parse(uint8_t *msg)
{
	MIDI_Packet packet = {0};

	if(msg)
	{
		packet.control = (msg[0] & 0x0F);
		packet.channel = (msg[0] & 0xF0);
		packet.note = msg[1];
		packet.velocity = msg[2];
	}

	return packet;
}


#endif /* INC_MIDI_H_ */
