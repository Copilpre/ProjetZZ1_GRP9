#include "pile.h"
#include <math.h>

#define nbIte 1000
#define learnRate 1
#define discount 0.5

lineTab_t calculQ(pile_t * pile,int nbite,int ***** qtable,lineTab_t q1,int q0){
    lineTab_t q;
    pile = depiler(pile,&q);
    int ite = 1/(1+exp(-nbIte));
    q0 = *qtable[q.T[0]][q.T[1]][q.T[2]][q.T[3]];


    int maxQ1 = *qtable[q1.T[0]][q1.T[1]][q1.T[2]][0];
    for (int i = 1; i < 3; i++){
        if (maxQ1 < *qtable[q1.T[0]][q1.T[1]][q1.T[2]][i]){
            maxQ1 = *qtable[q1.T[0]][q1.T[1]][q1.T[2]][i];
        }
    }

    q0 += learnRate * (ite + discount * maxQ1 - q0);

    *qtable[q.T[0]][q.T[1]][q.T[2]][q.T[3]]=q0;
    return q;
}


//CODE DE LA QUALITE DE Q (à ne pas mettre dans calculQ)

table[q.T[0]][q.T[1]][q.T[2]][q.T[3]]= learnRate * (ite - table[q.T[0]][q.T[1]][q.T[2]][q.T[3]]);