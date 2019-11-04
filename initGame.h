#ifndef __INITGAME_H__
#define __INITGAME_H__

typedef struct winsize Winsize;

typedef struct champion {
  int num;
  char *variete;
  char *type;
  int force;
  int resistance;
  int PVMax;
  int PV;
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

typedef struct {
  int id;
  int position;
  int CA;
  int CE;
  int maxCE;
  int maxCA;
  Champion *champion;
  Weapon *weapon;
  Protection *protection;
  Healing *healing;
  int protectionActivated;
} Team;

/*
  Create and return a new team
  @Param1 Team
  @Param2 int
  @Param3 Winsize
  @return Team
*/
Team * initTeam(Team *team, int id, Winsize sz);

/*
  Create and return a new champion.
  @Param1 char * (the champion name)
  @Param2 int
  @Return Champion
*/
Champion * createChampion(char *name, int nbChampions);

/*
  Create and return a new weapon.
  @Param1 char * (the weapon name)
  @Param2 int
  @Return Weapon
*/
Weapon * createWeapon(char *name, int nbWeapons);

/*
  Create and return a new protection.
  @Param1 char * (the protection name)
  @Param2 int
  @Return Protection
*/
Protection * createProtection(char *name, int nbProtection);

/*
  Create and return a new healing.
  @Param1 char * (the healing name)
  @Param2 int
  @Return Healing
*/
Healing * createHealing(char *name, int nbHeal);

/*
    Create and return the array of champion
    @Param1 Array of champion
    @Param2 int
    @Return void
*/
void initChampions(Champion **champions, int *nbChampions);

/*
    Create and return the array of weapon
    @Param1 Array of weapon
    @Param2 int
    @Return void
*/
void initWeapons(Weapon **weapons, int *nbWeapons);

/*
    Create and return the array of protection
    @Param1 Array of protection
    @Param2 int
    @Return void
*/
void initProtections(Protection **protections, int *nbProtections);

/*
    Create and return the array of healing
    @Param1 Array of healing
    @Param2 int
    @Return void
*/
void initHealings(Healing **healings, int *nbHealings);

/*
    Init game objects
    @Param1 Array of champion
    @Param2 Array of weapon
    @Param3 Array of protection
    @Param4 Array of healing
    @Param5 int (champion number)
    @Param6 int (weapon number)
    @Param7 int (protection number)
    @Param8 int (healing number)
    @Param9 Team
    @Param10 Team
    @Return Winsize
*/
Winsize initGame(Champion **champions, Weapon **weapons, Protection **protections, Healing **healings, int *nbChampions, int *nbWeapons, int *nbProtections, int *nbHealings, Team *team1, Team *team2);

#endif
