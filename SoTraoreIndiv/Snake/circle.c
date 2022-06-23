#include "circle.h"

circle_t * polaire(circle_t * c1, float angle) {
	circle_t * c = malloc(sizeof(circle_t)) ;
	c->rayon = c1->rayon ;
	//if (c1->angle > 360) c1->angle = 0 ;
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

	int step = 0.001 , x = y = 0;
	circle_t * c = malloc(sizeof(circle_t)) ;
	c->rayon = r ;
	c->angle = 0; 
	while (c->angle < 360) {
		c = polaire(c, pas) ;
		p = cartesien(c) ;

		x = p->x + origin->x ;
		y = p->y + origin->y ;

		if (SDL_RenderDrawPoint(renderer, x, y) != 0)
			SDL_ErrorCase("Trouble with draw point") ;

	}
}
