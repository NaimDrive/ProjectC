#include "initGame.h"
#include "commands.h"
#include "fight.h"
#include "colors.h"
#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void enterToContinue() {
    printf("(Appuyez sur Entrer pour continuer)");
    while(getchar() != '\n');
}

void showEquipment(Team *team) {
    Champion *c = team->champion;
    Weapon *w = team->weapon;
    Protection *p = team->protection;
    Healing *h = team->healing;

    if(team->id == 0) green();
    else yellow();
    printf("Votre %s possède %d/%d PV, avec une résistance de %d pour une force de %d.\n", c->variete, c->PV, c->PVMax, c->resistance, c->force);

    white();
    if(w != NULL)
        printf("   Arme    |--> '%s' faisant %d-%d de dégats, avec un portée de %d, chaque coup %d CA.\n", w->nom, w->degatsMin, w->degatsMax, w->portee, w->CA);
    
    if(p != NULL)
        printf("Protection |--> '%s' a une probabilité de blocage de %d%c, son activation coûte %d CA.\n", p->nom, p->probabilite, '%', p->CA);
    else
        printf("Aucune protection équipé.\n");
    
    if(h != NULL)
        printf("   Soin    |--> '%s' permet de récupérer %d-%d PV. Stock : %d\n", h->nom, h->effetMin, h->effetMax, h->volume);
    else
        printf("Aucun soin équipé.\n");
    
    resetColor();
}

void weaponChoice(Team *team, Weapon **weapons, int *nbWeapons, char *command) {
    long num = -1;
    char *endptr;
    printf("Joueur : %s | Crédits d'equipement : %d\n", team->champion->variete, team->maxCE);
    printf("Commençons par choisir de quoi tuer l'adversaire.\n");

    while((num >= *nbWeapons || num < 0) || !(*command != '\0' && *endptr == '\0')) {
        showWeapons(weapons, nbWeapons, team->maxCE);
        printf("Je choisis l'arme numéro... ");
        fgets(command, 256, stdin);
        if((strlen(command) > 0) && (command[strlen(command)-1] == '\n')) command[strlen(command)-1] = '\0';

        num = strtoul(command, &endptr, 10);

        white();
        if((num >= *nbWeapons || num < 0) || !(*command != '\0' && *endptr == '\0')) {
            system("clear");
            printf("Attention ! Vous devez choisir un chiffre compris entre 0 et %d\n", *nbWeapons-1);
        } else if(weapons[num]->CE > team->maxCE) {
            system("clear");
            printf("Vous n'avez pas assez de CE pour acheter '%s'.\n", weapons[num]->nom);
            num = -1;
        }
        resetColor();
    }

    buyWeapon(weapons[num], team);
    printf("Arme '%s' équipée !\n", team->weapon->nom);

    enterToContinue();
    system("clear");
}

void protectionChoice(Team *team, Protection **protections, int *nbProtections, char *command) {
    long num = -2;
    int ajout;
    char *endptr;
    printf("Joueur : %s | Crédits d'equipement : %d\n", team->champion->variete, team->maxCE);
    printf("Ensuite il faut de quoi se protéger.\n");

    while((num >= *nbProtections || num < -1) || !(*command != '\0' && *endptr == '\0')) {
        showProtections(protections, nbProtections, team->maxCE);
        printf("(Entrez '-1' si vous ne voulez pas de protection)\n");
        printf("Je choisis la protection numéro... ");
        fgets(command, 256, stdin);
        if((strlen(command) > 0) && (command[strlen(command)-1] == '\n')) command[strlen(command)-1] = '\0';
        num = strtoul(command, &endptr, 10);

        white();
        if((num >= *nbProtections || num < -1) || !(*command != '\0' && *endptr == '\0')) {
            system("clear");
            printf("Attention ! Vous devez choisir un chiffre compris entre 0 et %d ou '-1' si vous ne voulez pas de protection.\n", *nbProtections-1);
        } else if(num != -1 && protections[num]->CE > team->maxCE) {
            system("clear");
            printf("Vous n'avez pas assez de CE pour acheter '%s'.\n", protections[num]->nom);
            num = -2;
        }
        resetColor();
    }

    if(num == -1) {
        white();
        printf("Vous avez décidez de ne prendre aucune protections !\n");
        resetColor();
        enterToContinue();
        system("clear");
        return;
    }

    ajout = buyProtection(protections[num], team);

    if(ajout == 0) {
        enterToContinue();
        system("clear");
        return;
    }

    printf("Protection '%s' équipée !\n", team->protection->nom);

    enterToContinue();
    system("clear");
}

void healingChoice(Team *team, Healing **healings, int *nbHealings, char *command) {
    long num = -2;
    int ajout;
    char *endptr;
    printf("Joueur : %s | Crédits d'equipement : %d\n", team->champion->variete, team->maxCE);
    printf("Les soins peuvent sauver des vies... Croyez-moi !\n");

    while((num >= *nbHealings || num < -1) || !(*command != '\0' && *endptr == '\0')) {
        showCares(healings, nbHealings, team->maxCE);
        printf("(Entrez '-1' si vous ne voulez pas de soin)\n");
        printf("Je choisis le soin numéro... ");
        fgets(command, 256, stdin);
        if((strlen(command) > 0) && (command[strlen(command)-1] == '\n')) command[strlen(command)-1] = '\0';
        num = strtoul(command, &endptr, 10);

        white();
        if((num >= *nbHealings || num < -1) || !(*command != '\0' && *endptr == '\0')) {
            system("clear");
            printf("Attention ! Vous devez choisir un chiffre compris entre 0 et %d ou '-1' si vous ne voulez pas de soin.\n", *nbHealings-1);
        } else if(num != -1 && healings[num]->CE > team->maxCE) {
            system("clear");
            printf("Vous n'avez pas assez de CE pour acheter '%s'.\n", healings[num]->nom);
            num = -2;
        }
        resetColor();
    }

    if(num == -1) {
        white();
        printf("Vous avez décidez de ne prendre aucun soin !\n");
        resetColor();
        enterToContinue();
        system("clear");
        return;
    }

    ajout = buyHealing(healings[num], team);

    if(ajout == 0) {
        enterToContinue();
        system("clear");
        return;
    }

    printf("Soin '%s' équipée !\n", team->healing->nom);

    enterToContinue();
    system("clear");
}

void actionCreditChoice(Team *team, char *command) {
    long num = -1;
    char *endptr;
    printf("Joueur : %s | Crédits d'equipement : %d\n", team->champion->variete, team->maxCE);
    printf("Et enfin ! Il nous faut des crédits d'action pour enclencher !\n");

    while((num > team->maxCE || num < 0) || !(*command != '\0' && *endptr == '\0')) {
        printf("Je souhaite acheter...");
        fgets(command, 256, stdin);
        if((strlen(command) > 0) && (command[strlen(command)-1] == '\n')) command[strlen(command)-1] = '\0';

        num = strtoul(command, &endptr, 10);

        if((num > team->CE || num < 0) || !(*command != '\0' && *endptr == '\0')) {
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

void roundWinner(Team *team1, Team *team2, int maximumCE) {
    int CE_used_team1, CE_used_team2, max;

    CE_used_team1 = maximumCE - team1->maxCE;
    CE_used_team2 = maximumCE - team2->maxCE;

    if(team1->champion->PV == 0) {
        max = CE_used_team1 - CE_used_team2;
        if(max < 1)
            max = 1;
        team2->CE += 5 * max;
        printf("L'équipe %s gagne %d CE.\n", team2->champion->variete, 5 * max);
    } else {
        max = CE_used_team2 - CE_used_team1;
        if(max < 1)
            max = 1;
        team1->CE += 5 * max;
        printf("L'équipe %s gagne %d CE.\n", team1->champion->variete, 5 * max);
    }
}

void showEndGame(Team *team1, Team *team2) {
    system("clear");
    printf(" -- Partie terminé ! -- \n");
    if(team1->CE == 0 && team2->CE == 0) {
        printf("C'est incroyable, le résultat est un ex-aequo !\n");
    } else {
        if(team1->CE == 0) {
            printf("L'équipe %s gagne la partie !\n", team2->champion->variete);
        } else {
            printf("L'équipe %s gagne la partie !\n", team1->champion->variete);
        }
    }
}

void endRound(Team *team1, Team *team2, int maximumCE, int end, int stillHaveCA) {
    if(end == 0) {
        if(stillHaveCA == 1) {
            roundWinner(team1, team2, maximumCE);
        } else {
            printf("Plus personne n'a de CA pour attaquer, le duel est un ex-aequo.\n");
        }
        maxCE(team1, team2);
    }

    team1->protectionActivated = 0;
    team2->protectionActivated = 0;

    free(team1->champion);
    team1->champion = NULL;
    free(team1->weapon);
    team1->weapon = NULL;
    free(team1->protection);
    team1->protection = NULL;
    free(team1->healing);
    team1->healing = NULL;

    free(team2->champion);
    team2->champion = NULL;
    free(team2->weapon);
    team2->weapon = NULL;
    free(team2->protection);
    team2->protection = NULL;
    free(team2->healing);
    team2->healing = NULL;
}

void takeOffProtection(Team *team) {
    if(team->protectionActivated == 1) {
        team->protectionActivated = 0;
        printf("La protection %s est déactivée pour %s.\n", team->protection->nom, team->champion->variete);
    }
}

void resetGame(Team *team1, Team *team2, Winsize screenSize) {
    team1->CE = 1000;
    team1->CA = 0;
    team1->maxCE = 50;
    team1->maxCA = 50;
    team1->position = 1;

    team2->CE = 1000;
    team2->CA = 0;
    team2->maxCE = 50;
    team1->maxCA = 50;
    team2->position = screenSize.ws_col-2;
}

void helpFight() {
    white();
    printf("Commandes disponibles : \n\n");
    printf(" show - Affiche les informations du légume/fruit actuellement incarné.\n");
    printf(" move forward n - Avance de n pas. (Avance de 1 pas si n est null)\n");
    printf(" move forward n - Recul de n pas. (Recul de 1 pas si n est null)\n");
    printf(" use weapon n - Attaque n fois l'adversaire. (Attaque une fois si n est null)\n");
    printf(" use protection - Active la protection actuellement équipé.\n");
    printf(" use care n - Utilise n soins. (N'utilise qu'un seul soin si n est null)\n");
    printf(" end - Met fin au tour en cours.\n");
    printf(" clear - Nettoie le terminal.\n");
    printf(" help - Affiche les commandes disponibles.\n\n");
    resetColor();
}

void fightingMode(Team *team1, Team *team2, int screenSize) {
    char *command = malloc(256*sizeof(char));
    int end = 0, erreur = 0;

    while(team1->CA > 0 && team1->maxCA > 0 && team2->champion->PV > 0 && !end) {
        
        if(team1->id == 0) green();
        else yellow();
        printf("%s ", team1->champion->variete);
        white();
        printf("%d> ", team1->CA);
        resetColor();
        
        // printf("%s %d> ", team1->champion->variete, team1->maxCA);
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

        else if(strcmp(command, "end") == 0) end = 1;
        else if(strcmp(command,"clear") == 0) system("clear");

        else if(strcmp(command, "help") == 0) helpFight();

        else {
            erreur++;
            white();
            printf("Commande '%s' invalide.\n", command);
            if(erreur == 3) {
                helpFight();
                erreur = 0;
            }
            resetColor();
        }

    }
    if(team1->CA == 0)
        printf("Tour terminé. Vous n'avez plus de CA.\n");
    else if(team1->maxCA == 0)
        printf("Tour terminé. Vous avez atteint la limite de CA pour ce tour.\n");
    else if(team2->champion->PV == 0)
        printf("Duel terminé.\n");
    else
        printf("Tour terminé.\n");

    free(command);
}
