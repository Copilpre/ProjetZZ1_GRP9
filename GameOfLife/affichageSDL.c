#include "affichageSDL.h"

void affichageTableau(int ligne, int col,int **tab,SDL_Renderer * renderer,SDL_Window * window){
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
}
