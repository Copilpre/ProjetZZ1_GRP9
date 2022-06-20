#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

int main(){

    SDL_Window 
       *window_1 = NULL,
       *window_2 = NULL,
       *window_3 = NULL,
       *window_4 = NULL,
       *window_5 = NULL;

    SDL_DisplayMode current;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Error : SDL initialisation - %s\n", 
            SDL_GetError());                // l'initialisation de la SDL a échoué 
        exit(EXIT_FAILURE);
    }

    SDL_GetCurrentDisplayMode(0, &current);

    SDL_Texture *image; 
    image = IMG_LoadTexture(renderer,"./images/nyancat.bmp");


    window_1 = SDL_CreateWindow(
      "Etoile1",                    // codage en utf8, donc accents possibles
      0, 0,                                  // coin haut gauche en haut gauche de l'écran
      current.w/3, current.w/3,                              // largeur = 400, hauteur = 300
      SDL_WINDOW_RESIZABLE);


    SDL_Delay(20000);
    int x = 0,1;
    while (x<5){
        SDL_SetWindowPosition(SDL_Window * window, x, )
    }
    SDL_DestroyWindow(window_1);
    SDL_Quit();
}