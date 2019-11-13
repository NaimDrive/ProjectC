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

typedef union strat
{
    Commande commande;
    Operateur operateur;
} Strat;

typedef struct strategy {
    int num;
    char *nom;
    Strat strat;
    Strategy *suivant;
} Strategy;

int readStrat(Strategy *strategy,char *fileName);

Strategy ** initStrat(int argc, char *argv[]);

#endif