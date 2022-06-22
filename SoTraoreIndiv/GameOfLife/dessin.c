#define CARRE 4
#include "dessin.h"
#define TETE 1
#define LIGNE 3

void SDL_ErrorCase(char * msg) {
	SDL_Log("%s %s\n", msg, SDL_GetError()) ;
	exit(EXIT_FAILURE) ;
}

void SDL_DrawRect(SDL_Renderer * renderer, SDL_Rect rect, int r, int g, int b, SDL_bool fill) 
{
	if (fill == SDL_TRUE)
	if (SDL_RenderFillRect(renderer, r, g, b, SDL_ALPHA_OPAQUE) != 0)
		SDL_ErrorCase("Trouble with fill rect") ;

	if (SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE) != 0)
		SDL_ErrorCase("Trouble with draw color") ;
 
	if (SDL_RenderDrawRect(renderer, &rect) != 0)
		SDL_ErrorCase("Trouble with draw rect") ;
}

void SDL_DrawLine(SDL_Renderer * renderer, int x1, int y1, int x2, int y2) 
{
	if (SDL_RenderDrawLine(renderer, x1, y1, x2, y2) != 0) 
		SDL_ErrorCase("Trouble with draw line") ;
}

void SDL_DrawPoint(SDL_Renderer * renderer, int x, int y) 
{
	if (SDL_RenderDrawPoint(renderer, x, y) != 0) 
		SDL_ErrorCase("Trouble with draw point") ;
}

void SDL_DrawWindowOfGame(SDL_Renderer * renderer, int nbElts, int h, int w) 
{
	// Mise de la couleur de fond à noir 
	if (SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255) != 0)
		SDL_ErrorCase("Trouble with renderer") ;
	
	int pasH = h/nbElts, pasW = w/nbElts ;

	for (int i=0; i<nbElts; i++) 	
	{
		if (SDL_RenderDrawLine(renderer, pasH, 0, pasH, w) != 0)
			SDL_ErrorCase("Trouble with draw line") ;

		if (SDL_RenderDrawLine(renderer, 0, pasW, h, pasW) != 0)
			SDL_ErrorCase("Trouble with draw line") ;
	}
}

// rect = {i*pasH, j*pasW, i*pasH+pasH, j*pasW+pasW} ;

void SDL_ChangeColor(SDL_Renderer * renderer, SDL_Rect rect, SDL_bool newColor) 
{
	if (newColor = SDL_TRUE) 
	{
		// Mise à blanc de la case ciblée
		if (SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255) != 0) 
			SDL_ErrorCase("Trouble with fill rect") ;
		if (SDL_RenderFillRect(renderer, &rect) != 0) 
			SDL_ErrorCase("Trouble with fill rect") ;
	}
}
