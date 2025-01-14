#ifndef __STRAT_H__
#define __STRAT_H__

typedef union unionFonction {
    int (*buyWeapon)(Weapon *, Team *);
    int (*buyProtection)(Protection *, Team *);
    int (*buyCare)(Healing *, Team *);
    void (*buyCA)(Team *, int);
    void (*useWeapon)(Team *, Team *, int, int);
    void (*useProtection)(Team *);
    void (*useCare)(Team *, int);
    void (*moveForward)(Team *, Team *, int);
    void (*moveBackward)(Team *, int, int);
} UnionFonction;

typedef enum enumFonction{
    buy_weapon,
    buy_protection,
    buy_care,
    buy_CA,
    use_weapon,
    use_protection,
    use_care,
    move_forward,
    move_backward
} EnumFonction;

typedef union unionParametre {
    Team *team;
    Weapon *weapon;
    Protection *protection;
    Healing *healing;
    int entier;
} UnionParametre;


typedef struct commande {
    UnionFonction commande;
    EnumFonction enumCommande;
    UnionParametre *parametres; // Tableau des paramètres de la fonction
    int nbParametres;
} Commande;

typedef struct operateur {
    int op1;
    int op2;
    char *operateur;
    int nbParametres;
    char *chaine;
} Operateur;

typedef union unionStrat {
    Commande commande;
    Operateur operateur;
} UnionStrat;

typedef enum enumStrat{
    commande,
    operateur,
    fusion,
    retour
} EnumStrat;

typedef struct strat {
    UnionStrat unionStrat;
    EnumStrat enumStrat;
    struct strat *suivant; // The next by default
    struct strat *suivantSinon; // The next if the strategy is an operator and the condition return false.
} Strat;


typedef struct strategy {
    int num;
    char *nom;
    int coutCE;
    Team *allyTeam;
    Team *enemyTeam;
    Strat *strat; // Commands of the strategy
    Strat *initStrategy; // Commands to choose the weapon, the protection, the care and buy CA.
} Strategy;

typedef struct package {
    Champion **champions;
    Weapon **weapons;
    Protection **protections;
    Healing **healings;
    Strategy **strategies;
    int *nbChampions;
    int *nbWeapons;
    int *nbProtections;
    int *nbHealings;
    int *nbStrategies;
} Package;


int readStrat(Strategy **strategy, char *fileName, Champion **champions, Weapon **weapons, Protection **protections, Healing **healings, int *nbChampions, int *nbWeapons, int *nbProtections, int *nbHealings, Team *team1, Team *team2, Winsize screenSize);

Strategy ** initStrat(int argc, char *argv[], int *nbStrat, Champion **champions, Weapon **weapons, Protection **protections, Healing **healings, int *nbChampions, int *nbWeapons, int *nbProtections, int *nbHealings, Team *team1, Team *team2, Winsize screenSize);

Strat * strategyCreateChoose(Strategy **s, char *buffer, Champion **champions, Weapon **weapons, Protection **protections, Healing **healings, int *nbChampions, int *nbWeapons, int *nbProtections, int *nbHealings, Team *team1, Team *team2);

Strat * strategyCreateAddCA(Strategy **s, char *mot);

Strat * strategyCreateUse(char *mot, Winsize screenSize);

Strat * strategyCreateMove(char *mot, Winsize screenSize);

Strat * strategyCreateFusion();

Strat * strategyCreateReturn();

int initStructure(Strategy **s, char *buffer, FILE *fichier, int SIZE, char *delimiters, Champion **champions, Weapon **weapons, Protection **protections, Healing **healings, int *nbChampions, int *nbWeapons, int *nbProtections, int *nbHealings, Team *team1, Team *team2, Winsize screenSize);

void addInInitStrategy(Strategy **s, Strat *strat);

Strat * lastStrat(Strat *strat);

void addInStratStrategy(Strategy **s, Strat *strat);

void useInitStrat(Strat *strat);

void useStrat(Strat *strat, Team *team, Team *opponent, int screenSize);

void initializeTheCombatStrategy(Strategy **strategy, Team *team1, Team *team2);

void initStrategyInFight(Strategy **strategy);

void initStrategyTeams(Strat **strat, Strategy *strategy);

void catchConditions(Strategy *strategy, int *entier, int *entier2, char *mot);

Strat * copyStrat(Strat *strat, Strategy *strategy);

Strategy * copyStrategy(Strategy *strategy);

#endif