#ifndef __STATE_H__
#define __STATE_H__

#include <stdio.h>
#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
    uint8_t executerState;
    uint8_t mainMenuState;
    uint8_t newGameMenuState;
    uint8_t playerNameMenuState;

    int speedState;
    int score;
    uint8_t newScore;

    int letter1State;
    int letter2State;
    int letter3State;
} STATE;

void stateControl(STATE *state);
void stateInit(STATE *state);
void stateHandler(STATE *state);
void stateExecuter(STATE *state);
void mainMenuState(STATE *state);
void newGameMenuState(STATE *state);
void playerNameMenuState(STATE *state);
void Exit();

#endif //__STATE_H__