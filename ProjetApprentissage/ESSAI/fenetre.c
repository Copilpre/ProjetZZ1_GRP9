#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <time.h>

#define W 800
#define H 800
#define NB_CHAMBRE 7
#define MARGIN 5
#define NB_IMG 7
#define NB_ITER 200
#define NB_BUTTON 4


typedef struct barLevel {
	int i ; // manger
	int j ; // jouer 
	int k ; // dormir
} barLevel_t ;


void SDL_ErrorCase(char * msg) {
	SDL_Log("%s %s\n", SDL_GetError()) ;
	exit(EXIT_FAILURE) ;
}


/*void drawButtonCadre() ;
void drawChambreCadre() ;
void drawBarreCadre() ;*/


void drawCadre(SDL_Window * window, SDL_Renderer * renderer, 
				SDL_Rect chambre[NB_CHAMBRE], SDL_Rect button[NB_BUTTON], barLevel_t b) 
{
	SDL_Rect window_dim = {0} ;
	SDL_Rect cadre[3] ;
	SDL_Rect barre[3] ;
	SDL_Rect niveau[3] ;

	SDL_GetWindowSize(window, &window_dim.w, &window_dim.h) ;

	SDL_SetRenderDrawColor(renderer, 118, 107, 107, 255) ;
	SDL_RenderFillRect(renderer, &window_dim) ;
	
	// EMPLACEMENT DES BARRES DE NIVEAU
	cadre[0].x = MARGIN * 2;
	cadre[0].y = MARGIN * 2;
	cadre[0].w = (int)(window_dim.w / 5) - 2*MARGIN ;
	cadre[0].h = ((window_dim.h)-((int)(window_dim.h / 5))) - 4*MARGIN;
	
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0) ;
	SDL_RenderFillRect(renderer, &cadre[0]) ;

	// DESSIN DES BARRES 
	int bH = cadre[0].h * (2/3) ; 
	int bW = cadre[0].w * (1/5) ;
	int w_space = (cadre[0].w * (2/5))*(1/4) ;
	int h_space = (cadre[0].h * (1/3))*(1/2) ;

	barre[0].x = 2*MARGIN + w_space ;
	barre[0].y = 2*MARGIN + h_space ;
	barre[0].w = bH ;
	barre[0].h = bW ;
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0) ;
	SDL_RenderFillRect(renderer, &barre[0]) ;
	
	barre[1].x = barre[0].x + bW + w_space ;
	barre[1].y = 2*MARGIN + h_space ;
	barre[1].w = bH ;
	barre[1].h = bW ;
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0) ;
	SDL_RenderFillRect(renderer, &barre[1]) ;
	
	barre[2].x = barre[1].x + bW + w_space ;
	barre[2].y = 2*MARGIN + h_space ;
	barre[2].w = bH ;
	barre[2].h = bW ;
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0) ;
	SDL_RenderFillRect(renderer, &barre[2]) ;

	// NIVEAU DES BARRES 
	
	for (int i=0; i<3; i++) niveau[i] = barre[i] ;

	niveau[0].h = bH * ( b.i / 10 ) ;
	niveau[1].h = bH * ( b.j / 10 ) ;
	niveau[2].h = bH * ( b.k / 10 ) ;

	niveau[0].y = 2*MARGIN + h_space + (bH - niveau[0].h) ;
	niveau[1].y = 2*MARGIN + h_space + (bH - niveau[1].h) ;
	niveau[2].y = 2*MARGIN + h_space + (bH - niveau[2].h) ;

	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255) ;
	SDL_RenderFillRect(renderer, &niveau[0]) ;
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255) ;
	SDL_RenderFillRect(renderer, &niveau[1]) ;
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255) ;
	SDL_RenderFillRect(renderer, &niveau[2]) ;

	
	// EMPLACEMENT DES CHAMBRES

	cadre[1].x = (cadre[0].w+6*MARGIN) ;
	cadre[1].y = 2*MARGIN ;
	cadre[1].w = (int)(window_dim.w - cadre[1].x) - 2*MARGIN ;
	cadre[1].h = cadre[0].h ;

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255) ;
	SDL_RenderFillRect(renderer, &cadre[1]) ;

	// EMPLACEMENT DES OPTIONS DE JEU

	cadre[2].x = MARGIN * 2; 
	cadre[2].y = cadre[0].h + 4*MARGIN;
	cadre[2].w = window_dim.w - 4*MARGIN;
	cadre[2].h = (window_dim.h-(cadre[1].h + 4*MARGIN)-2*MARGIN) ;

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255) ;
	SDL_RenderFillRect(renderer, &cadre[2]) ;

	// IMAGE POUR LES CADRES
	int ch_H = (cadre[1].h / 3) ;
	int ch_W = (cadre[1].w / 3) ;

	chambre[0].x = cadre[1].x + 2*MARGIN ;
	chambre[0].y = cadre[1].y + 2*MARGIN ;
	chambre[0].w = ch_W;
	chambre[0].h = ch_H;
	SDL_SetRenderDrawColor(renderer, 177, 190, 167, 255) ;
	SDL_RenderFillRect(renderer, &chambre[0]) ;
		
	chambre[1].x = cadre[1].x + ch_W ;
	chambre[1].y = chambre[0].y + (ch_H/3) ;
	chambre[1].w = ch_W - 4*MARGIN;
	chambre[1].h = ch_H/3;
	SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255) ;
	SDL_RenderFillRect(renderer, &chambre[1]) ;

	chambre[2].x = chambre[1].x + chambre[1].w;
	chambre[2].y = chambre[0].y ;
	chambre[2].w = ch_W;
	chambre[2].h = ch_H;
	SDL_SetRenderDrawColor(renderer, 177, 190, 167, 255) ;
	SDL_RenderFillRect(renderer, &chambre[2]) ;

	chambre[3].x = chambre[2].x + chambre[2].w/3;
	chambre[3].y = chambre[2].y + chambre[2].h;
	chambre[3].w = ch_W/3 ;
	chambre[3].h = ch_H - 4*MARGIN;
	SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255) ;
	SDL_RenderFillRect(renderer, &chambre[3]) ;
		
	chambre[4].x = chambre[2].x;
	chambre[4].y = chambre[3].y + chambre[3].h;
	chambre[4].w = ch_W;
	chambre[4].h = ch_H;
	SDL_SetRenderDrawColor(renderer, 177, 190, 167, 255) ;
	SDL_RenderFillRect(renderer, &chambre[4]) ;

	chambre[5].x = chambre[0].x + ch_W/3;
	chambre[5].y = chambre[4].y + ch_H/3;
	chambre[5].w = ch_W*2 - 4*MARGIN -ch_W/3;
	chambre[5].h = ch_H/3;
	SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255) ;
	SDL_RenderFillRect(renderer, &chambre[5]) ;

	chambre[6].x = chambre[0].x + ch_H/3;
	chambre[6].y = chambre[3].y;
	chambre[6].w = ch_W/3;
	chambre[6].h = ch_H*2 - 4*MARGIN - ch_H/3;
	SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255) ;
	SDL_RenderFillRect(renderer, &chambre[6]) ;

	// DESSIN DES BUTTONS 

	int width = ((cadre[2].w) - 4*(4*MARGIN)) / 4 ;
	int heigth = (int)((cadre[2].h) - 4*MARGIN) ;

	button[0].x = 6*MARGIN ;
	button[0].y = (int)(cadre[0].h + 6*MARGIN) ;
	button[0].w = width ;
	button[0].h = heigth ;

	SDL_SetRenderDrawColor(renderer, 100, 100, 10, 255) ;
	SDL_RenderFillRect(renderer, &button[0]) ;

	button[1].x = (button[0].x + width) + 2*MARGIN ;
	button[1].y = button[0].y ;
	button[1].w = width ;
	button[1].h = heigth ;

	SDL_SetRenderDrawColor(renderer, 100, 100, 10, 255) ;
	SDL_RenderFillRect(renderer, &button[1]) ;

	button[2].x = (button[1].x + width) + 2*MARGIN;
	button[2].y = button[0].y ;
	button[2].w = width ;
	button[2].h = heigth ;

	SDL_SetRenderDrawColor(renderer, 100, 100, 10, 255) ;
	SDL_RenderFillRect(renderer, &button[2]) ;

	button[3].x = (button[2].x + width) + 2*MARGIN;
	button[3].y = button[0].y ;
	button[3].w = width ;
	button[3].h = heigth ;

	SDL_SetRenderDrawColor(renderer, 100, 100, 10, 255) ;
	SDL_RenderFillRect(renderer, &button[3]) ;
	SDL_RenderPresent(renderer) ;
	SDL_Delay(30) ;
}

SDL_Texture * load_TextureFromSurface(char * image, SDL_Renderer * renderer) {

	SDL_Surface * surface = IMG_Load(image) ;
	SDL_Texture * texture ;
	
	if ( surface == NULL ) 	
		SDL_ErrorCase("Trouble with load image") ;

	texture = SDL_CreateTextureFromSurface(renderer, surface) ;

	SDL_FreeSurface(surface) ;
	
	if (texture == NULL)
		SDL_ErrorCase("Trouble with texture") ;

	return texture ;
}


void animerImage(SDL_Window * window, SDL_Texture * texture, SDL_Rect rect, char * img, 
			SDL_Renderer * renderer, int pos, int wd, int hd, int boredX, int boredY, barLevel_t b) 
{
	SDL_Rect src = {0} ,
		 dst = {0} ,
		 state = {0}, 
		 chambre[NB_CHAMBRE], 
		 button[NB_BUTTON] 
	;
	
	texture = load_TextureFromSurface(img, renderer) ;
	
	SDL_QueryTexture(texture, NULL, NULL, &src.w, &src.h) ;
	
	dst = rect ;

	float zoom = 1 ; 
	
	int pas_x = src.w / wd ;
	int pas_y = src.h / hd ;
	int pasW  = rect.w / wd ;
	int pasH  = rect.h / hd ;
	//dst.w = pas_x ;
	//dst.h = pas_y * zoom ;
	state.x = rect.x  + boredX;
	state.y = pos*pasH + rect.y + boredY;
	state.w = pas_x * zoom - boredX;
	state.h = pas_y * zoom - boredY;

	int i, nb_iter=200 ,
	    limit_x = rect.x + rect.w ;

	for (i=0; i<nb_iter; i++) {
		//dst.x += pas_x ;
		//if (dst.x > limit_x) dst.x = rect.x ;
		state.x += pas_x ;
		if (state.x > limit_x) state.x = rect.x ;
		SDL_RenderClear(renderer) ;
		//SDL_SetTextureAlphaMod(texture, (1.0-1.0*i/nb_iter)*255) ;
		//drawCadre() ;
		drawCadre(window, renderer, chambre, button, b); 	
		SDL_RenderCopy(renderer, texture, &state, &dst) ;
		SDL_RenderPresent(renderer) ;
		SDL_Delay(30) ;
	}	

}


void changeState(barLevel_t barre, int action, int pas, int prec) {
	srand(time(NULL)) ;
	if (action == 0) { // manger
		barre.i += pas ;
		if (rand() % 2 == 0) {
			barre.j -= pas ;
		} else {
			barre.k -= pas ;
		}	
	}
	if (action == 1 || action == 3 || action == 5 || action == 6) { // deplace gauche <-> droite
		if (prec == 0) {
			barre.i += pas ;
		} else {		
			barre.j -= pas ;		
			barre.k -= pas ;
		}		
		if (prec == 2) {
			barre.j += pas ;
		} else {		
			barre.i -= pas ;		
			barre.k -= pas ;
		}		
		if (prec == 4) {
			barre.k += pas ;
		} else {		
			barre.i -= pas ;		
			barre.j -= pas ;
		}		
		if (prec != 0 && prec != 2 && prec != 4) {
			barre.i -= pas ;		
			barre.j -= pas ;
			barre.k -= pas ;
		}
	}
	if (action == 2) { // dormir
		barre.j += pas ;
		if (rand() % 2 == 0) {
			barre.i -= pas ;
		} else {
			barre.k -= pas ;
		}	
	}
	if (action == 4) { // jouer
		barre.k += pas ;
		if (rand() % 2 == 0) {
			barre.j -= pas ;
		} else {
			barre.i -= pas ;
		}	
	}
}

int main() {
	srand(time(NULL)) ;
	SDL_Window * window = NULL ;
	SDL_Renderer * renderer = NULL ;
	SDL_Texture * texture = NULL ;
	SDL_Texture * bg_texture = NULL ;
	SDL_Rect chambre[NB_CHAMBRE] ;
	SDL_Rect button[NB_BUTTON] ;
	SDL_Event event ;
	SDL_bool program_on = SDL_TRUE ;
	SDL_bool pause = SDL_FALSE ;
	int pos = 0, wd = 8, hd = 10 , boredX=10, boredY=10; 
	int mouseX, mouseY, pas=1, action, prec ;

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

	drawCadre(window, renderer, chambre, button, b); 	
	SDL_Delay(5000) ;
	exit(EXIT_SUCCESS) ;

	bg_texture = load_TextureFromSurface("./Image/sprite5.jpg", renderer) ;

	while (program_on) {
		if (SDL_PollEvent(&event)) 
		{
			switch (event.type){
			case SDL_KEYDOWN :
				switch (event.key.keysym.sym) {
				case SDLK_LEFT :
					// Action aller à gauche 
			
					break ;
				case SDLK_RIGHT :
					// Action aller à droite

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
					action = 0 ;
					changeState(b, action, pas, prec) ;	
					animerImage(window, texture, chambre[0], list[0], 
						renderer, pos, wd, hd, boredX, boredY, b) ;
				} 
				if (mouseX > button[1].x && mouseX < button[1].x+button[1].w) {
					// le  niveau de jouer augmente	
					action = 4 ;
					pos = 3 ;
					changeState(b, action, pas, prec) ;	
					animerImage(window, texture, chambre[4], list[0], 
						renderer, pos, wd, hd, boredX, boredY, b) ;
				} 
				if (mouseX > button[2].x && mouseX < button[2].x+button[2].w) {
					// le niveau de dormir augmente
					action = 2 ;
					pos = 5 ;
					changeState(b, action, pas, prec) ;	
					animerImage(window, texture, chambre[2], list[0], 
						renderer, pos, wd, hd, boredX, boredY, b) ;
				} 
				if (mouseX > button[3].x && mouseX < button[3].x+button[3].w) {
					// le niveau de tous les états diminues
					action = 3 ;
					changeState(b, action, pas, prec) ;	
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
	}
	SDL_RenderPresent(renderer) ;
	SDL_Delay(5000) ;
Quit :
	SDL_DestroyRenderer(renderer) ;	
	SDL_DestroyWindow(window) ;
	SDL_Quit() ;

	return EXIT_SUCCESS ;
}

/*
void movePingouin(SDL_Renderer * renderer, SDL_Rect rect[NB_CHAMBRE], 
				char image[6][30], int num_chr, int choix, int pos, int wd, int hd, int bX, int bY)
{
	SDL_Texture * texture = NULL;
	int i , w, h , nb_img=16;
	SDL_Rect src = {0} ;

	if (choix == 1) // Aller à droite
	{ 
		switch ( num_chr ) {
		case 0 | 1 :
			src = rect[1] ;		
			texture = load_TextureFromSurface(image[0], renderer) ;
			animerImage(texture, src, image[0], renderer, pos, wd, hd, bX, bY) ;
			break; 
		case 2 | 3 :
			src = rect[3] ;		
			texture = load_TextureFromSurface(image[1], renderer) ;
			animerImage(texture, src, image[1], renderer, pos, wd, hd, bX, bY) ;
			break;
		case 4 | 5 :
			src = rect[5] ;		
			texture = load_TextureFromSurface(image[2], renderer) ;
			animerImage(texture, src, image[2], renderer, pos, wd, hd, bX, bY) ;
			break;
		case 6:
			src = rect[6] ;		
			texture = load_TextureFromSurface(image[3], renderer) ;
			animerImage(texture, src, image[3], renderer, pos, wd, hd, bX, bY) ;
			break;
		default:
			break;
		}		
	}
	else // Aller à gauche
	{ 
		switch ( num_chr ) {
		case 0 | 1 :
			src = rect[1] ;		
			texture = load_TextureFromSurface(image[0], renderer) ;
			animerImage(texture, src, image[0], renderer, pos, wd, hd, bX, bY) ;
			break; 
		case 2 | 3 :
			src = rect[3] ;		
			texture = load_TextureFromSurface(image[1], renderer) ;
			animerImage(texture, src, image[1], renderer, pos, wd, hd, bX, bY) ;
			break;
		case 4 | 5 :
			src = rect[5] ;		
			texture = load_TextureFromSurface(image[2], renderer) ;
			animerImage(texture, src, image[2], renderer, pos, wd, hd, bX, bY) ;
			break;
		case 6:
			src = rect[6] ;		
			texture = load_TextureFromSurface(image[3], renderer) ;
			animerImage(texture, src, image[3], renderer, pos, wd, hd, bX, bY) ;
			break;
		default:
			break;
		}		
	}
}*/
