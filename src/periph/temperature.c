#include "temperature.h"


void temperature_adc_init(void)
{
    // AVcc as reference, ADC0 as input
    ADMUX = (1 << REFS0);

    // enable ADC
    // enable auto trigger
    // enable ADC interrupt (optional)
    // prescaler 128
    ADCSRA = (1 << ADEN)  | (1 << ADATE) | (1 << ADIE)  | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

    // timer0 compare match A
    ADCSRB = (0 << ADTS2) | (1 << ADTS1) | (0 << ADTS0);

    // start first conversion
    ADCSRA |= (1 << ADSC);
}

void temperature_timer0_init(void)
{
    // CTC mode
    TCCR0A = (1 << WGM01);

    // prescaler 1024
    TCCR0B = (1 << CS02) | (1 << CS00);

    // compare match A value (~10ms for F_CPU = 16 MHz)
    OCR0A = 156;
}
