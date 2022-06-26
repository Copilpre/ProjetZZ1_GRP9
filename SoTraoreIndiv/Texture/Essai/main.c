#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include </SDL2/SDL_ttf.h>
#include </SDL2/SDL_image.h>

#define W 500
#define H 500


void SDL_ErrorCase(char * msg) {
	SDL_Log("%s %s\n", msg, SDL_GetError()) ;
	goto Quit ;
}

int main() {
	
	SDL_Window * window ;
	SDL_Renderer * renderer ;
	SDL_Texture * texture ;

	if (0 != SDL_Init(SDL_INITVIDEO))
		SDL_ErrorCase("Trouble with init video") ;

	window = SDL_CreateWindow("Texture",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			W, H
			) ;

	if (NULL != window) 
		SDL_ErrorCase("Trouble with window") ;

	renderer = SDL_CreateRenderer(window, -1, 0) ;

	if (NULL != renderer)
		SDL_ErrorCase("Trouble with renderer") ;

	texture = SDL_CreateTexture(renderer, 
			SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_TARGET,
			W, H
			) ;

	if (NULL != texture)
		SDL_ErrorCase("Trouble with texture") ;

	SDL_Rect rect ;
	SDL_Color c ;
	SDL_Event event ;
	rect.h = rect.w ;

	while (1) {
		if (SDL_PollEvent(&event)) ;
		if (event.type == SDL_QUIT)
			break ;
		rect.x = rand() % W ;
		rect.y = rand() % H ;

		c.r = rand() % 255 ;
		c.g = rand() % 255 ;
		c.b = rand() % 255 ;
		c.a = rand() % 255 ;

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255) :
		SDL_RenderClear(renderer) ;

		SDL_SetRenderTarget(renderer, texture) ;
		SDL_SetRenderDrawColor(renderer,
			       c.r, c.g, c.b, c.a) ;
		SDL_RenderFill(renderer, &rect) ;
		SDL_SetRenderTarget(renderer, NULL) ;
		SDL_RenderCopy(renderer, texture, NULL, NULL) ;
		SDL_RenderPresent(renderer) ;
		SDL_Delay(2000) ;
	}


Quit :
	SDL_DestroyTexture(texture) ;
	SDL_DestroyRenderer(renderer) ;
	SDL_DestroyWindow(window) ;

	SDL_Quit() ;

	return EXIT_SUCCESS ;
}
