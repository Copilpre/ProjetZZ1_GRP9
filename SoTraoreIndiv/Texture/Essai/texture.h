#ifndef __TEXTURE__
#define __TEXTURE__

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
//#include <SDL2/SDL_image.h>
//#include <SDL2/SDL_ttf.h>

void SDL_ErrorCase(char * msg) ;
SDL_Texture * loadTextureFromImage(char * img, SDL_Renderer * renderer) 
void play_with_texture_1(SDL_Texture * texture, SDL_Window * window, SDL_Renderer * renderer) ;
void play_with_texture_2(SDL_Texture * texture, SDL_Window * window, SDL_Renderer * renderer) ; 
void play_with_texture_3(SDL_Texture * texture, SDL_Window window, SDL_Renderer * renderer) ;
void play_with_texture_4(SDL_Texture *texture, SDL_Window * window, SDL_Renderer * renderer) ; 
void play_with_texture_5(SDL_Texture *bg_texture, SDL_Texture * texture, SDL_Window * window, SDL_Renderer * renderer) ; 
#endif
