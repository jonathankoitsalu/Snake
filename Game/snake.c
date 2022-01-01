#include "GFX.h"
#include "serial.h"
#include "snake.h"
#include "button.h"
#include "timer.h"
#include "state.h"

static GAMESTATE game;
uint8_t startPosX = 7;
uint8_t startPosY = 3;
uint8_t startLength = 3;
uint8_t appleValue = 10;

bool gameOver = false;
bool operation = false;

/*Extern variables*/
extern volatile unsigned long millis;
extern volatile bool down;
extern volatile bool up;
extern volatile bool left;
extern volatile bool right;
extern volatile bool confirm;


GAMESTATE *gamestatePtr()
{
  return &game;
}

void initGameState()
{
  game.score = 0;
  game.direction = 0;
  game.speed = 200;

  game.snake.length = startLength;

  for (int i = 0; i < game.snake.length; i++)
  {
    game.snake.positions[i].x = startPosX - i;
    game.snake.positions[i].y = startPosY;
  }
  game.snake.binaryValues[1]=0;
  game.snake.binaryValues[2]=1;
  game.apple.value = appleValue;
  newApple(game);
}

void drawApple()
{
  if(operation==0)
  drawPixelSnakeBig0(game.apple.position.x, game.apple.position.y);
  else drawPixelSnakeBig1(game.apple.position.x, game.apple.position.y);
}

void longerSnake()
{
  game.snake.length++;
}

void drawSnake()
{
  drawPixelSnakeBigHead(game.snake.positions[0].x, game.snake.positions[0].y);
  for (int i = 1; i <= game.snake.length-1; i++){
    if(game.snake.binaryValues[i])drawPixelSnakeBig1(game.snake.positions[i].x, game.snake.positions[i].y);
    else drawPixelSnakeBig0(game.snake.positions[i].x, game.snake.positions[i].y);
  }
}

void newApple()
{
  game.apple.position.x = rand() % 16;
  game.apple.position.y = rand() % (7 + 1 - 1) + 1; //random range 1-7
}

bool eatApple()
{
  if (game.snake.positions[0].x == game.apple.position.x && game.snake.positions[0].y == game.apple.position.y)
  {
    return true;
  }
  return false;
}

void moveSnake()
{
  for (int i = game.snake.length; i > 0; i--)
    game.snake.positions[i] = game.snake.positions[i - 1];
  switch (game.direction)
  {
  case 0: //right
    if (game.snake.positions[0].x == 15)
      game.snake.positions[0].x = 0;
    else
      game.snake.positions[0].x++;
    break;
  case 1: //down
    if (game.snake.positions[0].y == 7)
      game.snake.positions[0].y = 1;
    else
      game.snake.positions[0].y++;
    break;
  case 2: //left
    if (game.snake.positions[0].x == 0)
      game.snake.positions[0].x = 15;
    else
      game.snake.positions[0].x--;
    break;
  case 3: //up
    if (game.snake.positions[0].y == 1)
      game.snake.positions[0].y = 7;
    else
      game.snake.positions[0].y--;
    break;
  }
}

void changeDirection()
{
  if (right || down || left || up || confirm)
  {
    if (game.direction != LEFT)
    {
      if (right)
      {
        game.direction = RIGHT;
      }
    }
    if (game.direction != UP)
    {
      if (down)
      {
        game.direction = DOWN;
      }
    }
    if (game.direction != RIGHT)
    {
      if (left)
      {
        game.direction = LEFT;
      }
    }
    if (game.direction != DOWN)
    {
      if (up)
      {
        game.direction = UP;
      }
    }
    if(confirm){
      operation=!operation;
    }
    right = false;
    down = false;
    left = false;
    up = false;
    confirm = false;
  }
}

bool hitTail()
{
  for (int i = 1; i <= game.snake.length; i++)
    if (game.snake.positions[0].x == game.snake.positions[i].x && game.snake.positions[0].y == game.snake.positions[i].y)
    {
      return true;
    }
  return false;
}

void snakeEngine(STATE *state)
{
  char scoreStr[20];
  char speed[20];
  initGameState();

  unsigned long currentTime;
  unsigned long lastTime = 0;

  while (!gameOver)
  {
    currentTime = millis;
    if (currentTime - lastTime > (-200 * state->speedState + 800))
    {
      changeDirection();
      moveSnake();
      if (eatApple())
      {
        game.score += game.apple.value;
        game.snake.binaryValues[game.snake.length]=operation;
        checkSpeed(state);
        longerSnake();
        newApple();
      }
      clearScreen();
      drawString("Speed: ", 80, 0);
      drawString(itoa(state->speedState, speed, 10), 120, 0);
      itoa(game.score, scoreStr, 10);
      drawString("Score: ", 0, 0);
      drawString(scoreStr, 40, 0);
      drawApple();
      drawSnake();
      updateScreen();
      if (hitTail())
      {
        gameOver = true;
        state->score = game.score;
        clearScreen();
      }
      lastTime = currentTime;
    }
  }
}

void checkSpeed(STATE *state)
{
  char received[50];
  uart_putstr("+");
  uart_getstr(received);
  if (atoi(received) < 4 && atoi(received) > 0)
    state->speedState = atoi(received);
}
