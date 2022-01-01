#ifndef __SNAKE_H__
#define __SNAKE_H__

#include <avr/io.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> //for rand() function
#include <avr/pgmspace.h>
#include <string.h>
#include <util/delay.h>
#include <stdint.h>

#include "state.h"

enum DIRECTION
{
  RIGHT,
  DOWN,
  LEFT,
  UP
};

typedef struct
{
  uint8_t x;
  uint8_t y;
} POSITION;

typedef struct
{
  POSITION position;
  int value;
} APPLE;

typedef struct
{
  uint8_t binaryValues[100];
  uint8_t length;
  POSITION positions[100];
} SNAKE;

typedef struct
{
  uint8_t direction;
  uint16_t speed;
  int score;
  SNAKE snake;
  APPLE apple;
} GAMESTATE;

GAMESTATE *gamestatePtr();
unsigned long snakeTimer();
void initGameState();
void snakeEngine(STATE *);
void checkSpeed(STATE *);
void changeDirection();
void drawSnake();
void moveSnake();
void newApple();
bool eatApple();
void drawApple();


#endif //__SNAKE_H__