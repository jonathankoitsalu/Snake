#ifndef COMMS_H
#define COMMS_H

#include <string.h>

typedef struct
{
    char name[4];
    char score[4];
} SCORE;

typedef struct
{
    SCORE list[10];
} SCORE_LIST;

void ParseScore(SCORE_LIST *score_list);
void ShowScore(void);

#endif //COMMS_H