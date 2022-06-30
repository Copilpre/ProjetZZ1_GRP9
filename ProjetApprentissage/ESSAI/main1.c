#include "fenetre.h"

int main() {

	srand(time(NULL)) ;
	SDL_Window * window = NULL ;
	SDL_Renderer * renderer = NULL ;
	SDL_Texture * texture = NULL ;
	SDL_Texture * bg_texture = NULL ;

	SDL_Rect cadre[3] ;
	SDL_Rect chambre[NB_CHAMBRE] ;
	SDL_Rect button[NB_BUTTON] ;

	SDL_Event event ;
	SDL_bool program_on = SDL_TRUE ;
	SDL_bool pause = SDL_FALSE ;
	int pos = 0, wd = 8, hd = 10 , boredX=10, boredY=10; 
	int mouseX, mouseY, pas=1, action, prec, cible ;

	barLevel_t b ;
	b.i = rand() % 10 ;
	b.j = rand() % 10 ;
	b.k = rand() % 10 ;

	char list[6][30] = {
			{"./Image/move.png"},
			{"./Image/move1"},
			{"./Image/pingouin.png"},
			{"./Image/pinguin1.png"},
			{"./Image/sprite5.jpg"},
			{"./Image/sprite3.png"}
		} ;

	window = SDL_CreateWindow("TAMAGO", 
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			W, H, 0
			) ;

	if (window == NULL) 
		SDL_ErrorCase("Trouble with window") ;

	renderer = SDL_CreateRenderer(window, -1, 0) ;

	if (renderer == NULL) 
		SDL_ErrorCase("Trouble with renderer") ;

	drawCadre(window, renderer, chambre); 	
	drawBarre(renderer, cadre[0], b) ;
	drawRoom(renderer, cadre[1], chambre) ;
	drawButton(renderer, cadre[2], button) ;
	//exit(EXIT_SUCCESS) ;
	/*
	bg_texture = load_TextureFromSurface("./Image/sprite5.jpg", renderer) ;

	while (program_on) {
		if (SDL_PollEvent(&event)) 
		{
			switch (event.type){
			case SDL_KEYDOWN :
				switch (event.key.keysym.sym) {
				case SDLK_LEFT :
					// Action aller à gauche 
					if (prec == 0 || prec == 2 || prec == 4) {
						if (prec == 0) action = 6 ;
						if (prec == 2) action = 1 ;
						if (prec == 4) action = 3 ;
					}
					else {
						action = prec - 1 ;
					}
					b = changeState(b, action, pas, prec, cible) ;
					break ;
				case SDLK_RIGHT :
					// Action aller à droite
					if (prec == 0 || prec == 2 || prec == 4) {
						if (prec == 0) action = 1 ;
						if (prec == 2) action = 3 ;
						if (prec == 4) action = 5 ;
					}
					else {
						action = prec + 1 ;
					}
					b = changeState(b, action, pas, prec, cible) ;
					break ;
				case SDLK_q :
					program_on = SDL_FALSE ;
					break ;
				default :
				break ;
				}
			case SDL_MOUSEBUTTONDOWN :
				SDL_GetMouseState(&mouseX, &mouseY) ;
				if (mouseY > button[0].y && mouseY < button[0].y+button[0].h) {
				if (mouseX > button[0].x && mouseX < button[0].x+button[0].w) {
					// le niveau de manger augmente
					action = 0 ; cible  = 0 ;
					b = changeState(b, action, pas, prec, cible) ;	
					//animerImage(window, texture, chambre[0], list[0], 
					//	renderer, pos, wd, hd, boredX, boredY, b) ;
					printf("%d %d %d\n", b.i, b.j, b.k) ;
				} 
				if (mouseX > button[1].x && mouseX < button[1].x+button[1].w) {
					// le  niveau de jouer augmente	
					action = 4 ; cible = 4 ;
					pos = 3 ;
					b = changeState(b, action, pas, prec, cible) ;	
					//animerImage(window, texture, chambre[4], list[0], 
					//	renderer, pos, wd, hd, boredX, boredY, b) ;
					printf("%d %d %d\n", b.i, b.j, b.k) ;
				} 
				if (mouseX > button[2].x && mouseX < button[2].x+button[2].w) {
					// le niveau de dormir augmente
					action = 2 ; cible = 2 ;
					pos = 5 ;
					b = changeState(b, action, pas, prec, cible) ;	
					//animerImage(window, texture, chambre[2], list[0], 
					//	renderer, pos, wd, hd, boredX, boredY, b) ;
					printf("%d %d %d\n", b.i, b.j, b.k) ;
				} 
				if (mouseX > button[3].x && mouseX < button[3].x+button[3].w) {
					// le niveau de tous les états diminues
					action = 3 ; 
					b = changeState(b, action, pas, prec, cible) ;	
					printf("%d %d %d\n", b.i, b.j, b.k) ;
				} 
				}
				prec = action ;
				break ;
			case SDL_QUIT :
				program_on = SDL_FALSE ;
				break ;
			default :
				break ;
			}
		}
	}*/
	SDL_RenderPresent(renderer) ;
	SDL_Delay(5000) ;
Quit :
	SDL_DestroyRenderer(renderer) ;	
	SDL_DestroyWindow(window) ;
	SDL_Quit() ;

	return EXIT_SUCCESS ;
}
