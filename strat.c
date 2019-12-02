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
    char delimiters[]=" \t\n\r";
    char *buffer = malloc(sizeof(char)* SIZE);

    initStructure(0, strategy, buffer, NULL, fichier, SIZE, delimiters, champions, weapons, protections, healings, nbChampions, nbWeapons, nbProtections, nbHealings, team1, team2, screenSize);

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
        strat = strategyCreateChoose(s, buffer, champions, weapons, protections, healings, nbChampions, nbWeapons, nbProtections, nbHealings, team1, team2);
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
        strat = strategyCreateAddCA(s, mot);
        Strat *next = strategy->initStrategy;
        if(strategy->initStrategy == NULL) {
            strategy->initStrategy = strat;
        } else {
            while(next->suivant != NULL) {
                next = next->suivant;
            }
            next->suivant = strat;
        }
    } else if(!strcmp(mot, "if")) {
        char *ptCondition, *condition = malloc(sizeof(char) * 100);
        char *space = " ";
        ptCondition = condition;

        strat = calloc(1, sizeof(Strat));
        strat->enumStrat = operateur;
        mot = strtok(NULL, delimiters);

        while(mot) {
            strcpy(ptCondition, mot);
            while (*ptCondition) ptCondition++;
            mot = strtok(NULL, delimiters);
            if(mot) strcpy(ptCondition++, space);
        }
        strat->unionStrat.operateur.chaine = condition;

        Strat *next = strategy->strat;
        if(strategy->strat == NULL) {
            strategy->strat = strat;
        } else {
            while(next->suivant != NULL) {
                next = next->suivant;
            }
            next->suivant = strat;
        }
    } else if(!strcmp(mot, "use")) {
        strat = strategyCreateUse(mot, screenSize);
        Strat *next = strategy->strat;
        if(strategy->strat == NULL) {
            strategy->strat = strat;
        } else {
            while(next->suivant != NULL) {
                next = next->suivant;
            }
            next->suivant = strat;
        }
    } else if(!strcmp(mot, "end")) {
        /*
        Fonction pour finir le tour
        strat = malloc(sizeof(Strat));        
        strat->enumStrat = commande;
        */
    } else {
        return;
    }
}

Strat * strategyCreateChoose(Strategy **s, char *buffer, Champion **champions, Weapon **weapons, Protection **protections, Healing **healings, int *nbChampions, int *nbWeapons, int *nbProtections, int *nbHealings, Team *team1, Team *team2) {
    char *mot1, *mot2;
    Weapon *weap;
    Protection *prot;
    Healing *heal;
    Strat *strat;
    char delimiters[]=" \t\n\r";

    strat = calloc(1, sizeof(Strat));        
    strat->enumStrat = commande;

    mot1 = strtok(NULL, delimiters);
    mot2 = strtok(NULL, delimiters);

    strat->unionStrat.commande.nbParametres = 2;
    strat->unionStrat.commande.parametres = malloc(sizeof(UnionParametre)*strat->unionStrat.commande.nbParametres);

    if(!strcmp(mot1, "weapon")) {
        weap = searchWeapon(weapons, nbWeapons, mot2);
        if(weap == NULL) {
            free(strat);
            return NULL;
        }
        strat->unionStrat.commande.parametres[0].weapon = weap;
        strat->unionStrat.commande.enumCommande = buy_weapon;
        strat->unionStrat.commande.commande.buyWeapon = buyWeapon;
        (*s)->coutCE += weap->CE;
    } else if(!strcmp(mot1, "protection")) {
        prot = searchProtection(protections, nbProtections, mot2);
        if(prot == NULL) {
            free(strat);
            return NULL;
        }
        strat->unionStrat.commande.parametres[0].protection = prot;
        strat->unionStrat.commande.enumCommande = buy_protection;
        strat->unionStrat.commande.commande.buyProtection = buyProtection;
        (*s)->coutCE += prot->CE;
    } else if(!strcmp(mot1, "care")) {
        heal = searchHealing(healings, nbHealings, mot2);
        if(heal == NULL) {
            free(strat);
            return NULL;
        }
        strat->unionStrat.commande.parametres[0].healing = heal;
        strat->unionStrat.commande.enumCommande = buy_care;
        strat->unionStrat.commande.commande.buyCare = buyHealing;
        (*s)->coutCE += heal->CE;
    }
    return strat;
}

Strat * strategyCreateAddCA(Strategy **s, char *mot) {
    Strat *strat;
    char delimiters[]=" \t\n\r";
    
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
        (*s)->coutCE += quant;
        return strat;
    }
    return NULL;
}

Strat * strategyCreateUse(char *mot, Winsize screenSize) {
    Strat *strat;
    char delimiters[]=" \t\n\r";
    mot = strtok(NULL, delimiters);
    if(!strcmp(mot, "protection")) {
        strat = calloc(1, sizeof(Strat));
        strat->enumStrat = commande;
        strat->unionStrat.commande.nbParametres = 1;
        strat->unionStrat.commande.parametres = malloc(sizeof(UnionParametre)*strat->unionStrat.commande.nbParametres);
        strat->unionStrat.commande.enumCommande = use_protection;
        strat->unionStrat.commande.commande.useProtection = useProtection;
        
    } else if(!strcmp(mot, "care")) {
        int quantite = 1;
        strat = calloc(1, sizeof(Strat));        
        strat->enumStrat = commande;
        strat->unionStrat.commande.nbParametres = 2;
        strat->unionStrat.commande.parametres = malloc(sizeof(UnionParametre)*strat->unionStrat.commande.nbParametres);
        strat->unionStrat.commande.enumCommande = use_care;
        strat->unionStrat.commande.commande.useCare = useCare;

        mot = strtok(NULL, delimiters);
        if(mot != NULL) {
            quantite = atoi(mot);
        }
        strat->unionStrat.commande.parametres[1].entier = quantite;
        
    } else if(!strcmp(mot, "weapon")) {
        int quantite = 1;
        strat = calloc(1, sizeof(Strat));        
        strat->enumStrat = commande;
        strat->unionStrat.commande.nbParametres = 4;
        strat->unionStrat.commande.parametres = malloc(sizeof(UnionParametre)*strat->unionStrat.commande.nbParametres);
        strat->unionStrat.commande.enumCommande = use_weapon;
        strat->unionStrat.commande.commande.useWeapon = useWeapon;
        strat->unionStrat.commande.parametres[3].entier = screenSize.ws_col;

        mot = strtok(NULL, delimiters);
        if(mot != NULL) {
            quantite = atoi(mot);
        }
        strat->unionStrat.commande.parametres[2].entier = quantite;
    }
    return strat;
}

int initStructure(int d, Strategy **s, char *buffer, Strat *stratParam, FILE *fichier, int SIZE, char *delimiters, Champion **champions, Weapon **weapons, Protection **protections, Healing **healings, int *nbChampions, int *nbWeapons, int *nbProtections, int *nbHealings, Team *team1, Team *team2, Winsize screenSize) {
    char *mot;
    Strat *strat;
    Strategy *strategy = *s;
    int i;
    while(fgets(buffer, SIZE, fichier)) {
        mot = strtok(buffer, delimiters);
        if(mot == NULL) continue;
        
        if(!strcmp(mot, "strategy")) {
            printf("Strategy\n");
            mot = strtok(NULL, delimiters);
            strategy->nom = malloc(sizeof(char)*(strlen(mot)+1));
            strcpy(strategy->nom, mot);
        } else if(!strcmp(mot, "choose")) {
            printf("Choose\n");
            strat = strategyCreateChoose(s, buffer, champions, weapons, protections, healings, nbChampions, nbWeapons, nbProtections, nbHealings, team1, team2);
            addInInitStrategy(s, strat);
        } else if(!strcmp(mot, "add")) {
            printf("Achat CA\n");
            strat = strategyCreateAddCA(s, mot);
            addInInitStrategy(s, strat);
        } else if(!strcmp(mot, "if")) {
            int ret;
            for (i = 0; i < d; i++) printf("  ");
            char *ptCondition, *condition = malloc(sizeof(char) * 50);
            char *space = " ";
            ptCondition = condition;

            strat = calloc(1, sizeof(Strat));
            strat->enumStrat = operateur;
            mot = strtok(NULL, delimiters);

            while(mot) {
                strcpy(ptCondition, mot);
                while (*ptCondition) ptCondition++;
                mot = strtok(NULL, delimiters);
                if(mot) strcpy(ptCondition++, space);
            }
            strat->unionStrat.operateur.chaine = condition;
            stratParam = strat;
            
            printf("if\n");
            ret = initStructure(d+1, s, buffer, strat->suivant, fichier, SIZE, delimiters, champions, weapons, protections, healings, nbChampions, nbWeapons, nbProtections, nbHealings, team1, team2, screenSize);
            if(ret == 1) { // 1 : else
                for (i = 0; i < d; i++) printf("  ");
                initStructure(d+1, s, buffer, strat->suivantSinon, fichier, SIZE, delimiters, champions, weapons, protections, healings, nbChampions, nbWeapons, nbProtections, nbHealings, team1, team2, screenSize);
            } else if(ret == 2) { // 2 : endif

            }
        } else if(!strcmp(mot, "else")) {
            stratParam = strat;
            for (i = 0; i < d-1; i++) printf("  ");
            printf("else\n");
            return 1;
        } else if(!strcmp(mot, "endif")) {
            for (i = 0; i < d-1; i++) printf("  ");
            printf("endif\n");
            return 2;
        } else if(!strcmp(mot, "use")) {
            for (i = 0; i < d; i++) printf("  ");
            printf("Use\n");
            strat = strategyCreateUse(mot, screenSize);
            addInStratStrategy(s, strat);
        } else if(!strcmp(mot, "move")) {
            for (int i = 0; i < d; i++) printf("  ");
            printf("Move\n");
        } else if(!strcmp(mot, "end")) {
            for (int i = 0; i < d; i++) printf("  ");
            printf("End\n");
        }
    }
    return 0;
}

void addInInitStrategy(Strategy **s, Strat *strat) {
    Strategy *strategy = *s;
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

void addInStratStrategy(Strategy **s, Strat *strat) {
    Strategy *strategy = *s;
    Strat *next = strategy->strat;
    if(strategy->strat == NULL) {
        strategy->strat = strat;
    } else {
        while(next->suivant != NULL) {
            next = next->suivant;
        }
        next->suivant = strat;
    }
}

void useStrategy(Strategy *strategy) {
    if(strategy == NULL) return;
    printf("Num %d | Strategy <%s>\n", strategy->num, strategy->nom);
    
    printf("\nInitialisation de la stratégie :\n\n");
    useStrat(strategy->initStrategy);

    printf("\nExecution de la stratégie :\n\n");
    useStrat(strategy->strat);
}

void useStrat(Strat *strat) {
    while(strat) {
        if(strat->enumStrat == commande) {
            if(strat->unionStrat.commande.enumCommande == buy_weapon) {
                (strat->unionStrat.commande.commande.buyWeapon)(strat->unionStrat.commande.parametres[0].weapon, strat->unionStrat.commande.parametres[1].team);
            } else if(strat->unionStrat.commande.enumCommande == buy_protection) {
                (strat->unionStrat.commande.commande.buyProtection)(strat->unionStrat.commande.parametres[0].protection, strat->unionStrat.commande.parametres[1].team);
            } else if(strat->unionStrat.commande.enumCommande == buy_care) {
                (strat->unionStrat.commande.commande.buyCare)(strat->unionStrat.commande.parametres[0].healing, strat->unionStrat.commande.parametres[1].team);
            } else if(strat->unionStrat.commande.enumCommande == buy_CA) {
                (strat->unionStrat.commande.commande.buyCA)(strat->unionStrat.commande.parametres[0].team, strat->unionStrat.commande.parametres[1].entier);
            } else if(strat->unionStrat.commande.enumCommande == use_weapon) {
                (strat->unionStrat.commande.commande.useWeapon)(strat->unionStrat.commande.parametres[0].team, strat->unionStrat.commande.parametres[1].team, strat->unionStrat.commande.parametres[2].entier, strat->unionStrat.commande.parametres[3].entier);
            } else if(strat->unionStrat.commande.enumCommande == use_protection) {
                (strat->unionStrat.commande.commande.useProtection)(strat->unionStrat.commande.parametres[0].team);
            } else if(strat->unionStrat.commande.enumCommande == use_care) {
                (strat->unionStrat.commande.commande.useCare)(strat->unionStrat.commande.parametres[0].team, strat->unionStrat.commande.parametres[1].entier);
            }
            strat = strat->suivant;
        } else if(strat->enumStrat == operateur) {
            if(strat->unionStrat.operateur.nbParametres == 1) {
                printf("if(%d)\n", strat->unionStrat.operateur.op1);
                if(strat->unionStrat.operateur.op1) {
                    strat = strat->suivant;
                } else {
                    strat = strat->suivantSinon;
                }
            } else {
                printf("if(%d %s %d)\n", strat->unionStrat.operateur.op1, strat->unionStrat.operateur.operateur, strat->unionStrat.operateur.op2);
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
                } else if(strcmp(strat->unionStrat.operateur.operateur,">=") == 0) {
                    if(strat->unionStrat.operateur.op1 >= strat->unionStrat.operateur.op2) {
                        strat = strat->suivant;
                    } else {
                        strat = strat->suivantSinon;
                    }
                } else if(strcmp(strat->unionStrat.operateur.operateur,"<=") == 0) {
                    if(strat->unionStrat.operateur.op1 <= strat->unionStrat.operateur.op2) {
                        strat = strat->suivant;
                    } else {
                        strat = strat->suivantSinon;
                    }
                } else if(strcmp(strat->unionStrat.operateur.operateur,"!=") == 0) {
                    if(strat->unionStrat.operateur.op1 != strat->unionStrat.operateur.op2) {
                        strat = strat->suivant;
                    } else {
                        strat = strat->suivantSinon;
                    }
                } else if(strcmp(strat->unionStrat.operateur.operateur,"=") == 0) {
                    if(strat->unionStrat.operateur.op1 == strat->unionStrat.operateur.op2) {
                        strat = strat->suivant;
                    } else {
                        strat = strat->suivantSinon;
                    }
                }
            }
        }
    }
}

void initializeTheCombatStrategy(Strategy **strategy, Team *team1, Team *team2) {
    (*strategy)->allyTeam = team1;
    (*strategy)->enemyTeam = team2;
    initStrategyInFight(strategy, team1, team2);
}

void initStrategyInFight(Strategy **strategy, Team *team1, Team *team2) {
    initStrategyTeams(&(*strategy)->initStrategy, *strategy);
    initStrategyTeams(&(*strategy)->strat, *strategy);
}

void initStrategyTeams(Strat **s, Strategy *strategy) {
    Strat *strat = *s;
    if(!strat) return;

    if(strat->enumStrat == commande) {
        if(strat->unionStrat.commande.enumCommande == buy_weapon || strat->unionStrat.commande.enumCommande == buy_protection || strat->unionStrat.commande.enumCommande == buy_care) {
            strat->unionStrat.commande.parametres[1].team = strategy->allyTeam;
        } else if(strat->unionStrat.commande.enumCommande == buy_CA) {
            strat->unionStrat.commande.parametres[0].team = strategy->allyTeam;
        } else if(strat->unionStrat.commande.enumCommande == use_weapon) {
            strat->unionStrat.commande.parametres[0].team = strategy->allyTeam;
            strat->unionStrat.commande.parametres[1].team = strategy->enemyTeam;
        } else if(strat->unionStrat.commande.enumCommande == use_protection) {
            strat->unionStrat.commande.parametres[0].team = strategy->allyTeam;
        } else if(strat->unionStrat.commande.enumCommande == use_care) {
            strat->unionStrat.commande.parametres[0].team = strategy->allyTeam;
        }
        initStrategyTeams(&strat->suivant, strategy);
    } else if(strat->enumStrat == operateur) {
        char *mot, *copy;
        copy = malloc(sizeof(char)*(strlen(strat->unionStrat.operateur.chaine)+1));
        strcpy(copy, strat->unionStrat.operateur.chaine);

        mot = strtok(copy, " ");
        catchConditions(strategy, &strat->unionStrat.operateur.op1, NULL, mot);

        mot = strtok(NULL, " ");
        if(mot == NULL) {
            strat->unionStrat.operateur.nbParametres = 1;
        } else {
            if(!strcmp(mot, "<")) {
                strat->unionStrat.operateur.operateur = "<";
            } else if(!strcmp(mot, ">")) {
                strat->unionStrat.operateur.operateur = ">";
            } else if(!strcmp(mot, "<=")) {
                strat->unionStrat.operateur.operateur = "<=";
            } else if(!strcmp(mot, ">=")) {
                strat->unionStrat.operateur.operateur = ">=";
            } else if(!strcmp(mot, "!=")) {
                strat->unionStrat.operateur.operateur = "!=";
            } else {
                strat->unionStrat.operateur.operateur = "=";
            }

            mot = strtok(NULL, " ");
            catchConditions(strategy, &strat->unionStrat.operateur.op2, &strat->unionStrat.operateur.op1, mot);
            strat->unionStrat.operateur.nbParametres = 3;
        }
        free(copy);
        initStrategyTeams(&strat->suivant, strategy);
        initStrategyTeams(&strat->suivantSinon, strategy);
    }
}

void catchConditions(Strategy *strategy, int *entier, int *entier2, char *mot) {
    if(!strcmp(mot, "life")) {
        *entier = strategy->allyTeam->champion->PV;
    } else if(!strcmp(mot, "enemyLife")) {
        *entier = strategy->enemyTeam->champion->PV;
    } else if(!strcmp(mot, "enemyInScope")) {
        *entier = distanceBetweenChampions(strategy->allyTeam, strategy->enemyTeam);
    } else if(mot[strlen(mot)-1] == '%') {
        if(entier2 != NULL) {
            mot[strlen(mot)-1] = '\0';
            *entier = *entier2 * atoi(mot) / 100;
        }
    } else {
        *entier = atoi(mot);
    }
}