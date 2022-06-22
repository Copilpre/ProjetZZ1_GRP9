#include "dessin.h"
#define H 800
#define W 800
#define TAILLE 20

int main(int argc, char ** argv) {
	SDL_Window * window ;
	SDL_Renderer * renderer ;
	
	window = SDL_CreateWindow("GameOfLife",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			H, W, 0
			);

	if (window == NULL) 
		SDL_ErrorCase("Trouble with window") ;

	renderer = SDL_CreateRenderer(window, -1, 0) ;

	if (renderer == 0) 
		SDL_ErrorCase("Trouble with renderer") ;

	int w, h, i = 0, j = 0, vitesse = 0, taille ;

	SDL_GetWindowSize(window, &w, &h) ;

	SDL_bool keepLoop = SDL_TRUE , newColor = SDL_FALSE ;

	SDL_Event event ;
	taille = TAILLE ;
	SDL_Rect rect ; 
	rect.w = (int)(w/taille) ;
	rect.h = (int)(h/taille) ;			

	SDL_DrawWindowOfGame(renderer, taille, h, w) ;
	
	while (keepLoop) {

		while (SDL_PollEvent(&event)) 
		{
			switch (event.type) 
			{
				case SDL_BUTTON_LEFT :
					vitesse = (vitesse < 100) ? vitesse+10 : 100 ;
					break ;
				case SDL_BUTTON_RIGHT :
					vitesse =  (vitesse > 10) ? vitesse-10 : 10;
					break ;
				case SDL_MOUSEBUTTONDOWN :
					SDL_GetMouseState(&i, &j) ;
					i = (int)(i / rect.w) ;
					j = (int)(j / rect.h) ;
					rect.x = i * rect.w ;
					rect.y = j * rect.h ;
					// Ici on doit prendre en compte certains 
					// changement au niveau de l'ecran et de la grille 
					newColor = SDL_TRUE ;
					SDL_ChangeColor(renderer, rect, newColor) ;
					break ;
				case SDL_WINDOWEVENT_CLOSE :
					keepLoop = SDL_FALSE ;
					break ;
				case SDL_QUIT :
					keepLoop = SDL_FALSE ;
					break ;
				case SDL_WINDOWEVENT_LEAVE :
					keepLoop = SDL_FALSE ;
					break ;
				default :
					break ;
			}

			SDL_RenderPresent(renderer) ;
			SDL_Delay(vitesse) ;
		}
	}

	SDL_DestroyRenderer(renderer) ;
	SDL_DestroyWindow(window) ;
	SDL_Quit() ;

	exit(EXIT_FAILURE) ;
}
