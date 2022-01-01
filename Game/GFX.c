#include <avr/io.h>
#include "lib/ssd1306.h"
#include "comms.h"
#include "snake.h"

void initDisplay()
{
    SSD1306_Init(SSD1306_ADDRESS);
}

void clearScreen()
{
    SSD1306_ClearScreen();
}

void drawPixel(uint8_t x, uint8_t y)
{ // x range: 0-127 | y range: 0-63
    SSD1306_DrawPixel(x, y);
}

void drawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2)
{ // x range: 0-127 | y range: 0-63
    SSD1306_DrawLine(x1, x2, y1, y2);
}

void drawChar(char c, uint8_t x, uint8_t y)
{ // x range: 0-127 | y range: 0-7
    SSD1306_SetPosition(x, y);
    SSD1306_DrawChar(c);
}

void drawString(char *string, uint8_t x, uint8_t y)
{ // x range: 0-127 | y range: 0-7
    SSD1306_SetPosition(x, y);
    SSD1306_DrawString(string);
}

void updateScreen()
{
    SSD1306_UpdateScreen(SSD1306_ADDRESS);
}

void drawPixelSnake(uint8_t x, uint8_t y) // simulates a pixelresolution of 32x16
{
    x = x * 4;
    y = y * 4;
    drawLine(x, y, x + 3, y);
    drawLine(x, y + 1, x + 3, y + 1);
    drawLine(x, y + 2, x + 3, y + 2);
    drawLine(x, y + 3, x + 3, y + 3);
}

void drawPixelSnakeBig0(uint8_t x, uint8_t y) // simulates a pixelresolution of 16x8
{
    x = x * 8;
    y = y * 8;
    drawLine(x+3, y, x+4, y);
    //drawLine(x+1, y+1, x+6, y + 1);
    drawLine(x+2, y+1, x+2, y+5);
    //drawLine(x+2, y+1, x+2, y+5);
    //drawLine(x+5, y+1, x+5, y+5);
    drawLine(x+5, y+1, x+5, y+5);
    //drawLine(x+1, y+5, x+6, y+5);
    drawLine(x+3, y+6, x+4, y+6);
}

void drawPixelSnakeBig1(uint8_t x, uint8_t y) // simulates a pixelresolution of 16x8
{
    x = x * 8;
    y = y * 8;
    drawLine(x+3, y+1, x+3, y+6);
    drawLine(x+1, y+2, x+2, y+1);
    drawLine(x+2, y+6, x+4, y+6);

}

void drawPixelSnakeBigHead(uint8_t x, uint8_t y) // simulates a pixelresolution of 16x8
{
    x = x * 8;
    y = y * 8;
    drawLine(x+2, y, x+5, y);
    drawLine(x+1, y+1, x+6, y+1);
    drawLine(x+1, y+2, x+6, y+2);
    drawLine(x+1, y+3, x+6, y+3);
    drawLine(x+1, y+4, x+6, y+4);
    drawLine(x+1, y+5, x+6, y+5);
    drawLine(x+2, y+6, x+5, y+6);
}

void drawEdge() //draws lines along the edge of the screen
{
    drawLine(0, 8, 127, 8);
    drawLine(127, 9, 127, 63);
    drawLine(0, 63, 127, 63);
    drawLine(0, 9, 0, 63);
}

void mainMenu(uint8_t pointerPos)
{
    switch (pointerPos)
    {       //1->New Game, 2->High Score, 3->Exit
    case 1: // New Game
        drawPixel(24, 20);
        drawPixel(24, 21);
        drawPixel(25, 20);
        drawPixel(25, 21);
        break;
    case 2: // High Score
        drawPixel(24, 36);
        drawPixel(24, 37);
        drawPixel(25, 36);
        drawPixel(25, 37);
        break;
    case 3: // Exit
        drawPixel(24, 52);
        drawPixel(24, 53);
        drawPixel(25, 52);
        drawPixel(25, 53);
        break;
    }
    drawString("BITS", 45, 0);
    drawString("New Game", 30, 2);
    drawString("High Score", 30, 4);
    drawString("Exit", 30, 6);
    drawString("by dajw", 85, 7);
}

void newGameMenu(uint8_t pointerPos, uint8_t speed)
{
    switch (pointerPos)
    {
    case 1: // Start
        drawPixel(24, 20);
        drawPixel(24, 21);
        drawPixel(25, 20);
        drawPixel(25, 21);
        break;
    case 2: // Speed
        drawPixel(24, 36);
        drawPixel(24, 37);
        drawPixel(25, 36);
        drawPixel(25, 37);
        break;
    case 3: // Back
        drawPixel(24, 52);
        drawPixel(24, 53);
        drawPixel(25, 52);
        drawPixel(25, 53);
        break;
    }
    drawString("NEW GAME", 45, 0);
    drawString("Start", 30, 2);
    switch (speed)
    {
    case 1: // Speed
        drawString("Speed x1", 30, 4);
        break;
    case 2: // Back
        drawString("Speed x2", 30, 4);
        break;
    case 3: // Back
        drawString("Speed x3", 30, 4);
        break;
    }
    drawString("Back", 30, 6);
}

void playerNameMenu(uint8_t letterPos, char letter1, char letter2, char letter3, int score)
{
    char scoreStr[20];
    itoa(score, scoreStr, 10);
    drawString("score:", 40, 6);
    drawString(scoreStr, 80, 6);
    drawString("PLAYER", 45, 0);
    drawChar(letter1, 45, 3);
    drawChar(letter2, 60, 3);
    drawChar(letter3, 75, 3);

    switch (letterPos)
    {
    case 1:
        drawLine(44, 33, 50, 33);
        break;
    case 2:
        drawLine(59, 33, 65, 33);
        break;
    case 3:
        drawLine(74, 33, 80, 33);
        break;
    }
}

void highScoreMenu(SCORE_LIST *score_list)
{
    drawString("HIGH SCORE", 35, 0);
    drawLine(11, 15, 11, 55);
    drawLine(36, 15, 36, 55);
    drawLine(60, 15, 60, 55);
    drawLine(75, 15, 75, 55);
    drawLine(101, 15, 101, 55);
    drawString("1", 4, 2);
    drawString(score_list->list[0].name, 15, 2);
    drawString(score_list->list[0].score, 40, 2);
    drawString("6", 65, 2);
    drawString(score_list->list[5].name, 79, 2);
    drawString(score_list->list[5].score, 105, 2);
    drawString("2", 4, 3);
    drawString(score_list->list[1].name, 15, 3);
    drawString(score_list->list[1].score, 40, 3);
    drawString("7", 65, 3);
    drawString(score_list->list[6].name, 79, 3);
    drawString(score_list->list[6].score, 105, 3);
    drawString("3", 4, 4);
    drawString(score_list->list[2].name, 15, 4);
    drawString(score_list->list[2].score, 40, 4);
    drawString("8", 65, 4);
    drawString(score_list->list[7].name, 79, 4);
    drawString(score_list->list[7].score, 105, 4);
    drawString("4", 4, 5);
    drawString(score_list->list[3].name, 15, 5);
    drawString(score_list->list[3].score, 40, 5);
    drawString("9", 65, 5);
    drawString(score_list->list[8].name, 79, 5);
    drawString(score_list->list[8].score, 105, 5);
    drawString("5", 4, 6);
    drawString(score_list->list[4].name, 15, 6);
    drawString(score_list->list[4].score, 40, 6);
    drawString("10", 61, 6);
    drawString(score_list->list[9].name, 79, 6);
    drawString(score_list->list[9].score, 105, 6);
}
