#include "strat.h"
#include <stdio.h>

int readStrat(Strategy *strategy, char *fileName) {
    fopen(fileName, "r");
    char *buffer = malloc(sizeof(char)* 256);
    
    while(fgets(buffer, 256, fileName)) {
        // On lit toutes les lignes du fichier et on stock dans la structure
    }
    
    fclose(fileName);
    return 0; // Return 0 si tout c'est correctement passé
    return 1; // Return 1 si erreur sur l'extention du fichier
    return 2; // Return 2 si strategie trop chère
    return 3; // Return 3 erreur de lecture du fichier
    return 4; // Return 4 si autre erreur
}

Strategy ** initStrat(int argc, char *argv[]) {
    Strategy **strategy;
    int nbStrategy = 0, read = 0;
    strategy = malloc(sizeof(Strategy *)*nbStrategy);
    for (int i = 1; i < argc; i++) {
        read = readStrat(strategy[nbStrategy], argv[i]);
        if(read == 0) {
            nbStrategy++;
            strategy = realloc(strategy, sizeof(Strategy *)*nbStrategy);
        } else if (read == 1) {
            printf("Erreur, le fichier %s n'est pas un fichier .strat !\n", argv[i]);
        } else if (read == 2) {
            printf("Erreur, la stratégie est trop chère !\n");
        } else if (read == 3) {
            printf("Erreur lors de la lecture du fichier %s. Stratégie ignorée !\n", argv[i]);
        } else if (read == 4) {
            printf("Erreur inconnue !\n");
        }
    }
}