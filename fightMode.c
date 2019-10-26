#include "initGame.h"
#include "commands.h"
#include "fight.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void enterToContinue() {
    printf("(Appuyez sur Entrer pour continuer)");
    while(getchar() != '\n');
}

void weaponChoice(Team *team, Weapon **weapons, int *nbWeapons, char *command) {
    int num;

    showWeapons(weapons, nbWeapons);
    printf("Je choisis l'arme numéro... ");
    fgets(command, 256, stdin);
    if((strlen(command) > 0) && (command[strlen(command)-1] == '\n')) command[strlen(command)-1] = '\0';
    num = getID(command, 0);

    if(num >= *nbWeapons || num < 0) {
        printf("Attention ! Vous devez choisir un chiffre compris entre 0 et %d\n", *nbWeapons-1);
        weaponChoice(team, weapons, nbWeapons, command);
    }

    buyWeapon(weapons[num], team, team->CE);
    printf("Arme '%s' équipée !\n", team->weapon->nom);
}

void protectionChoice(Team *team, Protection **protections, int *nbProtections, char *command) {
    int num;
    
    showProtections(protections, nbProtections);
    printf("(Entrez '-1' si vous ne voulez pas de protection)\n");
    printf("Je choisis la protection numéro... ");
    fgets(command, 256, stdin);
    if((strlen(command) > 0) && (command[strlen(command)-1] == '\n')) command[strlen(command)-1] = '\0';
    num = getID(command, 0);
    
    if(num >= *nbProtections || num < -1) {
        printf("Attention ! Vous devez choisir un chiffre compris entre 0 et %d ou '-1' si vous ne voulez pas de protection.\n", *nbProtections-1);
        protectionChoice(team, protections, nbProtections, command);
    } else if(num == -1) {
        printf("Vous avez décidez de ne prendre aucune protections !\n");
        return;
    }

    buyProtection(protections[num], team, team->CE);
    printf("Protection '%s' équipée !\n", team->protection->nom);
}

void healingChoice(Team *team, Healing **healings, int *nbHealings, char *command) {
    int num;
    
    showCares(healings, nbHealings);
    printf("(Entrez '-1' si vous ne voulez pas de soin)\n");
    printf("Je choisis le soin numéro... ");
    fgets(command, 256, stdin);
    if((strlen(command) > 0) && (command[strlen(command)-1] == '\n')) command[strlen(command)-1] = '\0';
    num = getID(command, 0);
    
    if(num >= *nbHealings || num < -1) {
        printf("Attention ! Vous devez choisir un chiffre compris entre 0 et %d ou '-1' si vous ne voulez pas de soin.\n", *nbHealings-1);
        healingChoice(team, healings, nbHealings, command);
    } else if(num == -1) {
        printf("Vous avez décidez de ne prendre aucun soin !\n");
        return;
    }

    buyHealing(healings[num], team, team->CE);
    printf("Soin '%s' équipée !\n", team->healing->nom);
}

void equipTeam(Team *team, Weapon **weapons, Protection **protections, Healing **healings, int *nbWeapons, int*nbProtections, int *nbHealings) {
    char *command = malloc(256*sizeof(char));
    printf("Commençons par choisir de quoi tuer l'autre en face.\n");
    /* Segmentation fault lorsque je me trompe dans l'id puis choisis une bonne arme */
    weaponChoice(team, weapons, nbWeapons, command);
    enterToContinue();
    system("clear");
    printf("Ensuite il faut de quoi se protéger.\n");
    protectionChoice(team, protections, nbProtections, command);
    enterToContinue();
    system("clear");
    printf("Les soins peuvent sauver des vies... Croyez-moi !\n");
    healingChoice(team, healings, nbHealings, command);
    enterToContinue();
    system("clear");

    free(command);
}

void fightingMode(Team *team) {
    char *command = malloc(256*sizeof(char));
    
    printf("%s %d> ", team->champion->variete, team->CA);
    fgets(command, 256, stdin);
    // printf("Entered command : %s", command);
    if((strlen(command) > 0) && (command[strlen(command)-1] == '\n')) command[strlen(command)-1] = '\0';

    while(team->CE != 0) {
        if(strcmp(command, "show") == 0) printf("je show des trucss lo\n");
        else if(strncmp(command, "move forward ", 13) == 0) printf("move forward %d truc\n", getID(command, 13));
        else if(strncmp(command, "move backward ", 14) == 0) printf("move backward %d truc\n", getID(command, 14));
        else if(strncmp(command, "use weapon ", 11) == 0) printf("use %d weapon lo\n", getID(command, 11));
        else if(strcmp(command, "use protection") == 0) printf("use la protection lo\n");
        else if(strncmp(command, "use care ", 9) == 0) printf("use %d heal lo\n", getID(command, 9));
        else if(strcmp(command, "end") == 0) {
            printf("Tour terminé\n"); 
            return;
        }
    }

    free(command);
}
