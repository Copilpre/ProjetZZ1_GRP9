#include <stdio.h>
#include <SDL2/SDL.h>
#include<stdlib.h>

void SDL_ErrorCase(char * msg) ;
void SDL_DrawRect(SDL_Renderer * renderer, SDL_Rect rect, int r, int g, int b, SDL_bool fill) ; 
void SDL_DrawLine(SDL_Renderer * renderer, int x1, int y1, int x2, int y2) ;
void SDL_DrawPoint(SDL_Renderer * renderer, int x, int y) ;
void SDL_DrawSnake(SDL_Renderer * renderer, int x, int y) ;
