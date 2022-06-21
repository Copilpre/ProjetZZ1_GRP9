#include <stdio.h>
#include<stdlib.h>

void SDL_ErrorCase(char * msg) {
	SDL_Log("%s %s\n", msg, SDL_GetError()) ;
	exit(EXIT_FAILURE) ;
}

void dessinRect(SDL_Renderer * renderer, SDL_Rect rect, int r, int g, int b, SDL_Bool fill) 
{
	if (fill == SDL_TRUE)
	if (SDL_RenderFillRect(renderer, r, g, b, SDL_ALPHA_OPAQUE) != 0)
		SDL_ErrorCase("Trouble with fill rect") ;
	if (SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE) != 0)
		SDL_ErrorCase("Trouble with 
	if (SDL_RenderDrawRect(renderer, &rect) != 0)
		SDL_ErrorCase("Trouble with draw rect") ;
}

void dessinPoint(SDL_Renderer * renderer, int x1, int y1, int x2, int y2) 
{
	if (
}

int main(int argc, char ** argc) {
	SDL_Window * window ;

	exit(EXIT_FAILURE) ;
}
