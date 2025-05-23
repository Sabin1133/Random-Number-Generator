Copyright Sabin Padurariu (c) 2025

# Random Number Generator

## General Overview

Random Number Generator (TRNG) designed for microcontroller-based systems.
Unlike pseudo-random number generators (PRNGs), which rely on deterministic
algorithms and seed values, this TRNG uses hardware-based entropy sources to
produce non-deterministic, unpredictable random numbers, ideal for cryptographic
applications, secure communications, and authentication systems.

## Getting Started

Compile the sources using make.

```Bash
make
```

Load the generated ".hex" file into the avr using avrdude utility.

```Bash
make upload
```

## Functionality

The microcontroller gets the values from three main sources.

Peripheral sources:
* entropy sampler circuit
* temperature sensor
* proximity sensor

It receives the values from the sources and applies a fast hashing algorithm
to compute the final random number.

The number is transmitted to the user over bluetooth.

## Peripherals and Pins

The peripherals use all built-in timers:
* timer0 - 8-bit
* timer1 - 16-bit
* timer2 - 8-bit

### Temperature Sensor

The DHT11 is a digital temperature and humidity sensor that communicates with
the microcontroller via a single-wire serial protocol. It has strict timing
requirements for initiating communication and receiving data.

The value from the temperature sensor is read by the ADC using timer0.

### Distance Sensor

The HC-SR04 ultrasonic sensor measures distance by emitting an ultrasonic pulse
and timing its echo. Accurate time measurement in microseconds is critical for
calculating distance.

The value from the ECHO pin is read using timer1.

### Sampler Circuit

The sampler circuit uses the noise from the junction of a BJT transistor to
produce random bits. The noise is amplified and sent to the ADC of the
microcontroller.

The value from the sampler circuit is read by the ADC using timer2.
