#ifndef __FIGHTMODE_H__
#define __FIGHTMODE_H__

void fightingMode(Team *team);

void equipTeam(Team *team, Weapon **weapons, Protection **protections, Healing **healings, int *nbWeapons, int*nbProtections, int *nbHealings);

#endif