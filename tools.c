#include "initGame.h"
#include "tools.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

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

char * strtolower( char * dest, const char * src ) {
    char * result = dest;
    while(*src) {
      if(*src == '_') {
        *dest++ = ' ';
      } else if(*src == '-') {
        *dest++ = ' ';
      } else {
        *dest++ = tolower(*src);
      }
      src++;
    }
    *dest = '\0';
    return result;
}

Weapon * searchWeapon(Weapon **weapon, int *nbWeapons, char *w) {
  char *param = malloc(sizeof(char)*(strlen(w)+1));
  char *name = malloc(sizeof(char)*100);
  strtolower(param, w);
  
  for (int i = 0; i < *nbWeapons; i++) {
    strtolower(name, weapon[i]->nom);

    if(strcmp(name, param) == 0) {
      free(name);
      free(param);
      return weapon[i];
    }
  }

  free(name);
  free(param);
  return NULL;
}

Protection * searchProtection(Protection **protection, int *nbProtections, char *p) {
  char *param = malloc(sizeof(char)*(strlen(p)+1));
  char *name = malloc(sizeof(char)*100);
  strtolower(param, p);
  
  for (int i = 0; i < *nbProtections; i++) {
    strtolower(name, protection[i]->nom);

    if(strcmp(name, param) == 0) {
      free(name);
      free(param);
      return protection[i];
    }
  }

  free(name);
  free(param);
  return NULL;
}

Healing * searchHealing(Healing **healing, int *nbHealings, char *h) {
  char *param = malloc(sizeof(char)*(strlen(h)+1));
  char *name = malloc(sizeof(char)*100);
  strtolower(param, h);
  
  for (int i = 0; i < *nbHealings; i++) {
    strtolower(name, healing[i]->nom);

    if(strcmp(name, param) == 0) {
      free(name);
      free(param);
      return healing[i];
    }
  }

  free(name);
  free(param);
  return NULL;
}