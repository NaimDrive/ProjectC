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

/*
    Display champions health points.
    @Param1 Team
    @Param2 Team
    @Param3 int
    @Return void
*/
void displayHealth(Team *team1, Team *team2, int sz);

/*
    Display champions in the map.
    @Param1 Team
    @Param2 Team
    @Param3 int
    @Return void
*/
void displayGame(Team *team1, Team *team2, int sz);

/*
    Display attacks in the map.
    @Param1 Team
    @Param2 Team
    @Param3 int
    @Return void
*/
void displayAttack(Team *team1, Team *team2, int sz);

#endif