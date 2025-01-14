#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <ctype.h>

#include "initGame.h"
#include "fight.h"
#include "strat.h"
#include "fightMode.h"
#include "endGame.h"
#include "commands.h"
#include "colors.h"
#include "tools.h"


void showTeamsCE(Team *team1, Team *team2) {
  printf(" -- > ");
  green();
  printf("Légume");
  white();
  printf(" : %d", team1->CE);
  resetColor();
  printf("  |  ");
  yellow();
  printf("Fruit");
  white();
  printf(" : %d", team2->CE);
  resetColor();
  printf(" < -- \n");
}

int getID(char *command, int n) {
  char *c = substring(command, n, strlen(command));
  char *endptr;
  long id = strtoul(c, &endptr, 10);
  long res;
  if(*c != '\0' && *endptr == '\0') {
    res = id;
  } else {
    res = -1;
  }
  free(c);
  return res;
}

int getChampIndex(char *champName, Champion **champions, int nbChampions) {
  champName[0] = toupper(champName[0]); // make first char an uppercase

  int i;
  for(i = 0; i < nbChampions; i++) {
    if(strcmp(champName, champions[i]->variete) == 0) return i;
  }

  return -1;
}

int checkingChamps(char *veg, char *fruit, int vegIndex, int fruitIndex, Champion **champions, int nbChampions) {
  int output = 0;

  white();

  if(vegIndex == -1) {
    red();
    printf("'%s' ne fait pas partie des champions jouables.\n", veg);
  } else if(vegIndex >= 6) {
    red();
    printf("'%s' n'est pas un légume !\n", veg);
  }

  if(fruitIndex == -1) {
    red();
    printf("'%s' ne fait pas partie des champions jouables.\n", fruit);
  } else if(fruitIndex < 6) {
    red();
    printf("'%s' n'est pas un fruit !\n", fruit);
  }

  if((vegIndex != -1 && fruitIndex != -1) && fruitIndex > 5 && vegIndex < 6) {
    output = 1;
  }
  resetColor();

  free(veg); // will never be used again
  free(fruit); // will never be used again

  return output;
}

void showVegetables(Champion **champions, int *nbChampions) {
  Champion *c;
  int i;
  for(i = 0; i < ((*nbChampions)-6); i++)
  {
    c = champions[i];
    printf("Num : %d | Variété : %s | Type : %s | Force : %d | Resistance : %d | PV Max : %d | CE : %d\n", c->num, c->variete, c->type, c->force, c->resistance, c->PVMax, c->CE);
  }
  printf("\n");
}

void showVegetable(Champion **champions, int *nbChampions, int id) {
  if(id <= ((*nbChampions)-7) && (id >= 0)) {
    printf("Num : %d | Variété : %s | Type : %s | Force : %d | Resistance : %d | PV Max : %d | CE : %d\n\n", champions[id]->num, champions[id]->variete, champions[id]->type, champions[id]->force, champions[id]->resistance, champions[id]->PVMax, champions[id]->CE);
  } else {
    red();
    printf("Veuillez choisir un ID compris entre 0 et %d\n", ((*nbChampions)-7));
    resetColor();
  }
}

void showFruits(Champion **champions, int *nbChampions) {
 Champion *c;
  int i;
  for(i = 6; i < *nbChampions; i++)
  {
    c = champions[i];
    printf("Num : %d | Variété : %s | Type : %s | Force : %d | Resistance : %d | PV Max : %d | CE : %d\n", (c->num)-6, c->variete, c->type, c->force, c->resistance, c->PVMax, c->CE);
  }
  printf("\n");
}

void showFruit(Champion **champions, int *nbChampions, int id) {
  int tmp = id;
  id += 6;
  if(tmp < (*nbChampions)-6 && tmp >= 0) {
    printf("Num : %d | Variété : %s | Type : %s | Force : %d | Resistance : %d | PV Max : %d | CE : %d\n\n", (champions[id]->num)-6, champions[id]->variete, champions[id]->type, champions[id]->force, champions[id]->resistance, champions[id]->PVMax, champions[id]->CE);
  } else {
    red();
    printf("Veuillez re-vérifier l'ID entré.\n");
    resetColor();
  }
}

void showWeapons(Weapon **weapons, int *nbWeapons, int ce) {
  Weapon *w;
  int i;
  for(i = 0; i < *nbWeapons; i++)
  {
    w = weapons[i];
    if(ce != -1) {
      if(ce >= w->CE) green();
      else { resetColor() , red(); }
    }
    printf("Num : %d | Nom : %s | CE : %d | CA : %d | Dégâts : %d-%d | Portée : %d\n", w->num, w->nom, w->CE, w->CA, w->degatsMin, w->degatsMax, w->portee);
  }
  printf("\n");
  resetColor();
}

void showWeapon(Weapon **weapons, int *nbWeapons, int id) {
  if(id < *nbWeapons && id >= 0) {
    printf("Num : %d | Nom : %s | CE : %d | CA : %d | Dégâts : %d-%d | Portée : %d\n\n", weapons[id]->num, weapons[id]->nom, weapons[id]->CE, weapons[id]->CA, weapons[id]->degatsMin, weapons[id]->degatsMax, weapons[id]->portee);
  } else {
    red();
    printf("Veuillez entrer un ID compris entre 0 et %d\n", *nbWeapons);
    resetColor();
  }
}

void showProtections(Protection **protections, int *nbProtections, int ce) {
  Protection *p;
  int i;

  for(i = 0; i < *nbProtections; i++)
  {
    p = protections[i];
    if(ce != -1) {
      if(ce >= p->CE) green();
      else { resetColor() , red(); }
    }
    printf("Num : %d | Nom : %s | CE : %d | CA : %d | Probabilité : %d %c \n", p->num, p->nom, p->CE, p->CA, p->probabilite, '%');
  }
  printf("\n");
  resetColor();

}

void showProtection(Protection **protections, int *nbProtections, int id) {
  if(id < *nbProtections && id >= 0) {
    printf("Num : %d | Nom : %s | CE : %d | CA : %d | Probabilité : %d %c \n\n", protections[id]->num, protections[id]->nom, protections[id]->CE, protections[id]->CA, protections[id]->probabilite, '%');
  } else {
    red();
    printf("Veuillez entrer un ID compris entre 0 et %d\n", *nbProtections);
    resetColor();
  }
}

void showCares(Healing **healings, int *nbHealings, int ce) {
  Healing *h;
  int i;
  for(i = 0; i < *nbHealings; i++)
  {
    h = healings[i];
    if(ce != -1) {
      if(ce >= h->CE) green();
      else { resetColor() , red(); }
    }
    printf("Num : %d | Nom : %s | CE : %d | CA : %d | Volume : %d | Effet (min-max) : %d-%d\n", h->num, h->nom, h->CE, h->CA, h->volume, h->effetMin, h->effetMax);
  }
  printf("\n");
  resetColor();
}

void showCare(Healing **healings, int *nbHealings, int id) {
  if(id < *nbHealings && id >= 0) {
    printf("Num : %d | Nom : %s | CE : %d | CA : %d | Volume : %d | Effet : %d-%d\n", healings[id]->num, healings[id]->nom, healings[id]->CE, healings[id]->CA, healings[id]->volume, healings[id]->effetMin, healings[id]->effetMax);
  } else {
    red();
    printf("Veuillez entrer un ID compris entre 0 et %d\n", *nbHealings-1);
    resetColor();
  }
}

void showStrategies(Strategy **strategy, int *nbStrategies) {
  if(strategy != NULL) {
    for (int i = 0; i < *nbStrategies; i++) {
      printf("Num : %d | Nom : %s | CE : %d\n", strategy[i]->num, strategy[i]->nom, strategy[i]->coutCE);
    }
  } else {
    printf("Aucune stratégie définie\n");
  }
}

void showStrategy(Strategy **strategy, int *nbStrategies, int id) {
  if(strategy != NULL && nbStrategies != NULL && id < *nbStrategies && id >= 0) {
    printf("Description de la strategy %s\n", strategy[id]->nom);
    Strat *strat = strategy[id]->initStrategy;
    while (strat != NULL) {
      if(strat->unionStrat.commande.enumCommande == buy_weapon) {
        printf("Arme : %s\n", strat->unionStrat.commande.parametres[0].weapon->nom);
      } else if(strat->unionStrat.commande.enumCommande == buy_protection) {
        printf("Protection : %s\n", strat->unionStrat.commande.parametres[0].protection->nom);
      } else if(strat->unionStrat.commande.enumCommande == buy_care) {
        printf("Soin : %s\n", strat->unionStrat.commande.parametres[0].healing->nom);
      } else if(strat->unionStrat.commande.enumCommande == buy_CA) {
        printf("Crédits d'action supplémentaires : %d\n", strat->unionStrat.commande.parametres[1].entier);
      }
      strat = strat->suivant;
    }
    printf("Crédits d'équipement nécessaires %d\n", strategy[id]->coutCE);
    
  } else {
    red();
    printf("Je suis là\n");
    if(nbStrategies != NULL && *nbStrategies > 0) {
      printf("Veuillez entrer un ID compris entre 0 et %d\n", *nbStrategies-1);
    } else {
      printf("Aucune stratégie n'est définie\n");
    }
    resetColor();
  }
}

int replay(char *command) {
  while(1) {
    printf("Voulez-vous rejouer ? (oui/non)\n");
    fgets(command, 256, stdin);
    if((strlen(command) > 0) && (command[strlen(command)-1] == '\n')) command[strlen(command)-1] = '\0';
    if(strcmp(command, "oui") == 0)
      return 2;
    else if(strcmp(command, "non") == 0)
      return 0;
    system("clear");
  }
}

void fight(Champion *vegetable, Champion* fruit, Package *package, Team *team1, Team *team2, Strategy *stratTeam1Param, Strategy *stratTeam2Param, Winsize screenSize) {
  int maximumCE = team1->maxCE, end = 0;
  Strategy *stratTeam1, *stratTeam2;

  if(stratTeam1Param != NULL && stratTeam1Param->coutCE + vegetable->CE > 50) {
    printf("La strategie appliquée à %s dépasse la limite de CE autorisé.\n", vegetable->variete);
    return;
  }
  if(stratTeam2Param != NULL && stratTeam2Param->coutCE + fruit->CE > 50) {
    printf("La strategie appliquée à %s dépasse la limite de CE autorisé.\n", fruit->variete);
    return;
  }

  buyChampion(vegetable, team1);
  buyChampion(fruit, team2);

  printf("\n%s VERSUS %s !\n", team1->champion->variete, team2->champion->variete);

  if(stratTeam1Param == NULL) {
    equipTeam(team1, package->weapons, package->protections, package->healings, package->nbWeapons, package->nbProtections, package->nbHealings);
  } else {
    stratTeam1 = copyStrategy(stratTeam1Param);
    printf("%s :\n", team1->champion->variete);
    initializeTheCombatStrategy(&stratTeam1, team1, team2);
  }
  
  if(stratTeam2Param == NULL) {
    equipTeam(team2, package->weapons, package->protections, package->healings, package->nbWeapons, package->nbProtections, package->nbHealings);
  } else {
    stratTeam2 = copyStrategy(stratTeam2Param);
    printf("%s :\n", team2->champion->variete);
    initializeTheCombatStrategy(&stratTeam2, team2, team1);
  }

  while(team1->champion->PV > 0 && team2->champion->PV > 0) {
    fighNotFinished(team1, team2); // Restore CA and healings used

    takeOffProtection(team1);
    if(stratTeam1Param == NULL) {
      fightingMode(team1, team2, NULL, screenSize.ws_col); // First player attack
    } else {
      fightingMode(team1, team2, stratTeam1, screenSize.ws_col); // First player attack
    }
    if(team2->champion->PV == 0) {
      break; // Avoid j2 playing if he's dead
    }
    takeOffProtection(team2);
    if(stratTeam2Param == NULL) {
      fightingMode(team2, team1, NULL, screenSize.ws_col); // Second player attack
    } else {
       fightingMode(team2, team1, stratTeam2, screenSize.ws_col); // Second player attack
    }
    
    
  }

  if(!((team1->CE > 0) && (team2->CE > 0) && (team1->CE >= package->weapons[0]->CE + package->champions[0]->CE) && (team2->CE >= package->weapons[0]->CE + package->champions[0]->CE))) {
    showEndGame(team1, team2);
    end = 1;
  }
  if(stratTeam1Param != NULL) {
    deallocateStrategy(stratTeam1);
  }
  if(stratTeam2Param != NULL) {
    deallocateStrategy(stratTeam2);
  }
  endRound(team1, team2, maximumCE, end, screenSize);
}

void help() {
  white();
  printf("Commandes :\n\n");
  printf(" show vegetables - Affiche tous les légumes.\n");
  printf(" show vegetable n - Affiche le légume numéro n.\n");
  printf(" show fruits - Affiche tous les fruits.\n");
  printf(" show fruit n - Affiche le fruit numéro n.\n");
  printf(" show weapons - Affiche toutes les armes.\n");
  printf(" show weapon n - Affiche l'arme numéro n.\n");
  printf(" show protections - Affiche toutes les protections.\n");
  printf(" show protection n - Affiche la protection numéro n.\n");
  printf(" show cares - Affiche tous les soins.\n");
  printf(" show care n - Affiche le soin numéro n.\n");
  printf(" fight v versus f - Lance un combat opposant le légume v au fruit f.\n");
  printf(" clear - Nettoie le terminal");
  printf(" help - Affiche un rappel de toutes les commandes disponibles.\n");
  printf(" exit - Quitte le jeu.\n\n");
  resetColor();
}

void exitGame(Package *package, Team *team1, Team *team2) {
  deallocateMemory(package, team1, team2);
  exit(0);
}

void readCommands(Package *package, Team *team1, Team *team2, Winsize screenSize) {
  purple();
  printf("Le nombre de crédits d'équipement initiaux par équipe est de : 1000\n");
  resetColor();
  char *command = (char*)malloc(256*sizeof(char));
  int erreur = 0, play = 1;

  while(play) {
    if(play == 2) {
      resetGame(team1, team2, screenSize);
    }
    while((team1->CE > 0) && (team2->CE > 0) && (team1->CE >= package->weapons[0]->CE + package->champions[0]->CE) && (team2->CE >= package->weapons[0]->CE + package->champions[0]->CE)) {
      showTeamsCE(team1, team2);
      printf("> ");
      fgets(command, 256, stdin);
      if((strlen(command) > 0) && (command[strlen(command)-1] == '\n')) command[strlen(command)-1] = '\0';

      // ~~~ Cases ~~~ //
      if(strcmp(command, "exit") == 0) {
        char c;
        int keepPlaying = 0;
        while(!keepPlaying) {
          printf("Voulez-vous vraiment quitter le jeu ? [o/n] ");
          c = getchar();
          if(c == 'o' || c == 'y') {
            free(command);
            exitGame(package, team1, team2);
          } else if(c == 'n') {
            keepPlaying = 1;
          }
        }
        c = getchar(); // without this getchar a '\n' is entered in the next prompt (return a 'command invalid' error)
      }
      else if(strcmp(command, "show vegetables") == 0) showVegetables(package->champions, package->nbChampions);
      else if(strncmp(command, "show vegetable ", 15) == 0) showVegetable(package->champions, package->nbChampions, getID(command, 15));

      else if(strcmp(command, "show fruits") == 0) showFruits(package->champions, package->nbChampions);
      else if(strncmp(command, "show fruit ", 11) == 0) showFruit(package->champions, package->nbChampions, getID(command, 11));

      else if(strcmp(command, "show weapons") == 0) showWeapons(package->weapons, package->nbWeapons, -1);
      else if(strncmp(command, "show weapon ", 12) == 0) showWeapon(package->weapons, package->nbWeapons, getID(command, 12));

      else if(strcmp(command, "show protections") == 0) showProtections(package->protections, package->nbProtections, -1);
      else if(strncmp(command, "show protection ", 16) == 0) showProtection(package->protections, package->nbProtections, getID(command, 16));

      else if(strcmp(command, "show cares") == 0) showCares(package->healings, package->nbHealings, -1);
      else if(strncmp(command, "show care ", 10) == 0) showCare(package->healings, package->nbHealings, getID(command, 10));

      else if(strcmp(command, "show strategies") == 0) showStrategies(package->strategies, package->nbStrategies);
      else if(strncmp(command, "show strategy ", 14) == 0) showStrategy(package->strategies, package->nbStrategies, getID(command, 14));

      else if(strncmp(command, "fight ", 6) == 0) {
        char *command_tmp = substring(command, 6, strlen(command));
        int legume = -1;
        int fruit = -1;
        int strat1 = -1;
        int strat2 = -1;
        int i = 0;
        int versusReached = 0;

        char* strToken = strtok(command_tmp, " ");

        while(strToken != NULL) {
          if((strcmp(strToken, "versus") == 0)) {
            strToken = strtok(NULL, " ");
            versusReached = 1;
            continue;
          }

          /*
            check si le mot est un legume/fruit (id ou nom) ou une strat (id ou nom)
          */
          if(!(isOnlyDigits(strToken))) {
            red();
            printf("Utilisation : fight <legume> <strategie> versus <fruit> <strategie>\n");
            resetColor();
            // free(command_tmp);
            break;
          }

          if(i == 0) {
            legume = atoi(strToken);
          } else if(i == 1 && !versusReached) {
            strat1 = atoi(strToken);
          } else if((i == 2 && strat1 != -1) || (i == 1 && strat1 == -1)) {
            fruit = atoi(strToken);
          } else if((i == 3 || i == 2) && versusReached) {
            strat2 = atoi(strToken);
          }
          
          // next string
          strToken = strtok(NULL, " ");
          i++;
        }

        if(package->nbStrategies == NULL) {
          red();
          printf("Nous n'avez aucune stratégie.\n");
          resetColor();
          free(command_tmp);
          continue;
        } else {
          if(strat1 >= *package->nbStrategies || strat1 < -1) {
            red();
            printf("La stratégie n°%d n'existe pas.\n", strat1);
            resetColor();
            free(command_tmp);
            continue;
          } else if(strat2 >= *package->nbStrategies || strat2 < -1) {
            red();
            printf("La stratégie n°%d n'existe pas.\n", strat2);
            resetColor();
            free(command_tmp);
            continue;
          }
        }

        // test si nbStrategie n'est pas nulle
        if(legume < 0 || fruit < 0 || fruit >= 6 || legume >= 6 || (package->nbStrategies != NULL && (strat1 >= *package->nbStrategies || strat2 >= *package->nbStrategies)) || !versusReached) {
          red();
          printf("Veuillez revoir les paramètres de votre commande.\n");
          resetColor();
          free(command_tmp);
          continue;
        }


        free(command_tmp);

        Strategy *stratTeam1 = (strat1 == -1 ? NULL : package->strategies[strat1]);
        Strategy *stratTeam2 = (strat2 == -1 ? NULL : package->strategies[strat2]);
        printf("strat %d - %d\n", strat1, strat2);
        fight(package->champions[legume], package->champions[fruit+6], package, team1, team2, stratTeam1, stratTeam2, screenSize);
      
      } else if(strcmp(command,"clear") == 0) system("clear");
      else if(strcmp(command, "help") == 0) help();
      else {
        erreur++;
        white();
        if(erreur == 3) {
          printf("Commande '%s' invalide.\n", command);
          help();
          erreur = 0;
        } else {
          printf("Commande '%s' invalide.\n(La commande 'help' permet d'afficher les commandes disponibles)\n", command);
        }
        resetColor();
      }
    }
    play = replay(command);
  }
  free(command);
  exitGame(package, team1, team2);
}
