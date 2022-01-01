#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdbool.h>
#include "timer.h"

volatile unsigned long millis = 0;
extern volatile bool inDebounce;

extern volatile int count;

void timer0Init()
{
	//Enable CTC timer0
	TCCR0A &= ~(1 << WGM00);
	TCCR0A |= (1 << WGM01);
	TCCR0A &= ~(1 << WGM02);

	//Set prescaler 1024 (Clk/1024)
	TCCR0B |= (1 << CS00) | (1 << CS02);
	TCCR0A &= ~(1 << CS01);

	//Output compare value calculated based on prescaler and period of ~16ms
	OCR0A = 254;

	//Counter init 0
	TCNT0 = 0;

	//Interrupt enable
	TIMSK0 |= (1 << OCIE0A);
}

void timer2Init()
{
	//set CTC (Clear Timer on Compare Match Mode)
	TCCR2A |= (1 << WGM21);

	//set Prescaler 64
	TCCR2B |= (1 << CS22);

	//enabling output compare match interrupt
	TIMSK2 |= (1 << OCIE2A);

	OCR2A = 249;
	/*
	OCR2A Calculations:
	
	TimerFrequency = ATmegaFrekvens / Prescaler = 16 000 000 / 64 = 250 000 Hz
	TimerPeriod = 1 ms = 1 ms
	OCR2A = (250 000 * 0.001)-1 = 249
	Substract 1 because we start counting at 0.
	*/
}

ISR(TIMER2_COMPA_vect)
{
	millis++;
}

ISR(TIMER0_COMPA_vect)
{
	count++;

	if (count == 5)
	{
		inDebounce = false;
		count = 0;
	}
}