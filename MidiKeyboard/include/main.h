#ifndef _MAIN_H
#define _MAIN_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include <stdint.h>
#include <stdlib.h>
// #include <string>

#include "uart.h"
#include "gpio.h"
#include "midi.h"

#define DEBUG

#define F_CPU            16000000 // Crystal oscillator frequency
#define MUX_SEL_N        3
#define MUX_READ_N       2
#define DEFAULT_VELOCITY 127
#define N_NOTES          12
#define BASE_NOTE        (uint8_t)65 // F4

/* Namespace includes */
using z_lib::Gpio;
using z_lib::UART;

typedef struct{ uint8_t a, b, chan; }MuxState;

/* Maps mux channels to physical layout of buttons */
const uint8_t note_to_key_map[N_NOTES] = {5, 6, 7, 4, 2, 1, 0, 3};
const uint8_t key_to_note_map[N_NOTES] = {6, 5, 4, 3, 0, 1, 2, 7};

/* Function protypes*/
void set_mux(uint8_t chan);


void     midi_send(MIDI_Packet *packet); /* Send midi packet over serial */
MuxState read_mux(uint8_t chan);         /* Set both muxes to given channel and read both */
bool     btns_pressed(MuxState state);
uint8_t  mux_to_key(MuxState mux);       /* Get the key pressed (returns val between 0 & 15 */
uint8_t  key_to_note(uint8_t key);       /* Get the midi note from the key pressed */
uint8_t  note_to_key(uint8_t note);      /* Get the key pressed from the midi note*/
#endif /*_MAIN_H  */