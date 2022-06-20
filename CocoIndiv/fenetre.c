
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL_image.h>


int main(int argc, char *argv[])
{
    int PositionX = 0;
    int PositionY = 0;
    int x = 10;
    int y = 10;
    
    
    SDL_Window *window = NULL;





    if(0 != SDL_Init(SDL_INIT_VIDEO))
    {
        fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());
        return EXIT_FAILURE;
    }
   window = SDL_CreateWindow(
      "Fenêtre à gauche",                    // codage en utf8, donc accents possibles
      0, 0,                                  // coin haut gauche en haut gauche de l'écran
      400, 300,                              // largeur = 400, hauteur = 300
      SDL_WINDOW_RESIZABLE);                 // redimensionnable

    if(NULL == window)
    {
        fprintf(stderr, "Erreur SDL_CreateWindow : %s", SDL_GetError());
        return EXIT_FAILURE;
    }
    /* On agit sur la fenêtre ici */
    while (PositionX<1700)
    {
        SDL_SetWindowPosition(window,PositionX,PositionY);
        PositionX+=x;
        PositionY+=y;
        SDL_Delay(20);
        if (PositionX > 1520) 
            {
                x = -5;
            }
        if (PositionY > 700)
            {
                y = -5;
            }
        if (PositionY < 10)
            {
                y = 5;
            }   
        if (PositionX < 10)
            {
                x = 5;
            }  
    } 
    

    SDL_Delay(2000);
    SDL_Quit();
return EXIT_SUCCESS;
}