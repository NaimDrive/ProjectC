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



Champion ** testCreateChampion() {
  FILE * fichier = NULL;
  Champion **champions, *champion;
  char *buffer, *ptBuffer, *chaine;
  int nbSeparateur, tailleChaine, tailleChampions, posChaine;

  champions = malloc(sizeof(Champion *));
  printf("  Malloc champions\n");
  tailleChampions = 1;

  fichier = fopen("champions.csv", "r");

  /* Si l'ouverture du fichier s'est bien passé */
  if(fichier == NULL) {
    fprintf(stderr, "Cannot load champions.csv file\n");
    exit(20);
  }

  buffer = malloc(MAX_FILES_LENGTH);
  printf("  Malloc buffer\n");

  /* Tant qu'il reste un caractète à lire dans le fichier */
  while(!feof(fichier)) {
    fgets(buffer, MAX_FILES_LENGTH, fichier);
    ptBuffer = buffer;

    /* Si il y a eu une erreur lors de la lecture du fichier */
    if(ferror(fichier)) {
      fprintf(stderr, "Reading error with code %d\n", errno);
      break;
    }

    champion = malloc(sizeof(Champion));
    printf("Malloc un petit champion\n");

    tailleChaine = 1;

    chaine = malloc(sizeof(char)*tailleChaine);
    printf("Malloc chaine variété\n");

    posChaine = 0;
    nbSeparateur = 0;

    while(*ptBuffer != '\0') {
      if(*ptBuffer == ',') {
        nbSeparateur++;
      } else {
        if(nbSeparateur == 0) {
          champion->num = atoi(ptBuffer);
        } else if (nbSeparateur == 1) {

          chaine = realloc(chaine, sizeof(char)*++tailleChaine);
          printf("Realloc chaine variété\n");
          chaine[posChaine++] = *ptBuffer;
        }
      }
      ptBuffer++;
    }
    chaine[posChaine] = '\0';
    *buffer = '\0';
    if(strcmp(chaine,"\0")) {
      tailleChampions++;
      champions = realloc(champions, sizeof(Champion *) * tailleChampions);
      printf("  Realloc champions\n");
      champions[tailleChampions-1] = champion;

      champions[tailleChampions-1]->variete = chaine;
      printf("MA CHIENNE DE CARACTERE %s\n",chaine);
      printf("ENCORE MA CHIENNE DE CARACTERE %s\n",champions[tailleChampions-1]->variete);
    } else {
      free(chaine);
    }
  }
  champions[tailleChampions-1] = NULL;

  free(buffer);
  printf("  Free Buffer\n");
  fclose(fichier);
  return champions;
}

/*
  Create and return a new champion.
  @Param the champion name and the current champion number.
  @Return the new champion.
*/
/*
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
  } else if (strcmp(name, "Poireau") == 0)
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
  } else {
    fprintf(stderr, "Champion name error\n");
    exit(1);
  }
  return champion;
}

Champion * initChampions(char *nom, int *nbChampions) {
  return createChampion(nom, nbChampions);
}*/

void testAfficher(Champion *c) {
  /*
  printf("Num %d\nVariété %s\nType %s\nForce %d\nResistance %d\nPV Max %d\nCE %d\n\n", c->num, c->variete, c->type, c->force, c->resistance, c->PVMax, c->CE);
  */
  printf("Num %d\nVariété %s\n\n", c->num, c->variete);

}


void initGame(int n, int *nbChampions) {
}

int main() {
  Champion **champions;
  int i;
  champions = testCreateChampion();

  for (i = 0; champions[i] != NULL; i++) {
    free(champions[i]->variete);
    printf("Free variété\n");
    free(champions[i]);
    printf("Free un petit champion\n");
  }

  free(champions);
  printf("  Free champions\n");
  return 0;
}
