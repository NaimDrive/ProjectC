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

  readCommands(champions, weapons, protections, healings, nbChampions, nbWeapons, nbProtections, nbHealings);

  deallocateMemory(champions, weapons, protections, healings, nbChampions, nbWeapons, nbProtections, nbHealings);

  return 0;
}
