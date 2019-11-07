#ifndef __FIGHT_H__
#define __FIGHT_H__

/*
  Calculate the maximum of CE which can be used during the round
  @Param1 Team
  @Param2 Team
  @Return void
*/
void maxCE(Team *team1, Team *team2);

/*
  Set the maximum of CA which can be used during the round
  @Param1 Team
  @Return void
*/
void resetCA(Team *team);

/*
  Reset the volume to the maximum
  @Param1 Team
  @Return void
*/
void resetHealing(Team *team);

/*
  Use CE to buy CA
  @Param1 Team
  @Param2 int
  @Return void
*/
void buyCA(Team *team, int number);

/*
  Buy a champion
  @Param1 Champion
  @Param2 Team
  @Return int
*/
int buyChampion(Champion *champion, Team *team);

/*
  Buy a weapon
  @Param1 Weapon
  @Param2 Team
  @Return int
*/
int buyWeapon(Weapon *weapon, Team *team);

/*
  Buy a protection
  @Param1 Protection
  @Param2 Team
  @Return int
*/
int buyProtection(Protection *protection, Team *team);

/*
  Buy a healing
  @Param1 Healing
  @Param2 Team
  @Return int
*/
int buyHealing(Healing *healing, Team *team);

/*
  The champion move foward.
  @Param1 Team
  @Param2 Team
  @Param3 int
  @Return void
*/
void moveForward(Team *team1, Team *team2, int n);

/*
  The champion move backward.
  @Param1 Team
  @Param2 int
  @Param3 int
  @Return void
*/
void moveBackward(Team *team, int n, int maxX);

/*
  The first team attack the second team n times
  @Param1 Team
  @Param2 Team
  @Param3 int
  @Param4 Screen size
  @Return void
*/
void useWeapon(Team *team1, Team *team2, int n, int sz);

/*
  Activate the weapon.
  @Param1 Team
  @Retun void
*/
void useProtection(Team *team);

/*
  Use care to heal the champion n times.
  @Param1 Team
  @Param2 int
  @Retun void
*/
void useCare(Team *team, int n);

#endif
