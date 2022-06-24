#include "serpent.h"
#include "circle.h"
#define CARRE 4
#define TETE 1
#define LIGNE 3

void SDL_ErrorCase(char * msg) {
	SDL_Log("%s %s\n", msg, SDL_GetError()) ;
	exit(EXIT_FAILURE) ;
}

void SDL_DrawRect(SDL_Renderer * renderer, SDL_Rect rect, int r, int g, int b, SDL_bool fill) 
{
	if (SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE) != 0)
		SDL_ErrorCase("Trouble with draw color") ;

	if (fill == SDL_TRUE)
	if (SDL_RenderFillRect(renderer, &rect) != 0)
		SDL_ErrorCase("Trouble with fill rect") ;
 
	if (SDL_RenderDrawRect(renderer, &rect) != 0)
		SDL_ErrorCase("Trouble with draw rect") ;
}

void SDL_DrawLine(SDL_Renderer * renderer, point_t p1, point_t p2) 
{
	if (SDL_RenderDrawLine(renderer, p1.x, p1.y, p2.x, p2.y) != 0) 
		SDL_ErrorCase("Trouble with draw line") ;
}

void SDL_DrawPoint(SDL_Renderer * renderer, point_t p) 
{
	if (SDL_RenderDrawPoint(renderer, p.x, p.y) != 0) 
		SDL_ErrorCase("Trouble with draw point") ;
}

point_t * SDL_GetMidle(void * objet, point_t * origin, SDL_bool isCircle) 
{
	point_t * p = NULL ;
	if (objet != NULL) 	
	{
		p = malloc(sizeof(point_t)) ;
	
		if (isCircle == SDL_TRUE)  {
			p->x = origin->x + ((circle_t*)(objet))->rayon ;
			p->y = origin->y + ((circle_t*)(objet))->rayon ;
		} else {
			p->x = objet->x + ((circle_t*)(objet))->w/2 ;
			p->y = objet->y + ((circle_t*)(objet))->h/2 ;
		}
	} 
	return p ;
}

void SDL_DrawSnake(SDL_Renderer * renderer, point_t * origin) 
{
	SDL_Rect new ;
	if (renderer == 0) 
		SDL_ErrorCase("Trouble with renderer") ;
	SDL_Rect rect ;
	rect.x = origin->x ;
	rect.y = origin->y ;
	rect.w = 10 ;
	rect.h = 30 ;
	int i = 0 ;

	SDL_Color c = {0, 255, 0, 255} ;
	point_t * p  = SDL_DrawCircle(renderer, c, origin, 20) ;
	
	while (i < 4) {
		SDL_DrawRect(renderer, rect, 255, 0, 0, SDL_TRUE) ;
		p = SDL_GetMidle(*rect, p, SDL_FALSE) ;
		rect.x = p->x ;
		rect.y = p->y ;
		i++ ;
	}
	
}
