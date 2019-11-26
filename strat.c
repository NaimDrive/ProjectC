#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>

#include "initGame.h"
#include "fight.h"
#include "tools.h"
#include "strat.h"

int readStrat(Strategy **strategy, char *fileName, Champion **champions, Weapon **weapons, Protection **protections, Healing **healings, int *nbChampions, int *nbWeapons, int *nbProtections, int *nbHealings, Team *team1, Team *team2, Winsize screenSize) {
    char *adress = strrchr(fileName, '.');
    if(adress == NULL || strcmp(adress+1, "strat") != 0) {
        return 1; // Return 1 si erreur sur l'extention du fichier
    }

    FILE *fichier = fopen(fileName, "r");
    if(fichier == NULL) {
        return 3; // Return 3 erreur d'ouverture du fichier
    }
    *strategy = calloc(1, sizeof(Strategy));
    int SIZE = 256;
    char *buffer = malloc(sizeof(char)* SIZE);

    while(fgets(buffer, SIZE, fichier) != NULL) {
        // On lit toutes les lignes du fichier et on stock dans la structure
        compareChain(strategy, buffer, champions, weapons, protections, healings, nbChampions, nbWeapons, nbProtections, nbHealings, team1, team2, screenSize);
    }
    
    free(buffer);
    fclose(fichier);

    if((*strategy)->coutCE + champions[0]->CE > 50) {
        printf("La stratégie est trop chère !\n");
        free(strategy);
        return 2; // Return 2 si strategie trop chère
    }
    return 0; // Return 0 si tout c'est correctement passé
}

Strategy ** initStrat(int argc, char *argv[], int *nbStrat, Champion **champions, Weapon **weapons, Protection **protections, Healing **healings, int *nbChampions, int *nbWeapons, int *nbProtections, int *nbHealings, Team *team1, Team *team2, Winsize screenSize) {
    Strategy **strategy;
    int nbStrategy = 0, read = 0;
    strategy = malloc(sizeof(Strategy *)*(argc-1));
    for (int i = 1; i < argc; i++) {
        read = readStrat(&strategy[nbStrategy], argv[i], champions, weapons, protections, healings, nbChampions, nbWeapons, nbProtections, nbHealings, team1, team2, screenSize);
        if(read == 0) {
            strategy[nbStrategy]->num = nbStrategy;
            nbStrategy++;
        } else if (read == 1) {
            printf("Erreur, le fichier %s n'est pas un fichier .strat !\n", argv[i]);
        } else if (read == 2) {
            printf("Erreur, la stratégie est trop chère !\n");
        } else if (read == 3) {
            printf("Erreur lors de l'ouverture du fichier %s. Stratégie ignorée !\n", argv[i]);
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


void compareChain(Strategy **s, char *buffer, Champion **champions, Weapon **weapons, Protection **protections, Healing **healings, int *nbChampions, int *nbWeapons, int *nbProtections, int *nbHealings, Team *team1, Team *team2, Winsize screenSize) {
    Strategy *strategy = *s;
    char delimiters[]=" \t\n\r";
    char *mot;
    Strat *strat;
    mot = strtok(buffer, delimiters);
    
    if(mot == NULL) {
        return;
    } else if(!strcmp(mot, "strategy")) {
        mot = strtok(NULL, delimiters);
        strategy->nom = malloc(sizeof(char)*(strlen(mot)+1));
        strcpy(strategy->nom, mot);
    } else if(!strcmp(mot, "choose")) {
        char *mot1, *mot2;

        strat = calloc(1, sizeof(Strat));        
        strat->enumStrat = commande;

        mot1 = strtok(NULL, delimiters);
        mot2 = strtok(NULL, delimiters);

        strat->unionStrat.commande.nbParametres = 2;
        strat->unionStrat.commande.parametres = malloc(sizeof(UnionParametre)*strat->unionStrat.commande.nbParametres);
        
        if(!strcmp(mot1, "weapon")) {
            strat->unionStrat.commande.parametres[0].weapon = searchWeapon(weapons, nbWeapons, mot2);
            strat->unionStrat.commande.enumCommande = buy_weapon;
            strat->unionStrat.commande.commande.buyWeapon = buyWeapon;
        } else if(!strcmp(mot1, "protection")) {
            strat->unionStrat.commande.parametres[0].protection = searchProtection(protections, nbProtections, mot2);
            strat->unionStrat.commande.enumCommande = buy_protection;
            strat->unionStrat.commande.commande.buyProtection = buyProtection;
        } else if(!strcmp(mot1, "care")) {
            strat->unionStrat.commande.parametres[0].healing = searchHealing(healings, nbHealings, mot2);
            strat->unionStrat.commande.enumCommande = buy_care;
            strat->unionStrat.commande.commande.buyCare = buyHealing;
        }
        Strat *next = strategy->initStrategy;
        if(strategy->initStrategy == NULL) {
            strategy->initStrategy = strat;
        } else {
            while(next->suivant != NULL) {
                next = next->suivant;
            }
            next->suivant = strat;
        }
    } else if(!strcmp(mot, "add")) {
        mot = strtok(NULL, delimiters);
        if(!strcmp(mot, "action")) {
            int quant;
            char *quantite;

            strat = calloc(1, sizeof(Strat));
            strat->enumStrat = commande;

            quantite = strtok(NULL, delimiters);
            quant = atoi(quantite); // Servira lors de l'appel de la fonction

            strat->unionStrat.commande.nbParametres = 2;
            strat->unionStrat.commande.parametres = malloc(sizeof(UnionParametre)*strat->unionStrat.commande.nbParametres);
            strat->unionStrat.commande.parametres[1].entier = quant;
            strat->unionStrat.commande.enumCommande = buy_CA;
            strat->unionStrat.commande.commande.buyCA = buyCA;

            Strat *next = strategy->initStrategy;
            if(strategy->initStrategy == NULL) {
                strategy->initStrategy = strat;
            } else {
                while(next->suivant != NULL) {
                    next = next->suivant;
                }
                next->suivant = strat;
            }
        }
    } else {
        //printf("Ligne inconnue, arrêt de la lecture.\n");
    }
}

void useStrategy(Strategy *strategy) {
    if(strategy == NULL) return;
    printf("Num %d | Strategy %s\n", strategy->num, strategy->nom);
    
    printf("Initialisation de la stratégie :\n");
    useStrat(strategy->initStrategy);

    printf("Execution de la stratégie :\n");
    useStrat(strategy->strat);
}

void useStrat(Strat *strat) {
    while(strat) {
        if(strat->enumStrat == commande) {
            if(strat->unionStrat.commande.enumCommande == buy_weapon) {
                //(strat->unionStrat.commande.commande.buyWeapon)(strat->unionStrat.commande.parametres[0].weapon, strat->unionStrat.commande.parametres[1].team);
                printf("buy weapon\n");
            } else if(strat->unionStrat.commande.enumCommande == buy_protection) {
                //(strat->unionStrat.commande.commande.buyProtection)(strat->unionStrat.commande.parametres[0].protection, strat->unionStrat.commande.parametres[1].team);
                printf("buy protection\n");
            } else if(strat->unionStrat.commande.enumCommande == buy_care) {
                //(strat->unionStrat.commande.commande.buyCare)(strat->unionStrat.commande.parametres[0].healing, strat->unionStrat.commande.parametres[1].team);
                printf("buy care\n");
            } else if(strat->unionStrat.commande.enumCommande == buy_CA) {
                //(strat->unionStrat.commande.commande.buyCA)(strat->unionStrat.commande.parametres[0].team, strat->unionStrat.commande.parametres[1].entier);
                printf("buy CA\n");
            }
            strat = strat->suivant;
        } else if(strat->enumStrat == operateur) {
            if(strcmp(strat->unionStrat.operateur.operateur,"<") == 0) {
                if(strat->unionStrat.operateur.op1 < strat->unionStrat.operateur.op2) {
                    strat = strat->suivant;
                } else {
                    strat = strat->suivantSinon;
                }
            } else if(strcmp(strat->unionStrat.operateur.operateur,">") == 0) {
                if(strat->unionStrat.operateur.op1 > strat->unionStrat.operateur.op2) {
                    strat = strat->suivant;
                } else {
                    strat = strat->suivantSinon;
                }
            }
        }
    }
}