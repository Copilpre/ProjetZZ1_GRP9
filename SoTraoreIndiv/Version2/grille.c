#include "grille.h"

int ** initGrille(int taille) {
	int ** Tab = malloc(sizeof(int*)*taille), i ;
	for (i=0; i<taille; i++) 
		Tab[i] = calloc(taille, sizeof(int)) ;
	return Tab ;
}
