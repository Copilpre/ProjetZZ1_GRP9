#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


void initSDL(int currentRoom,float barreM,float barreD,float barreJ,SDL_Renderer * renderer,int windowW,int windowH);

void eclosion(SDL_Renderer * renderer,int windowW,int windowH);

void afficheTama(SDL_Renderer * renderer,SDL_Rect position,int currMood,int currentRoom,float barreM,float barreJ,float barreD,int WindowW,int WindowH);