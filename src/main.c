#include <avr/io.h>

#include <stdio.h>

#include "compute.h"
#include "periph/sampler.h"
#include "periph/temperature.h"
#include "periph/proximity.h"
#include "ble.h"


#define DELAY_NUMBER 200000


unsigned int temperature_voltage;
unsigned int sampler_voltage;

FILE usart_out = FDEV_SETUP_STREAM(usart_putchar, NULL, _FDEV_SETUP_WRITE);


int main(void)
{
    int random_number;
    int dist;

    // stream for printf
    stdout = &usart_out;

    // init usart
    usart_init();

    // init temperature peripherals
    temperature_adc_init();
    temperature_timer0_init();

    // init proximity peripherals
    proximity_pins_init();
    proximity_timer1_init();

    // init sampler peripherals
    sampler_adc_init();
    sampler_timer2_init();

    while (1) {
        // wait some seconds
        for (int i = 0; i < DELAY_NUMBER; ++i);

        // get distance from proximity sensor
        dist = proximity_dist();

        // compute random number
        random_number = compute_number(sampler_voltage, temperature_voltage, dist);

        // send over bluetooth
        printf("%d", random_number);
    };

    return 0;
}
