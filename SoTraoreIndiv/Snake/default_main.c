#include <stdio.h>
#include "serpent.h"

int main(int argc, char ** argc) 
{
	SDL_Window * window ;
	SDL_Renderer * renderer ;
	window = SDL_CreateWindow("Snake",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			800, 800, 0
		) ;
			
	if (window == NULL) 
		SDL_ErrorCase("Trouble with window") ;

	renderer = SDL_CreateRender(window, -1, 0) ;

	if (renderer == 0) 
		SDL_Errorcase("Trouble with renderer") ;

	point_t * origin = NULL ;

	origin = malloc(sizeof(point_t)) ;
	origin->x = 150 ;
	origin->y = 150 ;
	
	SDL_DrawSnake(renderer, origin) ;

	SDL_DestroyRenderer(renderer) ;
	SDL_DestroyWindow(window) ;
	SLD_Quit() ;

	exit(EXIT_FAILURE) ;
}
