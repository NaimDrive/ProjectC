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