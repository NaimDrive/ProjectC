#include "initGame.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "initGame.h"
#include "commands.h"

char* substring(char *src, int beg, int end) {
  char *cpy = (char*)malloc(((end-beg)+1)*sizeof(char));
  int i;

  for(i = beg;(*(src+i) != '\0') && i < end; i++) {
    *cpy = *(src+i);
    cpy++;
  }
  *cpy = '\0';

  return cpy - (end-beg);
}

int getID(char *command, int n) {
  char *c = substring(command, n, strlen(command));
  int id = atoi(c);
  free(c);
  return id;
}

void showVegetables(Champion **champions, int *nbChampions) {
  Champion *c;
  int i;
  for(i = 0; i < ((*nbChampions)-6); i++)
  {   
    c = champions[i];
    printf("Num %d\nVariété %s\nType %s\nForce %d\nResistance %d\nPV Max %d\nCE %d\n\n", c->num, c->variete, c->type, c->force, c->resistance, c->PVMax, c->CE);
  }
}

void showVegetable(Champion **champions, int *nbChampions, int id) {
  if(id <= ((*nbChampions)-7) && (id >= 0)) {
    printf("Num %d\nVariété %s\nType %s\nForce %d\nResistance %d\nPV Max %d\nCE %d\n\n", champions[id]->num, champions[id]->variete, champions[id]->type, champions[id]->force, champions[id]->resistance, champions[id]->PVMax, champions[id]->CE);
  } else {
    printf("Veuillez choisir un ID compris entre 0 et %d\n", ((*nbChampions)-7));
  }
}

void showFruits(Champion **champions, int *nbChampions) {
 Champion *c;
  int i;
  for(i = 6; i < *nbChampions; i++)
  {   
    c = champions[i];
    printf("Num %d\nVariété %s\nType %s\nForce %d\nResistance %d\nPV Max %d\nCE %d\n\n", c->num, c->variete, c->type, c->force, c->resistance, c->PVMax, c->CE);
  }
}

void showFruit(Champion **champions, int *nbChampions, int id) {
  id = id <= 6 ? id+5 : id;
  if(id < *nbChampions && id > 0) {
    printf("Num %d\nVariété %s\nType %s\nForce %d\nResistance %d\nPV Max %d\nCE %d\n\n", champions[id]->num, champions[id]->variete, champions[id]->type, champions[id]->force, champions[id]->resistance, champions[id]->PVMax, champions[id]->CE);
  } else {
    printf("Veuillez re-vérifier l'ID entré.\n");
  }
}

void showWeapons(Weapon **weapons, int *nbWeapons) {
  Weapon *w;
  int i;
  for(i = 0; i < *nbWeapons; i++)
  {   
    w = weapons[i];
    printf("Num %d\nNom %s\nCE %d\nCA %d\nDégâts min %d\nDégâts max %d\nCE %d\n\n", w->num, w->nom, w->CE, w->CA, w->degatsMin, w->degatsMax, w->portee);
  }
}

void showWeapon(Weapon **weapons, int *nbWeapons, int id) {
  if(id < *nbWeapons && id >= 0) {
    printf("Num %d\nNom %s\nCE %d\nCA %d\nDégâts min %d\nDégâts max %d\nCE %d\n\n", weapons[id]->num, weapons[id]->nom, weapons[id]->CE, weapons[id]->CA, weapons[id]->degatsMin, weapons[id]->degatsMax, weapons[id]->portee);
  } else {
    printf("Veuillez entrer un ID compris entre 0 et %d\n", *nbWeapons);
  }
}

void showProtections(Protection **protections, int *nbProtections) {
  Protection *p;
  int i;
  for(i = 0; i < *nbProtections; i++)
  {   
    p = protections[i];
    printf("Num %d\nNom %s\nCE %d\nCA %d\nProbabilité %d %c \n\n", p->num, p->nom, p->CE, p->CA, p->probabilite, '%');
  }
}

void showProtection(Protection **protections, int *nbProtections, int id) {
  if(id < *nbProtections && id >= 0) {
    printf("Num %d\nNom %s\nCE %d\nCA %d\nProbabilité %d %c \n\n", protections[id]->num, protections[id]->nom, protections[id]->CE, protections[id]->CA, protections[id]->probabilite, '%');
  } else {
    printf("Veuillez entrer un ID compris entre 0 et %d\n", *nbProtections);
  }
}

void showCares(Healing **healings, int *nbHealings) {
  Healing *h;
  int i;
  for(i = 0; i < *nbHealings; i++)
  {   
    h = healings[i];
    printf("Num %d\nNom %s\nCE %d\nCA %d\nVolume %d\nEffet min %d\nEffet max %d\n\n", h->num, h->nom, h->CE, h->CA, h->volume, h->effetMin, h->effetMax);
  }
}

void showCare(Healing **healings, int *nbHealings, int id) {
  if(id < *nbHealings && id >= 0) {
    printf("Num %d\nNom %s\nCE %d\nCA %d\nVolume %d\nEffet min %d\nEffet max %d\n\n", healings[id]->num, healings[id]->nom, healings[id]->CE, healings[id]->CA, healings[id]->volume, healings[id]->effetMin, healings[id]->effetMax);
  } else {
    printf("Veuillez entrer un ID compris entre 0 et %d\n", *nbHealings);
  }
}

void fight(char *command) {
  printf("'Versus' présent ? %d\n", (strstr(command, "versus") != NULL));
}
/*
void save() {
  printf("%s\n", "save");
}
*/

void help() {
  printf("Show every possible command");
}

void exitGame() {
  exit(0);
}

void readCommands(Champion **champions, Weapon **weapons, Protection **protections, Healing **healings, int *nbChampions, int *nbWeapons, int *nbProtections, int *nbHealings) {
  char *command = (char*)malloc(256*sizeof(char));

  while(1) {
    printf("Veuillez saisir votre commande : ");
    fgets(command, 256, stdin);
    // printf("Entered command : %s", command);
    if((strlen(command) > 0) && (command[strlen(command)-1] == '\n')) command[strlen(command)-1] = '\0';

    // ~~~ Cases ~~~ //
    if(strcmp(command, "exit") == 0) exitGame();
    else if(strcmp(command, "show vegetables") == 0) showVegetables(champions, nbChampions);
    else if(strncmp(command, "show vegetable ", 15) == 0) showVegetable(champions, nbChampions, getID(command, 15));

    else if(strcmp(command, "show fruits") == 0) showFruits(champions, nbChampions);
    else if(strncmp(command, "show fruit ", 11) == 0) showFruit(champions, nbChampions, getID(command, 11));

    else if(strcmp(command, "show weapons") == 0) showWeapons(weapons, nbWeapons);
    else if(strncmp(command, "show weapon ", 12) == 0) showWeapon(weapons, nbWeapons, getID(command, 12));

    else if(strcmp(command, "show protections") == 0) showProtections(protections, nbProtections);
    else if(strcmp(command, "show protection ") == 0) showProtection(protections, nbProtections, getID(command, 16));

    else if(strcmp(command, "show cares") == 0) showCares(healings, nbHealings);
    else if(strcmp(command, "show care ") == 0) showCare(healings, nbHealings, getID(command, 10));

    else if(strncmp(command, "fight ", 6) == 0) {
      /* Work in progress */
      fight(substring(command, 6, strlen(command)));
    }

    else if(strcmp(command, "save") == 0) save();
  }

  free(command);
}


int main() {

  Champion **champions = malloc(sizeof(Champion *) * 12);
  Weapon **weapons = malloc(sizeof(Weapon *) * 5);
  Protection **protections = malloc(sizeof(Protection *) * 4);
  Healing **healings = malloc(sizeof(Healing *) * 3);

  int *nbChampions = calloc(1, sizeof(int));
  int *nbWeapons = calloc(1, sizeof(int)); 
  int *nbProtections = calloc(1, sizeof(int)); 
  int *nbHealings = calloc(1, sizeof(int));
  
  initGame(champions, weapons, protections, healings, nbChampions, nbWeapons, nbProtections, nbHealings);
  // afficherChampions(champions, nbChampions);
  // afficherWeapons(weapons, nbWeapons);
  // afficherProtections(protections, nbProtections);
  // afficherSoins(healings, nbHealings);
  
  readCommands(champions, weapons, protections, healings, nbChampions, nbWeapons, nbProtections, nbHealings);


  return 0;
}
