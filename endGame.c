#include "initGame.h"
#include "endGame.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void deallocateChampions(Champion **champions, int *nbChampions) {
    for (int i = 0; i < *nbChampions; i++) {
        free(champions[i]);
    }
    free(champions);
    free(nbChampions);
}

void deallocateWeapons(Weapon **weapons, int *nbWeapons) {
    for (int i = 0; i < *nbWeapons; i++) {
        free(weapons[i]);
    }
    free(weapons);
    free(nbWeapons);
}

void deallocateProtections(Protection **protections, int *nbProtections) {
    for (int i = 0; i < *nbProtections; i++) {
        free(protections[i]);
    }
    free(protections);
    free(nbProtections);
}

void deallocateHealings(Healing **healings, int *nbHealings) {
    for (int i = 0; i < *nbHealings; i++) {
        free(healings[i]);
    }
    free(healings);
    free(nbHealings);
}

void deallocateTeams(Team *team1, Team *team2) {
  free(team1->champion);
  team1->champion = NULL;
  free(team1->weapon);
  team1->weapon = NULL;
  free(team1->protection);
  team1->protection = NULL;
  free(team1->healing);
  team1->healing = NULL;
  free(team1);

  free(team2->champion);
  team2->champion = NULL;
  free(team2->weapon);
  team2->weapon = NULL;
  free(team2->protection);
  team2->protection = NULL;
  free(team2->healing);
  team2->healing = NULL;
  free(team2);
}

void deallocateMemory(Champion **champions, Weapon **weapons, Protection **protections, Healing **healings, int *nbChampions, int *nbWeapons, int *nbProtections, int *nbHealings, Team *team1, Team *team2) {
    deallocateChampions(champions, nbChampions);
    deallocateWeapons(weapons, nbWeapons);
    deallocateProtections(protections, nbProtections);
    deallocateHealings(healings, nbHealings);
    deallocateTeams(team1, team2);
}
