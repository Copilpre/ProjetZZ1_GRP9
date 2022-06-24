#include <stdio.h>
#include "serpent.h"

int main() 
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

	renderer = SDL_CreateRenderer(window, -1, 0) ;

	if (renderer == 0) 
		SDL_ErrorCase("Trouble with renderer") ;

	SDL_Point origin ;

	origin.x = 150 ;
	origin.y = 150 ;
	
	SDL_DrawSnake(renderer, origin) ;

	SDL_RenderPresent(renderer) ;
	SDL_Delay(5000) ;

	SDL_DestroyRenderer(renderer) ;
	SDL_DestroyWindow(window) ;
	SDL_Quit() ;

	exit(EXIT_FAILURE) ;
}
