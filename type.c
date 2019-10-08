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

void createChampion(char *name, int nbChampions) {
  Champion champion;
  if(strcmp(name, "test") == 0) {
    printf("%s\n", "OK");
  } else {
    printf("%s\n", "Pas ok");
  }

}

int main() {
  int nbChampions;
  nbChampions = 0;
  createChampion("test",nbChampions);
  return 0;
}
