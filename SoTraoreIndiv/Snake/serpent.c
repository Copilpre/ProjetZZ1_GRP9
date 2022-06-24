#include "serpent.h"
#define CARRE 5
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

void SDL_DrawPoint(SDL_Renderer * renderer, SDL_Point p) 
{
	if (SDL_RenderDrawPoint(renderer, p.x, p.y) != 0) 
		SDL_ErrorCase("Trouble with draw point") ;
}


void SDL_DrawCircle(SDL_Renderer * renderer, SDL_Color c, SDL_Point origin, int r)
{
	if (SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a) != 0) 
		SDL_ErrorCase("Trouble with draw color") ;

	int pas = 1 , x0 = 0 , y0 = 0 , x1 = 0, y1 = 0 ;

	circle_t * c1 = malloc(sizeof(circle_t)) ;
	c1->rayon = r ;
	c1->angle = 0; 
	point_t * p ;

	while ( c1->angle < 360 ) {

		c1 = polaire(c1, pas) ;
		p = cartesien(c1) ;

		x0 = p->x + origin.x ;
		y0 = p->y + origin.y ;


		c1 = polaire(c1, pas) ;
		p = cartesien(c1) ;

		x1 = p->x + origin.x ;
		y1 = p->y + origin.y ;

	
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
			p->x += ((circle_t*)objet)->rayon ;
		} 
		else {
			p->x = ((SDL_Rect*)objet)->x + ((SDL_Rect*)objet)->w ;
			p->y = ((SDL_Rect*)objet)->y ;
		}
	} 

	return p ;
}

void SDL_DrawSnake(SDL_Renderer * renderer, SDL_Point origin) 
{
	if (renderer == 0) 
		SDL_ErrorCase("Trouble with renderer") ;
	SDL_Rect rect ;
	rect.w = 20 ;
	rect.h = 20 ;
	int i = 0 , r = 20;
 
	SDL_Color c = {0, 255, 0, 255} ;
	SDL_DrawCircle(renderer, c, origin, r) ;
	SDL_Point * p = malloc(sizeof(SDL_Point)) ;
	p->x = origin.x + r;
        p->y = origin.y - (int)(r/2) ;
	rect.x = p->x ;
	rect.y = p->y ;
	
	while (i < CARRE) {
		c.r = 255 * cos(p->x) ;
		c.g = 255 * sin(p->y) ;
		c.b = 255 * sinh(p->x) ;
		SDL_DrawRect(renderer, rect, c.r, c.g, c.b, SDL_FALSE) ;
		p = SDL_GetMidle(&rect, p, SDL_FALSE) ;
		rect.x = p->x ;
		rect.y = p->y ;
		i++ ;
	}
	
}
