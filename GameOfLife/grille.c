#include "table.h"
#include "config.c"
#define TAILLE 20

int ** tab ;

int ** initTab(int taille) {

	tab = malloc(sizeof(int*)*TAILLE) ;

	for (int i=0; i<TAILLE; i++) {
		tab[i] = calloc(tab[i], sizeof(in)*TAILLE) ;
	}

	return tab ;
}

// Ici Il faudra inclure ce que Conrentin a fait
// Pour compter le nombre de voisin


int ** SetChangeInTab(int ** tab, int i, int j, SDL_bool on) {
	if (on == SDL_TRUE) {
		tab[i][j] = 1 ;
	} else {
		tab[i][j] = 0 ;
	}
	return tab ;
}


SDL_Color fromWindowToTab(SDL_Renderer * renderer, int taille, int w, int h) {

	int r, g, b, a , i, j ;

	for (i=0; i<taille; i+=w) {
		for (j=0; j<taille; j+=h) {
			if (SDL_GetRenderDrawColor(renderer, r, g, b, a) != 0)
				SDL_ErrorCase("Trouble with get color") ;
		}
	}

	SDL_Color color = {r, g, b, a} ;

	return color ;
}
