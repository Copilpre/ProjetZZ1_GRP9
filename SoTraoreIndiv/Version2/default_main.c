#include "compte_voisin.h"
#include "grille.h"
#define H 800
#define W 800
#define TAILLE 20
#include <SDL2/SDL.h>

int Tnaissance[9] = {1, 0, 0, 1, 1, 1, 0, 1, 0} ;
int Tsurvie[9] = {1, 1, 0, 0, 0, 0, 0, 1, 1} ;

void SDL_LoadGrille(SDL_Renderer * renderer, SDL_Rect r, SDL_bool mode) ;
void SDL_ErrorCase(char * msg) ;
void SDL_DrawRect(SDL_Renderer * renderer, SDL_Rect rect, int r, int g, int b, SDL_bool fill) ; 
void SDL_DrawWindowOfGame(SDL_Renderer * renderer, SDL_Color c, int nbElts, int h, int w) ;
void SDL_ChangeColor(SDL_Renderer * renderer, SDL_Rect rect, SDL_Color c) ;


int main() {
	SDL_Window * window ;
	SDL_Renderer * renderer ;
	SDL_bool keepLoop = SDL_TRUE , mode = SDL_TRUE ;
	SDL_Event event ;
	SDL_Rect rect = {0, 0, W, H} ; 
	SDL_Color c = {0, 0, 0, 255} ;
	int w, h, i = 0, j = 0, vitesse = 10, 
			taille, code = 0, compteur ;

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		SDL_ErrorCase("Trouble with init video") ;

	window = SDL_CreateWindow("GameOfLife",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			H, W, 0
			);

	if (window == NULL) 
		SDL_ErrorCase("Trouble with window") ;

	renderer = SDL_CreateRenderer(window, -1, 0) ;

	if (renderer == 0) 
		SDL_ErrorCase("Trouble with renderer") ;

	SDL_GetWindowSize(window, &w, &h) ; 

	if (SDL_RenderDrawRect(renderer, &rect) != 0)
		SDL_ErrorCase("Trouble with window size") ;

	if (SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a) != 0)
		SDL_ErrorCase("Trouble with draw color") ;

	taille = TAILLE ;
	
	// Variables globales
	Tvoisin = initGrille(TAILLE) ;
	grille = initGrille(TAILLE) ;

	rect.w = (int)(w/taille) ;
	rect.h = (int)(h/taille) ;			

	//SDL_DrawWindowOfGame(renderer, c, taille, h, w) ;
	
	while ( keepLoop ) {

		while (SDL_PollEvent(&event)) 
		{
			switch (event.type) {
				case SDL_BUTTON_LEFT :
					vitesse = (vitesse < 100) ? vitesse+10 : 100 ;
					break ;
				case SDL_BUTTON_RIGHT :
					vitesse =  (vitesse > 10) ? vitesse-10 : 10;
					break ;
				case SDL_MOUSEBUTTONDOWN :   
					SDL_GetMouseState(&i, &j) ;
					i = (int)(i / rect.w) ;
					j = (int)(j / rect.h) ;
					rect.x = i * rect.w ;
					rect.y = j * rect.h ;

      					if (SDL_GetMouseState(NULL, NULL) & 
          						SDL_BUTTON(SDL_BUTTON_LEFT) ) {
						c.r = c.g = c.b = 255 ;
						grille[i][j] = 0 ;
						SDL_ChangeColor(renderer, rect, c) ;
      					} else if (SDL_GetMouseState(NULL, NULL) & 
                 					SDL_BUTTON(SDL_BUTTON_RIGHT) ) { 
						c.r = c.g = c.b = 0 ;
						grille[i][j] = 1 ;
						SDL_ChangeColor(renderer, rect, c) ;
      					}

      					break;
				case SDL_WINDOWEVENT_CLOSE | SDL_QUIT | SDL_WINDOWEVENT_LEAVE:
					keepLoop = SDL_FALSE ;
					break ;
				default :
					break ;
			}

		}

		SDL_LoadGrille(renderer, rect, mode) ;
		SDL_RenderPresent(renderer) ;
		SDL_Delay(vitesse) ;

	}

	SDL_DestroyRenderer(renderer) ;
	SDL_DestroyWindow(window) ;
	SDL_Quit() ;

	exit(EXIT_FAILURE) ;
}

void SDL_LoadGrille(SDL_Renderer * renderer, SDL_Rect rect, SDL_bool mode) 
{
	int i, j , compteur ;
	SDL_Color c ;
	for ( i = 0 ; i < TAILLE ; i++ ) {
		for ( j = 0 ;  j < TAILLE; j++ ) {
			compteur = 0 ;
			rect.x = i * rect.w ;
			rect.y = j * rect.h ;

			if ( mode == SDL_TRUE ) {
				compteur = nbVoisinLimit(grille, i, j) ;
			} 
			else {
				compteur = nbVoisinTore(grille, i, j) ;
			}
			Tvoisin[i][j] = compteur ;
		}
	}

	for (i=0; i<TAILLE; i++) {
		for (j=0; j<TAILLE; j++) {
			if (grille[i][j] == 1) {
				grille[i][j] = Tsurvie[Tvoisin[i][j]] ;
			} 
			else {
				grille[i][j] = Tnaissance[Tvoisin[i][j]] ;
			}
			c.r = c.g = c.b = (grille[i][j] == 1) ? 0 : 255 ;
			SDL_ChangeColor(renderer, rect, c) ;
		}
	}
}

void SDL_ErrorCase(char * msg) {
	SDL_Log("%s %s", msg, SDL_GetError()) ;
	exit(EXIT_FAILURE) ;
}

void SDL_DrawRect(SDL_Renderer * renderer, SDL_Rect rect, int r, int g, int b, SDL_bool fill) 
{
	if (SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE) != 0)
		SDL_ErrorCase("Trouble with draw color") ;

	if (fill == SDL_TRUE)
	if (SDL_RenderFillRect(renderer, &rect) != 0)
		SDL_ErrorCase("Trouble with fill rect") ;
 
	if (SDL_RenderDrawRect(renderer, &rect) != 0)
		SDL_ErrorCase("Trouble with draw rect") ;
}

void SDL_DrawWindowOfGame(SDL_Renderer * renderer, SDL_Color c, int nbElts, int h, int w) 
{
	// Mise de la couleur de fond à noir 
	if (SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a) != 0)
		SDL_ErrorCase("Trouble with renderer") ;
	
	int pasH = h/nbElts, pasW = w/nbElts ;

	for (int i=0; i<nbElts; i++) 	
	{
		if (SDL_RenderDrawLine(renderer, pasH*i, 0, pasH*i, w) != 0)
			SDL_ErrorCase("Trouble with draw line") ;

		if (SDL_RenderDrawLine(renderer, 0, pasW*i, h, pasW*i) != 0)
			SDL_ErrorCase("Trouble with draw line") ;
	}
}

// rect = {i*pasH, j*pasW, pasH, pasW} ;

void SDL_ChangeColor(SDL_Renderer * renderer, SDL_Rect rect, SDL_Color c) 
{
	// Mise à rouge de la case ciblée
	SDL_DrawRect(renderer, rect, c.r, c.g, c.b, SDL_TRUE) ; 
}
