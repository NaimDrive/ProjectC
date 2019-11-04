#ifndef __ENDGAME_H__
#define __ENDGAME_H__

/*
    Free all champions in the table
    @Param1 Array of champion
    @Param2 int
    @Return void
*/
void deallocateChampions(Champion **champions, int *nbChampions);

/*
    Free all weapons in the table
    @Param1 Array of weapon
    @Param2 int
    @Return void
*/
void deallocateWeapons(Weapon **weapons, int *nbWeapons);

/*
    Free all protections in the table
    @Param1 Array of protection
    @Param2 int
    @Return void
*/
void deallocateProtections(Protection **protections, int *nbProtections);

/*
    Free all healings in the table
    @Param1 Array of healing
    @Param2 int
    @Return void
*/
void deallocateHealings(Healing **healings, int *nbHealings);

/*
    Free teams and their contents
    @Param1 Team
    @Param2 Team
    @Return void
*/
void deallocateTeams(Team *team1, Team *team2);

/*
    Free all malloc before exit the program
    @Param1 Array of champion
    @Param2 Array of weapon
    @Param3 Array of protection
    @Param4 Array of healing
    @Param5 int
    @Param6 int
    @Param7 int
    @Param8 int
    @Param9 Team
    @Param10 Team
    @Return void
*/
void deallocateMemory(Champion **champions, Weapon **weapons, Protection **protections, Healing **healings, int *nbChampions, int *nbWeapons, int *nbProtections, int *nbHealings, Team *team1, Team *team2);

#endif
