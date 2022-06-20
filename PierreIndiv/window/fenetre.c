#include <SDL2/SDL.h>
#//include <SDL2/SDL_image.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(){

    SDL_Window 
       *window_1 = NULL;

    SDL_DisplayMode current;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Error : SDL initialisation - %s\n", 
            SDL_GetError());                // l'initialisation de la SDL a échoué 
        exit(EXIT_FAILURE);
    }

    SDL_GetCurrentDisplayMode(0, &current);


    window_1 = SDL_CreateWindow(
      "Etoile1",                    // codage en utf8, donc accents possibles
      0, 0,                                  // coin haut gauche en haut gauche de l'écran
      current.w/6, current.w/6,                              // largeur = 400, hauteur = 300
      SDL_WINDOW_RESIZABLE);


    float x = 0;
    float y = 0;
    while (x<=current.w-current.w/6){
        SDL_SetWindowPosition(window_1, x, y);
        x +=5;
        y = 660 - 660 * fabs((sin(x*0.01))/(0.01*x));
        SDL_Delay(20);
    }

    SDL_DestroyWindow(window_1);
    SDL_Quit();
}