#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <math.h>

void affichageTableau(int ligne, int col,int tab[ligne][col],SDL_Renderer * renderer,SDL_Window * window){
    int i,j;
    SDL_SetRenderDrawColor(renderer, 255,255,255, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0,0,0, 0);
    SDL_Rect window_dimensions;

    SDL_GetWindowSize(window,&window_dimensions.w,&window_dimensions.h);

    SDL_Rect position = {0,0,window_dimensions.w/col,window_dimensions.w/ligne};
    for (i=0;i<ligne;i++){
        position.y = i*window_dimensions.h/ligne;
        for (j=0;j<col;j++){
            position.x=j*window_dimensions.w/(col);
            if(tab[i][j]==1){
            printf("salut");
            SDL_RenderFillRect(renderer,&position);
        }
        }
        
    }

     SDL_RenderPresent(renderer);
    SDL_Delay(3500);
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

    int WindowW = current.w;
    int WindowH = current.h;

    window_1 = SDL_CreateWindow("Piste de Danse",current.w/4,current.w/4,WindowH,WindowH,SDL_WINDOW_RESIZABLE);

    SDL_Renderer *renderer;

    renderer = SDL_CreateRenderer(window_1, -1, SDL_RENDERER_ACCELERATED );

    int tab[3][2]={{1,0},{0,1},{0,0}};

    affichageTableau(3,2,tab,renderer,window_1);
    return 0;
}