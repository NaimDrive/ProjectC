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

void deallocateStrat(Strat *strat);

void deallocateStrategy(Strategy *strategy);

void deallocateStrategies(Strategy **strategy, int *nbStrategies);
/*
    Free all malloc before exit the program
    @Param1 Package
    @Param2 Team
    @Param3 Team
    @Return void
*/
void deallocateMemory(Package *package, Team *team1, Team *team2);

#endif