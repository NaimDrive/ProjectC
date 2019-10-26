#include "initGame.h"
#include "commands.h"
#include "fight.h"
#include "fightMode.h"
#include "endGame.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>

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
  char *endptr;
  long id = strtoul(c, &endptr, 10);
  free(c);
  if(*command != '\0' && *endptr == '\0') {
    return id;
  } else {
    return -1;
  }
}

int getChampIndex(char *champName, Champion **champion, int *nbChampions) {
  int i = 0;
  for(; i < *nbChampions; i++) {
    if(strcmp(champName, champion[i]->variete) == 0) return i;
  }
  return -1;
}

void showVegetables(Champion **champions, int *nbChampions) {
  Champion *c;
  int i;
  for(i = 0; i < ((*nbChampions)-6); i++)
  {
    c = champions[i];
    printf("Num : %d | Variété : %s | Type : %s | Force : %d | Resistance : %d | PV Max : %d | CE : %d\n", c->num, c->variete, c->type, c->force, c->resistance, c->PVMax, c->CE);
  }
  printf("\n");
}

void showVegetable(Champion **champions, int *nbChampions, int id) {
  if(id <= ((*nbChampions)-7) && (id >= 0)) {
    printf("Num : %d | Variété : %s | Type : %s | Force : %d | Resistance : %d | PV Max : %d | CE : %d\n\n", champions[id]->num, champions[id]->variete, champions[id]->type, champions[id]->force, champions[id]->resistance, champions[id]->PVMax, champions[id]->CE);
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
    printf("Num : %d | Variété : %s | Type : %s | Force : %d | Resistance : %d | PV Max : %d | CE : %d\n", c->num, c->variete, c->type, c->force, c->resistance, c->PVMax, c->CE);
  }
  printf("\n");
}

void showFruit(Champion **champions, int *nbChampions, int id) {
  id = id <= 6 ? id+5 : id;
  if(id < *nbChampions && id > 0) {
    printf("Num : %d | Variété : %s | Type : %s | Force : %d | Resistance : %d | PV Max : %d | CE : %d\n\n", champions[id]->num-5, champions[id]->variete, champions[id]->type, champions[id]->force, champions[id]->resistance, champions[id]->PVMax, champions[id]->CE);
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
    printf("Num : %d | Nom : %s | CE : %d | CA : %d | Dégâts : %d-%d | CE : %d\n", w->num, w->nom, w->CE, w->CA, w->degatsMin, w->degatsMax, w->portee);
  }
  printf("\n");
}

void showWeapon(Weapon **weapons, int *nbWeapons, int id) {
  if(id < *nbWeapons && id >= 0) {
    printf("Num : %d | Nom : %s | CE : %d | CA : %d | Dégâts : %d-%d | CE : %d\n\n", weapons[id]->num, weapons[id]->nom, weapons[id]->CE, weapons[id]->CA, weapons[id]->degatsMin, weapons[id]->degatsMax, weapons[id]->portee);
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
    printf("Num : %d | Nom : %s | CE : %d | CA : %d | Probabilité : %d %c \n", p->num, p->nom, p->CE, p->CA, p->probabilite, '%');
  }
  printf("\n");
}

void showProtection(Protection **protections, int *nbProtections, int id) {
  if(id < *nbProtections && id >= 0) {
    printf("Num : %d | Nom : %s | CE : %d | CA : %d | Probabilité : %d %c \n\n", protections[id]->num, protections[id]->nom, protections[id]->CE, protections[id]->CA, protections[id]->probabilite, '%');
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
    printf("Num : %d | Nom : %s | CE : %d | CA : %d | Volume : %d | Effet (min-max) : %d-%d\n", h->num, h->nom, h->CE, h->CA, h->volume, h->effetMin, h->effetMax);
  }
  printf("\n");
}

void showCare(Healing **healings, int *nbHealings, int id) {
  if(id < *nbHealings && id >= 0) {
    printf("Num : %d | Nom : %s | CE : %d | CA : %d | Volume : %d | Effet : %d-%d\n", healings[id]->num, healings[id]->nom, healings[id]->CE, healings[id]->CA, healings[id]->volume, healings[id]->effetMin, healings[id]->effetMax);
  } else {
    printf("Veuillez entrer un ID compris entre 0 et %d\n", *nbHealings);
  }
}

void initFight(Champion *vegetable, Champion* fruit, Weapon **weapons, Protection **protections, Healing **healings, int *nbChampions, int *nbWeapons, int *nbProtections, int *nbHealings) {
  // Take console size
  Winsize screenSize;
  ioctl(0, TIOCGWINSZ, &screenSize);
  // screenSize.ws_col number of column
  // screenSize.ws_row number of row
  // printf("Screen width: %i  Screen height: %i\n", screenSize.ws_col, screenSize.ws_row);
  
  Team *team1 = initTeam(0, screenSize);
  Team *team2 = initTeam(1, screenSize);
  // char *command = malloc(256*sizeof(char));

  /* choose arme, soins, protections pour team1 et pour team2 */
  /* Set up fight */
  buyChampion(vegetable, team1);  
  buyChampion(fruit, team2);
  printf("\n%s VERSUS %s !\n", team1->champion->variete, team2->champion->variete);
  equipTeam(team1, weapons, protections, healings, nbWeapons, nbProtections, nbHealings);

  /* fin Set up fight */

  
  /* commence infinite loop avec le tour par tour */
  /*
  while((team1->champion->PV != 0 && team2->champion->PV != 0)) {
    fightingMode(team1);
    if(team2->champion->PV == 0) break; // Avoid j2 playing if he's dead 
    fightingMode(team2);
  }
  */
  endBattle(team1, team2);
}

void help() {
  printf("Show every possible command");
}

void exitGame(Champion **champions, Weapon **weapons, Protection **protections, Healing **healings, int *nbChampions, int *nbWeapons, int *nbProtections, int *nbHealings) {
  deallocateMemory(champions, weapons, protections, healings, nbChampions, nbWeapons, nbProtections, nbHealings);
  exit(0);
}

void readCommands(Champion **champions, Weapon **weapons, Protection **protections, Healing **healings, int *nbChampions, int *nbWeapons, int *nbProtections, int *nbHealings) {
  printf("Le nombre de crédits d'équipement initiaux par équipe est de : 1000\n");
  char *command = (char*)malloc(256*sizeof(char));

  while(1) {
    printf("> ");
    fgets(command, 256, stdin);
    if((strlen(command) > 0) && (command[strlen(command)-1] == '\n')) command[strlen(command)-1] = '\0';

    // ~~~ Cases ~~~ //
    if(strcmp(command, "exit") == 0) {
      free(command);
      exitGame(champions, weapons, protections, healings, nbChampions, nbWeapons, nbProtections, nbHealings);
    } 
    else if(strcmp(command, "show vegetables") == 0) showVegetables(champions, nbChampions);
    else if(strncmp(command, "show vegetable ", 15) == 0) showVegetable(champions, nbChampions, getID(command, 15));

    else if(strcmp(command, "show fruits") == 0) showFruits(champions, nbChampions);
    else if(strncmp(command, "show fruit ", 11) == 0) showFruit(champions, nbChampions, getID(command, 11));

    else if(strcmp(command, "show weapons") == 0) showWeapons(weapons, nbWeapons);
    else if(strncmp(command, "show weapon ", 12) == 0) showWeapon(weapons, nbWeapons, getID(command, 12));

    else if(strcmp(command, "show protections") == 0) showProtections(protections, nbProtections);
    else if(strncmp(command, "show protection ", 16) == 0) showProtection(protections, nbProtections, getID(command, 16));

    else if(strcmp(command, "show cares") == 0) showCares(healings, nbHealings);
    else if(strncmp(command, "show care ", 10) == 0) showCare(healings, nbHealings, getID(command, 10));

    else if(strncmp(command, "fight ", 6) == 0) {
      /* Work in progress */
      char *tmp = substring(command, 6, strlen(command));
      char *indexVersus = strstr(tmp, "versus");
      char *fruit;
      char *legume;
      int i = 0;

      if(indexVersus == NULL) {
        printf("! Utilisation ! : fight <legume> versus <fruit>\n");
        continue;
      }

      while((tmp+i) != indexVersus) i++; // get index 'v' de "versus"

      legume = substring(tmp, 0, i-1); // nom du legume
      fruit = substring(tmp, i+7, strlen(tmp)); // nom du fruit
      free(tmp);
      int indexVeg = getChampIndex(legume, champions, nbChampions);
      int indexFruit = getChampIndex(fruit, champions, nbChampions);
      free(legume);
      free(fruit);
      if(indexVeg != -1 && indexFruit != -1) {
        initFight(champions[indexVeg], champions[indexFruit], weapons, protections, healings, nbChampions, nbWeapons, nbProtections, nbHealings);
      }
    } else if(strcmp(command,"clear") == 0) system("clear");

  }

  free(command);
}