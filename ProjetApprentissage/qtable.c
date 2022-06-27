#include <stdio.h>
#include <stdlib.h>
#include "pile.h"

#define NB_ITER 200
#define NB_ACTION 3

typedef int **** qtab_t ;

// les niveau des barres sont les indices 
// du table raison pour laquelle on i, j, k
// la 4e valeur vaut {0, 1, 2} qui correspond 
// Vu que les indices correspondent aux valeurs 
// des barres 

typedef struct etat {
	int x ;
	int y ;
	int z ;
} etat_t ;


// action vaut 0 alors -> le tamago mange donc s.x croit
// action vaut 1 alors -> le tamago joue donc s.y croit
// action vaut 2 alors -> le tamago dort donc s.z croit


etat_t etatSuivant(etat_t s, int act, int pas) {
	etat_t suiv = s ;

	if (action == 0) {
		suiv.x += pas ;
		suiv.y -= pas ;
		suiv.z -= pas ;
	}
	if (action == 1) {
		suiv.x -= pas ;
		suiv.y += pas ;
		suiv.z -= pas ;
	}
	if (action == 2) {
		suiv.x -= pas ;
		suiv.y -= pas ;
		suiv.z += pas ;
	}		

	return suiv ;
}


qtab_t loadQtab(qtab_t QT, int greedy, etat_t s) {

	int n = 0, i = 0, defaite = 0, x = 0, alea, action ;
	lineTab_t line = {0, 0, 0, 0} ;
	int qua1, qua2, qua3 ; 

	pile_t * p = init_pile(NB_ITER) ;

	while ( !defaite && i < NB_ITER) {
		alea = rand() % NB_ITER ;
		if (greedy > alea) { 
			// choix d'une action aleatoire
			action = rand() % NB_ACTION ;
		}
		else {
			// choix de l'action la plus élévée
			qua1 = QT[s.x][s.y][s.z][0] ;
			qua2 = QT[s.x][s.y][s.z][1] ;
			qua3 = QT[s.x][s.y][s.z][1] ;
			if (qua1 > qua2) {
				if (qua1 > qua3) {
					action = 0 ;
				}
				else {
					action = 2 ;
				}
			}
			else {
				if (qua2 > qua3) {
					action = 1 ;
				}
				else {
					action = 2 ;
				}
			}
		}
		s = etatSuivant(s, action) ;	
	
		//QT[s.x][s.y][s.z]				

		line->T[0] = s.x ;
		line->T[1] = s.y ;
		line->T[2] = s.z ;
		line->T[3] = action ;				
		p = empiler(p, line) ;
		i++ ;
	}
	return QT ;
}
