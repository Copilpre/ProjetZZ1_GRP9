#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h>
#define TAILLE 40

typedef struct circle {
	int rayon ;	
	float angle ;
} circle_t ;

typedef struct point {
	int x ;
	int y ;
} point_t ;

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

int main( int argc, char ** argv)  
{
	SDL_Window * window ;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("%s\n", SDL_GetError()) ;
		return 1 ;
	}

	int keepContinu = 1 ;
	SDL_Window ** windows = malloc(sizeof(void*)*TAILLE) ;
	circle_t * c1 = malloc(sizeof(circle_t)) ;
	point_t * p ;
	c1->rayon = 300 ;
	c1->angle = 0 ;
	float pas = 360 / TAILLE ;
	point_t * origin = malloc(sizeof(point_t)) ;
	origin->x = 900 ;
	origin->y = 400 ;

	for (int i=0; i<TAILLE; i++) {
		c1 = polaire(c1, pas) ;
		p = cartesien(c1) ;
		windows[i] = SDL_CreateWindow(
			"Window",
			p->x + origin->x ,
			p->y + origin->y ,
			200,
        		200,
        		SDL_WINDOW_OPENGL
		);
		
		if (windows == NULL) {
			printf("Could not create window: %s\n", SDL_GetError()) ;
			return 1 ;
		}
	}

	SDL_Delay(6000) ;
	
	for (int i=TAILLE-1; i>-1; i--) {
		SDL_DestroyWindow(windows[i]) ;
	}

	exit(EXIT_FAILURE) ;
}
