#ifndef __COMMANDES_H__
#define __COMMANDES_H__

char* substring(char *src, int beg, int end);

int getID(char *command, int n);

void showVegetables(Champion **champions, int *nbChampions);

void showVegetable(Champion **champions, int *nbChampions, int id);

void showFruits(Champion **champions, int *nbChampions);

void showFruit(Champion **champions, int *nbChampions, int id);

void showWeapons(Weapon **weapons, int *nbWeapons);

void showWeapon(Weapon **weapons, int *nbWeapons, int id);

void showProtections(Protection **protections, int *nbProtections);

void showProtection(Protection **protections, int *nbProtections, int id);

void showCares(Healing **healings, int *nbHealings);

void showCare(Healing **healings, int *nbHealings, int id);

void fight(char *vegetable, char* fruit, Champion **champions, int *nbChampions);

// void save();

void help();

void exitGame();

void readCommands(Champion **champions, Weapon **weapons, Protection **protections, Healing **healings, int *nbChampions, int *nbWeapons, int *nbProtections, int *nbHealings);

#endif
