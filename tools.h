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

char * strtolower( char * dest, const char * src );

/*
    Check if the string is a number.
    @Param1 A string
    @Return An int as answer (1 OK, 0 not OK)
*/
int isOnlyDigits(char *chaine);

Weapon * searchWeapon(Weapon **weapon, int *nbWeapons, char *w);

Protection * searchProtection(Protection **protection, int *nbProtections, char *p);

Healing * searchHealing(Healing **healing, int *nbHealings, char *h);

#endif