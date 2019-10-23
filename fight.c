#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "initGame.h"
#include "fight.h"

Team * initTeam() {
  Team *team;
  team = malloc(sizeof(Team));
  team->CE = 1000;
  team->CA = 0;
  team->CE_USED = 0;
  team->champion = NULL;
  team->weapon = NULL;
  team->protection = NULL;
  team->healing = NULL;
  team->protectionActivated = 0;

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

void buyCA(Team *team, int number) {
  if(team->CE >= number) {
    team->CE -= number;
    team->CA += number;
  }
}

void buyChampion(Champion *champion, Team *team, int maxCE) {
  if(team->CE_USED == maxCE)
    printf("%s\n", "Vous avez atteint la limite de CE à dépenser pendant le tour.");
  else {
    if(team->CE_USED + champion->CE > maxCE)
      printf("%s\n", "Vous ne pouvez pas acheter le champion car vous allez dépasser la limite de CE.");
    else {
      if(team->champion != NULL)
        free(team->champion);
      team->champion = createChampion(champion->variete, champion->num);
      team->CE_USED += champion->CE;
      team->CE -= champion->CE;
    }
  }
}

void buyWeapon(Weapon *weapon, Team *team, int maxCE) {
  if(team->CE_USED == maxCE)
    printf("%s\n", "Vous avez atteint la limite de CE à dépenser pendant le tour.");
  else {
    if(team->CE_USED + weapon->CE > maxCE)
      printf("%s\n", "Vous ne pouvez pas acheter le champion car vous allez dépasser la limite de CE.");
    else {
      if(team->weapon != NULL)
        free(team->weapon);
      team->weapon = createWeapon(weapon->nom, weapon->num);
      team->CE_USED += weapon->CE;
      team->CE -= weapon->CE;
    }
  }
}

void buyProtection(Protection *protection, Team *team, int maxCE) {
  if(team->CE_USED == maxCE)
    printf("%s\n", "Vous avez atteint la limite de CE à dépenser pendant le tour.");
  else {
    if(team->CE_USED + protection->CE > maxCE)
      printf("%s\n", "Vous ne pouvez pas acheter le champion car vous allez dépasser la limite de CE.");
    else {
      if(team->protection != NULL)
        free(team->protection);
      team->protection = createProtection(protection->nom, protection->num);
      team->CE_USED += protection->CE;
      team->CE -= protection->CE;
    }
  }
}

void buyHealing(Healing *healing, Team *team, int maxCE) {
  if(team->CE_USED == maxCE)
    printf("%s\n", "Vous avez atteint la limite de CE à dépenser pendant le tour.");
  else {
    if(team->CE_USED + healing->CE > maxCE)
      printf("%s\n", "Vous ne pouvez pas acheter le champion car vous allez dépasser la limite de CE.");
    else {
      if(team->healing != NULL)
        free(team->healing);
      team->healing = createHealing(healing->nom, healing->num);
      team->CE_USED += healing->CE;
      team->CE -= healing->CE;
    }
  }
}

int weaponDamage(Weapon *weapon) {
    return (rand() % (weapon->degatsMax - weapon->degatsMin + 1)) + weapon->degatsMin;
}

int effectiveProtection(int protection) {
    int res = (rand() % 100) + 1;
    if(res <= protection)
      return 1;
    return 0;
}

void useWeapon(Team *team1, Team *team2, int n) {
  int damage = 0, i;
  if(team1->champion == NULL || team2->champion == NULL || team1->weapon == NULL || n > 0) {

    if(team1->weapon->CA * n > team1->CA) {
      printf("Pas assez de crédit d'action pour utiliser %d fois l'arme.\n", n);
    } else {
      for(i = 0 ; i < n && team2->champion->PVMax > 0 ; i++) {
        team1->CA -= team1->weapon->CA;
        printf("L'attaquant perd %d crédits d'attaques.\n", team1->weapon->CA);

        if(team2->protectionActivated && team2->protection != NULL)
          if(effectiveProtection(team2->protection->probabilite) == 1) {
            printf("La protection a contré l'attaque !\n");
            continue;
          }
        printf("WHAT %d\n", damage);
        damage = weaponDamage(team1->weapon) * ((100 + team1->champion->force) / 100);
        printf("WHAT %d\n", damage);
        damage *= ((100 - team2->champion->resistance) / 100);
        printf("WHAT %d\n", damage);
        
        printf("Le défenseur perd %d points de vie.\n", damage);
        if(damage > team2->champion->PVMax)
          team2->champion->PVMax = 0;
        else
          team2->champion->PVMax -= damage;
      }
    }
  }
}

/*
int main(void) {
    Champion **champions;
    Weapon **weapons;
    Protection **protections;
    Healing **healings;
    Team *team1, *team2;
    int *nbChampions, *nbWeapons, *nbProtections, *nbHealings, maximumCE;

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

    team1 = initTeam();
    team2 = initTeam();

    buyCA(team1, 20);
    buyCA(team2, 20);

    maximumCE = maxCE(team1, team2);
    buyChampion(champions[0], team1, maximumCE);
    buyChampion(champions[6], team2, maximumCE);

    buyWeapon(weapons[0], team1, maximumCE);
    buyWeapon(weapons[1], team2, maximumCE);

    buyProtection(protections[2], team2, maximumCE);

    useWeapon(team1, team2, 2);
    
    return 0;
}
*/