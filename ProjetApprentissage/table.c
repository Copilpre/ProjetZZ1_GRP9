
#include "table.h"

typedef struct couple {
	int act ;
	int rec ;
} couple_t ;

typedef struct cellule {
	couple_t C[NB_ACTION] ;
} cellule_t ;

typedef struct qtable {
	cellule_t  T[TAILLE][TAILLE][TAILLE] ;
} qtable_t ;

couple_t * allocCouple() {
	couple_t * nouv = NULL ;
	nouv = malloc(sizeof(couple_t)) ;
	return nouv ;
}

cellule_t * allocCellule() {
	cellule_t * nouv = NULL ;
	nouv = malloc(sizeof(cellule_t)) ;
	nouv->C[0] = malloc(sizeof(couple_t)) ;
	nouv->C[1] = malloc(sizeof(couple_t)) ;
	nouv->C[2] = malloc(sizeof(couple_t)) ;
	return nouv ;
}

qtable_t * allocTable(int taille) {
	qtable_t * nouv = NULL ;
	nouv = malloc(sizeof(qtable_t)) ;
	nouv->C = malloc(sizeof(cellule_t**)*TAILLE) ;
	int i, j ;

	for (i=0 ; i<TAILLE; i++) 
	{
		for (j=0; j<TAILLE; j++) 
		{
			for (k=0; k<TAILLE; k++) 
			{
				nouv->C[i][j][k] = 
					(malloc(sizeof(cellule_t)*TAILLE)) ;
			}
		}
	}	

	return nouv ;
}

// Ici vous pouvez plus mettre en le niveau des barres b1 b2 b3
// On veut aller jusqu'à nb_voisin dans le mise à
// jour (selon le cas il faudrait determiner quoi retourner)

// Cas du max 

int maxChoice(qtable * tab, i, j, k) {
	int max ;
	if (ta[i][j][k][0].rec > tab[i][j][k][1].rec)
	{
		if (ta[i][j][k][0].rec > tab[i][j][k][2].rec) {
			max = tab[i][j][k][0].act ;
		}
		else {
			max = tab[i][j][k][2].act ;
		}
	}
	else
	{
		if (ta[i][j][k][1].rec > tab[i][j][k][2].rec) {
			max = tab[i][j][k][1].act ;
		}
		else {
			max = tab[i][j][k][2].act ;
		}
	}

	return max ;
}

// Cas aleatoire

int aleaChoice(qtable * tab, i, j, k) {
	int alea = rand() % 3 ;
	return tab[i][j][k][alea].act ;
}

qtable_t * loadTable(qtable_t * tab, barre_t ** B, char choice) {
	int i = B[0]->level / PAS ;
	int j = B[1]->level / PAS ;
	int k = B[2]->level / PAS ;

	// Par defaut le choix est aléatoire est aleatoire

	if (choice == 'm') {
		tab[i][j][k] = maxChoice(tab, i, j, k) ;
	}  
	else {
		tab[i][j][k] = aleaChoice(tab, i,  j, k) ;
	}
	return tab ;
}

void tabToFile(char * filename, qtable_t * tab) {
	
	int i, j, k ;

	FILE * fp = fopen(filename, "r") ;
	
	for (i=0 ; i<TAILLE; i++) {
	for (j=0; j<TAILLE; j++)  {
		for (k=0; k<TAILLE; k++) {
			fprintf(fp, "%d %d %d %d %d\n", 
				i, j, k, tab[i][j][k][0].act,
					 tab[i][j][k][0].rect) ;
			fprintf(fp, "%d %d %d %d %d\n", 
				i, j, k, tab[i][j][k][1].act,
					 tab[i][j][k][1].rect) ;
			fprintf(fp, "%d %d %d %d %d\n", 
				i, j, k, tab[i][j][k][2].act,
					 tab[i][j][k][2].rect) ;
		}
	}
	}

}

qtable_t *  fileTotab(char * filename) {

	int i, j, k ;

	FILE * fp = fopen(filename, "r") ;
	size_t size = 0 ;
	char * sauv = NULL ;

	while (getline	
}

 
