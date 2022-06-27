#ifndef __TABLE__
#define __TABLE__

#include <stdio.h>
#include "fonction.h"

#define  NB_ACTION 3

typedef struct couple {
	int act ;
	int rec ;
} couple_t ;

typedef struct cellule {
	couple_t C[NB_ACTION] ;
} cellule_t ;

typedef struct qtable {
	cellule_t *** T ;
} qtable_t ;

couple_t * allocCouple() ;

cellule_t * allocCellule() ;

qtable_t * allocTable(int taille) ;

// Ici vous pouvez plus mettre en paramettre i,j,k
// On veut aller jusqu'à nb_voisin dans le mise à
// jour

qtable_t * loadTable(qtable_t * tab, barre_t * B) ;

void tabToFile(char * filename, qtable_t * tab) ;

qtable_t *  fileTotab(char * filename) ; 


#endif 
