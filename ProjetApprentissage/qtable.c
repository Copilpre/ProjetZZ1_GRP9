#include "qtable.h"


// action vaut 0 alors -> le tamago mange donc s.x croit
// action vaut 1 alors -> le tamago joue donc s.y croit
// action vaut 2 alors -> le tamago dort donc s.z croit

etat_t etatSuivant(etat_t s, int action, int pas) {
	if (action == 0) {
		s.x += (pas * 3) ;
		s.y -= pas ;
		s.z -= pas ;
	}
	if (action == 1) {
		s.x -= pas ;
		s.y += (pas * 3) ;
		s.z -= pas ;
	}
	if (action == 2) {
		s.x -= pas ;
		s.y -= pas ;
		s.z += (pas * 3) ;
	}		
	return s ;
}


// Cette fonction permet de sauvegarder le contexte


pile_t * sauvQtab(float QT[I_SIZE][J_SIZE][K_SIZE][NB_ACTION] , 
						int greedy, etat_t s) 
{
	lineTab_t * line = malloc(sizeof(lineTab_t));
	line->r = 0.0 ;
	float qua1, qua2, qua3, r = 0.0 ; 
	int i = 0, defaite = 1, alea, action ;
	line->T[0] = s.x;
	line->T[1] = s.y;
	line->T[2] = s.z;

	pile_t * p = init_pile(NB_ITER) ;

	while ( (defaite != 0) && (i < NB_ITER) ) {
		alea = rand() % NB_ITER ;
		if (greedy > alea) { 
			// choix d'une action aleatoire
			action = rand() % NB_ACTION ;
		}
		else {
			// Action de plus grande qualité
			qua1 = QT[s.x][s.y][s.z][0] ;
			qua2 = QT[s.x][s.y][s.z][1] ;
			qua3 = QT[s.x][s.y][s.z][2] ;
			if (qua1 > qua2) {
				if (qua1 > qua3) {
					action = 0 ;
				}
				else {
					action = 2 ;
				}
			} 
			else {
				if (qua3 > qua2) {
					action = 2 ;
				}
				else {
					action = 1 ;
				}
			}
		}
		r = 1 / ( 1 + exp( NB_ITER - i ) ) ;

		line->T[3] = action ;
		line->r = r ;

		p = empiler(p, *line) ;
		s = etatSuivant(s, action, PAS) ;	

		// Cas ou on a une barre à zero
		defaite = (s.x) * (s.y) * (s.z) ;
		// Cas ou on a une barre à 10
		if (defaite != 0) 
		if (s.x >= 10 || s.y >= 10 || s.z >= 10) {
			defaite = 0 ;
		}

		line->T[0] = s.x ;
		line->T[1] = s.y ;
		line->T[2] = s.z ;
		i++ ;
	}
		
	return p ;
}


void loadQtab(float QT[I_SIZE][J_SIZE][K_SIZE][NB_ACTION] , 
				pile_t * p, float eps, int gamma)
{
	etat_t s1, s2 ;
	int act, j;
	float qua1, qua2, qua3, maxQ, q_actuel ;
	lineTab_t QT_futur , QT_actuel ;
	
	p = depiler(p, &QT_actuel) ;
	s1.x = QT_actuel.T[0] ;
	s1.y = QT_actuel.T[1] ;
	s1.z = QT_actuel.T[2] ;

	float r = QT_actuel.r ;
	
	QT[s1.x][s1.y][s1.z][QT_actuel.T[3]] = QT[s1.x][s1.y][s1.z][QT_actuel.T[3]]
				+ eps*(r*NB_ITER - QT[s1.x][s1.y][s1.z][QT_actuel.T[3]]) ;
	QT_futur = QT_actuel ;

	while (p->nbElts > -1) {	
	

 		s1.x = QT_futur.T[0] ;
		s1.y = QT_futur.T[1] ;
		s1.z = QT_futur.T[2] ;
		act  = QT_futur.T[3] ;

		p = depiler(p, &QT_actuel) ;
 		s2.x = QT_actuel.T[0] ;
		s2.y = QT_actuel.T[1] ;
		s2.z = QT_actuel.T[2] ;

		r = QT_actuel.r ;
		qua1 = QT[s2.x][s2.y][s2.z][0] ;
		qua2 = QT[s2.x][s2.y][s2.z][1] ;
		qua3 = QT[s2.x][s2.y][s2.z][2] ;
		if (qua1 > qua2) {
			if (qua1 > qua3) {
				maxQ = 0 ;
			}
			else {
				maxQ = 2 ;
			}
		} 
		else {
			if (qua3 > qua2) {
				maxQ = 2 ;
			}
			else {
				maxQ = 1 ;
			}
		}

		q_actuel = QT[s1.x][s1.y][s1.z][act] ;
	
		QT[s1.x][s1.y][s1.z][act] = q_actuel + eps * (
				(r + gamma * maxQ) - q_actuel) ;
	} 

}

void afficherTab(float QT[I_SIZE][J_SIZE][K_SIZE][NB_ACTION]) {
	int i, j, k, a ;
	for (i=0; i<I_SIZE; i++) 
	{
		for (j=0; j<J_SIZE; j++) 
		{
			for (k=0; k<K_SIZE; k++)
			{
				for (a=0; a<NB_ACTION; a++)
				{
					if (j > 0 && i > 0 && k > 0)
					if (i <= 10 && j <= 10 && k <= 10)
					printf("%d %d %d %a %f\n",
						i, j, k, a, QT[i][j][k][a]) ;
				}
			}
		}	
	}
} 
