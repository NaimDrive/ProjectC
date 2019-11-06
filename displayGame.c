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
        } else if((i == team1->position && team1->id == 0)) {
            green();
            // printf("é");
            printf("%c", team1->champion->head);
        } else if((i == team2->position && team2->id == 0)) {
            green();
            // printf("é");
            printf("%c", team2->champion->head);
        } else if((i == team2->position && team2->id == 1)) {
            yellow();
            // printf("ù");
            printf("%c", team2->champion->head);
        } else if((i == team1->position && team1->id == 1)) {
            yellow();
            printf("%c", team1->champion->head);
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

void displayAttack(Team *team1, Team *team2, int sz) {
    AttackAnimation attack;
    int i;

    if(team1->id == 0 && team1->position+1 < team2->position) {
        attack.direction = 1;
        attack.position = team1->position+1;
    } else if(team1->id == 1 && team1->position-1 > team2->position){
        attack.direction = -1;
        attack.position = team1->position-1;
    }

    while((team1->id == 0 && attack.position+1 < team2->position) || (team1->id == 1 && attack.position-1 > team2->position)) {
        for (i = 0; i < sz; i++) {
            if(i == 0 || i == sz-1) {
                blue();
                printf("*");
            } else if((i == team1->position && team1->id == 0) || (i == team2->position && team2->id == 0)) {
                green();
                printf("é");
            } else if((i == team2->position && team2->id == 1) || (i == team1->position && team1->id == 1)) {
                yellow();
                printf("ù");
            } else if(i == attack.position) {
                if(attack.direction == 1)
                    printf(")");
                else
                    printf("(");
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
        if(team1->id == 0)
            attack.position++;
        else
            attack.position--;
    }
    printf("\n\n");
    resetColor();
}