#include "initGame.h"
#include "commands.h"
#include "fight.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void fightingMode(Team *team, int *end) {
    char *command = malloc(256*sizeof(char));
    
    printf("%s %d> ", team->champion->variete, team->CA);
    fgets(command, 256, stdin);
    // printf("Entered command : %s", command);
    if((strlen(command) > 0) && (command[strlen(command)-1] == '\n')) command[strlen(command)-1] = '\0';

    if(strcmp(command, "show") == 0) printf("je show des trucss lo\n");
    else if(strncmp(command, "move forward ", 13) == 0) printf("move forward %d truc\n", getID(command, 13));
    else if(strncmp(command, "move backward ", 14) == 0) printf("move backward %d truc\n", getID(command, 14));
    else if(strncmp(command, "use weapon ", 11) == 0) printf("use %d weapon lo\n", getID(command, 11));
    else if(strcmp(command, "use protection") == 0) printf("use la protection lo\n");
    else if(strncmp(command, "use care ", 9) == 0) printf("use %d heal lo\n", getID(command, 9));
    else if(strcmp(command, "end") == 0) printf("2 22 mamene !\n"), *end = 1;
    
    free(command);
}
