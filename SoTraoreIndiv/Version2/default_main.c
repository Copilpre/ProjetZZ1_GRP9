#include "compte_voisin.h"
#include "grille.h"
#define H 800
#define W 800
#define TAILLE 20
#include <SDL2/SDL.h>

int Tnaissance[9] = {0,0, 1, 1, 0, 0, 0, 0, 0} ;
int Tsurvie[9] = {0, 1, 0, 1, 0, 0, 0, 1, 1} ;

int ** SDL_LoadTvoisin(SDL_bool mode) ;
int ** SDL_LoadGrille(int ** tab) ; 
void SDL_LoadWindow(SDL_Renderer * renderer, SDL_Rect rect, int ** grille) ;
void SDL_ErrorCase(char * msg) ;
void SDL_DrawWindowOfGame(SDL_Renderer * renderer, SDL_Color c, int nbElts, int h, int w) ;

int main() {
	SDL_Window * window ;
	SDL_Renderer * renderer ;
	SDL_bool keepLoop = SDL_TRUE , mode = SDL_TRUE ;
	SDL_Event event ;
	SDL_Rect rect = {0, 0, W, H} ; 
	SDL_Color c = {0, 0, 0, 255} ;
	int w, h, i = 0, j = 0, vitesse = 100, taille ;

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

	taille = TAILLE ;
	
	// Variables globales
	Tvoisin = initGrille(TAILLE) ;
	grille = initGrille(TAILLE) ;

	rect.w = (int)(w/taille) ;
	rect.h = (int)(h/taille) ;			
	SDL_bool keepEvent = SDL_TRUE ;

	//SDL_DrawWindowOfGame(renderer, c, taille, h, w) ;
	
	while ( keepLoop ) {
		if (SDL_PollEvent(&event)) 
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
      					if (SDL_GetMouseState(NULL, NULL) & 
          						SDL_BUTTON(SDL_BUTTON_LEFT) ) {
						grille[i][j] = 0 ;
      					} else if (SDL_GetMouseState(NULL, NULL) & 
                 					SDL_BUTTON(SDL_BUTTON_RIGHT) ) { 
						grille[i][j] = 1 ;
      					}
      					break;
				case SDL_WINDOWEVENT :
					switch (event.window.event)  
					{
						case SDL_WINDOWEVENT_CLOSE:  
							printf("appui sur la croix\n");	
							break;
						default:
							break ;
					}  
					break ; 
				case SDL_QUIT :
					keepLoop = SDL_FALSE ;
					break ;
				default :
					break ;
			}
		}
		Tvoisin = SDL_LoadTvoisin(mode) ;
		grille = SDL_LoadGrille(Tvoisin) ;
		//SDL_RenderClear(renderer) ;
		SDL_LoadWindow(renderer, rect, grille) ;
		SDL_RenderPresent(renderer) ;
		SDL_Delay(vitesse) ;
	}

	SDL_DestroyRenderer(renderer) ;
	SDL_DestroyWindow(window) ;
	SDL_Quit() ;

	exit(EXIT_FAILURE) ;
}

int ** SDL_LoadTvoisin(SDL_bool mode) 
{
	int i, j , compteur ;
	for ( i = 0 ; i < TAILLE ; i++ ) {
		for ( j = 0 ;  j < TAILLE; j++ ) {
			compteur = 0 ;
			if ( mode == SDL_TRUE ) {
				compteur = nbVoisinLimit(grille, i, j) ;
			} 
			else {
				compteur = nbVoisinTore(grille, i, j) ;
			}
			Tvoisin[i][j] = compteur ;
		}
	}
	return Tvoisin ;
}

int ** SDL_LoadGrille(int ** tab) 
{
	int i, j ;
	for (i=0; i<TAILLE; i++) {
		for (j=0; j<TAILLE; j++) {
			if (grille[i][j] == 1) {
				grille[i][j] = Tsurvie[tab[i][j]] ;
			} 
			else {
				grille[i][j] = Tnaissance[tab[i][j]] ;
			}
		}
	}
	return grille ;
}


void SDL_LoadWindow(SDL_Renderer * renderer, SDL_Rect rect, int ** grille) {
	int i, j ;
	SDL_Color c = {0, 0, 0, 0} ;
	for ( i = 0 ; i<TAILLE ; i++ ) {
		for ( j = 0 ; j<TAILLE ; j++ ) {
			c.r = c.g = c.b = (grille[i][j] == 1) ? 0 : 255 ;
			rect.x = i * rect.w ;
			rect.y = j * rect.h ;
			if (SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a) != 0)
				SDL_ErrorCase("Trouble with draw color") ;
			if (SDL_RenderFillRect(renderer, &rect) != 0) 
				SDL_ErrorCase("Trouble with draw color") ;
		}
	}
}

void SDL_ErrorCase(char * msg) {
	SDL_Log("%s %s", msg, SDL_GetError()) ;
	exit(EXIT_FAILURE) ;
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

