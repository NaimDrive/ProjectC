#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#define MAX_FILES_LENGTH 128


typedef struct champion {
  int num;
  char *variete;
  char *type;
  int force;
  int resistance;
  int PVMax;
  int CE;
} Champion;

typedef struct arme{
  int num;
  char *nom;
  int CE;
  int CA;
  int degats;
  int portee;
} Arme;

typedef struct protection{
  int num;
  char *nom;
  int CE;
  int CA;
  int probabilite;
} Protection;

typedef struct soins{
  int num;
  char *nom;
  int CE;
  int CA;
  int volume;
  int effet;
} Soins;



int testCreateChampion() {
  FILE * fichier = NULL;
  char * buffer, *tmp; /* Tableau dans lequel on stocke la ligne du fichier  */
  int nbSeparateur;
  Champion *champion;

  fichier = fopen("champions.csv", "r");

  /* Si l'ouverture du fichier s'est bien passé */
  if(fichier == NULL) {
    fprintf(stderr, "Cannot load champions file");
    exit(20);
  }

  buffer = malloc(MAX_FILES_LENGTH);
  tmp = buffer;

  /* Tant qu'il reste un caractète à lire dans le fichier */
  while(!feof(fichier)) {
    fgets(buffer, MAX_FILES_LENGTH, fichier);
    tmp = buffer;

    /* Si il y a eu une erreur lors de la lecture du fichier */
    if(ferror(fichier)) {
      fprintf(stderr, "Reading error with code %d\n", errno);
      break;
    }

    champion = malloc(sizeof(Champion));
    nbSeparateur = 0;

    while(*tmp != '\0') {
      if(*tmp == ',') {
        nbSeparateur++;
        printf("Séparateur %d\n", nbSeparateur);
      } else {
        if(nbSeparateur == 0) {
          printf("Num %d\n", atoi(tmp));
        }
        
      }
      tmp++;
    }

    buffer[0] = '\0';
  }
  
  free(buffer);
  fclose(fichier);
  return 0;
}


/*
  Create and return a new champion.
  @Param the champion name and the current champion number.
  @Return the new champion.
*/
Champion * createChampion(char *name, int *nbChampions) {
  Champion *champion;
  champion = malloc(sizeof(champion));

  if(strcmp(name, "Haricot") == 0) {
    (*champion).num = (*nbChampions)++;
    (*champion).variete = "Haricot";
    (*champion).type = "Légume";
    (*champion).force = 10;
    (*champion).resistance = 10;
    (*champion).PVMax = 40;
    (*champion).CE = 5;
  } else if (strcmp(name, "Fenouil") == 0)
  {
    (*champion).num = (*nbChampions)++;
    (*champion).variete = "Fenouil";
    (*champion).type = "Légume";
    (*champion).force = 12;
    (*champion).resistance = 15;
    (*champion).PVMax = 40;
    (*champion).CE = 7;
  } /*else if (strcmp(name, "Poireau") == 0)
  {
    champion.num = (*nbChampions)++;
    champion.variete = "Poireau";
    champion.type = "Légume";
    champion.force = 15;
    champion.resistance = 20;
    champion.PVMax = 60;
    champion.CE = 10;
  } else if (strcmp(name, "Aubergine") == 0)
  {
    champion.num = (*nbChampions)++;
    champion.variete = "Aubergine";
    champion.type = "Légume";
    champion.force = 20;
    champion.resistance = 20;
    champion.PVMax = 60;
    champion.CE = 15;
  } else if (strcmp(name, "Courgette") == 0)
  {
    champion.num = (*nbChampions)++;
    champion.variete = "Courgette";
    champion.type = "Légume";
    champion.force = 20;
    champion.resistance = 25;
    champion.PVMax = 80;
    champion.CE = 20;
  } else if (strcmp(name, "Carotte") == 0)
  {
    champion.num = (*nbChampions)++;
    champion.variete = "Carotte";
    champion.type = "Légume";
    champion.force = 25;
    champion.resistance = 25;
    champion.PVMax = 80;
    champion.CE = 25;
  } else if (strcmp(name, "Banane") == 0)
  {
    champion.num = (*nbChampions)++;
    champion.variete = "Banane";
    champion.type = "Fruit";
    champion.force = 10;
    champion.resistance = 10;
    champion.PVMax = 40;
    champion.CE = 5;
  } else if (strcmp(name, "Kiwi") == 0)
  {
    champion.num = (*nbChampions)++;
    champion.variete = "Kiwi";
    champion.type = "Fruit";
    champion.force = 12;
    champion.resistance = 15;
    champion.PVMax = 40;
    champion.CE = 7;
  } else if (strcmp(name, "Poire") == 0)
  {
    champion.num = (*nbChampions)++;
    champion.variete = "Poire";
    champion.type = "Fruit";
    champion.force = 15;
    champion.resistance = 20;
    champion.PVMax = 60;
    champion.CE = 10;
  } else if (strcmp(name, "Pomme") == 0)
  {
    champion.num = (*nbChampions)++;
    champion.variete = "Pomme";
    champion.type = "Fruit";
    champion.force = 20;
    champion.resistance = 20;
    champion.PVMax = 60;
    champion.CE = 15;
  } else if (strcmp(name, "Ananas") == 0)
  {
    champion.num = (*nbChampions)++;
    champion.variete = "Ananas";
    champion.type = "Fruit";
    champion.force = 20;
    champion.resistance = 25;
    champion.PVMax = 80;
    champion.CE = 20;
  } else if (strcmp(name, "Durian") == 0)
  {
    champion.num = (*nbChampions)++;
    champion.variete = "Durian";
    champion.type = "Fruit";
    champion.force = 25;
    champion.resistance = 25;
    champion.PVMax = 80;
    champion.CE = 25;
  } */else {
    fprintf(stderr, "Champion name error\n");
    exit(1);
  }
  return champion;
}

Champion * initChampions(char *nom, int *nbChampions) {
  return createChampion(nom, nbChampions);
}

void testAfficher(Champion *c) {
  printf("Num %d\nVariété %s\nType %s\nForce %d\nResistance %d\nPV Max %d\nCE %d\n\n", c->num, c->variete, c->type, c->force, c->resistance, c->PVMax, c->CE);
}


void initGame(int n, int *nbChampions) {
}

int main() {
  int p;
  p = testCreateChampion();
  printf("Code retour fonction %d\n", p);
  return 0;
}
