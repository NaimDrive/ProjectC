#include "initGame.h"
#include "displayGame.h"
#include <sys/ioctl.h>
#include <stdio.h>


void displayGame(Team *team1, Team *team2, int sz) {
    int i;
    for (i = 0; i < sz; i++) {
        if(i == 0 || i == sz-1)
            printf("*");
        else if(i == team1->position || i == team2->position)
            printf("o");
        else
            printf(" ");
    }
    printf("\n");
    for (i = 0; i < sz; i++) {
        if(i == 0 || i == sz-1)
            printf("*");
        else if(i == team1->position)
            printf("|");
        else if(i == team2->position)
            printf("|");
        else
            printf(" ");
    }
    printf("\n");
    for (i = 0; i < sz; i++) {
        if(i == 0 || i == sz-1)
            printf("*");
        else if(i == team1->position)
            printf("|");
        else if(i == team2->position)
            printf("|");
        else
            printf(" ");
    }
    printf("\n");
    for (i = 0; i < sz; i++) {
        if(i == 0 || i == sz-1)
            printf("*");
        else
            printf("_");
    }
    printf("\n\n");
}