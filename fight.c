#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "initGame.h"
#include "fight.h"


Team initTeam() {
  Team team;
  team.CE = 1000;
  team.CA = 0;
  team.CE_USED = 0;
  team.champion = NULL;
  team.weapon = NULL;
  team.protection = NULL;
  team.healing = NULL;

  return team;
}

int maxCE(Team *team1, Team *team2) {
  if(team1->CE >= 50 && team2->CE >= 50)
    return 50;
  else {
    if(team1->CE >= team2->CE)
      return team1->CE;
    else
      return team2->CE;
  }
}

void buyChampion(Champion *champion, Team *team, int maxCE) {
  if(team->CE_USED == maxCE)
    printf("%s\n", "Vous avez atteint la limite de CE à dépenser pendant le tour.");
  else {
    if(team->CE_USED + champion->CE > maxCE)
      printf("%s\n", "Vous ne pouvez pas acheter le champion car vous allez dépasser la limite de CE.");
    else {
      team->champion = champion;
      team->CE_USED += champion->CE;
      team->CE -= champion->CE;
    }
  }
}

int weaponDamage(Weapon *weapon) {
    return (rand() % (weapon->degatsMax - weapon->degatsMin + 1)) + weapon->degatsMin;
}


/*
int main(void) {
    Champion **champions;
    Weapon **weapons;
    Protection **protections;
    Healing **healings;
    Team team1, team2;
    int *nbChampions, *nbWeapons, *nbProtections, *nbHealings;

    srand(time(NULL));

    champions = malloc(sizeof(Champion *) * 12);
    weapons = malloc(sizeof(Weapon *) * 5);
    protections = malloc(sizeof(Protection *) * 4);
    healings = malloc(sizeof(Healing *) * 3);

    nbChampions = malloc(sizeof(int));
    nbWeapons = malloc(sizeof(int));
    nbProtections = malloc(sizeof(int));
    nbHealings = malloc(sizeof(int));

    *nbChampions = 0;
    *nbWeapons = 0;
    *nbProtections = 0;
    *nbHealings = 0;

    initGame(champions, weapons, protections, healings, nbChampions, nbWeapons, nbProtections, nbHealings);

    printf("Damage : %d\n", weaponDamage(weapons[3]));

    team1 = initTeam();

    return 0;
}
*/
