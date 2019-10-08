#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct champion {
  int num;
  char *variete;
  char *type;
  int force;
  int resistance;
  int PVMax;
  int CE;
} Champion;

Champion createChampion(char *name, int nbChampions) {
  Champion champion;
  if(strcmp(name, "Haricot") == 0) {
    champion.num = nbChampions++;
    champion.variete = "Haricot";
    champion.type = "Légume";
    champion.force = 10;
    champion.resistance = 10;
    champion.PVMax = 40;
    champion.CE = 5;
  } else if (strcmp(name, "Fenouil") == 0)
  {
    champion.num = nbChampions++;
    champion.variete = "Fenouil";
    champion.type = "Légume";
    champion.force = 12;
    champion.resistance = 15;
    champion.PVMax = 40;
    champion.CE = 7;
  } else if (strcmp(name, "Poireau") == 0)
  {
    champion.num = nbChampions++;
    champion.variete = "Poireau";
    champion.type = "Légume";
    champion.force = 15;
    champion.resistance = 20;
    champion.PVMax = 60;
    champion.CE = 10;
  } else if (strcmp(name, "Aubergine") == 0)
  {
    champion.num = nbChampions++;
    champion.variete = "Aubergine";
    champion.type = "Légume";
    champion.force = 20;
    champion.resistance = 20;
    champion.PVMax = 60;
    champion.CE = 15;
  } else if (strcmp(name, "Courgette") == 0)
  {
    champion.num = nbChampions++;
    champion.variete = "Courgette";
    champion.type = "Légume";
    champion.force = 20;
    champion.resistance = 25;
    champion.PVMax = 80;
    champion.CE = 20;
  } else if (strcmp(name, "Carotte") == 0)
  {
    champion.num = nbChampions++;
    champion.variete = "Carotte";
    champion.type = "Légume";
    champion.force = 25;
    champion.resistance = 25;
    champion.PVMax = 80;
    champion.CE = 25;
  } else if (strcmp(name, "Banane") == 0)
  {
    champion.num = nbChampions++;
    champion.variete = "Banane";
    champion.type = "Fruit";
    champion.force = 10;
    champion.resistance = 10;
    champion.PVMax = 40;
    champion.CE = 5;
  } else if (strcmp(name, "Kiwi") == 0)
  {
    champion.num = nbChampions++;
    champion.variete = "Kiwi";
    champion.type = "Fruit";
    champion.force = 12;
    champion.resistance = 15;
    champion.PVMax = 40;
    champion.CE = 7;
  } else if (strcmp(name, "Poire") == 0)
  {
    champion.num = nbChampions++;
    champion.variete = "Poire";
    champion.type = "Fruit";
    champion.force = 15;
    champion.resistance = 20;
    champion.PVMax = 60;
    champion.CE = 10;
  } else if (strcmp(name, "Pomme") == 0)
  {
    champion.num = nbChampions++;
    champion.variete = "Pomme";
    champion.type = "Fruit";
    champion.force = 20;
    champion.resistance = 20;
    champion.PVMax = 60;
    champion.CE = 15;
  } else if (strcmp(name, "Ananas") == 0)
  {
    champion.num = nbChampions++;
    champion.variete = "Ananas";
    champion.type = "Fruit";
    champion.force = 20;
    champion.resistance = 25;
    champion.PVMax = 80;
    champion.CE = 20;
  } else if (strcmp(name, "Durian") == 0)
  {
    champion.num = nbChampions++;
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

void testAfficher(Champion c) {
  printf("Num %d\nVariété %s\nType %s\nForce %d\nResistance %d\nPV Max %d\nCE %d\n", c.num, c.variete, c.type, c.force, c.resistance, c.PVMax, c.CE);
}

int main() {
  Champion champion;
  int nbChampions;

  nbChampions = 0;

  champion = createChampion("Pomme",nbChampions);
  testAfficher(champion);
  return 0;
}
