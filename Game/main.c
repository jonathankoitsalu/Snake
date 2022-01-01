/** 
 * ---------------------------------------------------------------+ 
 * @desc        OLED SSD1306 example
 * ---------------------------------------------------------------+ 
 *              Copyright (C) 2020 Marian Hrinko.
 *              Written by Marian Hrinko (mato.hrinko@gmail.com)
 *
 * @author      Marian Hrinko
 * @datum       06.10.2020
 * @update      19.07.2021
 * @file        main.c
 * @tested      AVR Atmega328p
 *
 * @depend      ssd1306.h
 * ---------------------------------------------------------------+
 * @descr       Version 1.0 -> applicable for 1 display
 *              Version 2.0 -> rebuild to 'cacheMemLcd' array
 * ---------------------------------------------------------------+
 */

//print for debug
#include <avr/pgmspace.h>
#include <string.h>

// include libraries
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <stdbool.h>

#include "lib/ssd1306.h"
#include "timer.h"
#include "GFX.h"
#include "snake.h"
#include "serial.h"
#include "button.h"
#include "state.h"

/**
 * @desc    Main function
 *
 * @param   void
 *
 * @return  int
 */

int main(void)
{
  uart_init();
  buttonInit();
  timer0Init();
  timer2Init();
  sei();
  initDisplay();

  STATE state;
  stateControl(&state);



  return 0;
}