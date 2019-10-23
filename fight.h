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
} Team;

/*
  Create a new team
  @Param1 the champion of the team
  @Param2 the weapon of the team
  @Param3 the protection of the team
  @Param4 the healing of the team
  @return the new team
*/
Team initTeam();

/*
  Calculate the maximum of CE which can be used during the round
  @Param1 the first team
  @Param2 the second team
  @Return integer : number of CE
*/
int maxCE(Team *team1, Team *team2);

/*
  Buy a champion
  @Param1 the table of champion
  @Param2 the team which need a champion
  @Return void
*/
void buyChampion(Champion *champion, Team *team, int maxCE);

void startFight();

void moveForward();

void useWeapon(int n);

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
