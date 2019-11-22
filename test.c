#include "strat.h"
#include <stdio.h>

void afficherTypeStrat(Strategy *s) {
    printf("Num : %d\nNom : %s\n", s->num, s->nom);

    if(s->strat.enumStrat == commande) {
        printf("Strat : Commande\n");
        printf("Commande : %s\n", s->strat.unionStrat.commande.commande);
    } else if(s->strat.enumStrat == operateur) {
        printf("Strat : Opérateur\n");
        printf("%d %s %d\n", s->strat.unionStrat.operateur.op1, s->strat.unionStrat.operateur.operateur, s->strat.unionStrat.operateur.op2);
    }
    printf("\n");
}

void useCommande(Strategy *s) {
    while(s != NULL) {
        if(s->strat.enumStrat == commande) {
            printf("Execution de ... %s\n", s->strat.unionStrat.commande.commande);
            s = s->suivant;
        } else if(s->strat.enumStrat == operateur) {
            int op1, op2;
            op1 = s->strat.unionStrat.operateur.op1;
            op2 = s->strat.unionStrat.operateur.op2;

            if(op1 = s->strat.unionStrat.operateur.operateur == ">") {
                if(op1 > op2) {
                    printf("Condition %d > %d : true\n", op1, op2);
                    s = s->suivant;
                } else {
                    printf("Condition %d > %d : false\n", op1, op2);
                    s = s->suivantSinon;
                }
            } else if(op1 = s->strat.unionStrat.operateur.operateur == "<") {
                if(op1 < op2) {
                    printf("Condition %d < %d : true\n", op1, op2);
                    s = s->suivant;
                } else {
                    printf("Condition %d < %d : false\n", op1, op2);
                    s = s->suivantSinon;
                }
            }
        }
    }
}

int main(void) {
    Strategy s, s2, s3;

    // Commande
    s.num = 1;
    s.nom = "Je suis premier";
    s.strat.enumStrat = commande;
    s.strat.unionStrat.commande.commande = "use protection";
    s.suivant = &s3;
    s.suivantSinon = NULL;

    // Opérateur
    s2.num = 2;
    s2.nom = "Je m'en fous";
    s2.strat.enumStrat = operateur;
    s2.strat.unionStrat.operateur.op1 = 1;
    s2.strat.unionStrat.operateur.op2 = 5;
    s2.strat.unionStrat.operateur.operateur = "<";
    s2.suivant = &s;
    s2.suivantSinon = &s3;

    // Commande
    s3.num = 1;
    s3.nom = "Sinon";
    s3.strat.enumStrat = commande;
    s3.strat.unionStrat.commande.commande = "use care";
    s3.suivant = NULL;
    s3.suivantSinon = NULL;
    
    
    useCommande(&s2);

    // On pourra même faire un type avec op1 et op2 qui sont des pointeurs d'entier.
    // Car là à chaque fin de fight, les valeurs ne sont pas changée alors que si on met des pointeurs les valeurs seront changées automatiquement !!!
    // PUTAIN JE SUIS TROP FORT !!!

    return 0;
}