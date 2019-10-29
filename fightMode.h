#ifndef __FIGHTMODE_H__
#define __FIGHTMODE_H__

void fightingMode(Team *team1, Team *team2, int screenSize);

void equipTeam(Team *team, Weapon **weapons, Protection **protections, Healing **healings, int *nbWeapons, int*nbProtections, int *nbHealings);

void weaponChoice(Team *team, Weapon **weapons, int *nbChampions, char *command);

void protectionChoice(Team *team, Protection **protections, int *nbProtections, char *command);

void showEndGame(Team *team1, Team *team2);

void endRound(Team *team1, Team* team2, int maximumCE);

void roundWinner(Team *team1, Team *team2, int maximumCE);

void takeOffProtection(Team *team);

void healingChoice(Team *team, Healing **healings, int *nbHealings, char *command);

#endif
