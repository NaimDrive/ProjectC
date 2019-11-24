#include "initGame.h"
#include "fight.h"
#include "tools.h"
#include "strat.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int readStrat(Strategy *strategy, char *fileName, Champion **champions, Weapon **weapons, Protection **protections, Healing **healings, int *nbChampions, int *nbWeapons, int *nbProtections, int *nbHealings, Team *team1, Team *team2) {
    FILE *fichier = fopen(fileName, "r");
    int SIZE = 256;
    char *buffer = malloc(sizeof(char)* SIZE);
    
    while(fgets(buffer, SIZE, fichier) != NULL) {
        // On lit toutes les lignes du fichier et on stock dans la structure
        compareChain(strategy, buffer, champions, weapons, protections, healings, nbChampions, nbWeapons, nbProtections, nbHealings, team1, team2);
    }
    
    free(buffer);
    fclose(fichier);

    return 0; // Return 0 si tout c'est correctement passé
    return 1; // Return 1 si erreur sur l'extention du fichier
    return 2; // Return 2 si strategie trop chère
    return 3; // Return 3 erreur de lecture du fichier
    return 4; // Return 4 si autre erreur
}

Strategy ** initStrat(int argc, char *argv[], int *nbStrat, Champion **champions, Weapon **weapons, Protection **protections, Healing **healings, int *nbChampions, int *nbWeapons, int *nbProtections, int *nbHealings, Team *team1, Team *team2) {
    Strategy **strategy;
    int nbStrategy = 0, read = 0;
    strategy = malloc(sizeof(Strategy *)*(argc-1));
    for (int i = 1; i < argc; i++) {
        strategy[nbStrategy] = malloc(sizeof(Strategy *));
        read = readStrat(strategy[nbStrategy], argv[i], champions, weapons, protections, healings, nbChampions, nbWeapons, nbProtections, nbHealings, team1, team2);
        if(read == 0) {
            nbStrategy++;
        } else if (read == 1) {
            printf("Erreur, le fichier %s n'est pas un fichier .strat !\n", argv[i]);
        } else if (read == 2) {
            printf("Erreur, la stratégie est trop chère !\n");
        } else if (read == 3) {
            printf("Erreur lors de la lecture du fichier %s. Stratégie ignorée !\n", argv[i]);
        } else if (read == 4) {
            printf("Erreur inconnue !\n");
        }
    }
    if(nbStrategy < argc-1){
        strategy = realloc(strategy, sizeof(Strategy *)*nbStrategy);
    }
    *nbStrat = nbStrategy;
    return strategy;
}


void compareChain(Strategy *strategy, char *buffer, Champion **champions, Weapon **weapons, Protection **protections, Healing **healings, int *nbChampions, int *nbWeapons, int *nbProtections, int *nbHealings, Team *team1, Team *team2) {
    char delimiters[]=" \t\n\r";
    char *mot;
    Strat *strat;
    mot = strtok(buffer, delimiters);
    //printf("Mot : %s\n", mot);

    if(mot == NULL) {
        return;
    } else if(!strcmp(mot, "strategy")) {
        mot = strtok(NULL, delimiters);
        strategy->nom = mot;
        printf("Strategy <%s>\n", strategy->nom);

    } else if(!strcmp(mot, "choose")) {
        char *mot1, *mot2;

        strat = strategy->initStrategy;
        strat = malloc(sizeof(Strat));
        strat->enumStrat = commande;

        mot1 = strtok(NULL, delimiters);
        mot2 = strtok(NULL, delimiters);

        strat->unionStrat.commande.nbParametres = 2;
        strat->unionStrat.commande.parametres = malloc(sizeof(UnionParametre)*strat->unionStrat.commande.nbParametres);
        
        // Il faudra appeler les fonctions pour équiper
        if(!strcmp(mot1, "weapon")) {
            strat->unionStrat.commande.parametres[0].weapon = searchWeapon(weapons, nbWeapons, mot2);
            strat->unionStrat.commande.enumCommande = weapon;
            strat->unionStrat.commande.commande.buyWeapon = buyWeapon;
        } else if(!strcmp(mot1, "protection")) {
            strat->unionStrat.commande.parametres[0].protection = searchProtection(protections, nbProtections, mot2);
            strat->unionStrat.commande.enumCommande = protection;
            strat->unionStrat.commande.commande.buyProtection = buyProtection;
        } else if(!strcmp(mot1, "care")) {
            strat->unionStrat.commande.parametres[0].healing = searchHealing(healings, nbHealings, mot2);
            strat->unionStrat.commande.enumCommande = care;
            strat->unionStrat.commande.commande.buyCare = buyHealing;
        }
        
        printf("choose %s\n", mot1);
        
    } else if(!strcmp(mot, "add")) {
        mot = strtok(NULL, delimiters);
        if(!strcmp(mot, "action")) {
            int quant;
            char *quantite;

            strat = strategy->initStrategy;
            strat = malloc(sizeof(Strat));
            strat->enumStrat = commande;

            quantite = strtok(NULL, delimiters);
            quant = atoi(quantite); // Servira lors de l'appel de la fonction

            strat->unionStrat.commande.nbParametres = 2;
            strat->unionStrat.commande.parametres = malloc(sizeof(UnionParametre)*strat->unionStrat.commande.nbParametres);
            strat->unionStrat.commande.parametres[1].entier = quant;
            strat->unionStrat.commande.enumCommande = CA;
            strat->unionStrat.commande.commande.buyCA = buyCA;
        }
    } else if(!strcmp(mot, "if") || !strcmp(mot, "endif")) {
        //printf("if\n");
    } else {
        //printf("Ligne inconnue, arrêt de la lecture.\n");
    }
}