#ifndef __FENETRE__
#define __FENETRE__

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <time.h>

#define W 800
#define H 800
#define NB_CHAMBRE 7
#define MARGIN 5
#define NB_IMG 7
#define NB_ITER 200
#define NB_BUTTON 4


typedef struct barLevel {
	int i ; // manger
	int j ; // jouer 
	int k ; // dormir
} barLevel_t ;


void SDL_ErrorCase(char * msg) ;

SDL_Texture * load_TextureFromSurface(char * image, SDL_Renderer * renderer) ;

void drawCadre(SDL_Window * window, SDL_Renderer * renderer, SDL_Rect cadre[3]) ;

// cadre[0] pour le dessin des niveaus de barre

void drawBarre(SDL_Renderer * renderer, SDL_Rect src, barLevel_t b) ;

// cadre[2]  pour les buttons 

void drawButton(SDL_Renderer * renderer, SDL_Rect src, SDL_Rect button[4]) ;

// cadre[1] Pour les chambres

void drawRoom(SDL_Renderer * renderer, SDL_Rect src, SDL_Rect chambre[NB_CHAMBRE]) ;

void animerImage(SDL_Window * window, SDL_Texture * texture, SDL_Rect rect, char * img, SDL_Renderer * renderer, int pos, int wd, int hd, int boredX, int boredY, barLevel_t b) ; 

barLevel_t changeState(barLevel_t barre, int action, int pas, int prec, int cible) ;

#endif
