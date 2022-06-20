#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <math.h>

#define COULEURS 6
#define TAILLE 12
SDL_Color rouge = {255,0,0,255};
SDL_Color vert = {0,255,0,255};
SDL_Color bleu = {0,0,255,255};
SDL_Color orange ={255,128,0,255};
SDL_Color cyan = {0,250,255,255};
SDL_Color jaune = {255,242,0,255};
SDL_Color noir = {0,0,0,255};
SDL_Color blanc = {255,255,255,255};

void dessineRectCouleur(int i, int j, int width, SDL_Renderer * renderer){
    switch(rand()%6){
        case 0:
                    SDL_SetRenderDrawColor(renderer, rouge.r,rouge.g,rouge.b,255);
                    break;
        case 1:
                    SDL_SetRenderDrawColor(renderer, bleu.r, bleu.g, bleu.b, 0);
                    break;
        case 2:
                    SDL_SetRenderDrawColor(renderer, jaune.r,jaune.g,jaune.b, 0);
                    break;
        case 3:
                    SDL_SetRenderDrawColor(renderer, orange.r,orange.g,orange.b, 0);
                    break;
        case 4:
                    SDL_SetRenderDrawColor(renderer, cyan.r,cyan.g,cyan.b, 0);
                    break;
        case 5:
                    SDL_SetRenderDrawColor(renderer, vert.r,vert.g,vert.b, 0);
                    break;
    }
    
    SDL_Rect rectangle;
    rectangle.x = width/4*i;                                                  // x haut gauche du rectangle
    rectangle.y = width/4*j;                                                  // y haut gauche du rectangle
    rectangle.w = width/4;                                                // sa largeur (w = width)
    rectangle.h = width/4;                                                // sa hauteur (h = height)

    SDL_RenderFillRect(renderer, &rectangle); 
}

void dessineBonhomme(SDL_Renderer * renderer, int width){
    SDL_SetRenderDrawColor(renderer, 0,0,0,255);
    SDL_Rect rectangle;
    rectangle.x = width/2+10;                                                // x haut gauche du rectangle
    rectangle.y = 300;                                                 // y haut gauche du rectangle
    rectangle.w = width/8;                                                // sa largeur (w = width)
    rectangle.h = width/3; 
    SDL_RenderFillRect(renderer, &rectangle);

    switch(rand()%2){
        case 0 ://cas bras en bas
            break;
        case 1 : //cas bras en haut
            break;
    }
    
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

    window_1 = SDL_CreateWindow(
      "Piste de Danse",                    // codage en utf8, donc accents possibles
      current.w/4, current.w/4,                                  // coin haut gauche en haut gauche de l'écran
      current.w/2, current.w/2,                              // largeur = 400, hauteur = 300
      SDL_WINDOW_RESIZABLE);

    SDL_Renderer *renderer;

    renderer = SDL_CreateRenderer(window_1, -1, SDL_RENDERER_ACCELERATED );
    int ticks = 0;
    while(ticks <25){
        for (int i =0; i < 4; i++){
            for (int j = 0; j<4;j++){
                dessineRectCouleur(i,j,current.w/2,renderer);
            }
        }
        dessineBonhomme(renderer,current.w/2);
        SDL_RenderPresent(renderer);  
        SDL_Delay(250);
        ticks++;
    }
        

    return 0;

}