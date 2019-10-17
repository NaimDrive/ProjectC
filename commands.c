#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void showVegetables() {
  printf("%s\n", "show vegetables");
}
void showVegetable(int id) {
  printf("%s\n", "show vegetable i");
}

void showFruits() {
  printf("%s\n", "show fruits");
}

void showFruit(int id) {
  printf("%s\n", "show fruit i");
}

void weapons() {
  printf("%s\n", "show weapons");
}

void weapon(int id) {
  printf("%s\n", "show weapon i");
}

void showProtections() {
  printf("%s\n", "show protections");
}

void showProtection(int id) {
  printf("%s\n", "show protection i");
}

void showCares() {
  printf("%s\n", "show cares");
}

void showCare(int id) {
  printf("%s\n", "show care i");
}

void save() {
  printf("%s\n", "save");
}

void quitGame() {
  exit(0);
}

void readCommands() {
  char *command = (char*)malloc(256*sizeof(char));
  int fakeID = 1;

  while(1) {
    printf("%s", "Veuillez saisir votre commande : ");
    fgets(command, 256, stdin);
    printf("Entered command : %s", command);
    if((strlen(command) > 0) && (command[strlen(command)-1] == '\n')) command[strlen(command)-1] = '\0';

    if(strcmp(command, "quit") == 0) quitGame();
    else if(strcmp(command, "show vegetables") == 0) showVegetables();
    else if(strcmp(command, "show vegetable i") == 0) showVegetables(fakeID);
    else if(strcmp(command, "show fruits") == 0) showFruits();
    else if(strcmp(command, "show fruit i") == 0) showFruit(fakeID);
    else if(strcmp(command, "show weapons") == 0) weapons();
    else if(strcmp(command, "show weapon i") == 0) weapon(fakeID);
    else if(strcmp(command, "show protections") == 0) showProtections();
    else if(strcmp(command, "show protection i") == 0) showProtection(fakeID);
    else if(strcmp(command, "show cares") == 0) showCares();
    else if(strcmp(command, "show care i") == 0) showCare(fakeID);
    else if(strcmp(command, "save") == 0) save();
  }

  free(command);
}

int main(int argc, char *argv[]) {

  readCommands();


  return 0;

}
