#include <stdio.h>
#include <stdlib.h>

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
  printf("%s\n", "exit");
}

void readCommands() {
  char *command;
  printf("%s", "Veuillez saisir votre commande : ");
  scanf("%s", command);
  //printf("Entered command : '%s'\n", command);

  // free(command);
}

int main(int argc, char *argv[]) {
  /*int i = 1;
  while(i <= 2) {
    readCommands();
    i++;
  }*/
  readCommands();

  return 0;

}
