#include <stdio.h>
#include <stdlib.h>
#include "pile.h"
#include <time.h>



#define nbIte 1000
#define learnRate 1
#define discount 0.5

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


qtab_t loadQtab(qtab_t QT, int greedy, etat_t s) {

	int n = 0, i = 0, defaite = 1, x = 0, alea, action ;
	lineTab_t line = {0, 0, 0, 0} ;
	int qua1, qua2, qua3 ; 
	pile_t * p = init_pile(NB_ITER) ;

	while ( defaite && i < NB_ITER) {
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

		// Mettre à jour le QT	
		//QT[s.x][s.y][s.z][action] = ;	
		
		// Cas ou on a une barre à zero
		defaite = s.x * s.y * s.z ;
		// Cas ou on a une barre à 1 ou 10
		if (defaite != 0) 
		if (s.x == 1 || s.y == 1 || s.z == 1)
		defaite = 0 ;
		line->T[0] = s.x ;
		line->T[1] = s.y ;
		line->T[2] = s.z ;
		line->T[3] = action ;				
		p = empiler(p, line) ;
		i++ ;
	}

	return QT ;
}


lineTab_t calculQ(pile_t * pile,int nbite,int ***** qtable,lineTab_t q1,int q0){
    lineTab_t q;
    pile = depiler(pile,&q);
    int ite = 1/(1+exp(-nbIte));
    q0 = *qtable[q.T[0]][q.T[1]][q.T[2]][q.T[3]];


    int maxQ1 = *qtable[q1.T[0]][q1.T[1]][q1.T[2]][0];
    for (int i = 1; i < 3; i++){
        if (maxQ1 < *qtable[q1.T[0]][q1.T[1]][q1.T[2]][i]){
            maxQ1 = *qtable[q1.T[0]][q1.T[1]][q1.T[2]][i];
        }
    }

    q0 += learnRate * (ite + discount * maxQ1 - q0);

    *qtable[q.T[0]][q.T[1]][q.T[2]][q.T[3]]=q0;
    return q;
}


//CODE DE LA QUALITE DE Q (à ne pas mettre dans calculQ)

table[q.T[0]][q.T[1]][q.T[2]][q.T[3]]= learnRate * (ite - table[q.T[0]][q.T[1]][q.T[2]][q.T[3]]);



int main(){
   
//génération état aléatoire
int x, y, z;
etat_t etat;

int greedy = 200

    int Qtable[11][11][11][3];
    int i,j,k,a;
    for(i = 0; i<11; i++){
        for(j = 0; j<11; j++){
            for(k = 0; k<11; k++){
                for(a = 0; a<3; a++){
                    Qtable[i][j][k][a] = 0; 
                } 
            } 
        } 
    } 

for(int i = 0; i < NB_ITER; i++){
	
	etat.x = rand() % 10;
	etat.y = rand() % 10;
	etat.z = rand() % 10;
	greedy += -1;
	loadQtab(Qtable , greedy, etat);

} 











}