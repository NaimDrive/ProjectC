#include "strat.h"
#include <stdio.h>

void useCommandes(Strategy *s) {
    Strat *strat = s->strat;
    printf("Stratégie : %s\n", s->nom);
    while(strat != NULL) {
        if(strat->enumStrat == commande) {
            // printf("Execution de ... %s\n", strat->unionStrat.commande.commande);
            strat = strat->suivant;
        } else if(strat->enumStrat == operateur) {
            int op1, op2;
            op1 = strat->unionStrat.operateur.op1;
            op2 =strat->unionStrat.operateur.op2;

            if(strat->unionStrat.operateur.operateur == ">") {
                if(op1 > op2) {
                    printf("Condition %d > %d : true\n", op1, op2);
                    strat = strat->suivant;
                } else {
                    printf("Condition %d > %d : false\n", op1, op2);
                    strat = strat->suivantSinon;
                }
            } else if(strat->unionStrat.operateur.operateur == "<") {
                if(op1 < op2) {
                    printf("Condition %d < %d : true\n", op1, op2);
                    strat = strat->suivant;
                } else {
                    printf("Condition %d < %d : false\n", op1, op2);
                    strat = strat->suivantSinon;
                }
            }
        }
    }
}

int main(void) {
    Strategy strat;
    Strat s, s2, s3, init1, init2;

    // Commande
    strat.num = 1;
    strat.nom = "Je suis une stratégie";

    init1.enumStrat = commande;
    // init1.unionStrat.commande.commande = "choose weapon couteau";
    init1.suivant = &init2;
    init1.suivantSinon = NULL;

    init2.enumStrat = commande;
    // init2.unionStrat.commande.commande = "choose care potion";
    init2.suivant = NULL;
    init2.suivantSinon = NULL;

    s.enumStrat = commande;
    // s.unionStrat.commande.commande = "use protection";
    s.suivant = &s3;
    s.suivantSinon = NULL;

    // Opérateur
    s2.enumStrat = operateur;
    s2.unionStrat.operateur.op1 = 1;
    s2.unionStrat.operateur.op2 = 5;
    s2.unionStrat.operateur.operateur = "<";
    s2.suivant = &s;
    s2.suivantSinon = &s3;

    // Commande
    s3.enumStrat = commande;
    // s3.unionStrat.commande.commande = "use care";
    s3.suivant = NULL;
    s3.suivantSinon = NULL;

    strat.initStrategy = &init1;
    strat.strat = &s2;
    
    useCommandes(&strat);

    return 0;
}