#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <SDL2/SDL_ttf.h>



int nb_voisins_delimite(int tab[5][5] , int i, int j, int n, int m)
{
    int nb_voisins = 0; //On initialise le nombre de voisins de la cellule à zéro
 
 
    if (i - 1 >= 0 && j - 1 >= 0 && tab[i-1][j-1] == 1)
        nb_voisins += 1;
 
    if (i - 1 >= 0 && tab[i-1][j] == 1)
        nb_voisins += 1;
 
    if (i - 1 >= 0 && j + 1 < m && tab[i-1][j+1] == 1)
        nb_voisins += 1;
 
    if (j - 1 >= 0 && tab[i][j-1] == 1)
        nb_voisins += 1;
 
    if (j + 1 < m && tab[i][j+1] == 1)
        nb_voisins += 1;
 
    if (i + 1 < n && j - 1 >= 0 && tab[i+1][j-1] == 1)
        nb_voisins += 1;
 
    if (i + 1 < n && tab[i+1][j] == 1)
        nb_voisins += 1;
 
    if (i + 1 < n && j + 1 < m && tab[i+1][j+1])
        nb_voisins += 1;
    
    printf("%d\n ",nb_voisins);
    return nb_voisins;
}

int nb_voisins_delimite(int tab[5][5] , int i, int j, int n, int m)





int main()
{
    int tab[5][5] = {  
        {0, 0, 1, 1, 1} ,   
        {0, 0, 1, 1, 1} ,   
        {0, 0, 1, 1, 1} ,
        {0, 0, 1, 1, 1} ,
        {0, 0, 1, 1, 1} ,
        }; 
    nb_voisins_delimite(tab,2,2,5,5);
}


