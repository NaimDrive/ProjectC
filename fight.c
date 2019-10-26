#include "initGame.h"
#include "fight.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

Team * initTeam(int id) {
  Team *team;
  team = malloc(sizeof(Team));
  team->id = id;
  if(id == 0)
    team->position = 0;
  else
    team->position = 5;
  team->CE = 1000;
  team->CA = 0;
  team->maxCE = 50;
  team->champion = NULL;
  team->weapon = NULL;
  team->protection = NULL;
  team->healing = NULL;
  team->protectionActivated = 0;

  return team;
}

void maxCE(Team *team1, Team *team2) {
  if(team1->CE >= 50 && team2->CE >= 50) {
    team1->maxCE = 50;
    team2->maxCE = 50;
  } else {
    if(team1->CE >= team2->CE) {
      team1->maxCE = team2->CE;
      team2->maxCE = team2->CE;
    } else {
      team1->maxCE = team1->CE;
      team2->maxCE = team1->CE;
    }
  }
}

void buyCA(Team *team, int number) {
  if(team->maxCE - number >= 0 && team->CE >= number) {
    team->CE -= number;
    team->maxCE -= number;
    team->CA += number;
  }
}

void buyChampion(Champion *champion, Team *team) {
  if(team->maxCE == 0)
    printf("%s\n", "Vous avez atteint la limite de CE à dépenser pendant le tour.");
  else {
    if(team->maxCE - champion->CE < 0)
      printf("%s\n", "Vous ne pouvez pas acheter le champion car vous allez dépasser la limite de CE.");
    else {
      if(team->champion != NULL)
        free(team->champion);
      team->champion = createChampion(champion->variete, champion->num);
      team->maxCE -= champion->CE;
      team->CE -= champion->CE;
      printf("Achat du champion %s.\n", team->champion->variete);
    }
  }
}

void buyWeapon(Weapon *weapon, Team *team) {
  if(team->maxCE == 0)
    printf("%s\n", "Vous avez atteint la limite de CE à dépenser pendant le tour.");
  else {
    if(team->maxCE - weapon->CE < 0)
      printf("%s\n", "Vous ne pouvez pas acheter le champion car vous allez dépasser la limite de CE.");
    else {
      if(team->weapon != NULL)
        free(team->weapon);
      team->weapon = createWeapon(weapon->nom, weapon->num);
      team->maxCE -= weapon->CE;
      team->CE -= weapon->CE;
      printf("Achat de l'arme %s.\n", team->weapon->nom);
    }
  }
}

void buyProtection(Protection *protection, Team *team, int maxCE) {
  if(team->maxCE == 0)
    printf("%s\n", "Vous avez atteint la limite de CE à dépenser pendant le tour.");
  else {
    if(team->maxCE - protection->CE < 0)
      printf("%s\n", "Vous ne pouvez pas acheter le champion car vous allez dépasser la limite de CE.");
    else {
      if(team->protection != NULL)
        free(team->protection);
      team->protection = createProtection(protection->nom, protection->num);
      team->maxCE -= protection->CE;
      team->CE -= protection->CE;
      printf("Achat de la protection %s.\n", team->protection->nom);
    }
  }
}

void buyHealing(Healing *healing, Team *team, int maxCE) {
  if(team->maxCE == 0)
    printf("%s\n", "Vous avez atteint la limite de CE à dépenser pendant le tour.");
  else {
    if(team->maxCE - healing->CE < 0)
      printf("%s\n", "Vous ne pouvez pas acheter le champion car vous allez dépasser la limite de CE.");
    else {
      if(team->healing != NULL)
        free(team->healing);
      team->healing = createHealing(healing->nom, healing->num);
      team->maxCE -= healing->CE;
      team->CE -= healing->CE;
      printf("Achat du soin %s.\n", team->healing->nom);
    }
  }
}

void moveForward(Team *team1, Team *team2, int n) {
  if(n > 0) {
    if(team1->id == 0) {
      if(team1->position+1 == team2->position) {
        printf("Vous êtes déjà au plus près du champion ennemie.\n");
      } else {
        if(team1->position+n >= team2->position) {
          printf("Vous ne pouvez pas avancer de %d cases car vous allez dépasser le champion ennemie.\n", n);
        } else {
          if(team1->CA < n) {
            printf("Vous n'avez pas assez de CA pour avancer de %d cases.\n", n);
          } else {
            team1->position+=n;
            team1->CA-=n;
            printf("Vous avancez de %d cases.\n", n);
          }
        }
      }
    } else {
      if(team1->position-1 == team2->position) {
        printf("Vous êtes déjà au plus près du champion ennemie.\n");
      } else {
        if(team1->position-n <= team2->position) {
          printf("Vous ne pouvez pas avancer de %d cases car vous allez dépasser le champion ennemie.\n", n);
        } else {
          if(team1->CA < n) {
            printf("Vous n'avez pas assez de CA pour avancer de %d cases.\n", n);
          } else {
            team1->position-=n;
            team1->CA-=n;
            printf("Vous avancez de %d cases.\n", n);
          }
        }
      }
    }
  }
}

void moveBackward(Team *team, int n, int maxX) {
  if(n > 0) {
    if(team->id == 0) {
      if(team->position == 0) {
        printf("Vous ne pouvez pas reculer plus.\n");
      } else {
        if(team->position-n < 0) {
          printf("Vous ne pouvez pas reculer de %d cases.\n", n);
        } else {
          if(team->CA < (n*2)) {
            printf("Vous n'avez pas assez de CA pour reculer de %d cases.\n", n);
          } else {
            team->position-=n;
            team->CA-=(n*2);
            printf("Vous reculez de %d cases.\n", n);
          }
        }
      }
    } else {
      if(team->position == maxX) {
        printf("Vous ne pouvez pas reculer plus.\n");
      } else {
        if(team->position+n > maxX) {
          printf("Vous ne pouvez pas reculer de %d cases.\n", n);
        } else {
          if(team->CA < (n*2)) {
            printf("Vous n'avez pas assez de CA pour reculer de %d cases.\n", n);
          } else {
            team->position+=n;
            team->CA-=(n*2);
            printf("Vous reculez de %d cases.\n", n);
          }
        }
      }
    }
  }
}

int weaponDamage(Weapon *weapon) {
    return (rand() % (weapon->degatsMax - weapon->degatsMin + 1)) + weapon->degatsMin;
}

int effectiveProtection(int protection) {
    int res = (rand() % 100) + 1;
    if(res <= protection)
      return 1;
    return 0;
}

void useWeapon(Team *team1, Team *team2, int n) {
  int i, damage;
  float dmg, strength, resistance, weapon;
  if(team1->champion == NULL || team2->champion == NULL || team1->weapon == NULL || n > 0) {

    if(team1->weapon->CA * n > team1->CA) {
      printf("Pas assez de crédit d'action pour utiliser %d fois l'arme.\n", n);
    } else {
      for(i = 0 ; i < n && team2->champion->PV > 0 ; i++) {
        team1->CA -= team1->weapon->CA;
        printf("L'attaquant perd %d crédits d'attaques.\n", team1->weapon->CA);

        if(distanceBetweenChampions(team1, team2) <= team1->weapon->portee) {
          if(team2->protectionActivated && team2->protection != NULL) {
            if(effectiveProtection(team2->protection->probabilite) == 1) {
              printf("La protection a contré l'attaque !\n");
              continue;
            }
          }

          strength = 100 + team1->champion->force;
          weapon = weaponDamage(team1->weapon);
          dmg = weapon * (strength / 100);
          resistance = 100 - team2->champion->resistance;
          dmg = dmg * (resistance / 100);
          damage = dmg + 0.5;

          if(damage > team2->champion->PV) {
            printf("Le défenseur perd %d points de vie.\n", damage - team2->champion->PV);
            team2->champion->PV = 0;
          } else {
            printf("Le défenseur perd %d points de vie.\n", damage);
            team2->champion->PV -= damage;
          }
          printf("Il reste %d points de vie.\n", team2->champion->PV);
        } else {
          printf("Impossible d'attaquer, le champion est trop loin !\n");
          break;
        }
      }
    }
  } else {
    printf("Attaque impossible. Vérifiez que les deux équipes ont un champion et une arme.\n");
  }
}

void useProtection(Team *team) {
  if(team->weapon != NULL) {
    if(team->CA < team->protection->CA) {
      printf("Vous n'avez pas assez de CA pour activer la protection.\n");
    } else {
      team->protectionActivated = 1;
      printf("La protection %s est désormais active pendant 1 tour.\n", team->weapon->nom);
    }
  }
}

int randHeal(Healing *healing) {
  return (rand() % (healing->effetMin - healing->effetMax + 1)) + healing->effetMin;
}

void useCare(Team *team, int n) {
  if(team->healing == NULL) {
    printf("Vous n'avez aucune potion à utiliser.\n");
  } else {
    if(team->healing->volume < n) {
      printf("Vous n'avez pas assez de %s pour vous soigner %d fois \n", team->healing->nom, n);
    } else {
      if(team->CA < team->healing->CA * n) {
        printf("Vous n'avez pas assez de CA pour vous soignez %d fois.\n", n);
      } else {
        int soin;
        for (int i = 0; i < n; i++) {
          soin = randHeal(team->healing);
          team->CA -= team->healing->CA;
          team->healing->volume--;
          if(team->champion->PV + soin > team->champion->PVMax)
            team->champion->PV = team->champion->PVMax;
          else
            team->champion->PV += soin;
        }
        printf("Le champion %s a été soigné.\n", team->champion->variete);
        if(team->healing->volume == 0) {
          printf("Vous avez utilisé tous vos soins.\n");
          free(team->healing);
          team->healing = NULL;
        }
      }
    }
  }
}

int distanceBetweenChampions(Team *team1, Team *team2) {
  return team2->position - team1->position;
}

void endBattle(Team *team1, Team *team2) {
  free(team1->champion);
  free(team1->weapon);
  free(team1->protection);
  free(team1->healing);
  free(team1);

  free(team2->champion);
  free(team2->weapon);
  free(team2->protection);
  free(team2->healing);
  free(team2);
}