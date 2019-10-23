#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "initGame.h"

Champion * createChampion(char *name, int nbChampions) {
  Champion *champion;
  int sizeType;

  if(strcmp("Haricot", name) == 0) {
    champion = malloc(sizeof(Champion));
    sizeType = strlen("Légume");
    champion->type = malloc(sizeof(char) * (sizeType));
    strcpy(champion->type, "Légume");

    champion->num = nbChampions;
    champion->variete = name;
    champion->force = 10;
    champion->resistance = 10;
    champion->PVMax = 40;
    champion->CE = 5;
  } else if (strcmp(name, "Fenouil") == 0) {
    champion = malloc(sizeof(Champion));
    sizeType = strlen("Légume");
    champion->type = malloc(sizeof(char) * (sizeType));
    strcpy(champion->type, "Légume");

    champion->num = nbChampions;
    champion->variete = name;
    champion->force = 12;
    champion->resistance = 15;
    champion->PVMax = 40;
    champion->CE = 7;
  } else if (strcmp(name, "Poireau") == 0) {
    champion = malloc(sizeof(Champion));
    sizeType = strlen("Légume");
    champion->type = malloc(sizeof(char) * (sizeType));
    strcpy(champion->type, "Légume");

    champion->num = nbChampions;
    champion->variete = name;
    champion->force = 15;
    champion->resistance = 20;
    champion->PVMax = 60;
    champion->CE = 10;
  } else if (strcmp(name, "Aubergine") == 0) {
    champion = malloc(sizeof(Champion));
    sizeType = strlen("Légume");
    champion->type = malloc(sizeof(char) * (sizeType));
    strcpy(champion->type, "Légume");

    champion->num = nbChampions;
    champion->variete = name;
    champion->force = 20;
    champion->resistance = 20;
    champion->PVMax = 60;
    champion->CE = 15;
  } else if (strcmp(name, "Courgette") == 0) {
    champion = malloc(sizeof(Champion));
    sizeType = strlen("Légume");
    champion->type = malloc(sizeof(char) * (sizeType));
    strcpy(champion->type, "Légume");
    
    champion->num = nbChampions;
    champion->variete = name;
    champion->force = 20;
    champion->resistance = 25;
    champion->PVMax = 80;
    champion->CE = 20;
  } else if (strcmp(name, "Carotte") == 0) {
    champion = malloc(sizeof(Champion));
    sizeType = strlen("Légume");
    champion->type = malloc(sizeof(char) * (sizeType));
    strcpy(champion->type, "Légume");
    
    champion->num = nbChampions;
    champion->variete = name;
    champion->force = 25;
    champion->resistance = 25;
    champion->PVMax = 80;
    champion->CE = 25;
  } else if (strcmp(name, "Banane") == 0) {
    champion = malloc(sizeof(Champion));
    sizeType = strlen("Légume");
    champion->type = malloc(sizeof(char) * (sizeType));
    strcpy(champion->type, "Légume");
    
    champion->num = nbChampions;
    champion->variete = name;
    champion->force = 10;
    champion->resistance = 10;
    champion->PVMax = 40;
    champion->CE = 5;
  } else if (strcmp(name, "Kiwi") == 0) {
    champion = malloc(sizeof(Champion));
    sizeType = strlen("Fruit");
    champion->type = malloc(sizeof(char) * (sizeType));
    strcpy(champion->type, "Fruit");
    
    champion->num = nbChampions;
    champion->variete = name;
    champion->force = 12;
    champion->resistance = 15;
    champion->PVMax = 40;
    champion->CE = 7;
  } else if (strcmp(name, "Poire") == 0) {
    champion = malloc(sizeof(Champion));
    sizeType = strlen("Fruit");
    champion->type = malloc(sizeof(char) * (sizeType));
    strcpy(champion->type, "Fruit");
    
    champion->num = nbChampions;
    champion->variete = name;
    champion->force = 15;
    champion->resistance = 20;
    champion->PVMax = 60;
    champion->CE = 10;
  } else if (strcmp(name, "Pomme") == 0) {
    champion = malloc(sizeof(Champion));
    sizeType = strlen("Fruit");
    champion->type = malloc(sizeof(char) * (sizeType));
    strcpy(champion->type, "Fruit");
    
    champion->num = nbChampions;
    champion->variete = name;
    champion->force = 20;
    champion->resistance = 20;
    champion->PVMax = 60;
    champion->CE = 15;
  } else if (strcmp(name, "Ananas") == 0) {
    champion = malloc(sizeof(Champion));
    sizeType = strlen("Fruit");
    champion->type = malloc(sizeof(char) * (sizeType));
    strcpy(champion->type, "Fruit");
    
    champion->num = nbChampions;
    champion->variete = name;
    champion->force = 20;
    champion->resistance = 25;
    champion->PVMax = 80;
    champion->CE = 20;
  } else if (strcmp(name, "Durian") == 0) {
    champion = malloc(sizeof(Champion));
    sizeType = strlen("Fruit");
    champion->type = malloc(sizeof(char) * (sizeType));
    strcpy(champion->type, "Fruit");
    
    champion->num = nbChampions;
    champion->variete = name;
    champion->force = 25;
    champion->resistance = 25;
    champion->PVMax = 80;
    champion->CE = 25;
  } else {
    fprintf(stderr, "Champion name error\n");
    exit(1);
  }

  return champion;
}

Weapon * createWeapon(char *name, int nbWeapons) {
    Weapon *weapon;

    if(strcmp("Eplucheur Laser", name) == 0) {
        weapon = malloc(sizeof(Weapon));

        weapon->num = nbWeapons;
        weapon->nom = name;
        weapon->CE = 2;
        weapon->CA = 1;
        weapon->degatsMin = 1;
        weapon->degatsMax = 2;
        weapon->portee = 2;
    } else if(strcmp("Mandoline Sonique", name) == 0) {
        weapon = malloc(sizeof(Weapon));

        weapon->num = nbWeapons;
        weapon->nom = name;
        weapon->CE = 5;
        weapon->CA = 3;
        weapon->degatsMin = 1;
        weapon->degatsMax = 3;
        weapon->portee = 3;
    } else if(strcmp("Couperet Laser", name) == 0) {
        weapon = malloc(sizeof(Weapon));

        weapon->num = nbWeapons;
        weapon->nom = name;
        weapon->CE = 10;
        weapon->CA = 5;
        weapon->degatsMin = 2;
        weapon->degatsMax = 6;
        weapon->portee = 5;
    } else if(strcmp("Hachoir Neuronique", name) == 0) {
        weapon = malloc(sizeof(Weapon));

        weapon->num = nbWeapons;
        weapon->nom = name;
        weapon->CE = 20;
        weapon->CA = 7;
        weapon->degatsMin = 4;
        weapon->degatsMax = 9;
        weapon->portee = 7;
    } else if(strcmp("Mixeur Blaster", name) == 0) {
        weapon = malloc(sizeof(Weapon));

        weapon->num = nbWeapons;
        weapon->nom = name;
        weapon->CE = 30;
        weapon->CA = 10;
        weapon->degatsMin = 7;
        weapon->degatsMax = 12;
        weapon->portee = 11;
    } else {
        fprintf(stderr, "Weapon name error\n");
        exit(2);
    }

  return weapon;
}

Protection * createProtection(char *name, int nbProtection) {
    Protection *protection;

    if(strcmp("Casque-Egouttoir", name) == 0) {
        protection = malloc(sizeof(Protection));

        protection->num = nbProtection;
        protection->nom = name;
        protection->CE = 1;
        protection->CA = 2;
        protection->probabilite = 25;
    } else if(strcmp("Casque-Entonnoir", name) == 0) {
        protection = malloc(sizeof(Protection));

        protection->num = nbProtection;
        protection->nom = name;
        protection->CE = 3;
        protection->CA = 4;
        protection->probabilite = 40;
    } else if(strcmp("Woklier", name) == 0) {
        protection = malloc(sizeof(Protection));

        protection->num = nbProtection;
        protection->nom = name;
        protection->CE = 5;
        protection->CA = 6;
        protection->probabilite = 60;
    } else if(strcmp("Tablier-Armure", name) == 0) {
        protection = malloc(sizeof(Protection));

        protection->num = nbProtection;
        protection->nom = name;
        protection->CE = 10;
        protection->CA = 8;
        protection->probabilite = 80;
    } else {
        fprintf(stderr, "Protection name error\n");
        exit(3);
    }

    return protection;
}

Healing * createHealing(char *name, int nbHealings){
    Healing *healing;

    if(strcmp("Humus-Neutronique", name) == 0) {
        healing = malloc(sizeof(Healing));

        healing->num = nbHealings;
        healing->nom = name;
        healing->CE = 1;
        healing->CA = 5;
        healing->volume = 4;
        healing->effetMin = 2;
        healing->effetMax = 4;
    } else if(strcmp("Compost-Protonique", name) == 0) {
        healing = malloc(sizeof(Healing));

        healing->num = nbHealings;
        healing->nom = name;
        healing->CE = 5;
        healing->CA = 10;
        healing->volume = 3;
        healing->effetMin = 5;
        healing->effetMax = 8;
    } else if(strcmp("Engrais-Ionique", name) == 0) {
        healing = malloc(sizeof(Healing));

        healing->num = nbHealings;
        healing->nom = name;
        healing->CE = 7;
        healing->CA = 15;
        healing->volume = 2;
        healing->effetMin = 8;
        healing->effetMax = 12;
    } else {
        fprintf(stderr, "Healing name error\n");
        exit(4);
    }

    return healing;
}

void initChampions(Champion **champions, int *nbChampions) {
    champions[0] = createChampion("Haricot", (*nbChampions)++);
    champions[1] = createChampion("Fenouil", (*nbChampions)++);
    champions[2] = createChampion("Poireau", (*nbChampions)++);
    champions[3] = createChampion("Aubergine", (*nbChampions)++);
    champions[4] = createChampion("Courgette", (*nbChampions)++);
    champions[5] = createChampion("Carotte", (*nbChampions)++);
    champions[6] = createChampion("Banane", (*nbChampions)++);
    champions[7] = createChampion("Kiwi", (*nbChampions)++);
    champions[8] = createChampion("Poire", (*nbChampions)++);
    champions[9] = createChampion("Pomme", (*nbChampions)++);
    champions[10] = createChampion("Ananas", (*nbChampions)++);
    champions[11] = createChampion("Durian", (*nbChampions)++);
}

void initWeapons(Weapon **weapons, int *nbWeapons) {
    weapons[0] = createWeapon("Eplucheur Laser", (*nbWeapons)++);
    weapons[1] = createWeapon("Mandoline Sonique", (*nbWeapons)++);
    weapons[2] = createWeapon("Couperet Laser", (*nbWeapons)++);
    weapons[3] = createWeapon("Hachoir Neuronique", (*nbWeapons)++);
    weapons[4] = createWeapon("Mixeur Blaster", (*nbWeapons)++);
}

void initProtections(Protection **protections, int *nbProtections) {
    protections[0] = createProtection("Casque-Egouttoir", (*nbProtections)++);
    protections[1] = createProtection("Casque-Entonnoir", (*nbProtections)++);
    protections[2] = createProtection("Woklier", (*nbProtections)++);
    protections[3] = createProtection("Tablier-Armure", (*nbProtections)++);
}

void initHealings(Healing **healings, int *nbHealings) {
    healings[0] = createHealing("Humus-Neutronique", (*nbHealings)++);
    healings[1] = createHealing("Compost-Protonique", (*nbHealings)++);
    healings[2] = createHealing("Engrais-Ionique", (*nbHealings)++);
}

void initGame(Champion **champions, Weapon **weapons, Protection **protections, Healing **healings, int *nbChampions, int *nbWeapons, int *nbProtections, int *nbHealings) {
    initChampions(champions, nbChampions);
    initWeapons(weapons, nbWeapons);
    initProtections(protections, nbProtections);
    initHealings(healings, nbHealings);
}

void afficherChampions(Champion **champions, int *nbChampions) {
    Champion *c;
    int i;
    for(i = 0; i < *nbChampions; i++)
    {   
        c = champions[i];
        printf("Num %d\nVariété %s\nType %s\nForce %d\nResistance %d\nPV Max %d\nCE %d\n\n", c->num, c->variete, c->type, c->force, c->resistance, c->PVMax, c->CE);
    } 
}

void afficherWeapons(Weapon **weapons, int *nbWeapons) {
    Weapon *w;
    int i;
    for(i = 0; i < *nbWeapons; i++)
    {   
        w = weapons[i];
        printf("Num %d\nNom %s\nCE %d\nCA %d\nDégâts min %d\nDégâts max %d\nCE %d\n\n", w->num, w->nom, w->CE, w->CA, w->degatsMin, w->degatsMax, w->portee);
    } 
}

void afficherProtections(Protection **protections, int *nbProtections) {
    Protection *p;
    int i;
    for(i = 0; i < *nbProtections; i++)
    {   
        p = protections[i];
        printf("Num %d\nNom %s\nCE %d\nCA %d\nProbabilité %d %c \n\n", p->num, p->nom, p->CE, p->CA, p->probabilite, '%');
    }
}

void afficherSoins(Healing **healings, int *nbHealings) {
    Healing *h;
    int i;
    for(i = 0; i < *nbHealings; i++)
    {   
        h = healings[i];
        printf("Num %d\nNom %s\nCE %d\nCA %d\nVolume %d\nEffet min %d\nEffet max %d\n\n", h->num, h->nom, h->CE, h->CA, h->volume, h->effetMin, h->effetMax);
    }
}
/*
int main() {
    Champion **champions;
    Weapon **weapons;
    Protection **protections;
    Healing **healings;
    int *nbChampions, *nbWeapons, *nbProtections, *nbHealings;

    champions = malloc(sizeof(Champion *) * 12);
    weapons = malloc(sizeof(Weapon *) * 5);
    protections = malloc(sizeof(Protection *) * 4);
    healings = malloc(sizeof(Healing *) * 3);

    nbChampions = malloc(sizeof(int));
    nbWeapons = malloc(sizeof(int));
    nbProtections = malloc(sizeof(int));
    nbHealings = malloc(sizeof(int));

    *nbChampions = 0;
    *nbWeapons = 0;
    *nbProtections = 0;
    *nbHealings = 0;

    initGame(champions, weapons, protections, healings, nbChampions, nbWeapons, nbProtections, nbHealings);

    afficherChampions(champions, nbChampions);
    afficherWeapons(weapons, nbWeapons);
    afficherProtections(protections, nbProtections);
    afficherSoins(healings, nbHealings);
    return 0;
}
*/