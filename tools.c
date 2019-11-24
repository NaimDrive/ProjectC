#include "initGame.h"
#include "tools.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int weaponDamage(Weapon *weapon) {
    return (rand() % (weapon->degatsMax - weapon->degatsMin + 1)) + weapon->degatsMin;
}

int effectiveProtection(int protection) {
    int res = (rand() % 100) + 1;
    if(res <= protection)
      return 1;
    return 0;
}

int randHeal(Healing *healing) {
  return (rand() % (healing->effetMin - healing->effetMax + 1)) + healing->effetMin;
}

int distanceBetweenChampions(Team *team1, Team *team2) {
  if(team1->id == 0)
    return team2->position - team1->position;
  else
    return -(team2->position - team1->position);
}

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

void enterToContinue() {
    printf("(Appuyez sur Entrer pour continuer)");
    while(getchar() != '\n');
}

Weapon * searchWeapon(Weapon **weapon, int *nbWeapons, char *w) {
  for (int i = 0; i < *nbWeapons; i++) {
    if(strcmp(weapon[i]->nom, w) == 0) {
      return weapon[i];
    }
  }
  return NULL;
}

Protection * searchProtection(Protection **protection, int *nbProtections, char *p) {
  for (int i = 0; i < *nbProtections; i++) {
    if(strcmp(protection[i]->nom, p) == 0) {
      return protection[i];
    }
  }
  return NULL;
}

Healing * searchHealing(Healing **healing, int *nbHealings, char *h) {
  for (int i = 0; i < *nbHealings; i++) {
    if(strcmp(healing[i]->nom, h) == 0) {
      return healing[i];
    }
  }
  return NULL;
}