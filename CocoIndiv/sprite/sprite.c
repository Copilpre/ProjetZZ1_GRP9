#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>



void dessinePerso(SDL_Renderer * renderer,int stage,SDL_Window * window){
    
    SDL_Rect 
            source = {0},
            sprite = {0},                      // Rectangle définissant la zone de la texture à récupérer
            window_dimensions = {0},              // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
            destination = {0}; 

    SDL_Texture *my_texture; 
    my_texture = IMG_LoadTexture(renderer,"perso2.png");
    if(my_texture==NULL){
        printf("NULL");
    }

    SDL_QueryTexture(my_texture, NULL, NULL ,&source.w, &source.h);

    sprite.x = stage*source.w/6;
    sprite.y = 0;
    sprite.w = source.w/6;
    sprite.h = source.h;

    SDL_Rect position;
    position.x = 200;
    position.y = 500;
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
    my_texture = IMG_LoadTexture(renderer,"route.jpg");
    if(my_texture==NULL){
        printf("NULL");
    }

    SDL_QueryTexture(my_texture, NULL, NULL ,&source.w, &source.h);

    SDL_GetWindowSize(window,              // Récupération des dimensions de la fenêtre
                        &window_dimensions.w,
                        &window_dimensions.h);

    source2.x = 0;
    source2.y = 0;
    source2.w = source.w;
    source2.h = source.h;

    SDL_Rect position;
    position.x = 0;
    position.y = 0;
    position.w = window_dimensions.w;
    position.h = window_dimensions.h;
    
    SDL_RenderCopy(renderer, my_texture, &source2, &position);

    
    SDL_DestroyTexture(my_texture);
}

int main(){
    
    
    SDL_bool program_on = SDL_TRUE;               // Booléen pour dire que le programme doit continuer
    SDL_Event event;                              // c'est le type IMPORTANT !!
    
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
    
    
    while (SDL_PollEvent(&event)||(program_on)){
        
        switch(event.type)
    
        {
            case SDL_QUIT :
                program_on = SDL_FALSE;
                break;
            default:
                dessinePaysage(renderer,ticks%5,window_1);
                dessinePerso(renderer,ticks%5,window_1);
                SDL_RenderPresent(renderer); 
                
                ticks++;

            break;

        }
        SDL_Delay(50);
    }

    return 0;
}
