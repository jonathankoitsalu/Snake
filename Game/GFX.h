
#ifndef __GFX_H__
#define __GFX_H__

#include "comms.h"
#include <stdint.h>

void initDisplay();
void clearScreen();
void drawPixel(uint8_t, uint8_t);
void drawPixelSnake(uint8_t, uint8_t);
void drawPixelSnakeBig0(uint8_t x, uint8_t y);
void drawPixelSnakeBig1(uint8_t x, uint8_t y);
void drawPixelSnakeBigHead(uint8_t x, uint8_t y); 
void drawLine(uint8_t, uint8_t, uint8_t, uint8_t);
void drawString(char *string, uint8_t x, uint8_t y);
void updateScreen();
void drawEdge();
void mainMenu(uint8_t);
void newGameMenu(uint8_t, uint8_t);
void playerNameMenu(uint8_t, char, char, char, int);
void highScoreMenu(SCORE_LIST *get);

#endif //__GFX_H__