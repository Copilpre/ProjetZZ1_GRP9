#ifndef __PILE__
#define __PILE__

#include <stdio.h>

#include <stdlib.h>
#define TAILLE 4

typedef struct lineTab {
	int T[TAILLE] ;
} lineTab_t ;

typedef struct pile
{
    int nbElts;
    int position;
    lineTab_t * tab ; 
}pile_t;

pile_t * init_pile(int taille)


int EstVidePile(pile_t *p)

int empiler(pile_t * p, lineTab_t data)

pile_t* depiler(pile_t * p, lineTab_t * result)

void libererPile(pile_t * p)

void afficherPile(pile_t * p)

#endif
