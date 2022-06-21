#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <SDL2/SDL_ttf.h>

SDL_Color gris = {155,155,155,255};
SDL_Color grisF = {120,120,120,255};
SDL_Color noir = {0,0,0,255};

void creerMenu(SDL_Renderer * renderer,SDL_Window * window){

     TTF_Font*font = TTF_OpenFont("./fonts/Pacifico.ttf", 65); 
        if(font == NULL){
            printf("font null");
        }
    

    SDL_SetRenderDrawColor(renderer,gris.r,gris.g,gris.b,gris.a);
    SDL_RenderClear(renderer);
    SDL_Rect window_dimensions = {0};
    SDL_GetWindowSize(window,              // Récupération des dimensions de la fenêtre
                        &window_dimensions.w,
                        &window_dimensions.h);

    SDL_SetRenderDrawColor(renderer,grisF.r,grisF.g,grisF.b,grisF.a);
    SDL_Rect bouton,texte;
    
    bouton.x = window_dimensions.w*0.1;                                                  // x haut gauche du bouton
    bouton.y = window_dimensions.h*0.4;                                                  // y haut gauche du bouton
    bouton.w = window_dimensions.w*0.8;                                                // sa largeur (w = width)
    bouton.h = window_dimensions.h*0.1; 
    SDL_RenderFillRect(renderer,&bouton);

    SDL_Surface* text_surface = TTF_RenderText_Blended(font, "Monde fini", noir);
    texte.x = (window_dimensions.w-text_surface->w)/2;
    texte.y= bouton.y;
    texte.w = 0;
    texte.h = 0;
    SDL_Texture* text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
      
    SDL_QueryTexture(text_texture, NULL, NULL, &texte.w, &texte.h);         
    SDL_RenderCopy(renderer, text_texture, NULL, &texte);

    bouton.x = window_dimensions.w*0.1;                                                  // x haut gauche du bouton
    bouton.y = window_dimensions.h*0.6;
    texte.y= bouton.y;

    SDL_RenderFillRect(renderer,&bouton);

    text_surface = TTF_RenderText_Blended(font, "Monde infini", noir);
   

    text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);

                
    SDL_QueryTexture(text_texture, NULL, NULL, &texte.w, &texte.h);         
    SDL_RenderCopy(renderer, text_texture, NULL, &texte);  
    SDL_DestroyTexture(text_texture);

    SDL_RenderPresent(renderer);  
}

void creerMenu2(SDL_Renderer * renderer,SDL_Window * window){
    SDL_SetRenderDrawColor(renderer,gris.r,gris.g,gris.b,gris.a);
    SDL_RenderClear(renderer);
    SDL_Rect window_dimensions = {0};
    SDL_GetWindowSize(window,              // Récupération des dimensions de la fenêtre
                        &window_dimensions.w,
                        &window_dimensions.h);

    SDL_SetRenderDrawColor(renderer,grisF.r,grisF.g,grisF.b,grisF.a);
    SDL_Rect bouton;
    bouton.x = window_dimensions.w*0.1;                                                  // x haut gauche du bouton
    bouton.y = window_dimensions.h*0.4;                                                  // y haut gauche du bouton
    bouton.w = window_dimensions.w*0.35;                                                // sa largeur (w = width)
    bouton.h = window_dimensions.h*0.1; 
    SDL_RenderFillRect(renderer,&bouton);

    bouton.x = window_dimensions.w*0.55;
    SDL_RenderFillRect(renderer,&bouton);

    bouton.x = window_dimensions.w*0.1;                                                  // x haut gauche du bouton
    bouton.y = window_dimensions.h*0.6;
    SDL_RenderFillRect(renderer,&bouton);

    bouton.x = window_dimensions.w*0.55;
    SDL_RenderFillRect(renderer,&bouton);

    SDL_RenderPresent(renderer);

}

int main(){

    SDL_Window 
       *window_1 = NULL;

    SDL_DisplayMode current;

    if (TTF_Init() < 0){
        SDL_Log("Error : TTF initialisation - %s\n", 
            SDL_GetError());                // l'initialisation de la SDL a échoué 
        exit(EXIT_FAILURE);
    }
    

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Error : SDL initialisation - %s\n", 
            SDL_GetError());                // l'initialisation de la SDL a échoué 
        exit(EXIT_FAILURE);
    }

    SDL_GetCurrentDisplayMode(0, &current);

    SDL_bool program_on = SDL_TRUE;
    
    SDL_Rect window = {0,0,current.w/2, current.w/2};

    window_1 = SDL_CreateWindow(
      "Menu",window.x,window.y,window.w,window.h,SDL_WINDOW_RESIZABLE);
    int curX,curY;

    SDL_bool mondeInfini;

    SDL_Event event;
    SDL_Renderer * renderer = SDL_CreateRenderer(window_1, -1, SDL_RENDERER_ACCELERATED );
    creerMenu(renderer, window_1);
    while(program_on||SDL_PollEvent(&event)){
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_MOUSEBUTTONDOWN:
                    curX=event.motion.x;
                    curY = event.motion.y;
                    //printf("(%f > %d >%f ,%f < %d < %f)",window.w*0.9,event.motion.x,window.w*0.1,window.h*0.4,event.motion.y,window.h*0.5);
                    if((curX>=window.w*0.1)&&(curX<=window.w*0.9)){
                        if((curY>=window.h*0.4)&&(curY<=window.h*0.5)){
                            printf("coucou");
                            mondeInfini=SDL_FALSE;
                            creerMenu2(renderer, window_1);
                        }
                        else{
                            if((curY>=window.h*0.6)&&(curY<=window.h*0.7)){
                                printf("coucou2");
                                mondeInfini=SDL_TRUE;
                                creerMenu2(renderer, window_1);
                            }
                        }
                    }
                    
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
    TTF_Quit();
}