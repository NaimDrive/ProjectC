#include "initGame.h"
#include "tools.h"
#include <stdio.h>
#include <stdlib.h>
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
