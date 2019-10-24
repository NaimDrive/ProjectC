#ifndef __ENDGAME_H__
#define __ENDGAME_H__

/*
    Free all champions in the table
    @Param1 the table of champion
    @Param2 the total champion number.
    @Return void
*/
void deallocateChampions(Champion **champions, int *nbChampions);

/*
    Free all weapons in the table
    @Param1 the table of weapon
    @Param2 the total weapon number.
    @Return void
*/
void deallocateWeapons(Weapon **weapons, int *nbWeapons);

/*
    Free all protections in the table
    @Param1 the table of protection
    @Param2 the total protection number.
    @Return void
*/
void deallocateProtections(Protection **protections, int *nbProtections);

/*
    Free all healings in the table
    @Param1 the table of healing
    @Param2 the total healing number.
    @Return void
*/
void deallocateHealings(Healing **healings, int *nbHealings);

/*
    Free all malloc before exit the program
    @Param1 the table of champion
    @Param2 the table of weapon
    @Param3 the table of protection
    @Param4 the table of healing
    @Param5 the total champion number.
    @Param6 the total weapon number.
    @Param7 the total protection number.
    @Param8 the total healing number.
    @Return void
*/
void deallocateMemory(Champion **champions, Weapon **weapons, Protection **protections, Healing **healings, int *nbChampions, int *nbWeapons, int *nbProtections, int *nbHealings);

#endif