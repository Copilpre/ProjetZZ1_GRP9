#include "serpent.h"
#define CARRE 8
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

liste_t * creerListe() {
	liste_t * nouv = NULL ;
	nouv = malloc(sizeof(liste_t)) ;
	nouv->next = NULL ;
	return nouv ;
}

// Il sera preferable d'utiliser une file pour l'ajout ici


liste_t * ajoutTeteListe(liste_t * tete, SDL_Point p) {

	liste_t * nouv = creerListe() ;

	if (nouv != NULL)
	if (tete != NULL) {
		nouv->p = p ;
		nouv->next = tete ;
	} 
	tete = nouv ;

	return tete ;
}

liste_t * ajoutFinListe(liste_t * tete, SDL_Point p) {
	liste_t * nouv = NULL ;
	nouv = creerListe() ;

	if (nouv != NULL) {
		nouv->p = p ;
		if (tete == NULL) {
			tete = nouv ;
		} 
		else {
			liste_t * cour = tete ;
			while (cour->next != NULL) 
				cour = cour->next ;
			cour->next = nouv ;
		}
	}

	return tete ;
}

liste_t * supprimerTeteListe(liste_t * tete) {
	if (tete != NULL) 
	{
		liste_t * del = tete ;
		tete = tete->next ;
		free(del) ;
		del = NULL ;
	}
	return tete ;
}

liste_t * supprimerFinListe(liste_t * tete) {

	liste_t * del = NULL ;

	if (tete->next != NULL) 
	{
		liste_t * cour = tete ;
		while ((cour = cour->next) != NULL) ;
		del = cour ;
	} 
	else {
		del = tete ;
	}
	free(del) ;
	del = NULL ;

	return tete ;
}

void libererListe(liste_t * tete) {
	if (tete != NULL) 
	{
		liste_t * del = NULL ;
		while (tete != NULL) 
		{
			del = tete ;
			tete = tete->next ;
			free(del) ;
			del = NULL ;
		}
	}
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

liste_t * SDL_DrawSnake(SDL_Renderer * renderer, SDL_Point origin) 
{
	if (renderer == 0) 
		SDL_ErrorCase("Trouble with renderer") ;
	SDL_Rect rect ;
	rect.w = 15 ;
	rect.h = 15 ;
	int i = 0 , r = 15;
 	liste_t * tete =  NULL ;
	SDL_Color c = {255, 0, 0, 255} ;
	tete = ajoutTeteListe(tete, origin) ;

	SDL_DrawCircle(renderer, c, origin, r) ;
	SDL_Point * p = malloc(sizeof(SDL_Point)) ;
	p->x = origin.x + r;
        p->y = origin.y - (int)(r/2) ;
	rect.x = p->x ;
	rect.y = p->y ;
	
	while (i < CARRE) {
		SDL_DrawRect(renderer, rect, 0, 255, 0, SDL_FALSE) ;
		tete = ajoutFinListe(tete, *p) ;
		p = SDL_GetMidle(&rect, p, SDL_FALSE) ;
		rect.x = p->x ;
		rect.y = p->y ;
		i++ ;
	}
	
	return tete ;
}


SDL_bool SDL_IsSnakeVertical( liste_t * points ) {
	
	SDL_bool yes = SDL_TRUE ;

	liste_t * cour = points, * suiv =  points->next ;

	if (cour != NULL) {
		if (suiv != NULL) 
		if (cour->p.x == suiv->p.x)
			yes = SDL_FALSE ;
	}

	return yes ;
}


void SDL_MoveSnake(SDL_Renderer * renderer, liste_t * points, char choice, int pas) {
	if (points != NULL) 
	{
		liste_t * cour = points ;
		SDL_bool okDeleteIt = SDL_FALSE, first = SDL_TRUE ;
		SDL_Rect rect = {0, 0, 15, 15} ;
		switch (choice) {
		case 'g' :
			while (cour != NULL) {
				if (SDL_IsSnakeVertical(points)) {
					cour->p.y -= pas ;
				}
				else { 
					cour->p.x -= pas ;
				}
				rect.y = cour->p.y ;
				rect.x = cour->p.x ;
				points = ajoutTeteListe(points, cour->p) ;
				//SDL_SetRenderDrawColor(renderer, 255, 255, 
				//				255, 255
				//			) ;
				//SDL_RenderFillRect(renderer, &rect) ;

				SDL_DrawSnake(renderer, cour->p) ;
				cour = cour->next ;
			}
			okDeleteIt = SDL_TRUE ;
			break ;
		case 'd' :
			while (cour != NULL) {
				if (SDL_IsSnakeVertical(points)) {
					cour->p.y += pas ;
				}
				else { 
					cour->p.x += pas ;
				}
				rect.y = cour->p.y ;
				rect.x = cour->p.x ;
				//points = ajoutTeteListe(points, cour->p) ;
				//SDL_SetRenderDrawColor(renderer, 255, 255, 
				//				255, 255
				//			) ;
				//SDL_RenderFillRect(renderer, &rect) ;
				SDL_DrawSnake(renderer, cour->p) ;
				cour = cour->next ;
			}
			okDeleteIt = SDL_TRUE ;
			break ;
		case 'h' :
			while (cour != NULL) {
				if (!SDL_IsSnakeVertical(points)) {
					cour->p.x -= pas ;
				}
				else {
					cour->p.y -= pas ;
				}
				rect.y = cour->p.y ;
				rect.x = cour->p.x ;
				points = ajoutTeteListe(points, cour->p) ;
				//SDL_SetRenderDrawColor(renderer, 255, 255, 
				//				255, 255
				//			) ;
				//SDL_RenderFillRect(renderer, &rect) ;
				SDL_DrawSnake(renderer, cour->p) ;
				cour = cour->next ;
			}
			okDeleteIt = SDL_TRUE ;
			break ;
		case 'b' :
			while (cour != NULL) {
				if (!SDL_IsSnakeVertical(points)) {
					cour->p.x += pas ;
				}
				else {
					cour->p.y += pas ;
				}
				rect.y = cour->p.y ;
				rect.x = cour->p.x ;
				points = ajoutTeteListe(points, cour->p) ;
				//SDL_SetRenderDrawColor(renderer, 255, 255, 
				//				255, 255
				//			) ;
				//SDL_RenderFillRect(renderer, &rect) ;
				SDL_DrawSnake(renderer, cour->p) ;
				cour = cour->next ;
			}
			okDeleteIt = SDL_TRUE ;
			break ;
		default :
			break ;
		}
		if (okDeleteIt == SDL_TRUE) 
			points = supprimerFinListe(points) ;
	}
}
