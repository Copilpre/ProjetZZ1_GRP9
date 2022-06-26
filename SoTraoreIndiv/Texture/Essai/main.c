#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
//#include <SDL2/SDL_ttf.h>
//#include <SDL2/SDL_image.h>

#define W 600
#define H 600


void SDL_ErrorCase(char * msg) {
	SDL_Log("%s %s\n", msg, SDL_GetError()) ;
	exit(EXIT_FAILURE) ;
}

int main() {
	
	SDL_Window * window ;
	SDL_Renderer * renderer ;
	SDL_Texture * texture ;
	SDL_Surface * img , *dst;

	if (0 != SDL_Init(SDL_INIT_VIDEO))
		SDL_ErrorCase("Trouble with init video") ;

	window = SDL_CreateWindow("Texture",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			W, H, 
			SDL_WINDOW_OPENGL
			) ;

	if (NULL == window) 
		SDL_ErrorCase("Trouble with window") ;

	renderer = SDL_CreateRenderer(window, -1, 0) ;

	if (NULL == renderer)
		SDL_ErrorCase("Trouble with renderer") ;

	img = SDL_CreateRGBSurface(0, W/4, H/4, 32, 0, 0, 0, 0) ;
	dst = SDL_CreateRGBSurface(0, W/6, H/6, 32, 0, 0, 0, 0) ;

	if (img == NULL || dst == NULL) 
		SDL_ErrorCase("Trouble with surface") ;

	SDL_Rect src = {100, 100, 100, 100} ,
		 srcrect = {50, 50, 150, 150} ;
	SDL_Color c ;
	
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255) ;
	SDL_RenderClear(renderer) ;
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255) ;

	SDL_FillRect(img, &src, SDL_MapRGB(img->format, 255, 0, 0)); 
	SDL_BlitSurface(img, &srcrect, dst, &src) ;

	SDL_RenderPresent(renderer) ;
	SDL_Delay(4000) ;

Quit :
	SDL_FreeSurface(img) ;
	SDL_DestroyRenderer(renderer) ;
	SDL_DestroyWindow(window) ;

	SDL_Quit() ;

	return EXIT_SUCCESS ;
}
