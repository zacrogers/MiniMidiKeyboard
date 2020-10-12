#ifndef _MAIN_H
#define _MAIN_H

#define F_CPU 16000000 // Crystal oscillator frequency

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include <stdint.h>

#include "uart.h"
#include "gpio.h"
#include "midi.h"

/* Namespace includes */
using z_lib::Gpio;
using z_lib::UART;

/* Function protypes*/
void midi_send(MIDI_Packet *packet);

#endif /*_MAIN_H  */