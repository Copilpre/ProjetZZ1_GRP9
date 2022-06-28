#include "qtable.h"


// action vaut 0 alors -> le tamago mange donc s.x croit
// action vaut 1 alors -> le tamago joue donc s.y croit
// action vaut 2 alors -> le tamago dort donc s.z croit

etat_t etatSuivant(etat_t s, int action, int pas) {
	etat_t suiv = s ;
	if (action == 0) {
		suiv.x += (pas * 3) ;
		suiv.y -= pas ;
		suiv.z -= pas ;
	}
	if (action == 1) {
		suiv.x -= pas ;
		suiv.y += (pas * 3) ;
		suiv.z -= pas ;
	}
	if (action == 2) {
		suiv.x -= pas ;
		suiv.y -= pas ;
		suiv.z += (pas * 3) ;
	}		
	return suiv ;
}


// Cette fonction permet de sauvegarder le contexte


pile_t * sauvQtab(int **** QT, int greedy, etat_t s) 
{
	lineTab_t line ;
	int qua1, qua2, qua3 ; 
	int i = 0, defaite = 1, alea, action ;
	line.T[0] = line.T[1] = line.T[2] = line.T[3] = 0 ;

	pile_t * p = init_pile(NB_ITER) ;

	while ( defaite && i < NB_ITER) {
		alea = rand() % NB_ITER ;
		if (greedy > alea) { 
			// choix d'une action aleatoire
			action = rand() % NB_ACTION ;
		}
		else {
			// Action de plus grande qualité
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

		s = etatSuivant(s, action, PAS) ;	

		// Cas ou on a une barre à zero
		defaite = s.x * s.y * s.z ;
		// Cas ou on a une barre à 1 ou 10
		if (defaite != 0) 
		if (s.x == 1 || s.y == 1 || s.z == 1) {
			defaite = 0 ;
		}
		line.T[0] = s.x ;
		line.T[1] = s.y ;
		line.T[2] = s.z ;
		line.T[3] = action ;				
		p = empiler(p, line) ;
		i++ ;
	}

	return p ;
}


int **** loadQtab(int **** QT, pile_t * p, float eps, int gamma) 
{
	// Ici la bonne valeur de r à déterminer
	etat_t s1, s2 ;
	int act, qua1, qua2, qua3, maxQ , r = 10, q_actuel ;
	lineTab_t QT_futur , QT_actuel ;
	float r = 1/exp(NB_ITER-1) ;
	QT_futur = QT[NB_ITER-1] + eps*(r*NB_ITER - QT[NB_ITER-1]) ;

	while (p != NULL) {	

		// Q actuel est une liste [i, j, k, act] 

		//QT_actuel = QT[i][j][k][act] ;
 		s1.x = QT_futur.T[0] ;
		s1.y = QT_futur.T[1] ;
		s1.z = QT_futur.T[2] ;
		act  = QT_futur.T[3] ;

		p = depiler(p, &QT_actuel) ;
 		s2.x = QT_actuel.T[0] ;
		s2.y = QT_actuel.T[1] ;
		s2.z = QT_actuel.T[2] ;
		qua1 = QT[s2.x][s2.y][s2.z][0] ;
		qua2 = QT[s2.x][s2.y][s2.z][1] ;
		qua3 = QT[s2.x][s2.y][s2.z][2] ;
	
		if (qua1 > qua2) {
			if (qua1 > qua3) {
				maxQ = qua1 ;
			}
			else {
				maxQ = qua3 ;
			}
		}
		else {
			if (qua2 > qua3) {
				maxQ = qua2 ;
			}
			else {
				maxQ = qua3 ;
			}
		}

		q_actuel = QT[s1.x][s1.y][s1.z][act] ;
	
		QT[s1.x][s1.y][s1.z][act] = q_actuel + eps * (
				(int)(r + gamma * maxQ) - q_actuel) ;
	} 

	return QT ;
}
