#include "pile.h"

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


pile_t *  empiler(pile_t * p, lineTab_t data)
{
    if (p->position < p->nbElts)
    {
        p->position += 1;
        p->tab[p->position] = data; 
    }
    else {
	printf("Pas assez de place dans la pile\n") ;
    } 
    return p ;
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
		printf("%f\n", p->tab[i].r) ;
        }
        printf("\n");
    } 
}
