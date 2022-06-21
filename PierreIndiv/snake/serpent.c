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
    

    switch(rand()%2){
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

    int WindowW = current.w/2;
    int WindowH = current.w/2;

    window_1 = SDL_CreateWindow("Piste de Danse",current.w/4,current.w/4,WindowW,WindowH,SDL_WINDOW_RESIZABLE);

    SDL_Renderer *renderer;

    renderer = SDL_CreateRenderer(window_1, -1, SDL_RENDERER_ACCELERATED );
    int ticks = 0;
    while(ticks <25){
        for (int i =0; i < 4; i++){
            for (int j = 0; j<4;j++){
                dessineRectCouleur(i,j,WindowW,renderer);
            }
        }
        dessineBonhomme(renderer,WindowW);
        SDL_RenderPresent(renderer);  
        SDL_Delay(300);
        ticks++;
    }
        

    return 0;

}