#ifndef __FIGHT_H__
#define __FIGHT_H__

typedef struct {
  int CA;
  int CE;
  int CE_USED;
  Champion *champion;
  Weapon *weapon;
  Protection *protection;
  Healing *healing;
  int protectionActivated;
} Team;

/*
  Create a new team
  @return the new team
*/
Team * initTeam();

/*
  Calculate the maximum of CE which can be used during the round
  @Param1 the first team
  @Param2 the second team
  @Return integer : number of CE
*/
int maxCE(Team *team1, Team *team2);

/*
  Use CE to buy CA
  @Param1 the team
  @Param2 CA number
  @Return void
*/
void buyCA(Team *team, int number);

/*
  Buy a champion
  @Param1 the champion
  @Param2 the team which need a champion
  @Return void
*/
void buyChampion(Champion *champion, Team *team, int maxCE);

/*
  Buy a weapon
  @Param1 the weapon
  @Param2 the team which need a weapon
  @Return void
*/
void buyWeapon(Weapon *weapon, Team *team, int maxCE);

/*
  Buy a protection
  @Param1 the protection
  @Param2 the team which need a protection
  @Return void
*/
void buyProtection(Protection *protection, Team *team, int maxCE);

/*
  Buy a healing
  @Param1 the healing
  @Param2 the team which need a healing
  @Return void
*/
void buyHealing(Healing *healing, Team *team, int maxCE);

void startFight();

void moveForward();

/*
  The first team attack the second team n times
  @Param1 the first team
  @Param2 the second team
  @Param3 number of times
  @Return void
*/
void useWeapon(Team *team1, Team *team2, int n);

void useProtection();

void useCare(int n);

void end();

/*
    Calculate the random damage of the weapon between degatsMin and degatsMax
    @Param the weapon
    @Return integer
*/
int weaponDamage(Weapon *weapon);

#endif
