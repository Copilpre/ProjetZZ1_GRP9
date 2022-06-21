#include "table.h"
#include <SDL2/SDL.h>

#define TAILLE 9

typedef struct point {
	int i ;
	int j ;
} point_t ;

typedef struct table {
	int survie[TAILLE][TAILLE] ;
	int naissance[TAILLE][TAILLE] ;
} table_t ;

point_t voisinHaut(table_t * T, int i, int j) {
	point p = {i , j} ;
	if (i-1 < 0) {
		p->i = TAILLE-1 ;
	} else {
		p->i = i-1 ;
	} 
	p->j = j ;
	return p ;
}

point_t voisinBas(table_t * T, int i, int j) {
	point p ;
	if (i+1 > TAILLE-1) {
		p->i = 0 ;
	} else {
		p->i = i+1 ;
	} 
	p->j = j ;
	return p ;
}

point_t voisinDroite(table_t * T, int i, int j) { 
	point p ;
	if (i+1>TAILLE-1 && j+1>TAILLE-1 ) {
		p->i = 0 ;
		p->j = 0 ;
	} else {
		p->i = i+1 ;
		p->j = j+1 ;
	} 
	return p ;
} 

point_t voisinGauche(table_t * T, int i, int j) {
	point p = {i , j} ;
	if (i-1 < 0 && j-1 < 0) {
		p->i = TAILLE-1 ;
		p->j = TAILLE-1 ;
	} else {
		p->i = i-1 ;
		p->j = j-1 ;
	}
	return p ;
}

void gestionVie(table_t * T, int i, int j) {
	if (i == 0 || j == 0) {
		int e1 = 

		if (T->survie[i][j] == 1) {
			T->survie[i][j] = 0 ;
		}
	}
}

void gestionMort(table_t * T, int i, int j) {
	if (T->naissance[i][j] ==) {

	}
}


