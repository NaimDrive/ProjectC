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
  printf("%s\n", "show vegetable i");
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

void quitGame() {
  exit(0);
}

void readCommands() {
  char *command = (char*)malloc(255*sizeof(char));
  while(1) {
    printf("%s", "Veuillez saisir votre commande : ");
    scanf("%s", command);
    printf("Entered command : '%s'\n", command);
    if(strcmp(command, "quit") == 0) quitGame();
  }

  // free(command);
}

int main(int argc, char *argv[]) {

  readCommands();

  return 0;

}
