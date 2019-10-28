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

void showEquipment(Team *team) {
    Weapon *w = team->weapon;
    Protection *p = team->protection;
    Healing *h = team->healing;

    printf("Arme : '%s' faisant %d-%d de dégats, avec un portée de %d, chaque coup %d CA.\n", w->nom, w->degatsMin, w->degatsMax, w->portee, w->CA);
    printf("Protection : '%s' a une probabilité de blocage de %d%c, son activation coûte %d CA.\n", p->nom, p->probabilite, '%', p->CA);
    printf("Soin : '%s' permet de récupérer %d-%d PV. Stock : %d\n", h->nom, h->effetMin, h->effetMax, h->volume);
}

void weaponChoice(Team *team, Weapon **weapons, int *nbWeapons, char *command) {
    long num = -1;
    char *endptr;
    printf("Joueur : %s | Crédits d'equipement : %d\n", team->champion->variete, team->CE);
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
    printf("Joueur : %s | Crédits d'equipement : %d\n", team->champion->variete, team->CE);
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
    printf("Joueur : %s | Crédits d'equipement : %d\n", team->champion->variete, team->CE);
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

void actionCreditChoice(Team *team, char *command) {
    long num = 0;
    char *endptr;
    printf("Joueur : %s | Crédits d'equipement : %d\n", team->champion->variete, team->CE);
    printf("Et enfin ! Il nous faut des crédits d'action pour enclencher !\n");

    while((num > team->CE || num <= 0) || !(*command != '\0' && *endptr == '\0')) {
        printf("Je souhaite acheter...");
        fgets(command, 256, stdin);
        if((strlen(command) > 0) && (command[strlen(command)-1] == '\n')) command[strlen(command)-1] = '\0';

        num = strtoul(command, &endptr, 10);

        if((num > team->CE || num <= 0) || !(*command != '\0' && *endptr == '\0')) {
            system("clear");
            printf("Pour rappel, vous avez %d crédits d'équipement.\n", team->CE);
        }   
    }

    buyCA(team, num);
    printf("Désormais %d crédits d'action disponibles !\n", team->CA);

    enterToContinue();
    system("clear");
}

void equipTeam(Team *team, Weapon **weapons, Protection **protections, Healing **healings, int *nbWeapons, int*nbProtections, int *nbHealings) {
    char *command = malloc(256*sizeof(char));

    weaponChoice(team, weapons, nbWeapons, command);
    protectionChoice(team, protections, nbProtections, command);
    healingChoice(team, healings, nbHealings, command);
    actionCreditChoice(team, command);

    free(command);
}

void endRound(Team *team1, Team *team2) {
  team1->champion->PV = team1->champion->PVMax;
  team2->champion->PV = team2->champion->PVMax;

  free(team1->weapon);
  team1->weapon = NULL;
  free(team1->protection);
  team1->protection = NULL;
  free(team1->healing);
  team1->healing = NULL;

  free(team2->weapon);
  team2->weapon = NULL;
  free(team2->protection);
  team2->protection = NULL;
  free(team2->healing);
  team2->healing = NULL;
}

void fightingMode(Team *team1, Team *team2, int screenSize) {
    char *command = malloc(256*sizeof(char));
    int end = 0;

    while(team1->maxCE > 0 && !end) {
        printf("%s %d> ", team1->champion->variete, team1->CA);
        fgets(command, 256, stdin);
        if((strlen(command) > 0) && (command[strlen(command)-1] == '\n')) command[strlen(command)-1] = '\0';

        // ~~~ Cases ~~~ //
        if(strcmp(command, "show") == 0) showEquipment(team1);
        else if(strncmp(command, "move forward ", 13) == 0) moveForward(team1, team2, getID(command, 13));
        else if(strcmp(command, "move forward") == 0) moveForward(team1, team2, 1);

        else if(strncmp(command, "move backward ", 14) == 0) moveBackward(team1, getID(command, 14), screenSize);
        else if(strcmp(command, "move backward") == 0) moveBackward(team1, 1, screenSize);

        else if(strncmp(command, "use weapon ", 11) == 0) useWeapon(team1, team2, getID(command, 11));
	      else if(strcmp(command, "use weapon") == 0) useWeapon(team1, team2, 1);

        else if(strcmp(command, "use protection") == 0) useProtection(team1);

        else if(strncmp(command, "use care ", 9) == 0) useCare(team1, getID(command, 9));
	      else if(strcmp(command, "use care") == 0) useCare(team1, 1);

        else if(strcmp(command, "end") == 0) {
            printf("Tour terminé\n");
            end = 1;
        }
    }
    free(command);
}
