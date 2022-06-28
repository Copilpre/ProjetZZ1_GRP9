#ifndef __QTABLE__
#define __QTABLE__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pile.h"

#define NB_ITER 200
#define NB_ACTION 3
#define PAS 0.25

// les niveau des barres sont les indices 
// du table raison pour laquelle on i, j, k
// la 4e valeur vaut {0, 1, 2} qui correspond 
// Vu que les indices correspondent aux valeurs 
// des barres 

struct etat {
	int x ;
	int y ;
	int z ;
} ;

typedef struct etat etat_t ;


// action vaut 0 alors -> le tamago mange donc s.x croit
// action vaut 1 alors -> le tamago joue donc s.y croit
// action vaut 2 alors -> le tamago dort donc s.z croit

etat_t etatSuivant(etat_t s, int action, int pas) ;

// Cette permet un sauvegarde de contexte

pile_t * sauvQtab(float QT[11][11][11][3], int greedy, etat_t s) ;

void loadQtab(float QT[11][11][11][3], pile_t * p, float eps, int gamma);


#endif
