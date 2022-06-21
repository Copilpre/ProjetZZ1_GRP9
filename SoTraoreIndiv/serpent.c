#include "serpent.h"

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

/*
	Un serpent est composé de 5 carrés avec 4 ligne intermediaire
	la tete est un circle.
*/

void SDL_DrawSnake(SDL_Renderer * renderer, int x, int y) 
{
	

}

