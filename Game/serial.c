#include <avr/io.h>
#include <stdio.h>
#include <stdbool.h>
#include "serial.h"

extern volatile unsigned long millis;
bool received = false;

void uart_init(void)
{
    UBRR0H = (unsigned char)(UBRR >> 8);
    UBRR0L = (unsigned char)(UBRR);
    UCSR0A = 0;
    UCSR0B = (1 << TXEN0 | 1 << RXEN0);
    UCSR0C = (1 << UCSZ01 | 1 << UCSZ00);
}

void uart_putchar(char chr)
{
    //if character is '\n' insert '\r' to register UDR0.
    if (chr == '\n')
    {
        while (!(UCSR0A & (1 << UDRE0)))
            ;
        UDR0 = '\r';
    }
    //otherwise wait for the transmitbuffer to be empty and then write the next character into the uart data register(UDR).
    while (!(UCSR0A & (1 << UDRE0)))
        ;
    UDR0 = chr;
}
void uart_putstr(const char *str)
{
    //initalizes an index counter.
    int i = 0;
    //as long as the string is not completed write the character to putchar and then increment index counter to read the next character.
    while (str[i] != '\0')
    {
        uart_putchar(str[i]);
        i++;
    }
}

char uart_getchar(void)
{
    //wait for the recieve complete bit is set then return the value of uart data register.
    unsigned long timerStart = millis;
    while (millis-timerStart < 400){
    if (UCSR0A & (1 << RXC0)){received = true;return UDR0;}
    }
}

void uart_echo(void)
{
    //print out the recieved character back to the serial terminal.
    uart_putchar(uart_getchar());
}

void uart_getstr(char *str)
{
    //initalize counter and add the first character to index 0.
    int i = 0;
    str[i] = uart_getchar();
    while (str[i] != '\n' && received)
    {
        //while the character is not one of the ending characters increment the counter and add the next character to the string.
        i++;
        str[i] = uart_getchar();
    }
    received = false;
    //add the last bits to the string to complete it, endline characters and null character to mark the end of the string.
    str[i] = '\n';
    str[i + 1] = '\r';
    str[i + 2] = '\0';
}

/*
    [["DAD",300],["DAN",110],["JOK",70],["DAN",50],["BAA",10],["CEB",10],["AAA",0],["AAA",0],["AAD",0]]
*/
