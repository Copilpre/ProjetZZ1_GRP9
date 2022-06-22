#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "config.c"
#define TAILLE 20

int ** tab ;

int ** initTab(int taille) {

	tab = malloc(sizeof(int*)*taille) ;

	for (int i=0; i<taille; i++) {
		tab[i] = calloc(taille, sizeof(int)*TAILLE) ;
	}

	return tab ;
}

// Ici Il faudra inclure ce que Conrentin a fait
// Pour compter le nombre de voisin

void clic(int type,int x, int y, int tailleC, int ** tab) {
	tab[x][y]=type;
}
