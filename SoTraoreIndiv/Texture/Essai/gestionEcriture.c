#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
	
	if( TTF_Init() < 0 ) {
		SDL_Log("Trouble with ttf %s", SDL_GetError()) ;
		exit(EXIT_FAILURE) ;
	}
	
	TTF_Font * font = NULL ;
	
	font = TTF_OpenFont("./font/Pacifico.fft", 65) ;

	if (font == NULL) {
		SDL_Log("Trouble with font %s", SDL_GetError()) ;
		exit(EXIT_FAILURE) ;
	}
	
	TTF_SetFontStyle(font, TTF_STYLE_ITALIC | TTF_STYLE_BOLD) ;

	SDL_Color color = {20, 0, 40, 255} ;
	SDL_Surface * text_surface = NULL ;
	text_surface = TTF_RenderText_Blended(font, "Hello", color) ;

	if (text_surface == NULL) {
		SDL_Log("Trouble with text %s", SDL_GetError()) ;
		exit(EXIT_FAILURE) ;
	}

	SDL_Texture * text_texture = NULL ;
	text_texture = SDL_CreateTextureFromSurface(renderer, text_surface) ;

	if (text_texture != NULL) {
		SDL_Log("Trouble with ttf %s", SDL_GetError()) ;
		exit(EXIT_FAILURE) ;
	}

	SDL_FreeSurface(text_surface) ;

	SDL_Rect pos = {0, 0, 0, 0} ;
	SDL_QueryTexture(text_texture, NULL, NULL, &pos.w, &pos.h) ;
	SDL_RenderCopy(renderer, text_texture, NULL, &pos) ;
	SDL_DestroyTexture(text_texture) ;

	SDL_RenderPresent(renderer) ;
	TTF_Quit();
}
