#include <avr/io.h>


void sampler_adc_init(void)
{
    ADMUX = (1 << REFS0) | (1 << MUX0); // AVcc reference, ADC1 (PC1)
    
    ADCSRA = (1 << ADEN)  // Enable ADC
           | (1 << ADATE) // Enable Auto Trigger
           | (1 << ADIE)  // Enable ADC interrupt
           | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Prescaler 128

    ADCSRB = (1 << ADTS2) | (0 << ADTS1) | (0 << ADTS0); // ADTS = 100 → Timer1 Compare Match B

    ADCSRA |= (1 << ADSC); // Start first conversion
}


void sampler_timer2_init(void)
{
    TCCR2A = 0; // Normal port operation
    TCCR2B = (1 << WGM12) | (1 << CS12); // CTC mode (OCR1A), prescaler = 256

    OCR2B = 62500; // Compare Match B value (approx 1s for 16MHz / 256)
}
