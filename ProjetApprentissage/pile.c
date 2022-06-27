#include <stdio.h>
#include <stdlib.h>


typedef struct pile
{
    int nbElts;
    int position;
    int * tab; 
}pile_t;

pile_t * init_pile(int taille)
{
    pile_t * nouv = NULL;
    nouv = malloc(sizeof(pile_t));
    nouv -> nbElts = taille;
    nouv -> tab = malloc(sizeof(int) * taille);
    nouv -> position = -1;
    return nouv;
}


int EstVidePile(pile_t *p)
{
    return (p->position == -1);
}


int empiler(pile_t * p, int data)
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

pile_t* depiler(pile_t * p,int * code)
{
    *code = -1;
    if (! (EstVidePile(p)))
    {
        *code = p->tab[p->position];
        p->position -= 1;
        
    } 
    return p;
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
        for (int i = p -> position ;i > -1 ;i--)
        {
            printf("%d  ",p -> tab[i]);
        }
        printf("\n");
    } 
}
