#include <stdio.h>
#include "serpent.h"

int main() 
{
	SDL_Window * window ;
	SDL_Renderer * renderer ;
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		SDL_ErrorCase("Trouble with init vidéo") ;

	window = SDL_CreateWindow("Snake",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			800, 800, 0
		) ;
			
	if (window == NULL) 
		SDL_ErrorCase("Trouble with window") ;

	renderer = SDL_CreateRenderer(window, -1, 0) ;

	if (renderer == 0) 
		SDL_ErrorCase("Trouble with renderer") ;

	SDL_Point origin ;
	SDL_Event event ;
	SDL_bool program_on = SDL_TRUE , pause = SDL_FALSE,
			okClear = SDL_TRUE ; ;
	origin.x = 150 ;
	origin.y = 150 ;
	int rayon = 15 , pas = 30;
	char choice ;
	liste_t * points = SDL_DrawSnake(renderer, origin) ;
	
	while (program_on) {
		if (SDL_PollEvent(&event)) 
		{
		/*	if (okClear == SDL_TRUE) {
			if (SDL_SetRenderDrawColor(renderer, 255, 
						255, 255, 
						255) != 0)
				SDL_ErrorCase("Trouble with color") ;
				SDL_RenderClear(renderer) ;
			}*/
			switch (event.type) {
			case SDL_KEYDOWN :
				switch(event.key.keysym.sym) {
				case SDLK_RIGHT :
					choice = 'd' ;
					SDL_MoveSnake(renderer, 
							points, 
							choice, 
							pas
						) ;
					okClear = !okClear ;
					break ;
				case SDLK_LEFT :
					choice = 'g' ;
					SDL_MoveSnake(renderer, 
							points, 
							choice, 
							pas
						) ;
					okClear = !okClear ;
					break ;
				case SDLK_UP :
					choice = 'h' ;
					SDL_MoveSnake(renderer, 
							points, 
							choice, 
							pas
						) ;
					break ;
					okClear = !okClear ;
				case SDLK_DOWN :
					choice = 'b' ;
					SDL_MoveSnake(renderer, 
							points, 
							choice, 
							pas
						) ;
					okClear = !okClear ;
					break ;
				case SDLK_SPACE :
					pause = !pause ;
					program_on = SDL_FALSE ;
					break ;
				case SDLK_q :
					program_on = SDL_FALSE ;
					break ;
				default :
					break ;
				}
				break ;
			case SDL_QUIT :
				program_on = SDL_FALSE ;
				break ;
			default :
				break ;
			}
			SDL_RenderPresent(renderer) ;
			SDL_Delay(500) ;
		}
	}
	SDL_DestroyRenderer(renderer) ;
	SDL_DestroyWindow(window) ;
	SDL_Quit() ;

	exit(EXIT_FAILURE) ;
}
