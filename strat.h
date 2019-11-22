#ifndef __STRAT_H__
#define __STRAT_H__

typedef struct commande {
    char *commande;
} Commande;

typedef struct operateur {
    int op1;
    int op2;
    char *operateur;
} Operateur;

typedef union unionStrat {
    Commande commande;
    Operateur operateur;
} UnionStrat;

typedef enum enumStrat{
    commande,
    operateur
} EnumStrat;

typedef struct strat
{
    UnionStrat unionStrat;
    EnumStrat enumStrat;
} Strat;


typedef struct strategy {
    int num;
    char *nom;
    Strat strat; // Commands of the strategy
    Strat initStrategy; // Commands to choose the weapon, the protection, the care and buy CA.
    struct strategy *suivant; // The next by default
    struct strategy *suivantSinon; // The next if the strategy is an operator and the condition return false.
} Strategy;

int readStrat(Strategy *strategy,char *fileName);

Strategy ** initStrat(int argc, char *argv[]);

void compareChain(Strategy *strategy, char *buffer);

#endif