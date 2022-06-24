#include "serpent.h"
#define CARRE 4
#define TETE 1
#define LIGNE 3

circle_t * polaire(circle_t * c1, float angle) {
	circle_t * c = malloc(sizeof(circle_t)) ;
	c->rayon = c1->rayon ;
	c->angle = (c1->angle + angle) ;
	return c ;
}

point_t * cartesien(circle_t * c1) {
	point_t * p = malloc(sizeof(point_t)) ;
	p->x = c1->rayon * cos(c1->angle) ;
	p->y = c1->rayon * sin(c1->angle) ;
	return p ;
}

void SDL_ErrorCase(char * msg) {
	SDL_Log("%s %s\n", msg, SDL_GetError()) ;
	exit(EXIT_FAILURE) ;
}

void SDL_DrawRect(SDL_Renderer * renderer, SDL_Rect rect, int r, int g, int b, SDL_bool fill) 
{
	if (SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE) != 0)
		SDL_ErrorCase("Trouble with draw color") ;
	if (!fill == SDL_TRUE)
	if (SDL_RenderFillRect(renderer, &rect) != 0)
		SDL_ErrorCase("Trouble with fill rect") ;
 	if (fill == SDL_TRUE)
	if (SDL_RenderDrawRect(renderer, &rect) != 0)
		SDL_ErrorCase("Trouble with draw rect") ;
}

void SDL_DrawLine(SDL_Renderer * renderer, SDL_Point p1, SDL_Point p2) 
{
	if (SDL_RenderDrawLine(renderer, p1.x, p1.y, p2.x, p2.y) != 0) 
		SDL_ErrorCase("Trouble with draw line") ;
}

void SDL_DrawPoint(SDL_Renderer * renderer, point_t p) 
{
	if (SDL_RenderDrawPoint(renderer, p.x, p.y) != 0) 
		SDL_ErrorCase("Trouble with draw point") ;
}


void SDL_DrawCircle(SDL_Renderer * renderer, SDL_Color c, point_t origin, int r)
{
	if (SDL_RenderDrawColor(renderer, c.r, c.g, c.b, c.a) != 0) 
		SDL_ErrorCase("Trouble with draw color") ;

	int pas = 1 , x0 = 0 , y0 = 0 , x1 = 0, y1 = 0 ;

	circle_t * c = malloc(sizeof(circle_t)) ;
	c->rayon = r ;
	c->angle = 0; 

	while ( c->angle < 360 ) {

		c = polaire(c, pas) ;
		p = cartesien(c) ;

		x0 = p->x + origin->x ;
		y0 = p->y + origin->y ;


		c = polaire(c, pas) ;
		p = cartesien(c) ;

		x1 = p->x + origin->x ;
		y1 = p->y + origin->y ;

	
		if (SDL_RenderDrawLine(renderer, x0, y0, x1, y1) != 0)
			SDL_ErrorCase("Trouble with draw point") ;

	}
}

SDL_Point * SDL_GetMidle(void * objet, SDL_Point * origin, SDL_bool isCircle) 
{
	SDL_Point * p = NULL ;

	if (objet != NULL) 	
	{
		p = malloc(sizeof(SDL_Point)) ;
		p->x = origin->x ;
		p->y = origin->y ;
	
		if (isCircle == SDL_TRUE)  {
			objet = ((circle_t*)objet) ;
			p->x += objet->rayon ;
		} 
		else {
			objet = ((SDL_Rect*)objet) ;	
			p->x = objet->x + objet->w/2 ;
			p->y = objet->y ;
		}
	} 

	return p ;
}

void SDL_DrawSnake(SDL_Renderer * renderer, point_t * origin) 
{
	if (renderer == 0) 
		SDL_ErrorCase("Trouble with renderer") ;
	SDL_Rect * rect = malloc(sizeof(rect)) ;
	rect->x = origin->x ;
	rect->y = origin->y ;
	rect->w = 10 ;
	rect->h = 20 ;
	int i = 0 ;

	SDL_Color c = {0, 255, 0, 255} ;
	point_t * p  = SDL_DrawCircle(renderer, c, origin, 20) ;
	
	while (i < 4) {
		SDL_DrawRect(renderer, rect, 255, 0, 0, SDL_FALSE) ;
		p = SDL_GetMidle(rect, p, SDL_FALSE) ;
		rect->x = p->x ;
		rect->y = p->y ;
		i++ ;
	}
	
}
