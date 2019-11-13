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

int main(void) {
    Strategy s, s2;
    s.num = 1;
    s.nom = "Je suis premier";
    s.suivant = &s2;

    s2.num = 2;
    s2.nom = "Je m'en fous";
    s2.suivant = NULL;

    // Commande
    s.strat.enumStrat = commande;
    s.strat.unionStrat.commande.commande = "Je suis une magnifique commande !";
    afficherTypeStrat(&s);
    
    // Opérateur
    s2.strat.enumStrat = operateur;
    s2.strat.unionStrat.operateur.op1 = 1;
    s2.strat.unionStrat.operateur.op2 = 5;
    s2.strat.unionStrat.operateur.operateur = "+";
    afficherTypeStrat(s.suivant);

    return 0;
}