#include "initGame.h"

#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Champion * generateChampion(char *name, int nbChampions, char *type, int force, int resistance, int PVMax, int PV, int CE, char head) {
  Champion *champion;
  champion = malloc(sizeof(Champion));

  champion->variete = name;
  champion->num = nbChampions;
  champion->type = type;
  champion->force = force;
  champion->resistance = resistance;
  champion->PVMax = PVMax;
  champion->PV = PV;
  champion->CE = CE;
  champion->head = head;

  return champion;
}

Weapon * generateWeapon(char *name, int nbWeapons, int CE, int CA, int dmgMin, int dmgMax, int portee) {
  Weapon *weapon;
  weapon = malloc(sizeof(Weapon));

  weapon->nom = name;
  weapon->num = nbWeapons;
  weapon->CE = CE;
  weapon->CA = CA;
  weapon->degatsMin = dmgMin;
  weapon->degatsMax = dmgMax;
  weapon->portee = portee;

  return weapon;
}

Protection * generateProtection(char *name, int nbProtection, int CE, int CA, int probabilite) {
  Protection *protection;
  protection = malloc(sizeof(Protection));

  protection->nom = name;
  protection->num = nbProtection;
  protection->CE = CE;
  protection->CA = CA;
  protection->probabilite = probabilite;

  return protection;
}

Healing * generateHealing(char *name, int nbHealings, int CE, int CA, int volume, int effetMin, int effetMax) {
  Healing *healing;
  healing = malloc(sizeof(Healing));

  healing->nom = name;
  healing->num = nbHealings;
  healing->CE = CE;
  healing->CA = CA;
  healing->volume = volume;
  healing->maxVolume = volume;
  healing->effetMin = effetMin;
  healing->effetMax = effetMax;

  return healing;
}

Champion * createChampion(char *name, int nbChampions) {
  Champion *champion;

  if(strcmp("Haricot", name) == 0) {
    champion = generateChampion(name, nbChampions, "Légume", 10, 10, 40, 40, 5, ';');
  } else if (strcmp(name, "Fenouil") == 0) {
    champion = generateChampion(name, nbChampions, "Légume", 12, 15, 40, 40, 7, 'W');
  } else if (strcmp(name, "Poireau") == 0) {
    champion = generateChampion(name, nbChampions, "Légume", 15, 20, 60, 60, 10, 'Y');
  } else if (strcmp(name, "Aubergine") == 0) {
    champion = generateChampion(name, nbChampions, "Légume", 20, 20, 60, 60, 15, 'u');
  } else if (strcmp(name, "Courgette") == 0) {
    champion = generateChampion(name, nbChampions, "Légume", 20, 25, 80, 80, 20, 'i');
  } else if (strcmp(name, "Carotte") == 0) {
    champion = generateChampion(name, nbChampions, "Légume", 25, 25, 80, 80, 25, '\'');
  } else if (strcmp(name, "Banane") == 0) {
    champion = generateChampion(name, nbChampions, "Fruit", 10, 10, 40, 40, 5, ',');
  } else if (strcmp(name, "Kiwi") == 0) {
    champion = generateChampion(name, nbChampions, "Fruit", 12, 15, 40, 40, 7, 'o');
  } else if (strcmp(name, "Poire") == 0) {
    champion = generateChampion(name, nbChampions, "Fruit", 15, 20, 60, 60, 10, ')');
  } else if (strcmp(name, "Pomme") == 0) {
    champion = generateChampion(name, nbChampions, "Fruit", 20, 20, 60, 60, 15, '@');
  } else if (strcmp(name, "Ananas") == 0) {
    champion = generateChampion(name, nbChampions, "Fruit", 20, 25, 80, 80, 20, '#');
  } else if (strcmp(name, "Durian") == 0) {
    champion = generateChampion(name, nbChampions, "Fruit", 25, 25, 80, 80, 25, 'X');
  }

  return champion;
}

Weapon * createWeapon(char *name, int nbWeapons) {
  Weapon *weapon;

  if(strcmp("Eplucheur Laser", name) == 0) {
    weapon = generateWeapon(name, nbWeapons, 2, 1, 1, 2, 2);
  } else if(strcmp("Mandoline Sonique", name) == 0) {
    weapon = generateWeapon(name, nbWeapons, 5, 3, 1, 3, 3);
  } else if(strcmp("Couperet Laser", name) == 0) {
    weapon = generateWeapon(name, nbWeapons, 10, 5, 2, 6, 5);
  } else if(strcmp("Hachoir Neuronique", name) == 0) {
    weapon = generateWeapon(name, nbWeapons, 20, 7, 4, 9, 7);
  } else if(strcmp("Mixeur Blaster", name) == 0) {
    weapon = generateWeapon(name, nbWeapons, 30, 10, 7, 12, 11);
  }

  return weapon;
}

Protection * createProtection(char *name, int nbProtection) {
  Protection *protection;

  if(strcmp("Casque-Egouttoir", name) == 0) {
    protection = generateProtection(name, nbProtection, 1, 2, 25);
  } else if(strcmp("Casque-Entonnoir", name) == 0) {
    protection = generateProtection(name, nbProtection, 3, 4, 40);
  } else if(strcmp("Woklier", name) == 0) {
    protection = generateProtection(name, nbProtection, 5, 6, 60);
  } else if(strcmp("Tablier-Armure", name) == 0) {
    protection = generateProtection(name, nbProtection, 10, 8, 80);
  }
  
  return protection;
}

Healing * createHealing(char *name, int nbHealings){
  Healing *healing;

  if(strcmp("Humus-Neutronique", name) == 0) {
    healing = generateHealing(name, nbHealings, 1, 5, 4, 2, 4);
  } else if(strcmp("Compost-Protonique", name) == 0) {
    healing = generateHealing(name, nbHealings, 5, 10, 3, 5, 8);
  } else if(strcmp("Engrais-Ionique", name) == 0) {
    healing = generateHealing(name, nbHealings, 7, 15, 2, 8, 12);
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