#include "initGame.h"
#include "colors.h"
#include "displayGame.h"
#include "tools.h"

#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void displayStats(Team *team1, Team *team2, int sz) {
    int soin1, soin2, margin;
    if(team1->healing != NULL) soin1 = team1->healing->volume;
    else soin1 = 0;

    if(team2->healing != NULL) soin2 = team2->healing->volume;
    else soin2 = 0;

    green();
    printf("  CA   |-> %d", team1->CA);
    margin = (team1->CA > 9 ? (sz-24) : (sz-23));
    yellow();
    printf("%*d", margin, team2->CA);
    printf(" <-|   CA\n");

    green();
    printf("Portée |-> %d", team1->weapon->portee);
    margin = (team1->weapon->portee > 9 ? (sz-24) : (sz-23));
    yellow();
    printf("%*d", margin, team2->weapon->portee);
    printf(" <-| Portée\n");

    green();
    printf(" Soin  |-> %d", soin1);
    yellow();
    printf("%*d <-|  Soin\n", (sz-(23)), soin2);
    printf("\n");
}

void displayHealth(Team *team1, Team *team2, int sz) {
    int lenHealthBar = strlen(team1->champion->variete)-strlen(team2->champion->variete)-((8+2+20)*2)-(sz/10)-(9);
    int margin =  (double)((sz-2)/2)+(double)(lenHealthBar/2);
    int pvLeftP1 = (int)(((double)(team1->champion->PV)/(double)(team1->champion->PVMax)) * 20);
    int pvLeftP2 = (int)(((double)(team2->champion->PV)/(double)(team2->champion->PVMax)) * 20);
    int distance = distanceBetweenChampions(team1, team2);

    green();
    printf("%*s ", margin, team1->champion->variete);
    resetColor();
    // len (with the previous space) : 8
    printf("(%02d/%02d)[", team1->champion->PV, team1->champion->PVMax);

    greenBG();
    printf("%*c", pvLeftP1, ' ');
    resetColor();
    if(pvLeftP1 < 20)
        printf("%*c", (20 - pvLeftP1), ' ');
    
    printf("]%*c", ((sz/10)/2), ' ');
    gray();
    whiteBG();
    printf("/| %03d |\\", distance);
    resetColor();
    printf("%*c[", ((sz/10)/2), ' ');
    
    if(pvLeftP2 < 20)
        printf("%*c", (20 - pvLeftP2), ' ');
    yellowBG();
    printf("%*c", pvLeftP2, ' ');
    resetColor();


    printf("](%02d/%02d)", team2->champion->PV, team2->champion->PVMax);
    yellow();
    printf(" %s\n\n", team2->champion->variete);
    resetColor();
}

void displayGame(Team *team1, Team *team2, int sz) {
    int i;
    for (i = 0; i < sz; i++) {
        if(i == 0 || i == sz-1) {
            blue();
            printf("*");
        } else if(i == team1->position) {
            green();
            printf("%c", team1->champion->head);
        } else if(i == team2->position) {
            yellow();
            printf("%c", team2->champion->head);
        } else {
            printf(" ");
        }
    }
    printf("\n");
    for (i = 0; i < sz; i++) {
        if(i == 0 || i == sz-1) {
            white();
            printf("*");
        } else if(i == team1->position) {
            if(team1->protectionActivated)
                white();
            else
                green();
            printf("|");
        } else if(i == team2->position) {
            if(team2->protectionActivated)
                white();
            else
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
        } else if(i == team1->position) {
            green();
            printf("|");
        } else if(i == team2->position) {
            yellow();
            printf("|");
        } else{
            printf(" ");
        }
    }
    printf("\n");
    for (i = 0; i < sz; i++) {
        whiteBG();
        gray();
        if(i == 0){
            printf("\\");
        } else if(i == sz-1) {
            printf("/");
        } else {
            printf("|");
        }
        resetColor();
    }
    printf("\n\n");
    resetColor();
}

void displayAttack(Team *team1, Team *team2, int sz) {
    AttackAnimation attack;
    unsigned int micro = 350000;
    int i;

    if(team1->id == 0 && team1->position+1 < team2->position) {
        attack.direction = 1;
        attack.position = team1->position+1;
    } else if(team1->id == 1 && team1->position-1 > team2->position){
        attack.direction = -1;
        attack.position = team1->position-1;
    } else {
        return;
    }

    while((team1->id == 0 && attack.position+1 < team2->position) || (team1->id == 1 && attack.position-1 > team2->position)) {
        system("clear");
        for (i = 0; i < sz; i++) {
            if(i == 0 || i == sz-1) {
                blue();
                printf("*");
            } else if((i == team1->position && team1->id == 0)) {
                green();
                printf("%c", team1->champion->head);
            } else if((i == team2->position && team2->id == 0)) {
                green();
                printf("%c", team2->champion->head);
            } else if((i == team2->position && team2->id == 1)) {
                yellow();
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
                if(attack.position == (team2->position)+2)
                    red();
                else
                    green();
                printf("|");
            } else if((i == team2->position && team2->id == 1) || (i == team1->position && team1->id == 1)) {
                if(attack.position == (team2->position)-2)
                    red();
                else
                    yellow();
                printf("|");
            } else if(i == attack.position) {
                if(attack.direction == 1) {
                    green();
                    printf(")");
                } else {
                    yellow();
                    printf("(");
                }
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
            whiteBG();
            if(i == 0){
                printf("\\");
            } else if(i == sz-1) {
                printf("/");
            } else {
                printf("_");
            }
            resetColor();
        }
        if(team1->id == 0)
            attack.position++;
        else
            attack.position--;
        printf("\n");

        usleep(micro);
    }
    printf("\n\n");
    resetColor();
}
