#ifndef __FIGHTMODE_H__
#define __FIGHTMODE_H__

void enterToContinue();

void fightingMode(Team *team1, Team *team2, int screenSize);

void equipTeam(Team *team, Weapon **weapons, Protection **protections, Healing **healings, int *nbWeapons, int*nbProtections, int *nbHealings);

void weaponChoice(Team *team, Weapon **weapons, int *nbChampions, char *command);

void protectionChoice(Team *team, Protection **protections, int *nbProtections, char *command);

void showEndGame(Team *team1, Team *team2);

void endRound(Team *team1, Team* team2, int maximumCE, int end, Winsize sz);

void roundWinner(Team *team1, Team *team2, int maximumCE);

/*
    Remove the protection if it is equipped.
    @Param Team
    @Return void
*/
void takeOffProtection(Team *team1);

/*
    While the duel is not finished, reset contents to fight again.
    @Param1 Team
    @Param2 Team
    @Return void
*/
void fighNotFinished(Team *team1, Team *team2);

/*
    The player can buy a care for the duel.
    @Param1 Team
    @Param2 Array with every heal
    @Param3 int
    @Param4 char *
    @Return void
*/
void healingChoice(Team *team, Healing **healings, int *nbHealings, char *command);

/*
    Reset the team contents to play again.
    @Param1 Team
    @Param2 Team
    @Param3 Winsize
    @Return void
*/
void resetGame(Team *team1, Team *team2, Winsize screenSize);

#endif
