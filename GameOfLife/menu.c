#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

SDL_Color gris = {155,155,155,255};
SDL_Color grisF = {120,120,120,255};

void creerMenu(SDL_Renderer * renderer,SDL_Window * window){
    SDL_SetRenderDrawColor(renderer,gris.r,gris.g,gris.b,gris.a);
    SDL_RenderClear(renderer);
    SDL_Rect window_dimensions = {0};
    SDL_GetWindowSize(window,              // Récupération des dimensions de la fenêtre
                        &window_dimensions.w,
                        &window_dimensions.h);

    SDL_SetRenderDrawColor(renderer,grisF.r,grisF.g,grisF.b,grisF.a);
    SDL_Rect rectangle;
    rectangle.x = window_dimensions.w*0.1;                                                  // x haut gauche du rectangle
    rectangle.y = window_dimensions.h*0.4;                                                  // y haut gauche du rectangle
    rectangle.w = window_dimensions.w*0.8;                                                // sa largeur (w = width)
    rectangle.h = window_dimensions.h*0.1; 
    SDL_RenderFillRect(renderer,&rectangle);

    rectangle.x = window_dimensions.w*0.1;                                                  // x haut gauche du rectangle
    rectangle.y = window_dimensions.h*0.6;
    SDL_RenderFillRect(renderer,&rectangle);

    SDL_RenderPresent(renderer);  
}

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

    SDL_bool program_on = SDL_TRUE;

    window_1 = SDL_CreateWindow(
      "Menu",                    // codage en utf8, donc accents possibles
      0, 0,                                  // coin haut gauche en haut gauche de l'écran
      current.w/2, current.w/4,                              // largeur = 400, hauteur = 300
      SDL_WINDOW_RESIZABLE);

    SDL_Event event;
    SDL_Renderer * renderer = SDL_CreateRenderer(window_1, -1, SDL_RENDERER_ACCELERATED );
    creerMenu(renderer, window_1);
    while(program_on||SDL_PollEvent(&event)){
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_MOUSEBUTTONDOWN:
                    printf("(%d,%d)",event.motion.x,event.motion.y);
                    //
                    
                    break;
                case SDL_QUIT:                                // Un évènement simple, on a cliqué sur la x de la // fenêtre
                    program_on = SDL_FALSE;
                    break;
                default:
                    break;
            }
        }
        SDL_Delay(20);
        
    }
    
    SDL_DestroyWindow(window_1);
    SDL_Quit();
}