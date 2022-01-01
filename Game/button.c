#include "button.h"

/*   Global variables   */

volatile bool inDebounce = false;
volatile bool buttonReleased = true;
volatile bool down = false;
volatile bool up = false;
volatile bool left = false;
volatile bool right = false;
volatile bool confirm = false;

volatile int count;

void buttonInit()
{
    // Directional buttons
    /*  Set digital pins 0-3    */
    DDRB &= ~(1 << PB0);
    DDRB &= ~(1 << PB1);
    DDRB &= ~(1 << PB2);
    DDRB &= ~(1 << PB3);
    DDRB &= ~(1 << PB4);

    // Enable pin change interrupts
    PCICR |= (1 << PCIE0);
    PCMSK0 |= (1 << PCINT0) | (1 << PCINT1) | (1 << PCINT2) | (1 << PCINT3) | (1 << PCINT4);
}

ISR(PCINT0_vect)
{
    if ((PINB & (1 << PINB0)) && (PINB & (1 << PINB1)) && (PINB & (1 << PINB2)) && (PINB & (1 << PINB3)) && (PINB & (1 << PINB4)))
    {
        buttonReleased = true;
    }

    if (!inDebounce && buttonReleased)
    {
        if (!(PINB & (1 << PINB0))) //Button: right
        {
            right = true;
            
            inDebounce = true;
            buttonReleased = false;

            count = 0;
        }
        if (!(PINB & (1 << PINB1))) //Button: down
        {
            down = true;

            inDebounce = true;
            buttonReleased = false;

            count = 0;
        }
        if (!(PINB & (1 << PINB2))) //Button: left
        {
            left = true;

            inDebounce = true;
            buttonReleased = false;

            count = 0;
        }
        if (!(PINB & (1 << PINB3))) //Button: right
        {
            up = true;

            inDebounce = true;
            buttonReleased = false;

            count = 0;
        }
        if (!(PINB & (1 << PINB4))) //Button: confirm
        {
            confirm = true;
            
            inDebounce = true;
            buttonReleased = false;

            count = 0;
        }
    }
}