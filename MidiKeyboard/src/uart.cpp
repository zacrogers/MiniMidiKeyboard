#include "uart.h"

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

namespace z_lib
{	
    #define UART_IS_CLEAR (UCSR0A & (1U << UDRE0))
    #define UART_DATA     UDR0

    UART::UART(int baudrate)
    {
        int UBRR_val = (F_CPU/16)/(baudrate-1);

        /* Write upper bit of baudrate to register */
        UBRR0H = UBRR_val >> 8;
        
        /* Write lower bit of baudrate to register */
        UBRR0L = UBRR_val;

        /* Enable transmitter, receiver, and receiver interrupt */
        UCSR0B |= (1<<TXEN0) | (1<<RXEN0) | (1<<RXCIE0);  
        
        UCSR0C |= (1<<USBS0) | (3<<UCSZ00); 
    }

    void UART::putc(unsigned char c)
    {
        while(!UART_IS_CLEAR); /* Wait until sending is possible */
        UART_DATA = c;         /* Output character saved in c */
    }


    void UART::print(char *s)
    {
        while(*s)
        {
            UART::putc(*s);
            s++;
        }
    }

    void UART::println(char *s)
    {
        while(*s)
        {
            UART::putc(*s);
            s++;
        }
        UART::putc("\n");
    }

}