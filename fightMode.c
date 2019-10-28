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
    long num = -1;
    char *endptr;
    printf("Commençons par choisir de quoi tuer l'adversaire.\n");

    while((num >= *nbWeapons || num < 0) || !(*command != '\0' && *endptr == '\0')) {
        showWeapons(weapons, nbWeapons);
        printf("Je choisis l'arme numéro... ");
        fgets(command, 256, stdin);
        if((strlen(command) > 0) && (command[strlen(command)-1] == '\n')) command[strlen(command)-1] = '\0';

        num = strtoul(command, &endptr, 10);

        if((num >= *nbWeapons || num < 0) || !(*command != '\0' && *endptr == '\0')) {
            system("clear");
            printf("Attention ! Vous devez choisir un chiffre compris entre 0 et %d\n", *nbWeapons-1);
        }
    }

    buyWeapon(weapons[num], team);
    printf("Arme '%s' équipée !\n", team->weapon->nom);

    enterToContinue();
    system("clear");
}

void protectionChoice(Team *team, Protection **protections, int *nbProtections, char *command) {
    long num = -2;
    char *endptr;
    printf("Ensuite il faut de quoi se protéger.\n");

    while((num >= *nbProtections || num < -1) || !(*command != '\0' && *endptr == '\0')) {
        showProtections(protections, nbProtections);
        printf("(Entrez '-1' si vous ne voulez pas de protection)\n");
        printf("Je choisis la protection numéro... ");
        fgets(command, 256, stdin);
        if((strlen(command) > 0) && (command[strlen(command)-1] == '\n')) command[strlen(command)-1] = '\0';
        num = strtoul(command, &endptr, 10);

        if((num >= *nbProtections || num < -1) || !(*command != '\0' && *endptr == '\0')) {
            system("clear");
            printf("Attention ! Vous devez choisir un chiffre compris entre 0 et %d ou '-1' si vous ne voulez pas de protection.\n", *nbProtections-1);
        }
    }

    if(num == -1) {
        printf("Vous avez décidez de ne prendre aucune protections !\n");
        enterToContinue();
        system("clear");
        return;
    }

    buyProtection(protections[num], team);
    printf("Protection '%s' équipée !\n", team->protection->nom);

    enterToContinue();
    system("clear");
}

void healingChoice(Team *team, Healing **healings, int *nbHealings, char *command) {
    long num = -2;
    char *endptr;
    printf("Les soins peuvent sauver des vies... Croyez-moi !\n");

    while((num >= *nbHealings || num < -1) || !(*command != '\0' && *endptr == '\0')) {
        showCares(healings, nbHealings);
        printf("(Entrez '-1' si vous ne voulez pas de soin)\n");
        printf("Je choisis le soin numéro... ");
        fgets(command, 256, stdin);
        if((strlen(command) > 0) && (command[strlen(command)-1] == '\n')) command[strlen(command)-1] = '\0';
        num = strtoul(command, &endptr, 10);

        if((num >= *nbHealings || num < -1) || !(*command != '\0' && *endptr == '\0')) {
            system("clear");
            printf("Attention ! Vous devez choisir un chiffre compris entre 0 et %d ou '-1' si vous ne voulez pas de soin.\n", *nbHealings-1);
        }
    }

    if(num == -1) {
        printf("Vous avez décidez de ne prendre aucun soin !\n");
        enterToContinue();
        system("clear");
        return;
    }

    buyHealing(healings[num], team);
    printf("Soin '%s' équipée !\n", team->healing->nom);

    enterToContinue();
    system("clear");
}

void equipTeam(Team *team, Weapon **weapons, Protection **protections, Healing **healings, int *nbWeapons, int*nbProtections, int *nbHealings) {
    char *command = malloc(256*sizeof(char));

    weaponChoice(team, weapons, nbWeapons, command);
    protectionChoice(team, protections, nbProtections, command);
    healingChoice(team, healings, nbHealings, command);

    free(command);
}

void fightingMode(Team *team1) {
    char *command = malloc(256*sizeof(char));
    int end = 0;

    while(team1->maxCE > 0 && !end) {
        printf("%s %d> ", team1->champion->variete, team1->CA);
        fgets(command, 256, stdin);
        if((strlen(command) > 0) && (command[strlen(command)-1] == '\n')) command[strlen(command)-1] = '\0';

        // ~~~ Cases ~~~ //
        if(strcmp(command, "show") == 0) printf("je show des trucss lo\n");
        else if(strncmp(command, "move forward ", 13) == 0) printf("move forward %d truc\n", getID(command, 13));
        else if(strcmp(command, "move forward") == 0) printf("move forward de 1 truc\n");

        else if(strncmp(command, "move backward ", 14) == 0) printf("move backward %d truc\n", getID(command, 14));
        else if(strcmp(command, "move backward") == 0) printf("move backward de 1 truc\n");

        else if(strncmp(command, "use weapon ", 11) == 0) printf("use %d weapon lo\n", getID(command, 11));
	else if(strcmp(command, "use weapon") == 0) printf("use 1 fois weapon lo\n");

        else if(strcmp(command, "use protection") == 0) printf("use la protection lo\n");

        else if(strncmp(command, "use care ", 9) == 0) printf("use %d heal lo\n", getID(command, 9));
	else if(strcmp(command, "use care") == 0) printf("use 1 fois le heal lo\n");

        else if(strcmp(command, "end") == 0) {
            printf("Tour terminé\n");
            end = 1;
        }
    }
    free(command);
}
