#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <SDL2/SDL_ttf.h>



int nb_voisins_torrique(int tab[5][5] , int i, int j, int n, int m)
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


int nb_voisins_delimite(int tab[5][5] , int i, int j, int n, int m)
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




int main()
{
    int tab[5][5] = {  
        {0, 0, 1, 1, 1} ,   
        {0, 0, 1, 1, 1} ,   
        {0, 0, 1, 1, 1} ,
        {0, 0, 1, 1, 1} ,
        {0, 0, 1, 1, 1} ,
        }; 
    for (int a=0; a<5; a++)
    {
        for (int b=0; b<5; b++)
        {
            printf("Coordonées : (%d/%d)\n",a,b);
            nb_voisins_delimite(tab,a,b,5,5);
            nb_voisins_torrique(tab,a,b,5,5);
        } 
    } 

}


