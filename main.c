#include "initGame.h"
#include "fight.h"
#include "commands.h"
#include "endGame.h"
#include "main.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

int main() {
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

  afficherChampions(champions, nbChampions);
  afficherWeapons(weapons, nbWeapons);
  afficherProtections(protections, nbProtections);
  afficherSoins(healings, nbHealings);

  team1 = initTeam(0);
  team2 = initTeam(1);

  buyCA(team1, 20);
  buyCA(team2, 30);

  maximumCE = maxCE(team1, team2);
  buyChampion(champions[11], team1, maximumCE);
  buyChampion(champions[0], team2, maximumCE);

  buyWeapon(weapons[3], team1, maximumCE);
  buyWeapon(weapons[1], team2, maximumCE);

  buyHealing(healings[0], team2, maximumCE);

  buyProtection(protections[2], team2, maximumCE);

  useProtection(team2);
  moveForward(team1, team2, 3);

  useWeapon(team1, team2, 1);

  moveBackward(team2, 5, 50);
  useCare(team2, 4);
  
  endBattle(team1, team2);

  deallocateMemory(champions, weapons, protections, healings, nbChampions, nbWeapons, nbProtections, nbHealings);

  return 0;
}
