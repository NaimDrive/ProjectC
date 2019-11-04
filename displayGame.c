#include "initGame.h"
#include "colors.h"
#include "displayGame.h"
#include <sys/ioctl.h>
#include <stdio.h>


void displayGame(Team *team1, Team *team2, int sz) {
    int i;
    for (i = 0; i < sz; i++) {
        if(i == 0 || i == sz-1) {
            blue();
            printf("*");
        } else if((i == team1->position && team1->id == 0) || (i == team2->position && team2->id == 0)) {
            green();
            printf("é");
            // printf("o");
        } else if((i == team2->position && team2->id == 1) || (i == team1->position && team1->id == 1)) {
            yellow();
            printf("ù");
            // printf("o");
        } else {
            printf(" ");
        } 
    }
    printf("\n");
    for (i = 0; i < sz; i++) {
        if(i == 0 || i == sz-1) {
            white();
            printf("*");
        } else if((i == team1->position && team1->id == 0) || (i == team2->position && team2->id == 0)) {
            green();
            printf("|");
        } else if((i == team2->position && team2->id == 1) || (i == team1->position && team1->id == 1)) {
            yellow();
            printf("|");
        } else {
            printf(" ");
        }
    }
    printf("\n");
    for (i = 0; i < sz; i++) {
        if(i == 0 || i == sz-1) {
            red();
            printf("*");
        } else if((i == team1->position && team1->id == 0) || (i == team2->position && team2->id == 0)) {
            green();
            printf("|");
        } else if((i == team2->position && team2->id == 1) || (i == team1->position && team1->id == 1)) {
            yellow();
            printf("|");
        } else{
            printf(" ");
        }
    }
    printf("\n");
    for (i = 0; i < sz; i++) {
        brown();
        if(i == 0 || i == sz-1){
            printf("*");
        } else {
            brown();
            printf("_");
        }
    }
    printf("\n\n");
    resetColor();
}