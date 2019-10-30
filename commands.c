#include "initGame.h"
#include "fight.h"
#include "fightMode.h"
#include "endGame.h"
#include "commands.h"
#include "colors.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <ctype.h>

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
  long res;
  if(*c != '\0' && *endptr == '\0') {
    res = id;
  } else {
    res = -1;
  }
  free(c);
  return res;
}

int getChampIndex(char *champName, Champion **champions, int nbChampions) {
  champName[0] = toupper(champName[0]); // make first char an uppercase

  int i;
  for(i = 0; i < nbChampions; i++) {
    if(strcmp(champName, champions[i]->variete) == 0) return i;
  }

  return -1;
}

int checkingChamps(char *veg, char *fruit, int vegIndex, int fruitIndex, Champion **champions, int nbChampions) {
  int output = 0;
  veg[0] = toupper(veg[0]); // make first char an uppercase
  fruit[0] = toupper(fruit[0]); // make first char an uppercase
  
  white();
  
  if(vegIndex == -1) {
    red();
    printf("'%s' ne fait pas partie des champions jouables.\n", veg);
  } else if(vegIndex >= 6) {
    red();
    printf("'%s' n'est pas un légume !\n", veg);
  }

  if(fruitIndex == -1) {
    red();
    printf("'%s' ne fait pas partie des champions jouables.\n", fruit);
  } else if(fruitIndex < 6) {
    red();
    printf("'%s' n'est pas un fruit !\n", fruit);
  }  

  if((vegIndex != -1 && fruitIndex != -1) && fruitIndex > 5 && vegIndex < 6) output = 1;
  resetColor();

  free(veg); // will never be used again
  free(fruit); // will never be used again
  
  return output;
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
  printf("id reçu : %d\n", id);
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

void showWeapons(Weapon **weapons, int *nbWeapons, int ce) {
  Weapon *w;
  int i;
  for(i = 0; i < *nbWeapons; i++)
  {
    w = weapons[i];
    if(ce != -1) {
      if(ce >= w->CE) green();
      else { resetColor() , red(); }
    }
    printf("Num : %d | Nom : %s | CE : %d | CA : %d | Dégâts : %d-%d | CE : %d\n", w->num, w->nom, w->CE, w->CA, w->degatsMin, w->degatsMax, w->portee);
  }
  printf("\n");
  resetColor();
}

void showWeapon(Weapon **weapons, int *nbWeapons, int id) {
  if(id < *nbWeapons && id >= 0) {
    printf("Num : %d | Nom : %s | CE : %d | CA : %d | Dégâts : %d-%d | CE : %d\n\n", weapons[id]->num, weapons[id]->nom, weapons[id]->CE, weapons[id]->CA, weapons[id]->degatsMin, weapons[id]->degatsMax, weapons[id]->portee);
  } else {
    printf("Veuillez entrer un ID compris entre 0 et %d\n", *nbWeapons);
  }
}

void showProtections(Protection **protections, int *nbProtections, int ce) {
  Protection *p;
  int i;
  
  for(i = 0; i < *nbProtections; i++)
  {
    p = protections[i];
    if(ce != -1) {
      if(ce >= p->CE) green();
      else { resetColor() , red(); }
    }
    printf("Num : %d | Nom : %s | CE : %d | CA : %d | Probabilité : %d %c \n", p->num, p->nom, p->CE, p->CA, p->probabilite, '%');
  }
  printf("\n");
  resetColor();
  
}

void showProtection(Protection **protections, int *nbProtections, int id) {
  if(id < *nbProtections && id >= 0) {
    printf("Num : %d | Nom : %s | CE : %d | CA : %d | Probabilité : %d %c \n\n", protections[id]->num, protections[id]->nom, protections[id]->CE, protections[id]->CA, protections[id]->probabilite, '%');
  } else {
    printf("Veuillez entrer un ID compris entre 0 et %d\n", *nbProtections);
  }
}

void showCares(Healing **healings, int *nbHealings, int ce) {
  Healing *h;
  int i;
  for(i = 0; i < *nbHealings; i++)
  {
    h = healings[i];
    if(ce != -1) {
      if(ce >= h->CE) green();
      else { resetColor() , red(); }
    }
    printf("Num : %d | Nom : %s | CE : %d | CA : %d | Volume : %d | Effet (min-max) : %d-%d\n", h->num, h->nom, h->CE, h->CA, h->volume, h->effetMin, h->effetMax);
  }
  printf("\n");
  resetColor();
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

  Team *team1 = initTeam(0, screenSize);
  Team *team2 = initTeam(1, screenSize);
  
  // char *command = malloc(256*sizeof(char));

  /* choose arme, soins, protections pour team1 et pour team2 */
  /* Set up fight */
  buyChampion(vegetable, team1);
  buyChampion(fruit, team2);
  printf("\n%s VERSUS %s !\n", team1->champion->variete, team2->champion->variete);

  /* fin Set up fight */
  int maximumCE = 0;
  
  /* commence infinite loop avec le tour par tour */
  while(team1->CE > 0 && team2->CE > 0 && team1->CE >= weapons[0]->CE && team2->CE >= weapons[0]->CE) {
    maximumCE = team1->maxCE;
    equipTeam(team1, weapons, protections, healings, nbWeapons, nbProtections, nbHealings);
    equipTeam(team2, weapons, protections, healings, nbWeapons, nbProtections, nbHealings);
    while((team1->champion->PV != 0 && team2->champion->PV != 0)) {
      fightingMode(team1, team2, screenSize.ws_col);
      takeOffProtection(team2);
      if(team2->champion->PV == 0) break; // Avoid j2 playing if he's dead
      fightingMode(team2, team1, screenSize.ws_col);
      takeOffProtection(team1);
    }
    endRound(team1, team2, maximumCE);
  }
  showEndGame(team1, team2);
  endBattle(team1, team2);
}

void help() {
  white();
  printf("Commandes :\n\n");
  printf(" show vegetables - Affiche tous les légumes.\n");
  printf(" show vegetable n - Affiche le légume numéro n.\n");
  printf(" show fruits - Affiche tous les fruits.\n");
  printf(" show fruit n - Affiche le fruit numéro n.\n");
  printf(" show weapons - Affiche toutes les armes.\n");
  printf(" show weapon n - Affiche l'arme numéro n.\n");
  printf(" show protections - Affiche toutes les protections.\n");
  printf(" show protection n - Affiche la protection numéro n.\n");
  printf(" show cares - Affiche tous les soins.\n");
  printf(" show care n - Affiche le soin numéro n.\n");
  printf(" fight v versus f - Lance un combat opposant le légume v au fruit f.\n");
  printf(" help - Affiche un rappel de toutes les commandes disponibles.\n");
  printf(" exit - Quitte le jeu.\n\n");
  resetColor();
}

void exitGame(Champion **champions, Weapon **weapons, Protection **protections, Healing **healings, int *nbChampions, int *nbWeapons, int *nbProtections, int *nbHealings) {
  deallocateMemory(champions, weapons, protections, healings, nbChampions, nbWeapons, nbProtections, nbHealings);
  exit(0);
}

void readCommands(Champion **champions, Weapon **weapons, Protection **protections, Healing **healings, int *nbChampions, int *nbWeapons, int *nbProtections, int *nbHealings) {
  printf("Le nombre de crédits d'équipement initiaux par équipe est de : 1000\n");
  char *command = (char*)malloc(256*sizeof(char));
  int erreur = 0;
  
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

    else if(strcmp(command, "show weapons") == 0) showWeapons(weapons, nbWeapons, -1);
    else if(strncmp(command, "show weapon ", 12) == 0) showWeapon(weapons, nbWeapons, getID(command, 12));

    else if(strcmp(command, "show protections") == 0) showProtections(protections, nbProtections, -1);
    else if(strncmp(command, "show protection ", 16) == 0) showProtection(protections, nbProtections, getID(command, 16));

    else if(strcmp(command, "show cares") == 0) showCares(healings, nbHealings, -1);
    else if(strncmp(command, "show care ", 10) == 0) showCare(healings, nbHealings, getID(command, 10));

    else if(strncmp(command, "fight ", 6) == 0) {
      /* Work in progress */
      char *tmp = substring(command, 6, strlen(command));
      char *indexVersus = strstr(tmp, "versus");
      char *fruit;
      char *legume;
      int vegIndex;
      int fruitIndex;
      int ready;
      int i = 0;

      if(indexVersus == NULL) {
        printf("! Utilisation ! : fight <legume> versus <fruit>\n");
        continue;
      }

      while((tmp+i) != indexVersus) i++; // get index 'v' de "versus"

      legume = substring(tmp, 0, i-1); // nom du legume
      fruit = substring(tmp, i+7, strlen(tmp)); // nom du fruit
      free(tmp);
      vegIndex = getChampIndex(legume, champions, *nbChampions);
      fruitIndex = getChampIndex(fruit, champions, *nbChampions);

      ready = checkingChamps(legume, fruit, vegIndex, fruitIndex, champions, *nbChampions);
      
      if(ready) {
        initFight(champions[vegIndex], champions[fruitIndex], weapons, protections, healings, nbChampions, nbWeapons, nbProtections, nbHealings);
      }

    } else if(strcmp(command,"clear") == 0) system("clear");
    else if(strcmp(command, "help") == 0) help();
    else {
      white();
      if(erreur == 3) {
        printf("Commande '%s' invalide.\n", command);
        help();
        erreur = 0;
      } else {
        printf("Commande '%s' invalide.\n(La commande 'help' permet d'afficher les commandes disponibles)\n", command);
        erreur++;
      }
      resetColor();
	  }

  }

  free(command);
}
