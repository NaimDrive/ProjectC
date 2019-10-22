#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* substring(char *src, int beg, int end) {
  int i = beg;
  char *cpy = (char*)malloc(((end-beg)+1)*sizeof(char));

  for(;(*(src+i) != '\0') && i < end; i++) {
    *cpy = *(src+i);
    cpy++;
  }
  *cpy = '\0';

  return cpy - (end-beg);
}

int getID(char *command, int n) {
  char *c = substring(command, n, strlen(command));
  int id = atoi(c);
  free(c);
  return id;
}

void showVegetables() {
  printf("%s\n", "show vegetables");
}
void showVegetable(int id) {
  printf("show vegetable %d\n", id);
}

void showFruits() {
  printf("%s\n", "show fruits");
}

void showFruit(int id) {
  printf("show fruit %d\n", id);
}

void weapons() {
  printf("%s\n", "show weapons");
}

void weapon(int id) {
  printf("show weapon %d\n", id);
}

void showProtections() {
  printf("%s\n", "show protections");
}

void showProtection(int id) {
  printf("show protection %d\n", id);
}

void showCares() {
  printf("%s\n", "show cares");
}

void showCare(int id) {
  printf("show care %d\n", id);
}

void fight(char *command) {
  printf("'Versus' présent ? %d\n", (strstr(command, "versus") != NULL));
}

void save() {
  printf("%s\n", "save");
}

void help() {
  printf("Show every possible command");
}

void quitGame() {
  exit(0);
}

void readCommands() {
  char *command = (char*)malloc(256*sizeof(char));

  while(1) {
    printf("Veuillez saisir votre commande : ");
    fgets(command, 256, stdin);
    printf("Entered command : %s", command);
    if((strlen(command) > 0) && (command[strlen(command)-1] == '\n')) command[strlen(command)-1] = '\0';

    // ~~~ Cases ~~~ //
    if(strcmp(command, "quit") == 0) quitGame();
    else if(strcmp(command, "show vegetables") == 0) showVegetables();
    else if(strncmp(command, "show vegetable ", 15) == 0) {
      // char *c = substring(command, 15, strlen(command));
      // int id = atoi(c);
      showVegetable(getID(command, 15));
    } 

    else if(strcmp(command, "show fruits") == 0) showFruits();
    else if(strncmp(command, "show fruit ", 11) == 0) showFruit(getID(command, 11));

    else if(strcmp(command, "show weapons") == 0) weapons();
    else if(strncmp(command, "show weapon ", 12) == 0) weapon(getID(command, 12));

    else if(strcmp(command, "show protections") == 0) showProtections();
    else if(strcmp(command, "show protection ") == 0) showProtection(getID(command, 16));

    else if(strcmp(command, "show cares") == 0) showCares();
    else if(strcmp(command, "show care ") == 0) showCare(getID(command, 10));

    else if(strncmp(command, "fight ", 6) == 0) {
      fight(substring(command, 6, strlen(command)));
    }

    else if(strcmp(command, "save") == 0) save();
  }

  free(command);
}

int main() {
  readCommands();
  return 0;
}