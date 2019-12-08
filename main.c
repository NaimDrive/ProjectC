#include <sys/ioctl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "initGame.h"
#include "strat.h"
#include "fight.h"
#include "commands.h"
#include "endGame.h"
#include "displayGame.h"

int main(int argc, char *argv[]) {
  
  Champion **champions;
  Weapon **weapons;
  Protection **protections;
  Healing **healings;
  Team *team1, *team2;
  Strategy **strategy;
  int *nbChampions, *nbWeapons, *nbProtections, *nbHealings, *nbStrategies;
  Winsize screenSize;
  Package *package;

  srand(time(NULL));

  package = malloc(sizeof(Package));
  champions = malloc(sizeof(Champion *) * 12);
  weapons = malloc(sizeof(Weapon *) * 5);
  protections = malloc(sizeof(Protection *) * 4);
  healings = malloc(sizeof(Healing *) * 3);
  strategy = NULL;

  team1 = malloc(sizeof(Team));
  team2 = malloc(sizeof(Team));

  nbChampions = malloc(sizeof(int));
  nbWeapons = malloc(sizeof(int));
  nbProtections = malloc(sizeof(int));
  nbHealings = malloc(sizeof(int));
  nbStrategies = NULL;

  *nbChampions = 0;
  *nbWeapons = 0;
  *nbProtections = 0;
  *nbHealings = 0;
  
  screenSize = initGame(champions, weapons, protections, healings, nbChampions, nbWeapons, nbProtections, nbHealings, team1, team2);

  if(argc > 1) {
    // Si il y a au moins 1 fichier .strat en paramètre
    nbStrategies = malloc(sizeof(int));
    *nbStrategies = 0;
    strategy = initStrat(argc, argv, nbStrategies, champions, weapons, protections, healings, nbChampions, nbWeapons, nbProtections, nbHealings, team1, team2, screenSize);      
  }

  package->champions = champions;
  package->weapons = weapons;
  package->protections = protections;
  package->healings = healings;
  package->strategies = strategy;
  package->nbChampions = nbChampions;
  package->nbWeapons = nbWeapons;
  package->nbProtections = nbProtections;
  package->nbHealings = nbHealings;
  package->nbStrategies = nbStrategies;

  readCommands(package, team1, team2, screenSize);

  return 0;
}
