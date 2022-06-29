#include "qtable.h"
#include <time.h>

#define NIVEAU_MAX 10
#define NIVEAU_MIN 0


int main(){

	// INITIALISATION POUR L'ALEATOIRE   
	srand(time(NULL)) ;

	// DECLARATION DES VARIABLES

	etat_t * etat = malloc(sizeof(etat_t)) ;
	pile_t *p ;
	float eps = 0.7, gamma = 0.65 ;
	float Qtable[I_SIZE][J_SIZE][K_SIZE][NB_ACTION];
	int x, y, z, i, j, k, a , greedy = 200;

	// INITIALISATION DE LA QTABLE

	for(i = 0; i<I_SIZE; i++)
	{
        	for(j = 0; j<J_SIZE; j++)
		{
            		for(k = 0; k<K_SIZE; k++)
			{
                		for(a = 0; a<3; a++)
				{
                    			Qtable[i][j][k][a] = 0; 
                		} 
            		} 
        	} 
        } 

 
	for(i = 0; i < NB_ITER; i++) {
		// CHOIX D'UN ETAT AU HAZAR
		etat->x = rand() % NIVEAU_MAX ;
		etat->y = rand() % NIVEAU_MAX ;
		etat->z = rand() % NIVEAU_MAX ;
		greedy -= 1;

		// SAUVEGARDE DU CONTEXT
		p = sauvQtab(Qtable, greedy, etat);
		// MISE A JOUR DE LA TABLE
    		loadQtab(Qtable, p, eps, gamma);
		//afficherPile(p) ;
		libererPile(p) ;
	}

	//afficherTab(Qtable) ;
 
Quit :
	if (p != NULL) {
		libererPile(p) ;
	}
	return EXIT_SUCCESS ;
}
