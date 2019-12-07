#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "initGame.h"
#include "strat.h"
#include "endGame.h"

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

void deallocateStrat(Strat *strat) {
    if(strat == NULL) {
        return;
    }
    
    if(strat->enumStrat == operateur) {
        free(strat->unionStrat.operateur.chaine);
    }

    if(strat->enumStrat == commande) {
        free(strat->unionStrat.commande.parametres);
    }
    
    deallocateStrat(strat->suivant);
    deallocateStrat(strat->suivantSinon);

    free(strat);
}

void deallocateStrategy(Strategy *strategy) {
    free(strategy->nom);
    deallocateStrat(strategy->initStrategy);
    deallocateStrat(strategy->strat);
    free(strategy);
}

void deallocateStrategies(Strategy **strategy, int *nbStrategies) {
    if(strategy != NULL && nbStrategies != NULL) {
        for (int i = 0; i < *nbStrategies; i++) {
            deallocateStrategy(strategy[i]);
        }

        free(strategy);
        free(nbStrategies);
    }
}

void deallocateMemory(Champion **champions, Weapon **weapons, Protection **protections, Healing **healings, Strategy **strategy, int *nbChampions, int *nbWeapons, int *nbProtections, int *nbHealings, int *nbStrategies, Team *team1, Team *team2) {
    deallocateStrategies(strategy, nbStrategies);
    deallocateChampions(champions, nbChampions);
    deallocateWeapons(weapons, nbWeapons);
    deallocateProtections(protections, nbProtections);
    deallocateHealings(healings, nbHealings);
    deallocateTeams(team1, team2);
}
