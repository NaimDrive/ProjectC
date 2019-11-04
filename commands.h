#ifndef __COMMANDES_H__
#define __COMMANDES_H__

/*
    Get the substring of a string
    @Param1 Target
    @Param2 Start of the substring
    @Param3 End of the substring
    @Return A string (char*)
*/
char* substring(char *src, int beg, int end);

/*
    Get id entered in a command line
    @Param1 The command line
    @Param2 Where the id starts
    @Return The id (int)
*/
int getID(char *command, int n);

/*
    Get champion's index from his name
    @Param1 Champion's name
    @Param2 Array of available champions
    @Param3 Number of champions in the second parameter
    @Return The champion's id (int)
*/
int getChampIndex(char *champName, Champion **champion, int nbChampions);

/*
    Show every vegetable
    @Param1 Array of available champions
    @Param2 Number of champs
    @Return void
*/
void showVegetables(Champion **champions, int *nbChampions);

/*
    Show a vegetable
    @Param1 Array of available champions
    @Param2 Number of champs
    @Param3 Vegetable's id
    @Return void
*/
void showVegetable(Champion **champions, int *nbChampions, int id);

/*
    Show every fruit
    @Param1 Array of available champions
    @Param2 Number of champs
    @Return void
*/
void showFruits(Champion **champions, int *nbChampions);

/*
    Show a fruit
    @Param1 Array of available champions
    @Param2 Number of champs
    @Param3 Fruit's id
    @Return void
*/
void showFruit(Champion **champions, int *nbChampions, int id);

/*
    Show every weapon
    @Param1 Array of available weapons
    @Param2 Number of weapons
    @Return void
*/
void showWeapons(Weapon **weapons, int *nbWeapons, int ce);

/*
    Show a weapon
    @Param1 Array of available weapon
    @Param2 Number of champs
    @Return void
*/
void showWeapon(Weapon **weapons, int *nbWeapons, int id);

void showProtections(Protection **protections, int *nbProtections, int ce);

void showProtection(Protection **protections, int *nbProtections, int id);

void showCares(Healing **healings, int *nbHealings, int ce);

void showCare(Healing **healings, int *nbHealings, int id);

int replay(char *command);

void fight(Champion *vegetable, Champion* fruit, Champion **champions, Weapon **weapons, Protection **protections, Healing **healings, int *nbChampions, int *nbWeapons, int *nbProtections, int *nbHealings, Team *team1, Team *team2, Winsize screenSize);

void help();

void exitGame(Champion **champions, Weapon **weapons, Protection **protections, Healing **healings, int *nbChampions, int *nbWeapons, int *nbProtections, int *nbHealings, Team *team1, Team *team2);

void readCommands(Champion **champions, Weapon **weapons, Protection **protections, Healing **healings, int *nbChampions, int *nbWeapons, int *nbProtections, int *nbHealings, Team *team1, Team *team2, Winsize screenSize);

#endif
