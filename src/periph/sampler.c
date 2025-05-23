#include "sampler.h"


void sampler_adc_init(void)
{
    // AVcc reference, ADC1 (PC1)
    ADMUX = (1 << REFS0) | (1 << MUX0);
    
    // enable ADC
    // enable auto trigger
    // enable ADC interrupt
    // prescaler 128
    ADCSRA = (1 << ADEN) | (1 << ADATE) | (1 << ADIE) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

    // timer1 compare match B
    ADCSRB = (1 << ADTS2) | (0 << ADTS1) | (0 << ADTS0);

    // start first conversion
    ADCSRA |= (1 << ADSC);
}

void sampler_timer2_init(void)
{
    // normal mode
    TCCR2A = 0;

    // CTC mode (OCR1A), prescaler = 256
    TCCR2B = (1 << WGM12) | (1 << CS12);

    // compare match B value (~1s for 16MHz / 256)
    OCR2B = 62500;
}
