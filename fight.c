#include "initGame.h"
#include "fight.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


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

void resetCA(Team *team) {
  team->CA = team->maxCA;
}

void buyCA(Team *team, int number) {
  if(team->maxCE - number >= 0 && team->CE >= number) {
    team->CE -= number;
    team->maxCE -= number;
    team->maxCA += number;
  }
}

int buyChampion(Champion *champion, Team *team) {
  if(team->maxCE == 0) {
    printf("%s\n", "Vous avez atteint la limite de CE à dépenser pendant le tour.");
    return 0;
  }
  else if(team->CE - champion->CE < 0) {
    printf("%s\n", "Vous n'avez plus assez de CE pour acheter ce champion.");
    return 0;
  }
  else {
    if(team->maxCE - champion->CE < 0) {
      printf("%s\n", "Vous ne pouvez pas acheter le champion car vous allez dépasser la limite de CE.");
      return 0;
    }
    else {
      if(team->champion != NULL)
        free(team->champion);
      team->champion = createChampion(champion->variete, champion->num);
      team->maxCE -= champion->CE;
      team->CE -= champion->CE;
      printf("Achat du champion %s.\n", team->champion->variete);
      return 1;
    }
  }
}

int buyWeapon(Weapon *weapon, Team *team) {
  if(team->maxCE == 0) {
    printf("%s\n", "Vous avez atteint la limite de CE à dépenser pendant le tour.");
    return 0;
  }
  else if(team->CE - weapon->CE < 0) {
    printf("%s\n", "Vous n'avez plus assez de CE pour acheter cette arme.");
    return 0;
  }
  else {
    if(team->maxCE - weapon->CE < 0) {
      printf("%s\n", "Vous ne pouvez pas acheter l'arme car vous allez dépasser la limite de CE.");
      return 0;
    }
    else {
      if(team->weapon != NULL)
        free(team->weapon);
      team->weapon = createWeapon(weapon->nom, weapon->num);
      team->maxCE -= weapon->CE;
      team->CE -= weapon->CE;
      printf("Achat de l'arme %s.\n", team->weapon->nom);
      return 1;
    }
  }
}

int buyProtection(Protection *protection, Team *team) {
  if(team->maxCE == 0) {
    printf("%s\n", "Vous avez atteint la limite de CE à dépenser pendant le tour.");
    return 0;
  }
  else if(team->CE - protection->CE < 0) {
    printf("%s\n", "Vous n'avez plus assez de CE pour acheter cette protection.");
    return 0;
  }
  else {
    if(team->maxCE - protection->CE < 0) {
      printf("%s\n", "Vous ne pouvez pas acheter la protection car vous allez dépasser la limite de CE.");
      return 0;
    }
    else {
      if(team->protection != NULL)
        free(team->protection);
      team->protection = createProtection(protection->nom, protection->num);
      team->maxCE -= protection->CE;
      team->CE -= protection->CE;
      printf("Achat de la protection %s.\n", team->protection->nom);
      return 1;
    }
  }
}

int buyHealing(Healing *healing, Team *team) {
  if(team->maxCE == 0) {
    printf("%s\n", "Vous avez atteint la limite de CE à dépenser pendant le tour.");
    return 0;
  }
  else if(team->CE - healing->CE < 0) {
    printf("%s\n", "Vous n'avez plus assez de CE pour acheter ce soin.");
    return 0;
  }
  else {
    if(team->maxCE - healing->CE < 0) {
      printf("%s\n", "Vous ne pouvez pas acheter le soin car vous allez dépasser la limite de CE.");
      return 0;
    }
    else {
      if(team->healing != NULL)
        free(team->healing);
      team->healing = createHealing(healing->nom, healing->num);
      team->maxCE -= healing->CE;
      team->CE -= healing->CE;
      printf("Achat du soin %s.\n", team->healing->nom);
      return 1;
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
      if(team->position == 1) {
        printf("Vous ne pouvez pas reculer plus.\n");
      } else {
        if(team->position-n < 1) {
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
      if(team->position == maxX-2) {
        printf("Vous ne pouvez pas reculer plus.\n");
      } else {
        if(team->position+n > maxX-2) {
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

int useWeapon(Team *team1, Team *team2, int n) {
  int i, damage, CALost, totalDamage, successAttack, protectionCounter;
  float dmg, strength, resistance, weapon;

  damage = 0;
  CALost = 0;
  totalDamage = 0;
  successAttack = 0;
  protectionCounter = 0;

  if(n > 0) {
    if(team1->champion == NULL || team2->champion == NULL || team1->weapon == NULL) {
      printf("Attaque impossible. Vérifiez que les deux équipes ont un champion et une arme.\n");
    } else {
      if(team1->weapon->CA * n > team1->CA) {
        printf("Pas assez de crédit d'action pour utiliser %d fois l'arme.\n", n);
      } else {
        for(i = 0 ; i < n && team2->champion->PV > 0 ; i++) {
          CALost += team1->weapon->CA;

          if(distanceBetweenChampions(team1, team2) <= team1->weapon->portee) {
            successAttack = 1;
            if(team2->protectionActivated && team2->protection != NULL) {
              if(effectiveProtection(team2->protection->probabilite) == 1) {
                protectionCounter++;
                continue;
              }
            }

            strength = 100 + team1->champion->force;
            weapon = weaponDamage(team1->weapon);
            dmg = weapon * (strength / 100);
            resistance = 100 - team2->champion->resistance;
            dmg = dmg * (resistance / 100);
            damage = dmg + 0.5;
            totalDamage += damage;
          }
        }
        printf("%s perd %d crédits d'attaques.\n", team1->champion->variete, CALost);
        team1->CA -= CALost;

        if(!successAttack) {
          printf("Impossible d'attaquer, le champion est trop loin !\n");
        } else {
          if(protectionCounter > 0) {
            printf("La protection a contré %d attaques !\n", protectionCounter);
          }
          if(totalDamage > team2->champion->PV) {
            team2->champion->PV = 0;
            printf("Vous avez tué %s.\n", team2->champion->variete);
          } else {
            team2->champion->PV -= totalDamage;
            printf("%s perd %d points de vie. Il reste %d points de vie.\n", team2->champion->variete, totalDamage, team2->champion->PV);
          }
        }
      }
    }
  }
  else {
    printf("Vous ne pouvez attaquer avec un nombre négatif.\n");
  }
  return successAttack;
}

void useProtection(Team *team) {
  if(team->weapon != NULL) {
    if(team->CA < team->protection->CA) {
      printf("Vous n'avez pas assez de CA pour activer la protection.\n");
    } else {
      team->CA -= team->protection->CA;
      team->protectionActivated = 1;
      printf("La protection %s est désormais active pendant 1 tour.\n", team->protection->nom);
    }
  }
}

int randHeal(Healing *healing) {
  return (rand() % (healing->effetMin - healing->effetMax + 1)) + healing->effetMin;
}

void useCare(Team *team, int n) {
  int i, soin, totalSoin, CALost;

  totalSoin = 0;
  CALost = 0;

  if(n > 0) {
    if(team->healing == NULL) {
      printf("Vous n'avez aucune potion à utiliser.\n");
    } else {
      if(team->healing->volume < n) {
        printf("Vous n'avez pas assez de %s pour vous soigner %d fois \n", team->healing->nom, n);
      } else {
        if(team->CA < team->healing->CA * n) {
          printf("Vous n'avez pas assez de CA pour vous soignez %d fois.\n", n);
        } else {
          for (i = 0; i < n; i++) {
            soin = randHeal(team->healing);
            totalSoin += soin;
            CALost += team->healing->CA;
            team->healing->volume--;
          }
          printf("%s perd %d crédits d'attaques.\n", team->champion->variete, CALost);
          team->CA -= CALost;

          if(team->champion->PV + totalSoin > team->champion->PVMax) {
            team->champion->PV = team->champion->PVMax;
            printf("%s a récupéré tous ses points de vie.\n", team->champion->variete);
          }
          else {
            team->champion->PV += totalSoin;
            printf("%s a récupéré %d points de vie. Il reste %d points de vie.\n", team->champion->variete, totalSoin, team->champion->PV);
          }

          if(team->healing->volume == 0) {
            printf("Vous avez utilisé tous vos soins.\n");
          }
        }
      }
    }
  }
}

int distanceBetweenChampions(Team *team1, Team *team2) {
  if(team1->id == 0)
    return team2->position - team1->position;
  else
    return -(team2->position - team1->position);
}
