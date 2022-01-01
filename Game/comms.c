#include "GFX.h"
#include "comms.h"
#include "serial.h"

void ParseScore(SCORE_LIST *score_list)
{
    int nameIndex = 0;
    int scoreIndex = 0;
    int playerRank = 0;
    char received[200];
    uart_putstr("@"); //send gethighscore request to esp32 with wifi
    uart_getstr(received); //receive top10 list as a string

     for (int playerRank = 0; playerRank < 10; playerRank++)
    {
        memset(score_list->list[playerRank].name, ' ', 4);
        memset(score_list->list[playerRank].score, ' ', 4);
    }

    playerRank = 0;
        
    for (int i = 0; i < strlen(received); i++) //Loops through all the characters in the received string
    {
        if (received[i] == '"') //uses quotes as delimiter 1 
        {
            while (received[i + 1] != '"') //uses quotes again as delimiter 2
            {
                score_list->list[playerRank].name[nameIndex] = received[i + 1]; //saves name in the score_list

                nameIndex++;
                i++;
            }
            score_list->list[playerRank].name[nameIndex] = '\0';

            nameIndex = 0;
            i++; //
        }
        else if (received[i] == ',') //uses comma as delimiter 3
        {
            while (received[i + 1] != ']') // uses bracket as delimiter 4
            {
                score_list->list[playerRank].score[scoreIndex] = received[i + 1]; //saves score in the score_list
                scoreIndex++;
                i++;
            }
            score_list->list[playerRank].score[scoreIndex] = '\0';

            scoreIndex = 0;
            i += 2;
            playerRank++;
        }
    }
    if (playerRank < 10) // fill the highscore with empty spaces if less then 10 players received.
    {
        for (int i = playerRank; i < 10; i++)
        {
            strcpy(score_list->list[i].name, "   ");
            strcpy(score_list->list[i].score, "   ");
        }
    }
}

void ShowScore()
{
    SCORE_LIST score_list;

    ParseScore(&score_list);

    highScoreMenu(&score_list);
}