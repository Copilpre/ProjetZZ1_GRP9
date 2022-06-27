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
{
    pile_t * nouv = NULL;
    nouv = malloc(sizeof(pile_t));
    nouv->nbElts = taille;
    nouv->tab = malloc(sizeof(lineTab_t) * taille);
    nouv->position = -1;
    return nouv;
}


int EstVidePile(pile_t *p)
{
    return (p->position == -1);
}


int empiler(pile_t * p, lineTab_t data)
{
    int boolean = 0;
    if (p->position < p->nbElts)
    {
        p->position += 1;
        p->tab[p->position]=data; 
        boolean = 1;
    } 
    return boolean;
}

pile_t* depiler(pile_t * p, lineTab_t * result)
{
    if (! (EstVidePile(p)))
    {
        *result = p->tab[p->position];
        p->position -= 1;
        
    } 
    return p ;
}

void libererPile(pile_t * p)
{
    if (p != NULL)
    {
        free(p->tab);
        p->tab=NULL;
        free(p);
        p=NULL;
    } 
}

void afficherPile(pile_t * p)
{
    if (p != NULL)
    {
        for (int i = p->position; i>-1; i--)
        {
		for (int j=0; j<TAILLE; j++)
            		printf("%d  ",p->tab[i].T[j]);
		printf("\n") ;
        }
        printf("\n");
    } 
}


/*int main() {
	
	lineTab_t tab ;
	tab.T[0] = 1 ;
	tab.T[1] = 2 ;
	tab.T[2] = 3 ;
	tab.T[3] = 3 ;
	pile_t * p = NULL;
	p = init_pile(12) ;

	for (int i=0; i<10 ; i++) {
		empiler(p,  tab) ;
	}
	
	afficherPile(p) ;

	return EXIT_SUCCESS ;
}*/
