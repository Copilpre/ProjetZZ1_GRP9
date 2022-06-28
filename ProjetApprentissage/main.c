
#include "qtable.h"

#include <time.h>



#define nbIte 1000
#define learnRate 1
#define discount 0.5

#define NB_ITER 50
#define NB_ACTION 3
#define eps 0.5
#define gamma 0.5




int main(){
   
//génération état aléatoire
int x, y, z;
etat_t etat;
pile_t *p;


int greedy = 200;

    float Qtable[11][11][11][3];
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
	etat.x = rand() % 10;
	etat.y = rand() % 10;
	etat.z = rand() % 10;

    p = sauvQtab(Qtable , greedy, etat);
    
    
    
    //for(int i = 0; i < NB_ITER; i++){
	
	//etat.x = rand() % 10;
	//etat.y = rand() % 10;
	//etat.z = rand() % 10;
	//greedy += -1;

	//p = sauvQtab(Qtable , greedy, etat);

    //loadQtab(Qtable, p, eps, gamma);


    return 0;

//} 











}