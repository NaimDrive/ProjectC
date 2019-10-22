#include "initGame.c"
#include <time.h>

#include "fight.h"

int weaponDamage(Weapon *weapon) {
    return (rand() % (weapon->degatsMax - weapon->degatsMin + 1)) + weapon->degatsMin;
}

int main(void) {
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
    
    printf("Damage : %d\n", weaponDamage(weapons[3]));

    return 0;
}