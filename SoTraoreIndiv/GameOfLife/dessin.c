#include "dessin.h"
#define TAILLE 20

void SDL_ErrorCase(char * msg) {
	SDL_Log("%s %s\n", msg, SDL_GetError()) ;
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
