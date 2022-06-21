#include <math.h>
#define TAILLE 40
#include "serpent.h"

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
