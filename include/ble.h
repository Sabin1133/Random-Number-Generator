#include <stdio.h>


struct pdu {
    char padding[4];
    int number;
};


void pdu_init(struct pdu *pdu);

void usart_init(unsigned int ubrr);

void usart_send(unsigned char data);

unsigned char usart_recv();

int usart_putchar(char c, FILE *stream);
