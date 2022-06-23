#include <stdio.h>
#include <SDL2/SDL.h>
#include<stdlib.h>

void SDL_ErrorCase(char * msg) ;
void SDL_DrawRect(SDL_Renderer * renderer, SDL_Rect rect, int r, int g, int b, SDL_bool fill) ; 
void SDL_DrawLine(SDL_Renderer * renderer, point_t p1, point_t p2) ;
void SDL_DrawPoint(SDL_Renderer * renderer, point_t origin) ;
point_t * SDL_GetMid(void * objet, point_t * origin, SDL_bool isCircle) ;
void SDL_DrawSnake(SDL_Renderer * renderer, point_t * origin) ;
