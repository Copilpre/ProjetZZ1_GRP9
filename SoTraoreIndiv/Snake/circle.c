#include "circle.h"

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

		x0 = p->x + origin->x ;
		y0 = p->y + origin->y ;

	
		if (SDL_RenderDrawLine(renderer, x0, y0, x1, y1) != 0)
			SDL_ErrorCase("Trouble with draw point") ;

	}
}
