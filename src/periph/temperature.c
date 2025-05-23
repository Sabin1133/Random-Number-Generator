#include <avr/io.h>


void temperature_adc_init(void)
{
    // AVcc as reference, ADC0 as input
    ADMUX = (1 << REFS0);

    ADCSRA = (1 << ADEN)  // Enable ADC
           | (1 << ADATE) // Enable Auto Trigger
           | (1 << ADIE)  // Enable ADC interrupt (optional)
           | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Prescaler 128

    ADCSRB = (0 << ADTS2) | (1 << ADTS1) | (0 << ADTS0); // ADTS[2:0] = 010 → Timer0 Compare Match A

    // start first conversion
    ADCSRA |= (1 << ADSC);
}

void temperature_timer0_init(void)
{
    // CTC mode
    TCCR0A = (1 << WGM01);
    // prescaler 1024
    TCCR0B = (1 << CS02) | (1 << CS00);
    // compare value
    // (~10ms if F_CPU = 16 MHz)
    OCR0A = 156;
}
