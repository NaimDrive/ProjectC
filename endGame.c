#include "initGame.h"
#include "endGame.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void deallocateChampions(Champion **champions, int *nbChampions) {
    
}

void deallocateWeapons(Weapon **weapons, int *nbWeapons) {

}

void deallocateProtections(Protection **protections, int *nbProtections) {

}

void deallocateHealings(Healing **healings, int *nbHealings) {

}

void deallocateMemory(Champion **champions, Weapon **weapons, Protection **protections, Healing **healings, int *nbChampions, int *nbWeapons, int *nbProtections, int *nbHealings) {
    deallocateChampions(champions, nbChampions);
    deallocateWeapons(weapons, nbWeapons);
    deallocateProtections(protections, nbProtections);
    deallocateHealings(healings, nbHealings);
}