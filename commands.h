#ifndef __COMMANDES_H__
#define __COMMANDES_H__

char* substring(char *src, int beg, int end);

int getID(char *command, int n);

int getChampIndex(char *champName, Champion **champion, int nbChampions);

void showVegetables(Champion **champions, int *nbChampions);

void showVegetable(Champion **champions, int *nbChampions, int id);

void showFruits(Champion **champions, int *nbChampions);

void showFruit(Champion **champions, int *nbChampions, int id);

void showWeapons(Weapon **weapons, int *nbWeapons, int ce);

void showWeapon(Weapon **weapons, int *nbWeapons, int id);

void showProtections(Protection **protections, int *nbProtections, int ce);

void showProtection(Protection **protections, int *nbProtections, int id);

void showCares(Healing **healings, int *nbHealings, int ce);

void showCare(Healing **healings, int *nbHealings, int id);

int replay(char *command);

void fight(Champion *vegetable, Champion* fruit, Champion **champions, Weapon **weapons, Protection **protections, Healing **healings, int *nbChampions, int *nbWeapons, int *nbProtections, int *nbHealings, Team *team1, Team *team2, Winsize screenSize);

void help();

void exitGame(Champion **champions, Weapon **weapons, Protection **protections, Healing **healings, int *nbChampions, int *nbWeapons, int *nbProtections, int *nbHealings);

void readCommands(Champion **champions, Weapon **weapons, Protection **protections, Healing **healings, int *nbChampions, int *nbWeapons, int *nbProtections, int *nbHealings, Team *team1, Team *team2, Winsize screenSize);

#endif
