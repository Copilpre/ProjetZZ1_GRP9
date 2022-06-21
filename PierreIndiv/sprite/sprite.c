#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void dessinePerso(SDL_Renderer * renderer,int stage,SDL_Window * window){
    
    SDL_Rect 
            source = {0},
            sprite = {0},                      // Rectangle définissant la zone de la texture à récupérer
            window_dimensions = {0},              // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
            destination = {0}; 

    SDL_Texture *my_texture; 
    my_texture = IMG_LoadTexture(renderer,"./images/nyan.png");
    if(my_texture==NULL){
        printf("NULL");
    }

    SDL_QueryTexture(my_texture, NULL, NULL ,&source.w, &source.h);

    sprite.x = stage*source.w/5;
    sprite.y = 0;
    sprite.w = source.w/5;
    sprite.h = source.h;

    SDL_Rect position;
    position.x = 200;
    position.y = 200;
    position.w =sprite.w;
    position.h = sprite.h;
    
    SDL_RenderCopy(renderer, my_texture, &sprite, &position);
    

    SDL_DestroyTexture(my_texture);
}

void dessinePaysage(SDL_Renderer * renderer,int stage,SDL_Window * window){
     SDL_Rect 
            source = {0},
            source2 = {0},                      // Rectangle définissant la zone de la texture à récupérer
            window_dimensions = {0},              // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
            destination = {0}; 

    SDL_Texture *my_texture; 
    my_texture = IMG_LoadTexture(renderer,"./images/galaxy.jpg");
    if(my_texture==NULL){
        printf("NULL");
    }

    SDL_QueryTexture(my_texture, NULL, NULL ,&source.w, &source.h);

    SDL_GetWindowSize(window,              // Récupération des dimensions de la fenêtre
                        &window_dimensions.w,
                        &window_dimensions.h);

    source2.x = stage*source.w/10;
    source2.y = 0;
    source2.w = source.w-source2.x;
    source2.h = source.h;

    SDL_Rect position;
    position.x = 0;
    position.y = 0;
    position.w = source.w-source2.x;
    position.h = window_dimensions.h;
    
    SDL_RenderCopy(renderer, my_texture, &source2, &position);
    
    source2.x = 0;
    source2.y = 0;
    source2.w = stage*source.w/10;
    source2.h = window_dimensions.h;

    position.x = source.w-source2.x;
    position.y = 0;
    position.w = source2.x;
    position.h = window_dimensions.h;


    SDL_RenderCopy(renderer, my_texture, &source2, &position);
    
    SDL_DestroyTexture(my_texture);
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

    int WindowW = current.w/2;
    int WindowH = current.w/2;

    window_1 = SDL_CreateWindow("Petite animation",current.w/4,current.w/4,WindowW,WindowH,SDL_WINDOW_RESIZABLE);

    SDL_Renderer *renderer;

    renderer = SDL_CreateRenderer(window_1, -1, SDL_RENDERER_ACCELERATED );

    int ticks = 0;

    while (ticks < 150){
        if(ticks%3==0){
            dessinePaysage(renderer,ticks/3,window_1);
        }
        

        dessinePerso(renderer,ticks%5,window_1);
        SDL_RenderPresent(renderer); 
        SDL_Delay(50);
        ticks++;
    }

    return 0;
}