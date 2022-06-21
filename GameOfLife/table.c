#include "table.h"
#include "config.c"
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
	point p ;
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
	point p ;
	if (i-1 < 0 && j-1 < 0) {
		p->i = TAILLE-1 ;
		p->j = TAILLE-1 ;
	} else {
		p->i = i-1 ;
		p->j = j-1 ;
	}
	return p ;
}

table_t * initTable(table_t * T) {
	int i, j ;
	for (i=0; i<TAILLE; i++) {
		for (j=0; j<TAILLE; j++) {
			T->survie[i][j] = 0 ;
			T->naissance[i][j] = 0 ;
		}
	}

}

void gestionVie(table_t * T, int i, int j) {

}

void gestionMort(table_t * T, int i, int j) {

}


