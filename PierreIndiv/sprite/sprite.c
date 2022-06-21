#include <SDL2/SDL.h>
#include <SDL/SDL_image.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

SDL_Color rouge = {255,0,0,255};
SDL_Color vert = {0,255,0,255};
SDL_Color bleu = {0,0,255,255};
SDL_Color orange ={255,128,0,255};
SDL_Color cyan = {0,250,255,255};
SDL_Color jaune = {255,242,0,255};
SDL_Color noir = {0,0,0,255};
SDL_Color blanc = {255,255,255,255};
SDL_Color gris = {155,155,155,255};

void dessinePerso(SDL_Renderer * renderer,int  width,int  stage){
    SDL_SetRenderDrawColor(renderer, gris.r,gris.g,gris.b,gris.a);
    SDL_Rect rectangle;
    float posBonhommeX=0.3+rand()%12*0.1;
    float posBonhommeY=0.3+rand()%15*0.1;
    int CorpsX = posBonhommeX*width/2;
    int CorpsY = posBonhommeY*width/4;
    int CorpsW = width/8;
    int CorpsH = width/3;

    //corps
    rectangle.x = CorpsX;                                               
    rectangle.y = CorpsY;                                               
    rectangle.w = CorpsW;
    rectangle.h = CorpsH; 
    SDL_RenderFillRect(renderer, &rectangle);

    //tete
    rectangle.x = CorpsX+0.2*CorpsW;
    rectangle.y = CorpsY-0.8*CorpsW;
    rectangle.w = CorpsW*0.65;
    rectangle.h = CorpsW*0.65;
    SDL_RenderFillRect(renderer, &rectangle);

    //jambes
    rectangle.x = CorpsX;
    rectangle.y = CorpsY+CorpsH;
    rectangle.w = CorpsW*0.3;
    rectangle.h = CorpsH*0.7;
    SDL_RenderFillRect(renderer, &rectangle);

    rectangle.x = CorpsX+CorpsW-CorpsW*0.3;
    rectangle.y = CorpsY+CorpsH;
    rectangle.w = CorpsW*0.3;
    rectangle.h = CorpsH*0.7;
    SDL_RenderFillRect(renderer, &rectangle);

    //chaussures
    

    switch(stage){
        case 0 ://cas tete à gauche
            //cou
            rectangle.x = CorpsX+CorpsW*0.5;
            rectangle.y = CorpsY-0.15*CorpsW;
            rectangle.w = CorpsW*0.3;
            rectangle.h = CorpsY - rectangle.y;
            SDL_RenderFillRect(renderer, &rectangle);
            
            //brasG
            rectangle.x = CorpsX-CorpsH*0.4;
            rectangle.y = CorpsY;
            rectangle.h = CorpsW*0.25;
            rectangle.w = CorpsH*0.4;
            SDL_RenderFillRect(renderer, &rectangle);
            rectangle.x = CorpsX-CorpsH*0.4;
            rectangle.y = CorpsY-CorpsH*0.4;
            rectangle.w = CorpsW*0.25;
            rectangle.h = CorpsH*0.4;
            SDL_RenderFillRect(renderer, &rectangle);

            //brasD
            rectangle.x = CorpsX+CorpsW;
            rectangle.y = CorpsY;
            rectangle.h = CorpsW*0.25;
            rectangle.w = CorpsH*0.4;
            SDL_RenderFillRect(renderer, &rectangle);
            rectangle.x = CorpsX+CorpsW-CorpsW*0.25+CorpsH*0.4;
            rectangle.y = CorpsY+CorpsW*0.25;
            rectangle.w = CorpsW*0.25;
            rectangle.h = CorpsH*0.4;
            SDL_RenderFillRect(renderer, &rectangle);
            
            break;
        case 1 : //cas tete à droite
            //cou
            rectangle.x = CorpsX+0.25*CorpsW;
            rectangle.y = CorpsY-0.15*CorpsW;
            rectangle.w = CorpsW*0.3;
            rectangle.h = CorpsY - rectangle.y;
            SDL_RenderFillRect(renderer, &rectangle);

            //brasG
            rectangle.x = CorpsX-CorpsH*0.4;
            rectangle.y = CorpsY;
            rectangle.h = CorpsW*0.25;
            rectangle.w = CorpsH*0.4;
            SDL_RenderFillRect(renderer, &rectangle);
            rectangle.x = CorpsX-CorpsH*0.4;
            rectangle.y = CorpsY+CorpsW*0.25;
            rectangle.w = CorpsW*0.25;
            rectangle.h = CorpsH*0.4;
            SDL_RenderFillRect(renderer, &rectangle);

            //brasD
            rectangle.x = CorpsX+CorpsW;
            rectangle.y = CorpsY;
            rectangle.h = CorpsW*0.25;
            rectangle.w = CorpsH*0.4;
            SDL_RenderFillRect(renderer, &rectangle);
            rectangle.x = CorpsX+CorpsW-CorpsW*0.25+CorpsH*0.4;
            rectangle.y = CorpsY-CorpsH*0.4;
            rectangle.w = CorpsW*0.25;
            rectangle.h = CorpsH*0.4;
            SDL_RenderFillRect(renderer, &rectangle);

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

    window_1 = SDL_CreateWindow("Chevalier",current.w/4,current.w/4,WindowW,WindowH,SDL_WINDOW_RESIZABLE);

    SDL_Renderer *renderer;

    renderer = SDL_CreateRenderer(window_1, -1, SDL_RENDERER_ACCELERATED );

    int ticks = 0;

    while (ticks < 25){
        dessinePaysage(renderer,WindowW,ticks%3);

        dessinePerso(renderer,WindowW,ticks%2);

        SDL_Delay(400);
        ticks++;
    }

    return 0;
}