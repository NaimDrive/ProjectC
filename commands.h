#ifndef __COMMANDES_H__
#define __COMMANDES_H__

char* substring(char *src, int beg, int end);

int getID(char *command, int n);

void showVegetables();

void showVegetable(int id);

void showFruits();

void showFruit(int id);

void weapons();

void weapon(int id);

void showProtections();

void showProtection(int id);

void showCares();

void showCare(int id);

void save();

void help();

void quitGame();

void readCommands();

#endif