#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#define H 800
#define W 800

void SDL_ErrorCase(char * msg) {
	printf("%s %s\n", msg, SDL_GetError()) ;
	exit(EXIT_FAILURE) ;
}

SDL_Texture * loadTextureFromImage(SDL_Renderer * renderer, char * img_name) {
	SDL_Surface * img = NULL ;
	SDL_Texture * texture = NULL ;

	img = IMG_Load(img_name) ;
	
	if (img == NULL) 
		SDL_ErrorCase("Trouble with load image") ;

	texture = SDL_CreateTextureFromSurface(renderer, img) ;

	if (texture == NULL) 
		SDL_ErrorCase("Trouble with create texture from surface") ;

	SDL_FreeSurface(img) ;

	return texture ;
}


int main() {

	SDL_Renderer * renderer ;

	SDL_Window * window ;

	window = SDL_CreateWindow("IMAGE",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			H, W, 0
		) ;
	
	if (window != NULL) 
		SDL_ErrorCase("Trouble with window") ;

	renderer = SDL_CreateRenderer(window, -1, 0) ;

	if (renderer != 0)
		SDL_ErrorCase("Trouble with renderer") ;

	SDL_Texture * texture ;

	char * img_name = "index.jpeg" ;

	texture = loadTextureFromImage(renderer, img_name) ;

	SDL_DestroyTexture(texture) ;
	SDL_DestroyRenderer(renderer) ;
	SDL_DestroyWindow(window) ;

	SDL_Quit() ;

	exit(EXIT_FAILURE) ;
}
