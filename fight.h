#ifndef __FIGHT_H__
#define __FIGHT_H__

typedef struct {
  int id;
  int position;
  int CA;
  int CE;
  int maxCE;
  Champion *champion;
  Weapon *weapon;
  Protection *protection;
  Healing *healing;
  int protectionActivated;
} Team;

typedef struct winsize Winsize;

/*
  Create a new team
  @return the new team
*/
Team * initTeam(int id, Winsize sz);

/*
  Calculate the maximum of CE which can be used during the round
  @Param1 the first team
  @Param2 the second team
  @Return void
*/
void maxCE(Team *team1, Team *team2);

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
void buyChampion(Champion *champion, Team *team);

/*
  Buy a weapon
  @Param1 the weapon
  @Param2 the team which need a weapon
  @Return void
*/
void buyWeapon(Weapon *weapon, Team *team);

/*
  Buy a protection
  @Param1 the protection
  @Param2 the team which need a protection
  @Return void
*/
void buyProtection(Protection *protection, Team *team);

/*
  Buy a healing
  @Param1 the healing
  @Param2 the team which need a healing
  @Return void
*/
void buyHealing(Healing *healing, Team *team);

/*
  The champion move foward.
  @Param1 the first team
  @Param2 the second team
  @Param3 number of case
  @Return void
*/
void moveForward(Team *team1, Team *team2, int n);

/*
  The champion move backward.
  @Param1 the team
  @Param2 number of case
  @Param3 the maximum position of the area
  @Return void
*/
void moveBackward(Team *team, int n, int maxX);

/*
  The first team attack the second team n times
  @Param1 the first team
  @Param2 the second team
  @Param3 number of times
  @Return void
*/
void useWeapon(Team *team1, Team *team2, int n);

/*
  Activate the weapon.
  @Param1 the team
  @Retun void
*/
void useProtection(Team *team);

/*
  Use care to heal the champion.
*/
void useCare(Team *team, int n);

/*
  Calculate the distance between the champions.
  @Param1 the first team.
  @Param2 the second team.
  @Return integer
*/
int distanceBetweenChampions(Team *team1, Team *team2);

/*
  Free all the allocated memory for the fight.
  @Param1 the first team
  @Param2 the second team
*/
void endBattle(Team *team1, Team *team2);

/*
    Calculate the random damage of the weapon between degatsMin and degatsMax
    @Param the weapon
    @Return integer
*/
int weaponDamage(Weapon *weapon);

#endif
