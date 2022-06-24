#ifndef __SNAKE__
#define __SNAKE__
#include <stdio.h>
#include <math.h>
#include <SDL2/SDL.h>
#include<stdlib.h>
#define TAILLE 40


typedef struct circle {
	int rayon ;	
	float angle ;
} circle_t ;

typedef struct point {
	int x ;
	int y ;
} point_t ;

circle_t * polaire(circle_t * c1, float angle) ;
point_t * cartesien(circle_t * c1) ;
void SDL_DrawCircle(SDL_Renderer * renderer, SDL_Color c, point_t origin, int r) ;
void SDL_ErrorCase(char * msg) ;
void SDL_DrawRect(SDL_Renderer * renderer, SDL_Rect rect, int r, int g, int b, SDL_bool fill) ; 
void SDL_DrawLine(SDL_Renderer * renderer, SDL_Point p1, SDL_Point p2) ;
void SDL_DrawPoint(SDL_Renderer * renderer, SDL_Point origin) ;
SDL_Point * SDL_GetMid(void * objet, SDL_Point * origin, SDL_bool isCircle) ;
void SDL_DrawSnake(SDL_Renderer * renderer, SDL_Point * origin) ;

#endif 
