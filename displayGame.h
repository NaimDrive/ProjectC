#ifndef __DISPLAYGAME_H__
#define __DISPLAYGAME_H__

#ifndef _DEFAULT_SOURCE
#define _DEFAULT_SOURCE
#endif

typedef struct {
    char c;
    int position;
    int direction;
} AttackAnimation;

void displayGame(Team *team1, Team *team2, int sz);

void displayAttack(Team *team1, Team *team2, int sz);

#endif