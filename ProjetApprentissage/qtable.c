#include "qtable.h"


// action vaut 0 alors -> le tamago mange donc s.x croit
// action vaut 1 alors -> le tamago joue donc s.y croit
// action vaut 2 alors -> le tamago dort donc s.z croit

etat_t etatSuivant(etat_t s, int action, int pas) {
	if (action == 0) {
		s.x += (pas * 2) ;
		s.y -= pas ;
		s.z -= pas ;
	}
	if (action == 1) {
		s.x -= pas ;
		s.y += (pas * 2) ;
		s.z -= pas ;
	}
	if (action == 2) {
		s.x -= pas ;
		s.y -= pas ;
		s.z += (pas * 2) ;
	}		
	return s ;
}


// Cette fonction permet de sauvegarder le contexte


pile_t * sauvQtab(float QT[I_SIZE][J_SIZE][K_SIZE][NB_ACTION] , 
						int greedy, etat_t s) 
{
	srand(time(NULL)) ;
	lineTab_t * line = malloc(sizeof(lineTab_t));
	line->r = 0.0 ;
	float qua1, qua2, qua3, r = 0.0 ; 
	int i = 1, defaite = 1, alea, action ;
	line->T[0] = s.x;
	line->T[1] = s.y;
	line->T[2] = s.z;
	float facteur = 0.0015 ;

	pile_t * p = init_pile(NB_ITER) ;

	while ( (defaite != 0) && (i < NB_ITER+1) ) {
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

		r = facteur * i ;
		line->T[3] = action ;
		line->r = r ;


		// Cas ou on a une barre à zero
		if (s.x <= 0 || s.y <= 0 || s.z <= 0) {
			defaite = 0 ;
		} 
		else { 	
		// Cas ou on a une barre à 10
		if (s.x >= 10 || s.y >= 10 || s.z >= 10) {
			defaite = 0 ;
		} 
		else {
			line->T[0] = s.x ;
			line->T[1] = s.y ;
			line->T[2] = s.z ;
			p = empiler(p, *line) ;
			s = etatSuivant(s, action, PAS) ;	
		}
		}

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

	while (p->position > -1) {	
	
 		s1.x = QT_futur.T[0] ;
		s1.y = QT_futur.T[1] ;
		s1.z = QT_futur.T[2] ;
		r = QT_futur.r ;
		//printf("%f ::: ", r) ;
		p = depiler(p, &QT_actuel) ;
 		s2.x = QT_actuel.T[0] ;
		s2.y = QT_actuel.T[1] ;
		s2.z = QT_actuel.T[2] ;
		act  = QT_actuel.T[3] ;

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
			if (qua3 > qua2) {
				maxQ = qua3 ;
			}
			else {
				maxQ = qua2 ;
			}
		}

		q_actuel = QT[s2.x][s2.y][s2.z][act] ;
	
		QT[s2.x][s2.y][s2.z][act] = q_actuel + eps * (
				(r + gamma * maxQ) - q_actuel) ;

		QT_futur = QT_actuel ;

		printf("load q_actuel %d %d %d %d %f\n", 
			s2.x, s2.y, s2.z, act, QT[s2.x][s2.y][s2.z][act]) ;
	} 

}

void afficherTab(float QT[I_SIZE][J_SIZE][K_SIZE][NB_ACTION]) 
{
	int i, j, k, a ;

	for (i=0; i<I_SIZE; i++) 
	{
		for (j=0; j<J_SIZE; j++) 
		{
			for (k=0; k<K_SIZE; k++)
			{
				for (a=0; a<NB_ACTION; a++)
				{
					if (QT[i][j][k][a] != 0)
					printf("%d %d %d %a %0.3f\n",
						i, j, k, a, QT[i][j][k][a]) ;
				}
			}
		}	
	}
} 
