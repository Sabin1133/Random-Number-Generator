#include <avr/io.h>

#include <stdio.h>

#include "compute.h"
#include "sampler.h"
#include "proximity.h"
#include "ble.h"
#include "ble.h"


unsigned int temperature_voltage;
unsigned int sampler_voltage;
unsigned int proximity_interval;


FILE usart_out = FDEV_SETUP_STREAM(usart_putchar, NULL, _FDEV_SETUP_WRITE);


int main(void)
{
    usart_init();
    sampler_adc_init();
    temperature_adc_init();

    stdout = &usart_out;

    while (1) {
        for (int i = 0; i < 200000; ++i);

        
        

    };

    return 0;
}
