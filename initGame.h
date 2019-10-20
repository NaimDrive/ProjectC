#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct champion {
  int num;
  char *variete;
  char *type;
  int force;
  int resistance;
  int PVMax;
  int CE;
} Champion;

typedef struct weapon{
  int num;
  char *nom;
  int CE;
  int CA;
  int degatsMin;
  int degatsMax;
  int portee;
} Weapon;

typedef struct protection{
  int num;
  char *nom;
  int CE;
  int CA;
  int probabilite;
} Protection;

typedef struct healing{
  int num;
  char *nom;
  int CE;
  int CA;
  int volume;
  int effetMin;
  int effetMax;
} Healing;

/*
  Create and return a new champion.
  @Param1 the champion name
  @Param2 the current champion number.
  @Return the new champion.
*/
Champion * createChampion(char *name, int *nbChampions);

/*
  Create and return a new weapon.
  @Param1 the weapon name
  @Param2 the current weapon number.
  @Return the new weapon.
*/
Weapon * createWeapon(char *name, int *nbWeapons);

/*
  Create and return a new protection.
  @Param1 the protection name
  @Param2 the current protection number.
  @Return the new protection.
*/
Protection * createProtection(char *name, int *nbProtection);

/*
  Create and return a new healing.
  @Param1 the healing name
  @Param2 the current healing number.
  @Return the new healing.
*/
Healing * createHealing(char *name, int *nbHeal);

/*
    Create and return the table of champion
    @Param1 the table of champion
    @Param2 the current champion number.
    @Return void
*/
void initChampions(Champion **champions, int *nbChampions);

/*
    Create and return the table of weapon
    @Param1 the table of weapon
    @Param2 the current weapon number.
    @Return void
*/
void initWeapons(Weapon **weapons, int *nbWeapons);

/*
    Create and return the table of protection
    @Param1 the table of protection
    @Param2 the current protection number.
    @Return void
*/
void initProtections(Protection **protections, int *nbProtections);

/*
    Create and return the table of healing
    @Param1 the table of healing
    @Param2 the current healing number.
    @Return void
*/
void initHealings(Healing **healings, int *nbHealings);

/*
    Init game objects
    @Param1 the table of champion
    @Param2 the table of weapon
    @Param3 the table of protection
    @Param4 the table of healing
    @Param5 the current champion number.
    @Param6 the current weapon number.
    @Param7 the current protection number.
    @Param8 the current healing number.
    @Return void
*/
void initGame(Champion **champions, Weapon **weapons, Protection **protections, Healing **healings, int *nbChampions, int *nbWeapons, int *nbProtections, int *nbHealings);
