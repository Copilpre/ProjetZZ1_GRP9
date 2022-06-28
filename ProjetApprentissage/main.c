#include "qtable.h"
#include <time.h>

#define eps 0.5
#define gamma 0.5


int main(){
   
	//génération état aléatoire

	etat_t etat;
	pile_t *p;
	srand(time(NULL));
	float Qtable[I_SIZE][J_SIZE][K_SIZE][NB_ACTION];
	int x, y, z, i, j, k, a, greedy = 200;

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

   	// PHASE DE CHARGEMENT DE LA Q TABLE
		etat.x = rand() % 10;
		etat.y = rand() % 10;
		etat.z = rand() % 10;
		greedy -= 1;
		p = sauvQtab(Qtable , greedy, etat);
		afficherPile(p) ;
//    		loadQtab(Qtable, p, eps, gamma);
 
	/*for(int i = 0; i < NB_ITER; i++) {
	
		etat.x = rand() % 10;
		etat.y = rand() % 10;
		etat.z = rand() % 10;
		greedy -= 1;

		p = sauvQtab(Qtable , greedy, etat);

    		loadQtab(Qtable, p, eps, gamma);

	}*/

	afficherTab(Qtable) ;
 
	libererPile(p) ;

	return EXIT_SUCCESS ;
}
