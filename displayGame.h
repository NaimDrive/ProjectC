#ifndef __DISPLAYGAME_H__
#define __DISPLAYGAME_H__

typedef struct {
    char c;
    int position;
    int direction;
} AttackAnimation;

void displayGame(Team *team1, Team *team2, int sz);

void displayAttack(Team *team1, Team *team2, int sz);

#endif