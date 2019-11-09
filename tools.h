#ifndef __TOOLS_H__
#define __TOOLS_H__

/*
    Calculate the random damage of the weapon between degatsMin and degatsMax
    @Param Weapon
    @Return int
*/
int weaponDamage(Weapon *weapon);

/*
    Calculate if the protection will counter the next attack.
    @Param int
    @Return int
*/
int effectiveProtection(int protection);

/*
    Calculate the number of HP that the care will cure.
    @Param Healing
    @Return int
*/
int randHeal(Healing *healing);

/*
  Calculate the distance between the champions.
  @Param1 Team
  @Param2 Team
  @Return int
*/
int distanceBetweenChampions(Team *team1, Team *team2);

/*
    Get the substring of a string
    @Param1 Target
    @Param2 Start of the substring
    @Param3 End of the substring
    @Return A string (char*)
*/
char* substring(char *src, int beg, int end);

/*
    Ask user to push Enter to continue
    @Return void
*/
void enterToContinue();

#endif