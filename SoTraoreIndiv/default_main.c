#include <stdio.h>
#include "serpent.h"

int main(int argc, char ** argc) {
	SDL_Window * window ;
	SDL_Renderer * renderer ;



	SDL_DestroyRenderer(renderer) ;
	SDL_DestroyWindow(window) ;
	SLD_Quit() ;

	exit(EXIT_FAILURE) ;
}
