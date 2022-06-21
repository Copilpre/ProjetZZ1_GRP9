#include "serpent.h"
#define CARRE 4
#define TETE 1
#define LIGNE 3

void SDL_ErrorCase(char * msg) {
	SDL_Log("%s %s\n", msg, SDL_GetError()) ;
	exit(EXIT_FAILURE) ;
}

void SDL_DrawRect(SDL_Renderer * renderer, SDL_Rect rect, int r, int g, int b, SDL_bool fill) 
{
	if (fill == SDL_TRUE)
	if (SDL_RenderFillRect(renderer, r, g, b, SDL_ALPHA_OPAQUE) != 0)
		SDL_ErrorCase("Trouble with fill rect") ;

	if (SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE) != 0)
		SDL_ErrorCase("Trouble with draw color") ;
 
	if (SDL_RenderDrawRect(renderer, &rect) != 0)
		SDL_ErrorCase("Trouble with draw rect") ;
}

void SDL_DrawLine(SDL_Renderer * renderer, int x1, int y1, int x2, int y2) 
{
	if (SDL_RenderDrawLine(renderer, x1, y1, x2, y2) != 0) 
		SDL_ErrorCase("Trouble with draw line") ;
}

void SDL_DrawPoint(SDL_Renderer * renderer, int x, int y) 
{
	if (SDL_RenderDrawPoint(renderer, x, y) != 0) 
		SDL_ErrorCase("Trouble with draw point") ;
}

point_t * SDL_GetMidle(void * objet, point_t * origin, SDL_bool isCircle) 
{
	point_t * p = NULL ;

	if (objet != NULL) 	
	{
		p = malloc(sizeof(point_t)) ;
	
		if (isCircle == SDL_TRUE)  {
			p->x = origin->x + objet.rayon ;
			p->y = origin->y + objet.rayon ;
		} else {
			p->x = objet->x + (objet.w/2) ;
			p->y = objet->y + (objet.h/2) ;
		}
	} 
	return p ;
}

void SDL_DrawSnake(SDL_Renderer * renderer, point_t * origin) 
{
	SDL_Rect new ;
	if (renderer == 0) 
		SDL_ErrorCase("Trouble with renderer") ;
	SDL_Rect rect1 ;
	rect.x = origin->x ;
	rect.y = origin->y ;
	rect.w = 10 ;
	rect.h = 30 ;
	int i = 0 ;

	SDL_Color c = {0, 255, 0, 255} ;
	point_t * p  = SDL_DrawCircle(renderer, c, origin, 20) ;
	
	while (i < 4) {
		SDL_DrawRect(renderer, rect, 255, 0, 0, SDL_TRUE) ;
		point_t * p = SDL_GetMidle(*rect, origin, SDL_FALSE) ;
		rect.x = p->x ;
		rect.y = p->y ;
		i++ ;
	}
	
}

