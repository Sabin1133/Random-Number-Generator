#include <avr/io.h>
#include <stdio.h>

#include "ble.h"


void pdu_init(struct pdu *pdu)
{
    pdu->padding[0] = -1;
    pdu->padding[1] = -1;
    pdu->padding[2] = -1;
    pdu->padding[3] = -1;

    pdu->number = 0;
}

void usart_init(unsigned int ubrr)
{
    UBRR0H = (unsigned char)(ubrr>>8);
    UBRR0L = (unsigned char)ubrr;

    UCSR0B = (1<<RXEN0) | (1<<TXEN0);

    UCSR0C = (1<<USBS0) | (3<<UCSZ00);
}

void usart_send(unsigned char data)
{
    while(!(UCSR0A & (1<<UDRE0)));

    UDR0 = data;
}

unsigned char usart_recv()
{
    while(!(UCSR0A & (1<<RXC0)));

    return UDR0;
}

int usart_putchar(char c, FILE *stream)
{
    // convert \n to \r\n (optional)
    // if (c == '\n')
        // uart_putchar('\r', stream);

    while (!(UCSR0A & (1 << UDRE0)));

    UDR0 = c;

    return 0;
}

void usart_send_rand_number(int number)
{

}
