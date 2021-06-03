#include "lcd.h"
#include "ringbuffer.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <math.h>

#define PI 3.14159265
#define MORSE_IN 2
#define LED_OUT 0

volatile unsigned short MS_COUNTER;
volatile unsigned short MORSE_LEN;

unsigned int HZ = 700;
unsigned int PWM_SEC_PRESCALED = 15625;

uint8_t get_PWM_duty_cycle(unsigned int time)
{
    unsigned int cycle_len = HZ / PWM_SEC_PRESCALED;

    float duty_cycle_factor = (time % cycle_len * 2 * PI + 1) / 2;

    return (uint8_t)floorf(duty_cycle_factor * UINT8_MAX);
}

// handle MORSE_IN interrupts
ISR(INT0_vect)
{
    MORSE_LEN = MS_COUNTER;
    MS_COUNTER = 0;

    if ((PIND & _BV(MORSE_IN)) == _BV(MORSE_IN))
    {
        PORTB |= _BV(LED_OUT);
    }
    else
    {
        PORTB &= ~_BV(LED_OUT);
    }
}

ISR(TIMER1_COMPA_vect)
{
    MS_COUNTER++;
}

void init_clocks()
{
    TCCR1B |= _BV(CS11) | _BV(CS10);
}

void init_interrupts()
{
    cli();

    // set interrupt on change on INT0 (MORSE_IN)
    EICRA |= _BV(ISC00);
    EIMSK |= _BV(INT0);

    // timer 1: count 250 cycles for 1 ms interrupt
    OCR1A = 250;
    TCCR1B |= _BV(WGM12);
    TIMSK1 |= _BV(OCIE1A);

    sei();
}

void init_io()
{
    DDRD &= ~_BV(DDD2); // MORSE_IN is input
    DDRB |= _BV(DDB0);  // LED_OUT is output
}

void init_globals()
{
    MS_COUNTER = 0;
    MORSE_LEN = 0;
}

int main()
{
    init_clocks();
    init_interrupts();
    init_io();
    init_globals();
    lcd_init();

    for (;;)
    {
    }

    return 0;
}
