#include "recherche_voisins.h"



int nb_voisins_torrique(int **tab , int i, int j, int n, int m)
{
    int nb_voisins_torrique = 0; //On initialise le nombre de voisins de la cellule à zéro
 
 
    if (tab[(i-1+n)%n][(j-1+m)%m] == 1) //voisin haut gauche
        nb_voisins_torrique += 1;
 
    if (tab[(i-1+n)%n][j] == 1) // voisin haut
        nb_voisins_torrique += 1;
 
    if (tab[(i-1+n)%n][(j+1+m)%m] == 1) //voisin haut droite
        nb_voisins_torrique += 1;
 
    if (tab[i][(j-1+m)%m] == 1) //voisin gauche
        nb_voisins_torrique += 1;
 
    if (tab[i][(j+1+m)%m] == 1) //voisin droite
        nb_voisins_torrique += 1;
 
    if (tab[(i+1+n)%n][(j-1+m)%m] == 1) //voisin bas gauche
        nb_voisins_torrique += 1;

    if (tab[(i+1+n)%n][j] == 1) //voisin bas
        nb_voisins_torrique += 1;
 
    if (tab[(i+1+n)%n][(j+1+m)%m]) //voisin bas droite
        nb_voisins_torrique += 1;
    
    printf("nombre de voisins en torrique %d\n\n ",nb_voisins_torrique);
    return nb_voisins_torrique;
}


int nb_voisins_delimite(int **tab , int i, int j, int n, int m)
{
    int nb_voisins = 0; //On initialise le nombre de voisins de la cellule à zéro
 
 
    if (i - 1 >= 0 && j - 1 >= 0 && tab[i-1][j-1] == 1) //voisin haut gauche
        nb_voisins += 1;
 
    if (i - 1 >= 0 && tab[i-1][j] == 1) // voisin haut
        nb_voisins += 1;
 
    if (i - 1 >= 0 && j + 1 < m && tab[i-1][j+1] == 1) //voisin haut droite
        nb_voisins += 1;
 
    if (j - 1 >= 0 && tab[i][j-1] == 1) //voisin gauche
        nb_voisins += 1;
 
    if (j + 1 < m && tab[i][j+1] == 1) //voisin droite
        nb_voisins += 1;
 
    if (i + 1 < n && j - 1 >= 0 && tab[i+1][j-1] == 1) //voisin bas gauche
        nb_voisins += 1;

    if (i + 1 < n && tab[i+1][j] == 1) //voisin bas
        nb_voisins += 1;
 
    if (i + 1 < n && j + 1 < m && tab[i+1][j+1]) //voisin bas droite
        nb_voisins += 1;
    
    printf("nb voisins en delimite %d\n ",nb_voisins);
    return nb_voisins;
}


