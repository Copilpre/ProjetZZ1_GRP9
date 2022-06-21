#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h>
// #include <SDL2/SDL_image.h>
// #include <SDL2/SDL_ttf.h>
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
	if (c1->angle > 360) c1->angle = 0 ;
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

int main( int argc, char ** argv)  
{

	SDL_Window * window ;
	SDL_Renderer * renderer ;
	SDL_Rect rect ;
	SDL_DisplayMode screen ;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) 
		SDL_ErrorCase("Problème d'ouverture de la vidéo") ;

	window = SDL_CreateWindow(
		"Objet mouvement Circulaire",
		100, 100, 600, 600, 0
	);
	
	if (window == NULL) 
		SDL_ErrorCase("Could not create window") ;

	renderer = SDL_CreateRenderer(window , -1 , 0) ;

	if (renderer == 0) 
		SDL_ErrorCase("Problème d'ouverture du rendu") ;

	rect.x = rect.y = 100 ;
	rect.w = rect.h = 200 ;

	circle_t * c1 = malloc(sizeof(circle_t)) ;
	point_t * p ;
	c1->rayon = 100 ;
	c1->angle = 0 ;
	float pas = 0.0001 ;
	point_t * origin = malloc(sizeof(point_t)) ;
	origin->x = 300;
	origin->y = 400;
	
	SDL_bool keepContinu = SDL_TRUE ;
	SDL_Event event ;

	while (keepContinu) {
		c1 = polaire(c1, pas) ;
		p = cartesien(c1) ;
		if (SDL_SetRenderDrawColor(renderer,
			cos(c1->angle) * 255, 
			sin(c1->angle) * 255,
			cosh(c1->angle) * 255, 
			SDL_ALPHA_OPAQUE)  != 0)
			SDL_ErrorCase("Trouble with Color") ;
		rect.x = (int)(p->x + origin->x) ;
		rect.y = (int)(p->y + origin->y) ;
		rect.w = 20 ; 
		rect.h = 20 ;
		if (SDL_RenderDrawRect(renderer, &rect) != 0)
			SDL_ErrorCase("Trouble with Rect") ;
		if (SDL_RenderFillRect(renderer, &rect) != 0)
			SDL_ErrorCase("Trouble with fill") ;
		SDL_RenderPresent(renderer) ;

		if (SDL_PollEvent(&event)) 
		{
			switch(event.type) {
			case SDL_QUIT :
				keepContinu = SDL_FALSE ;
				break ;
			case SDL_WINDOWEVENT_LEAVE :
				keepContinu = SDL_FALSE ;
				break ;
			case SDL_WINDOWEVENT_CLOSE :
				keepContinu = SDL_FALSE ;
				break ;
			default :
				break ;
			}
		}	
	}

	SDL_RenderClear(renderer) ;

	SDL_DestroyRenderer(renderer) ;
	SDL_DestroyWindow(window) ;

	SDL_Quit() ;

	exit(EXIT_FAILURE) ;
}
