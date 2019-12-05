#ifndef __COMMANDES_H__
#define __COMMANDES_H__

/*
    Get id entered in a command line
    @Param1 The command line
    @Param2 Where the id starts
    @Return The id (int)
*/
int getID(char *command, int n);

/*
    Check if the fighters are in the available champions
    @Param1 Vegetable's name
    @Param2 Fruit's name
    @Param3 Vegetable index
    @Param4 Fruit index
    @Param5 Array of available champions
    @Param6 Number of champions
    @Return The id (int)
*/
int checkingChamps(char *veg, char *fruit, int vegIndex, int fruitIndex, Champion **champions, int nbChampions);

/*
    Get champion's index from his name
    @Param1 Champion's name
    @Param2 Array of available champions
    @Param3 Number of champions
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
    @Param2 Number of champ
    @Param3 Vegetable's id
    @Return void
*/
void showVegetable(Champion **champions, int *nbChampions, int id);

/*
    Show every fruit
    @Param1 Array of available champions
    @Param2 Number of champ
    @Return void
*/
void showFruits(Champion **champions, int *nbChampions);

/*
    Show a fruit
    @Param1 Array of available champions
    @Param2 Number of champ
    @Param3 Fruit's id
    @Return void
*/
void showFruit(Champion **champions, int *nbChampions, int id);

/*
    Show every weapon
    @Param1 Array of available weapons
    @Param2 Number of weapon
    @Return void
*/
void showWeapons(Weapon **weapons, int *nbWeapons, int ce);

/*
    Show a weapon
    @Param1 Array of available weapons
    @Param2 Number of weapon
    @Param3 Weapon's id
    @Return void
*/
void showWeapon(Weapon **weapons, int *nbWeapons, int id);

/*
    Show every protection
    @Param1 Array of available protections
    @Param2 Number of protection
    @Return void
*/
void showProtections(Protection **protections, int *nbProtections, int ce);

/*
    Show a protection
    @Param1 Array of available protections
    @Param2 Number of protection
    @Param3 Protection's id
    @Return void
*/
void showProtection(Protection **protections, int *nbProtections, int id);

/*
    Show every heal
    @Param1 Array of available heals
    @Param2 Number of heal
    @Return void
*/
void showCares(Healing **healings, int *nbHealings, int ce);

/*
    Show a heal
    @Param1 Array of available heals
    @Param2 Number of heal
    @Param3 Heal's id
    @Return void
*/
void showCare(Healing **healings, int *nbHealings, int id);

/*
    Ask if the player want to replay
    @Param1 Buffer
    @Return The answer as an int
*/
int replay(char *command);

/*
    Launches the fight.
    @Param1 A vegetable
    @Param2 A fruit
    @Param3 Array with every champion
    @Param4 Array with every weapon
    @Param5 Array with every protection
    @Param6 Array with every heal
    @Param7 Number of champions
    @Param8 Number of weapons
    @Param9 Number of protections
    @Param10 Number of heals
    @Param11 Team vegetable
    @Param12 Team fruit
    @Param13 Size of the terminal
    @Return void
*/
void fight(Champion *vegetable, Champion* fruit, Champion **champions, Weapon **weapons, Protection **protections, Healing **healings, int *nbChampions, int *nbWeapons, int *nbProtections, int *nbHealings, Team *team1, Team *team2, Winsize screenSize);

/*
    Show every command line available
    @Return void
*/
void help();

/*
    Deallocate and exit the game.
    @Param1 Array with every champion
    @Param2 Array with every weapon
    @Param3 Array with every protection
    @Param4 Array with every heal
    @Param5 Number of champions
    @Param6 Number of weapons
    @Param7 Number of protections
    @Param8 Number of heals
    @Param9 Team vegetable
    @Param10 Team fruit
    @Return void
*/
void exitGame(Champion **champions, Weapon **weapons, Protection **protections, Healing **healings, int *nbChampions, int *nbWeapons, int *nbProtections, int *nbHealings, Team *team1, Team *team2);

/*
    Read commands line entered.
    @Param1 Array with every champion
    @Param2 Array with every weapon
    @Param3 Array with every protection
    @Param4 Array with every heal
    @Param5 Number of champions
    @Param6 Number of weapons
    @Param7 Number of protections
    @Param8 Number of heals
    @Param9 Team vegetable
    @Param10 Team fruit
    @Param11 Size of the terminal
    @Return void
*/
void readCommands(Champion **champions, Weapon **weapons, Protection **protections, Healing **healings, Strategy **strategy, int *nbChampions, int *nbWeapons, int *nbProtections, int *nbHealings, int *nbStrategies, Team *team1, Team *team2, Winsize screenSize);

#endif
