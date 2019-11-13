#ifndef __FIGHTMODE_H__
#define __FIGHTMODE_H__

/*
    Handle fighting mode
    @Param1 String
    @Param2 Team
    @Param3 Team
    @Param4 Int
    @Return Int (0 OK, 1 end the turn, 2 wrong command)
*/
int readAction(char *command, Team *team1, Team *team2, int screenSize);

/*
    Handle the fight
    @Param1 Team
    @Param2 Team
    @Param3 Int
    @Return void
*/
void fightingMode(Team *team1, Team *team2, int screenSize);

/*
    Equip a team (Weapon, protection and cares)
    @Param1 Team
    @Param2 Array of weapons
    @Param3 Array of protections
    @Param4 Array of cares
    @Param5 Number of weapon
    @Param6 Number of protection
    @Param7 Nummber of care
    @Return void
*/
void equipTeam(Team *team, Weapon **weapons, Protection **protections, Healing **healings, int *nbWeapons, int*nbProtections, int *nbHealings);

/*
    Ask the player which weapon he wants
    @Param1 Team
    @Param2 Array of weapons
    @Param3 Number of weapon
    @Param4 String buffer
    @Return void
*/
void weaponChoice(Team *team, Weapon **weapons, int *nbWeapons, char *command);

/*
    Ask the player which protection he wants
    @Param1 Team
    @Param2 Array of protections
    @Param3 Number of protection
    @Param4 String buffer
    @Return void
*/
void protectionChoice(Team *team, Protection **protections, int *nbProtections, char *command);

/*
    Print which team won
    @Param1 Team
    @Param2 Team
    @Return void
*/
void showEndGame(Team *team1, Team *team2);

/*
    Ask the player which protection he wants
    @Param1 Team
    @Param2 Team
    @Param3 Int
    @Param4 Int
    @Param5 Winsize
    @Return void
*/
void endRound(Team *team1, Team* team2, int maximumCE, int end, Winsize sz);

/*
    Gives reward to the winner
    @Param1 Team
    @Param2 Team
    @Param3 Int
    @Return void
*/
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
