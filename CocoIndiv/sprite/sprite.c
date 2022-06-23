#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>



void dessinePerso(SDL_Renderer * renderer,int stage,SDL_Window * window, int temps){
    
    SDL_Rect 
            source = {0},
            sprite = {0},                      // Rectangle définissant la zone de la texture à récupérer
            window_dimensions = {0},              // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
            destination = {0}; 

    SDL_Texture *my_texture; 
    my_texture = IMG_LoadTexture(renderer,"indiana.png");
    if(my_texture==NULL){
        printf("NULL");
    }

    SDL_QueryTexture(my_texture, NULL, NULL ,&source.w, &source.h);

    sprite.x = stage*source.w/8;
    sprite.y = source.h/7*2;
    sprite.w = source.w/8;
    sprite.h = source.h/7;

    
    
    SDL_Rect position;
    position.x = (temps*10)%source.w;
    position.y = 800;
    position.w =sprite.w*3;
    position.h = sprite.h*3;
    
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
    my_texture = IMG_LoadTexture(renderer,"desert.png");
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
    
    
    int temps = 0;
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
    int acceleration = 150;
    SDL_Event event;
    SDL_bool quit = SDL_FALSE;
    while(!quit)
    {
        while(SDL_PollEvent(&event))
            {
                if(event.type == SDL_QUIT)
                    quit = SDL_TRUE;
                else if(event.type == SDL_KEYDOWN)
                    {
                    if(event.key.keysym.scancode == SDL_SCANCODE_RIGHT)
                       {if (acceleration>0)
                            acceleration -= 10;}
                    if(event.key.keysym.sym == SDLK_LEFT)
                        acceleration += 10;
                    }
            } 
        SDL_Delay(acceleration);
        
        dessinePaysage(renderer,ticks%5,window_1);
        dessinePerso(renderer,ticks%5,window_1,temps);
        
        SDL_RenderPresent(renderer);
        temps += 1;
        ticks++;
    } 
    return 0;
}
