#include "grille.h"
#define TAILLE 20

int ** tab ;

int ** initTab(int taille) {

	tab = malloc(sizeof(int*)*taille) ;

	for (int i=0; i<taille; i++) {
		tab[i] = calloc(taille, sizeof(int)*TAILLE) ;
	}

	return tab ;
}


void clic(int type,int x, int y, int tailleC, int ** tab) {
	tab[x][y]=type;
}
