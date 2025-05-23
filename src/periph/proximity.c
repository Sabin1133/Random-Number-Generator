#include "proximity.h"

#define TRIGGER_PIN PA3


void proximity_timer1_init(void)
{
    TIMSK = (1 << TOIE1);  // enable timer1 overflow interrupts
    TCCR1A = 0;		       // set all bit to zero normal operation
}


void proximity_pins_init(void)
{
    DDRA |= (1 << TRIGGER_PIN);
}


int proximity_dist(void)
{
    int timer_count;
    int count;
    int distance;

    // give 10us trigger pulse on trigger pin to HC-SR04
    
    PORTA |= (1 << TRIGGER_PIN);
    _delay_us(10);
    PORTA &= (~(1 << TRIGGER_PIN));

    // calculate width of echo by input capture (ICP)

    TCNT1 = 0;	        // clear timer counter
    TCCR1B = 0x41;	    // capture on rising edge, no prescaler
    TIFR = 1 << ICF1;   // clear ICP flag (Input Capture flag)
    TIFR = 1 << TOV1;   // clear timer overflow flag

    // wait for rising edge
    while ((TIFR & (1 << ICF1)) == 0);

    TCNT1 = 0;	        // clear timer counter
    TCCR1B = 0x01;	    // capture on falling edge, no prescaler
    TIFR = 1 << ICF1;   // clear ICP flag (Input Capture flag)
    TIFR = 1 << TOV1;   // clear timer overflow flag
    timer_count = 0;    // clear timer overflow count

    // wait for falling edge
    while ((TIFR & (1 << ICF1)) == 0);

    count = ICR1 + (65535 * timer_count); // take count
    distance = (double)count / 466.47;    // 8MHz timer frequency, sound speed = 343 m/s

    return distance;
}
