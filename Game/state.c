#include "state.h"
#include "GFX.h"
#include "snake.h"
#include "serial.h"
#include "comms.h"

extern bool gameOver;
extern volatile bool down;
extern volatile bool up;
extern volatile bool left;
extern volatile bool right;
extern volatile bool confirm;

void stateControl(STATE *state)
{
    stateInit(state);
    while (1)
    {
        if (right || down || left || up || confirm) //enter if a button has been pressed
        {
            stateHandler(state);
            right = false;  //consume buttonpress
            down = false;
            left = false;
            up = false;
            confirm = false;
            clearScreen();
            stateExecuter(state);
            updateScreen();
        }
    }
}

void stateInit(STATE *state)
{
    state->score = 0;
    state->newScore = 0;
    state->executerState = 1;
    state->mainMenuState = 1;
    state->newGameMenuState = 1;
    state->speedState = 2;
    state->playerNameMenuState = 1;
    state->letter1State = 0;
    state->letter2State = 0;
    state->letter3State = 0;
}

void stateHandler(STATE *state)
{
    switch (state->executerState)
    {
    case 1: //MainMenu
        if (down)
        {
            state->mainMenuState++;
            if (state->mainMenuState > 3)
                state->mainMenuState = 1;
        }
        if (up)
        {
            state->mainMenuState--;
            if (state->mainMenuState < 1)
                state->mainMenuState = 3;
        }
        if (confirm)
        {
            state->executerState = state->mainMenuState + 1;
        }
        break;
    case 2: //NewGameMenu
        if (down)
        {
            state->newGameMenuState++;
            if (state->newGameMenuState > 3)
                state->newGameMenuState = 1;
        }
        if (up)
        {
            state->newGameMenuState--;
            if (state->newGameMenuState < 1)
                state->newGameMenuState = 3;
        }
        if (state->newGameMenuState == 2)
        {
            if (right)
            {
                state->speedState++;
                if (state->speedState > 3)
                    state->speedState = 1;
            }
            if (left)
            {
                state->speedState--;
                if (state->speedState < 1)
                    state->speedState = 3;
            }
        }
        if (confirm)
        {
            if (state->newGameMenuState == 1)
            {
                state->executerState = 5;
            }
            if (state->newGameMenuState == 3)
            {
                state->executerState = 1;
            }
        }
        break;
    case 3: //HighScoreMenu
        if (confirm)
        {
            state->executerState = 1;
        }
        break;
    case 4: //Exit
        if (confirm)
        {
            state->executerState = 1;
        }
        break;
    case 5: //PlayerNameMenu (menu where you choose name for high score)
        if (right)
        {
            state->playerNameMenuState++;
            if (state->playerNameMenuState > 3)
                state->playerNameMenuState = 1;
        }
        if (left)
        {
            state->playerNameMenuState--;
            if (state->playerNameMenuState < 1)
                state->playerNameMenuState = 3;
        }
        if (state->playerNameMenuState == 1)
        {
            if (up)
            {
                state->letter1State++;
                if (state->letter1State > 25)
                    state->letter1State = 0;
            }
            if (down)
            {
                state->letter1State--;
                if (state->letter1State < 0)
                    state->letter1State = 25;
            }
        }
        if (state->playerNameMenuState == 2)
        {
            if (up)
            {
                state->letter2State++;
                if (state->letter2State > 25)
                    state->letter2State = 0;
            }
            if (down)
            {
                state->letter2State--;
                if (state->letter2State < 0)
                    state->letter2State = 25;
            }
        }
        if (state->playerNameMenuState == 3)
        {
            if (up)
            {
                state->letter3State++;
                if (state->letter3State > 25)
                    state->letter3State = 0;
            }
            if (down)
            {
                state->letter3State--;
                if (state->letter3State < 0)
                    state->letter3State = 25;
            }
        }
        if (confirm)
        {
            state->executerState = 1;
        }
        break;
    }
}

void mainMenuState(STATE *state)
{
    switch (state->mainMenuState)
    {
    case 1:
        mainMenu(1);
        break;
    case 2:
        mainMenu(2);
        break;
    case 3:
        mainMenu(3);
        break;
    }
}

void newGameMenuState(STATE *state)
{
    switch (state->newGameMenuState)
    {
    case 1:
        newGameMenu(1, state->speedState);
        break;
    case 2:
        newGameMenu(2, state->speedState);
        break;
    case 3:
        newGameMenu(3, state->speedState);
        break;
    }
}

void playerNameMenuState(STATE *state)
{
    char alphabet[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    switch (state->playerNameMenuState)
    {
    case 1:
        playerNameMenu(1, alphabet[state->letter1State], alphabet[state->letter2State], alphabet[state->letter3State], state->score);
        break;
    case 2:
        playerNameMenu(2, alphabet[state->letter1State], alphabet[state->letter2State], alphabet[state->letter3State], state->score);
        break;
    case 3:
        playerNameMenu(3, alphabet[state->letter1State], alphabet[state->letter2State], alphabet[state->letter3State], state->score);
        break;
    }
}

void sendScore(STATE *state)
{
    char alphabet[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    char player[4] = {alphabet[state->letter1State], alphabet[state->letter2State], alphabet[state->letter3State], '\0'};

    char score[4];
    char scoreStr[4] = "000";
    itoa(state->score, score, 10);

    if (state->score < 10)
    {
        scoreStr[2] = score[0];
    }

    else if (state->score < 100 && state->score > 9)
    {
        scoreStr[2] = score[1];
        scoreStr[1] = score[0];
    }
    else if (state->score > 100)
    {
        strcpy(scoreStr, score);
    }

    char str[16]; //= "!KAN,012,\n";

    strcpy(str, "!");
    strcat(str, player);
    strcat(str, ",");
    strcat(str, scoreStr);
    strcat(str, ",");
    strcat(str, "\n");

    uart_putstr(str);
}

void Exit()
{
    clearScreen();
}

void stateExecuter(STATE *state)
{
    switch (state->executerState)
    {
    case 1:
        gameOver = false;
        if (state->newScore)
        {
            sendScore(state);
            state->newScore = 0;
            state->letter1State = 0;
            state->letter2State = 0;
            state->letter3State = 0;
        }
        mainMenuState(state);

        break;
    case 2:
        newGameMenuState(state);
        break;
    case 3:
        ShowScore();
        break;
    case 4:
        Exit();
        break;
    case 5:
        snakeEngine(state);
        playerNameMenuState(state);
        state->newScore = 1;
        break;
    }
}
