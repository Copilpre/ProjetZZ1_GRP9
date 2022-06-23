#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "sceneSDL.h"

SDL_Color gris = {155,155,155,255};
SDL_Color grisF = {120,120,120,255};
SDL_Color noir = {0,0,0,255};
SDL_Color rouge = {255,0,0,255};
SDL_Color cyan = {0,250,255,255};
SDL_Color vert = {0,255,30,255};

void eclosion(SDL_Renderer * renderer,int windowW,int windowH){
    SDL_Rect source,position;
    SDL_Texture * texture = IMG_LoadTexture(renderer,"./image/eclosion.png");

    SDL_QueryTexture(texture,NULL,NULL,NULL,&source.h);
     int i;
    position.x = windowW/4;
    position.y = windowH/8;
    
    //TABLEAU CONTENANT LES COORDONNES DES 6 SPRITES DE L'OEUF
    SDL_Rect spriteOeuf[6];

    for (i = 0;i<6;i++){
        spriteOeuf[i].h = 125;
        spriteOeuf[i].y = 0;
    }

    for (i = 0;i <3;i++){
        spriteOeuf[i].x = i*100+35;
        spriteOeuf[i].w = 100;
    }

    spriteOeuf[3].x=350;
    spriteOeuf[3].w=100;

    spriteOeuf[4].x=450;
    spriteOeuf[4].w=150;

    spriteOeuf[5].x=600;
    spriteOeuf[5].w=170;

    //AFFICHAGE OEUFS
    for (i = 0;i<6;i++){
        position.w = windowH/2;
        position.h = windowH/2;
        SDL_RenderCopy(renderer, texture, &spriteOeuf[i], &position);
        SDL_RenderPresent(renderer);
        SDL_Delay(200);
        SDL_RenderClear(renderer);
    }
    SDL_Delay(1000);

    //AFFICHAGE ECRAN DE DEMARAGE
    texture = IMG_LoadTexture(renderer,"./image/pingouinOut.png");

    SDL_Rect flash,pingouin;
    SDL_QueryTexture(texture,NULL,NULL,&source.w,&flash.h);
    
    SDL_Texture * texturePingouin = IMG_LoadTexture(renderer,"./image/pingouin.png");
    flash.y=0;
    flash.w=source.w/2;

    position.x=windowW/8;
    position.w = windowW*0.9-position.x;
    SDL_QueryTexture(texture,NULL,NULL,&pingouin.w,&flash.h);
    pingouin.x = position.x + position.w/2 - pingouin.w/2;
    pingouin.h = windowH*0.2;
    pingouin.y = 1.5*position.y;
    pingouin.w = 0.5*position.w;

    for(int i = 0; i < 10;i++){
        flash.x=((i%2)*source.w)/2;
        SDL_RenderCopy(renderer, texture, &flash, &position);

        SDL_RenderCopy(renderer, texturePingouin, &pingouin, &position);
        SDL_RenderPresent(renderer);
        SDL_Delay(500);
        SDL_RenderClear(renderer);
    }
    
}



void initSDL(int currentRoom,float barreM,float barreJ,float barreD,SDL_Renderer * renderer,int windowW,int windowH){
    char salles[3][20]={{"./image/chambre.jpg"},{"./image/cuisine.png"},{"./image/stade.jpg"}};
    char icones[3][20]={{"./image/manger.png"},{"./image/jouer.png"},{"./image/dormir.png"}};
    SDL_Rect position,position2,source;


    //image de fond
    SDL_Texture * texture = IMG_LoadTexture(renderer,salles[currentRoom]);
    SDL_QueryTexture(texture,NULL,NULL,NULL,&source.h);
    source.x = 0;
    source.y= source.h/4;
    source.w=source.h;

    position.x = 0;
    position.y = 0;
    position.w = windowW;
    position.h = windowH;
    SDL_RenderCopy(renderer, texture, &source, &position);
        
    SDL_Color couleur[3]={rouge,vert,cyan};
    float barres[3] = {barreM,barreJ,barreD};

    //barres de vie
    int ecartBarre = windowW*0.02;

    position.w = windowW/16;
    position.y = ecartBarre;
    position.h = windowH/4;
        
    for (int i = 0; i < 3;i++){
        position.x= i * position.w + ecartBarre *(i+1);
        position2.x = position.x+0.5*ecartBarre;
        position2.w = position.w-ecartBarre;
        position2.h = position.h*barres[i];
        position2.y = (position.h+position.y-(position2.h));
           if(barres[i]!=0){
           position2.h -= 5;
        }
            
        SDL_SetRenderDrawColor(renderer,gris.r,gris.g,gris.b,gris.a);
        SDL_RenderFillRect(renderer,&position);
        SDL_SetRenderDrawColor(renderer,couleur[i].r,couleur[i].g,couleur[i].b,couleur[i].a);
        SDL_RenderFillRect(renderer,&position2);
    }

    //barre du bas
    SDL_SetRenderDrawColor(renderer,gris.r,gris.g,gris.b,gris.a);
    position.x = 0;
    position.y = windowH*0.7;
    position.h = windowH*0.3;
    position.w = windowW;
    SDL_RenderFillRect(renderer,&position);

    //boutons
    SDL_SetRenderDrawColor(renderer,grisF.r,grisF.g,grisF.b,grisF.a);
    
    //positions boutons
    int ecartBoutons = windowW*0.05;
    position.y = windowH*0.75;
    position.w = (windowW-4*ecartBoutons)/3;
    position.h = position.w;


    //positions icones relatives aux boutons
    SDL_Rect icone;
    icone.w=position.w*0.85;
    icone.h=position.h*0.85;

    for (int i = 0; i < 3;i++){
        //boutons
        position.x= i * position.w + ecartBoutons *(i+1);
        SDL_SetRenderDrawColor(renderer,couleur[i].r,couleur[i].g,couleur[i].b,couleur[i].a);
        SDL_RenderFillRect(renderer,&position);

        //icones
        texture = IMG_LoadTexture(renderer,icones[i]);
        source.x=0;
        source.y=0;
        SDL_QueryTexture(texture,NULL,NULL,&source.w,&source.h);

        icone.x=position.x+0.1*icone.w;
        icone.y=position.y+0.1*icone.w;

        SDL_RenderCopy(renderer, texture, &source, &icone);
    }

    //bouton pause
    SDL_DestroyTexture(texture);
}

void afficheTama(SDL_Renderer * renderer,SDL_Rect position,int currMood,int currentRoom,float barreM,float barreJ,float barreD,int WindowW,int WindowH){
    SDL_Texture * texture = IMG_LoadTexture(renderer,"./image/spriteSheet.png");
    SDL_Rect source,sprite;
    
    SDL_QueryTexture(texture,NULL,NULL,&source.w,&source.h);
    int hauteurCase = source.h/7;
    int LargeurCase = source.w/12;
    sprite.w=LargeurCase;
    sprite.h=hauteurCase;
    
    

    int nbSprite;

    switch(currMood){
        case 0 :
            nbSprite=12;
            sprite.y = 0;
            break;
        case 1 :
            nbSprite = 7;
            sprite.y = hauteurCase;
            break;
        case 2 :
            nbSprite=6;
            sprite.y = 3*hauteurCase;
            break;
        case 3 :
            nbSprite = 7;
            sprite.y = 6*hauteurCase;
            break;
        case 4 :
            break;
    }

    for (int i = 0;i<nbSprite;i++){
        //ON AFFICHE LA SCENE AVANT LE PERSO
        initSDL(currentRoom,barreM,barreJ,barreD,renderer,WindowW,WindowH);

        //AFFICHAGE TAMAGOCHI

        sprite.x = i*LargeurCase;
        SDL_RenderCopy(renderer, texture, &sprite, &position);
        SDL_RenderPresent(renderer);
        SDL_Delay(150);
    }
    
    SDL_DestroyTexture(texture);
}
