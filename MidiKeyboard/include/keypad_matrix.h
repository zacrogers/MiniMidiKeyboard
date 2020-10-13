#ifndef _KEYPAD_MATRIX_H
#define _KEYPAD_MATRIX_H


#include "gpio.h"
#include <stdint.h>

using z_lib::Gpio;

typedef void (*key_handler) (const char which_key)
typedef int  (*col_handler) (uint8_t)
typedef void (*row_handler) (uint8_t)

template<uint8_t n_rows, uint8_t n_cols>
class Keypad
{
    public:
        Keypad(const Gpio *row_pins, const Gpio *col_pins, const char *key_map);
        ~Keypad();

    private:
        /* Gpio pin mappings */
        const Gpio *row_pins;
        const Gpio *col_pins;

        uint8_t num_rows = rows;
        uint8_t num_cols = cols;

        void init();
        void scan();

        key_handler key_down_handler;  // For handling keyup event
        key_handler key_up_handler;    // For handling keydown event
        row_handler row_start_handler; // Called at the start of each
        row_handler row_end_handler;
        col_handler col_read_handler;

};

#endif /* _KEYPAD_MATRIX_H */