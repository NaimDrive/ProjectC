#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "initGame.h"
#include "fight.h"
#include "tools.h"
#include "strat.h"
#include "displayGame.h"

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

    initStructure(strategy, buffer, fichier, SIZE, delimiters, champions, weapons, protections, healings, nbChampions, nbWeapons, nbProtections, nbHealings, team1, team2, screenSize);

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

Strat * strategyCreateMove(char *mot, Winsize screenSize) {
    Strat *strat;
    char delimiters[]=" \t\n\r";
    int quantite = 1;
    mot = strtok(NULL, delimiters);

    if(!strcmp(mot, "forward")) {
        strat = calloc(1, sizeof(Strat));
        strat->enumStrat = commande;
        strat->unionStrat.commande.nbParametres = 3;
        strat->unionStrat.commande.parametres = malloc(sizeof(UnionParametre)*strat->unionStrat.commande.nbParametres);
        strat->unionStrat.commande.enumCommande = move_forward;
        strat->unionStrat.commande.commande.moveForward = moveForward;

        mot = strtok(NULL, delimiters);
        if(mot != NULL) {
            quantite = atoi(mot);
        }
        strat->unionStrat.commande.parametres[2].entier = quantite;
    } else if(!strcmp(mot, "backward")) {
        strat = calloc(1, sizeof(Strat));
        strat->enumStrat = commande;
        strat->unionStrat.commande.nbParametres = 3;
        strat->unionStrat.commande.parametres = malloc(sizeof(UnionParametre)*strat->unionStrat.commande.nbParametres);
        strat->unionStrat.commande.parametres[2].entier = screenSize.ws_col;
        strat->unionStrat.commande.enumCommande = move_backward;
        strat->unionStrat.commande.commande.moveBackward = moveBackward;

        mot = strtok(NULL, delimiters);
        if(mot != NULL) {
            quantite = atoi(mot);
        }
        strat->unionStrat.commande.parametres[1].entier = quantite;
    }
        
    return strat;
}

Strat * strategyCreateIf(char *mot) {
    char delimiters[]=" \t\n\r";
    char *ptCondition, *condition = malloc(sizeof(char) * 50);
    char *space = " ";

    Strat *strat;
    strat = calloc(1, sizeof(Strat));
    
    ptCondition = condition;
    strat->enumStrat = operateur;
    mot = strtok(NULL, delimiters);

    while(mot) {
        strcpy(ptCondition, mot);
        while (*ptCondition) ptCondition++;
        mot = strtok(NULL, delimiters);
        if(mot) strcpy(ptCondition++, space);
    }
    strat->unionStrat.operateur.chaine = condition;
    return strat;
}

Strat * strategyCreateFusion() {
    Strat * strat = calloc(1, sizeof(Strat));
    strat->enumStrat = fusion;
    return strat;
}

Strat * strategyCreateReturn() {
    Strat * strat = calloc(1, sizeof(Strat));
    strat->enumStrat = retour;
    return strat;
}

int initStructure(Strategy **s, char *buffer, FILE *fichier, int SIZE, char *delimiters, Champion **champions, Weapon **weapons, Protection **protections, Healing **healings, int *nbChampions, int *nbWeapons, int *nbProtections, int *nbHealings, Team *team1, Team *team2, Winsize screenSize) {
    char *mot;
    Strat *strat;
    Strategy *strategy = *s;

    while(fgets(buffer, SIZE, fichier)) {
        mot = strtok(buffer, delimiters);
        if(mot == NULL) continue;

        if(!strcmp(mot, "strategy")) { // Si le premier mot est strategy
            mot = strtok(NULL, delimiters);
            strategy->nom = malloc(sizeof(char)*(strlen(mot)+1));
            strcpy(strategy->nom, mot);

        } else if(!strcmp(mot, "choose")) { // Si le premier mot est choose
            strat = strategyCreateChoose(s, buffer, champions, weapons, protections, healings, nbChampions, nbWeapons, nbProtections, nbHealings, team1, team2);
            addInInitStrategy(s, strat);

        } else if(!strcmp(mot, "add")) { // Si le premier mot est add
            strat = strategyCreateAddCA(s, mot);
            addInInitStrategy(s, strat);

        } else {
            if(!strcmp(mot, "if")) { // Si le premier mot est if
                /*
                strat = strategyCreateIf(mot);
                //last->suivant = strat;
                addInStratStrategy(s, strat);
                ret = initStructure(s, buffer, strat->suivant, fichier, SIZE, delimiters, champions, weapons, protections, healings, nbChampions, nbWeapons, nbProtections, nbHealings, team1, team2, screenSize);
                if(ret == 1) {
                    initStructure(s, buffer, strat->suivantSinon, fichier, SIZE, delimiters, champions, weapons, protections, healings, nbChampions, nbWeapons, nbProtections, nbHealings, team1, team2, screenSize);
                }
                ret = 0;
                
                Strat * fusion = strategyCreateFusion();
                if(strat->suivant == NULL) {
                    strat->suivant = fusion;
                } else {
                    Strat *lastSuivant;
                    lastSuivant = lastStrat(strat->suivant);
                    lastSuivant->suivant = fusion;
                }
                if(strat->suivantSinon == NULL) {
                    strat->suivantSinon = fusion;
                } else {
                    Strat *lastSuivantSinon;
                    lastSuivantSinon = lastStrat(strat->suivantSinon);
                    lastSuivantSinon->suivant = fusion;
                }
                */
            } else if(!strcmp(mot, "else")) { // Si le premier mot est else
                //return 1;

            } else if(!strcmp(mot, "endif")) { // Si le premier mot est endif
                //return 2;

            } else if(!strcmp(mot, "use")) { // Si le premier mot est use
                strat = strategyCreateUse(mot, screenSize);
                if(strat != NULL) {
                    addInStratStrategy(s, strat);
                }
                
            } else if(!strcmp(mot, "move")) { // Si le premier mot est move
                strat = strategyCreateMove(mot, screenSize);
                if(strat != NULL) {
                    addInStratStrategy(s, strat);
                }
            } else if(!strcmp(mot, "end")) { // Si le premier mot est end
                strat = strategyCreateReturn();
                if(strat != NULL) {
                    addInStratStrategy(s, strat);
                }
            }
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

Strat * lastStrat(Strat *strat) {
    if(strat) {
        while(strat->suivant) {
            printf("Je vais au suivant\n");
            strat = strat->suivant;
        }
        return strat;
    }
    return NULL;
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

void useInitStrat(Strat *strat) {
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
            }
        }
        strat = strat->suivant;
    }
    enterToContinue();
    system("clear");
}

void useStrat(Strat *strat, Team *team, Team *opponent, int screenSize) {
    unsigned int micro = 1500000;
    while(strat && team->CA >= 0) {
        if(strat->enumStrat == retour) {
            printf("Tour terminé\n");
            break;
        } else if(strat->enumStrat == commande) {
            printf("Execution commande : ");
            if(strat->unionStrat.commande.enumCommande == use_weapon) {
                (strat->unionStrat.commande.commande.useWeapon)(strat->unionStrat.commande.parametres[0].team, strat->unionStrat.commande.parametres[1].team, strat->unionStrat.commande.parametres[2].entier, strat->unionStrat.commande.parametres[3].entier);
            } else if(strat->unionStrat.commande.enumCommande == use_protection) {
                (strat->unionStrat.commande.commande.useProtection)(strat->unionStrat.commande.parametres[0].team);
            } else if(strat->unionStrat.commande.enumCommande == use_care) {
                (strat->unionStrat.commande.commande.useCare)(strat->unionStrat.commande.parametres[0].team, strat->unionStrat.commande.parametres[1].entier);
            } else if(strat->unionStrat.commande.enumCommande == move_forward) {
                (strat->unionStrat.commande.commande.moveForward)(strat->unionStrat.commande.parametres[0].team, strat->unionStrat.commande.parametres[1].team, strat->unionStrat.commande.parametres[2].entier);
            } else if(strat->unionStrat.commande.enumCommande == move_backward) {
                (strat->unionStrat.commande.commande.moveBackward)(strat->unionStrat.commande.parametres[0].team, strat->unionStrat.commande.parametres[1].entier, strat->unionStrat.commande.parametres[2].entier);
            }
            strat = strat->suivant;
        } else if(strat->enumStrat == operateur) {
            printf("Execution IF : ");
            printf("Commande : %s\n", strat->unionStrat.operateur.chaine);
            if(strat->unionStrat.operateur.nbParametres == 1) {
                printf("1 opérant : ");
                printf("if(%d)\n", strat->unionStrat.operateur.op1);
                if(strat->unionStrat.operateur.op1) {
                    strat = strat->suivant;
                } else {
                    strat = strat->suivantSinon;
                }
            } else {
                printf("2 opérants ");
                printf("if(%d %s %d)\n", strat->unionStrat.operateur.op1, strat->unionStrat.operateur.operateur, strat->unionStrat.operateur.op2);
                if(strcmp(strat->unionStrat.operateur.operateur,"<") == 0) {
                    if(strat->unionStrat.operateur.op1 < strat->unionStrat.operateur.op2) {
                        printf("OUI\n");
                        strat = strat->suivant;
                    } else {
                        printf("NON\n");
                        if(strat->suivantSinon != NULL) printf("Pas null\n");
                        else printf("Null\n");
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
        } else {
            strat = strat->suivant;
        }
        if(team->id == 0) {
            displayStats(team, opponent, screenSize);
            displayGame(team, opponent, screenSize);
            displayHealth(team, opponent, screenSize);
        } else {
            displayStats(opponent, team, screenSize);
            displayGame(opponent, team, screenSize);
            displayHealth(opponent, team, screenSize);
        }
        usleep(micro);
        system("clear");
        
    }
}

void initializeTheCombatStrategy(Strategy **strategy, Team *team1, Team *team2) {
    (*strategy)->allyTeam = team1;
    (*strategy)->enemyTeam = team2;
    initStrategyInFight(strategy);
}

void initStrategyInFight(Strategy **strategy) {
    initStrategyTeams(&(*strategy)->initStrategy, *strategy);
    initStrategyTeams(&(*strategy)->strat, *strategy);

    useInitStrat((*strategy)->initStrategy);
}

void initStrategyTeams(Strat **s, Strategy *strategy) {
    Strat *strat = *s;
    if(!strat) return;

    if(strat->enumStrat == commande) {
        if(strat->unionStrat.commande.enumCommande == buy_weapon || strat->unionStrat.commande.enumCommande == buy_protection || strat->unionStrat.commande.enumCommande == buy_care) {
            strat->unionStrat.commande.parametres[1].team = strategy->allyTeam;
        } else if(strat->unionStrat.commande.enumCommande == use_weapon || strat->unionStrat.commande.enumCommande == move_forward) {
            strat->unionStrat.commande.parametres[0].team = strategy->allyTeam;
            strat->unionStrat.commande.parametres[1].team = strategy->enemyTeam;
        } else if(strat->unionStrat.commande.enumCommande == use_protection || strat->unionStrat.commande.enumCommande == use_care || strat->unionStrat.commande.enumCommande == move_backward || strat->unionStrat.commande.enumCommande == buy_CA) {
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
            strat->unionStrat.operateur.nbParametres = 3;
            strat->unionStrat.operateur.op2 = strategy->allyTeam->weapon->portee;
            strat->unionStrat.operateur.operateur = "<=";
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

Strat * copyStrat(Strat *strat, Strategy *strategy) {
    if(strat == NULL) {
        return NULL;
    }

    Strat *copy;
    copy = calloc(1, sizeof(Strat));
    
    if(strat->enumStrat == commande) {
        copy->enumStrat = commande;
        copy->unionStrat.commande.enumCommande = strat->unionStrat.commande.enumCommande;
        copy->unionStrat.commande.nbParametres = strat->unionStrat.commande.nbParametres;
        copy->unionStrat.commande.parametres = malloc(sizeof(UnionParametre) * copy->unionStrat.commande.nbParametres);

        if(strat->unionStrat.commande.enumCommande == buy_weapon) {
            copy->unionStrat.commande.commande.buyWeapon = buyWeapon;
            //copy->unionStrat.commande.parametres[1].team = strategy->allyTeam;
            copy->unionStrat.commande.parametres[0].weapon = strat->unionStrat.commande.parametres[0].weapon;
            copy->unionStrat.commande.parametres[1].team = strat->unionStrat.commande.parametres[1].team;
        } else if(strat->unionStrat.commande.enumCommande == buy_protection) {
            copy->unionStrat.commande.commande.buyProtection = buyProtection;
            //copy->unionStrat.commande.parametres[1].team = strategy->allyTeam;
            copy->unionStrat.commande.parametres[0].protection = strat->unionStrat.commande.parametres[0].protection;
            copy->unionStrat.commande.parametres[1].team = strat->unionStrat.commande.parametres[1].team;
        } else if(strat->unionStrat.commande.enumCommande == buy_care) {
            copy->unionStrat.commande.commande.buyCare = buyHealing;
            //copy->unionStrat.commande.parametres[1].team = strategy->allyTeam;
            copy->unionStrat.commande.parametres[0].healing = strat->unionStrat.commande.parametres[0].healing;
            copy->unionStrat.commande.parametres[1].team = strat->unionStrat.commande.parametres[1].team;
        } else if(strat->unionStrat.commande.enumCommande == buy_CA) {
            copy->unionStrat.commande.commande.buyCA = buyCA;
            //copy->unionStrat.commande.parametres[0].team = strategy->allyTeam;
            copy->unionStrat.commande.parametres[0].team = strat->unionStrat.commande.parametres[0].team;
            copy->unionStrat.commande.parametres[1].entier = strat->unionStrat.commande.parametres[1].entier;
        } else if(strat->unionStrat.commande.enumCommande == use_weapon) {
            copy->unionStrat.commande.commande.useWeapon = useWeapon;
            //copy->unionStrat.commande.parametres[0].team = strategy->allyTeam;
            //copy->unionStrat.commande.parametres[1].team = strategy->enemyTeam;
            copy->unionStrat.commande.parametres[0].team = strat->unionStrat.commande.parametres[0].team;
            copy->unionStrat.commande.parametres[1].team = strat->unionStrat.commande.parametres[1].team;
            copy->unionStrat.commande.parametres[2].entier = strat->unionStrat.commande.parametres[2].entier;
            copy->unionStrat.commande.parametres[3].entier = strat->unionStrat.commande.parametres[3].entier;
        } else if(strat->unionStrat.commande.enumCommande == use_protection) {
            copy->unionStrat.commande.commande.useProtection = useProtection;
            //copy->unionStrat.commande.parametres[0].team = strategy->allyTeam;
            copy->unionStrat.commande.parametres[0].team = strat->unionStrat.commande.parametres[0].team;
        } else if(strat->unionStrat.commande.enumCommande == use_care) {
            copy->unionStrat.commande.commande.useCare = useCare;
            //copy->unionStrat.commande.parametres[0].team = strategy->allyTeam;
            copy->unionStrat.commande.parametres[0].team = strat->unionStrat.commande.parametres[0].team;
            copy->unionStrat.commande.parametres[1].entier = strat->unionStrat.commande.parametres[1].entier;
        } else if(strat->unionStrat.commande.enumCommande == move_forward) {
            copy->unionStrat.commande.commande.moveForward = moveForward;
            //copy->unionStrat.commande.parametres[0].team = strategy->allyTeam;
            //copy->unionStrat.commande.parametres[1].team = strategy->enemyTeam;
            copy->unionStrat.commande.parametres[0].team = strat->unionStrat.commande.parametres[0].team;
            copy->unionStrat.commande.parametres[1].team = strat->unionStrat.commande.parametres[1].team;
            copy->unionStrat.commande.parametres[2].entier = strat->unionStrat.commande.parametres[2].entier;
        } else if(strat->unionStrat.commande.enumCommande == move_backward) {
            copy->unionStrat.commande.commande.moveBackward = moveBackward;
            //copy->unionStrat.commande.parametres[0].team = strategy->allyTeam;
            copy->unionStrat.commande.parametres[0].team = strat->unionStrat.commande.parametres[0].team;
            copy->unionStrat.commande.parametres[1].entier = strat->unionStrat.commande.parametres[1].entier;
            copy->unionStrat.commande.parametres[2].entier = strat->unionStrat.commande.parametres[2].entier;
        }

    } else if(strat->enumStrat == operateur) {
        copy->enumStrat = operateur;
        copy->unionStrat.operateur.chaine = malloc(sizeof(char) * (strlen(strat->unionStrat.operateur.chaine)+1));
    } else if(strat->enumStrat == fusion) {
        copy->enumStrat = fusion;
    }

    copy->suivant = copyStrat(strat->suivant, strategy);
    copy->suivantSinon = copyStrat(strat->suivantSinon, strategy);

    return strat;
}

Strategy * copyStrategy(Strategy *strategy) {
    Strategy *copy;
    copy = malloc(sizeof(Strategy));
    copy->num = strategy->num;
    copy->coutCE = strategy->coutCE;
    copy->allyTeam = NULL;
    copy->enemyTeam = NULL;

    copy->nom = malloc(sizeof(char) * (strlen(strategy->nom)+1));
    strcpy(copy->nom, strategy->nom);

    copy->initStrategy = copyStrat(strategy->initStrategy, strategy);
    copy->strat = copyStrat(strategy->strat, strategy);

    return copy;
}