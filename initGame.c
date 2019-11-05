#include "initGame.h"

#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Champion * createChampion(char *name, int nbChampions) {
  Champion *champion;

  if(strcmp("Haricot", name) == 0) {
    champion = malloc(sizeof(Champion));

    champion->num = nbChampions;
    champion->variete = name;
    champion->type = "Légume";
    champion->force = 10;
    champion->resistance = 10;
    champion->PVMax = 40;
    champion->PV = 40;
    champion->CE = 5;
  } else if (strcmp(name, "Fenouil") == 0) {
    champion = malloc(sizeof(Champion));

    champion->num = nbChampions;
    champion->variete = name;
    champion->type = "Légume";
    champion->force = 12;
    champion->resistance = 15;
    champion->PVMax = 40;
    champion->PV = 40;
    champion->CE = 7;
  } else if (strcmp(name, "Poireau") == 0) {
    champion = malloc(sizeof(Champion));

    champion->num = nbChampions;
    champion->variete = name;
    champion->type = "Légume";
    champion->force = 15;
    champion->resistance = 20;
    champion->PVMax = 60;
    champion->PV = 60;
    champion->CE = 10;
  } else if (strcmp(name, "Aubergine") == 0) {
    champion = malloc(sizeof(Champion));

    champion->num = nbChampions;
    champion->variete = name;
    champion->type = "Légume";
    champion->force = 20;
    champion->resistance = 20;
    champion->PVMax = 60;
    champion->PV = 60;
    champion->CE = 15;
  } else if (strcmp(name, "Courgette") == 0) {
    champion = malloc(sizeof(Champion));
    
    champion->num = nbChampions;
    champion->variete = name;
    champion->type = "Légume";
    champion->force = 20;
    champion->resistance = 25;
    champion->PVMax = 80;
    champion->PV = 80;
    champion->CE = 20;
  } else if (strcmp(name, "Carotte") == 0) {
    champion = malloc(sizeof(Champion));
    
    champion->num = nbChampions;
    champion->variete = name;
    champion->type = "Légume";
    champion->force = 25;
    champion->resistance = 25;
    champion->PVMax = 80;
    champion->PV = 80;
    champion->CE = 25;
  } else if (strcmp(name, "Banane") == 0) {
    champion = malloc(sizeof(Champion));
    
    champion->num = nbChampions;
    champion->variete = name;
    champion->type = "Fruit";
    champion->force = 10;
    champion->resistance = 10;
    champion->PVMax = 40;
    champion->PV = 40;
    champion->CE = 5;
  } else if (strcmp(name, "Kiwi") == 0) {
    champion = malloc(sizeof(Champion));
    
    champion->num = nbChampions;
    champion->variete = name;
    champion->type = "Fruit";
    champion->force = 12;
    champion->resistance = 15;
    champion->PVMax = 40;
    champion->PV = 40;
    champion->CE = 7;
  } else if (strcmp(name, "Poire") == 0) {
    champion = malloc(sizeof(Champion));
    
    champion->num = nbChampions;
    champion->variete = name;
    champion->type = "Fruit";
    champion->force = 15;
    champion->resistance = 20;
    champion->PVMax = 60;
    champion->PV = 60;
    champion->CE = 10;
  } else if (strcmp(name, "Pomme") == 0) {
    champion = malloc(sizeof(Champion));

    champion->num = nbChampions;
    champion->variete = name;
    champion->type = "Fruit";
    champion->force = 20;
    champion->resistance = 20;
    champion->PVMax = 60;
    champion->PV = 60;
    champion->CE = 15;
  } else if (strcmp(name, "Ananas") == 0) {
    champion = malloc(sizeof(Champion));
    
    champion->num = nbChampions;
    champion->variete = name;
    champion->type = "Fruit";
    champion->force = 20;
    champion->resistance = 25;
    champion->PVMax = 80;
    champion->PV = 80;
    champion->CE = 20;
  } else if (strcmp(name, "Durian") == 0) {
    champion = malloc(sizeof(Champion));
    
    champion->num = nbChampions;
    champion->variete = name;
    champion->type = "Fruit";
    champion->force = 25;
    champion->resistance = 25;
    champion->PVMax = 80;
    champion->PV = 80;
    champion->CE = 25;
  } else {
    fprintf(stderr, "Champion name error\n");
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
        healing->maxVolume = 4;
        healing->effetMin = 2;
        healing->effetMax = 4;
    } else if(strcmp("Compost-Protonique", name) == 0) {
        healing = malloc(sizeof(Healing));

        healing->num = nbHealings;
        healing->nom = name;
        healing->CE = 5;
        healing->CA = 10;
        healing->volume = 3;
        healing->maxVolume = 3;
        healing->effetMin = 5;
        healing->effetMax = 8;
    } else if(strcmp("Engrais-Ionique", name) == 0) {
        healing = malloc(sizeof(Healing));

        healing->num = nbHealings;
        healing->nom = name;
        healing->CE = 7;
        healing->CA = 15;
        healing->volume = 2;
        healing->maxVolume = 2;
        healing->effetMin = 8;
        healing->effetMax = 12;
    } else {
        fprintf(stderr, "Healing name error\n");
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

Winsize initGame(Champion **champions, Weapon **weapons, Protection **protections, Healing **healings, int *nbChampions, int *nbWeapons, int *nbProtections, int *nbHealings, Team *team1, Team *team2) {
    Winsize screenSize;
    ioctl(0, TIOCGWINSZ, &screenSize);

    initChampions(champions, nbChampions);
    initWeapons(weapons, nbWeapons);
    initProtections(protections, nbProtections);
    initHealings(healings, nbHealings);
    initTeam(team1, 0, screenSize);
    initTeam(team2, 1, screenSize);

    return screenSize;
}

void afficherChampions(Champion **champions, int *nbChampions) {
    Champion *c;
    int i;
    for(i = 0; i < *nbChampions; i++)
    {   
        c = champions[i];
        printf("Num %d\nVariété %s\nType %s\nForce %d\nResistance %d\nPV Max %d\nPV %d\nCE %d\n\n", c->num, c->variete, c->type, c->force, c->resistance, c->PVMax,c->PV, c->CE);
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

Team * initTeam(Team *team, int id, Winsize sz) {
  team->id = id;
  if(id == 0)
    team->position = 1;
  else
    team->position = sz.ws_col-2;
  team->CE = 1000;
  team->CA = 50;
  team->maxCE = 50;
  team->maxCA = 50;
  team->champion = NULL;
  team->weapon = NULL;
  team->protection = NULL;
  team->healing = NULL;
  team->protectionActivated = 0;

  return team;
}