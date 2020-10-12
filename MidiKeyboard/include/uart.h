#ifndef _UART_H_
#define _UART_H_

#include <avr/io.h>
#include <stdint.h>

namespace z_lib
{	
    class UART
    {  
        public:
            UART(int baudrate);
            void putc(unsigned char c);
            void print(char *s);
    };
}

#endif /* _UART_H_ */