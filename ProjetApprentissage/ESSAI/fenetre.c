#include "fenetre.h"

void SDL_ErrorCase(char * msg) {
	SDL_Log("%s %s\n", SDL_GetError()) ;
	exit(EXIT_FAILURE) ;
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


void drawCadre(SDL_Window * window, SDL_Renderer * renderer, SDL_Rect cadre[3]) {

	SDL_Rect window_dim = {0} ;
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
}

void drawBarre(SDL_Renderer * renderer, SDL_Rect src, barLevel_t b) {

	SDL_Rect barre[3],
		 niveau[3] 
	; 

	// DESSIN DES BARRES 
	int bH = src.h * (2/3) ; 
	int bW = src.w * (1/5) ;
	int w_space = (src.w * (2/5))*(1/4) ;
	int h_space = (src.h * (1/3))*(1/2) ;

	barre[0].x = 2*MARGIN + w_space ;
	barre[0].y = 2*MARGIN + h_space ;
	barre[0].w = bH ;
	barre[0].h = bW ;
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 150) ;
	SDL_RenderFillRect(renderer, &barre[0]) ;
	
	barre[1].x = barre[0].x + bW + w_space ;
	barre[1].y = 2*MARGIN + h_space ;
	barre[1].w = bH ;
	barre[1].h = bW ;
	SDL_RenderFillRect(renderer, &barre[1]) ;
	
	barre[2].x = barre[1].x + bW + w_space ;
	barre[2].y = 2*MARGIN + h_space ;
	barre[2].w = bH ;
	barre[2].h = bW ;
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
}


void drawButton(SDL_Renderer * renderer, SDL_Rect src, SDL_Rect button[4]) {

	// DESSIN DES BUTTONS 

	int width  = (src.w - 4*(4*MARGIN)) / 4 ;
	int heigth = src.h - 4*MARGIN ;

	button[0].x = 6*MARGIN ;
	button[0].y = (int)(src.h + 6*MARGIN) ;
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
}


void drawRoom(SDL_Renderer * renderer, SDL_Rect src, SDL_Rect chambre[NB_CHAMBRE]) {

	int ch_H = (src.h / 3) ;
	int ch_W = (src.w / 3) ;

	chambre[0].x = src.x + 2*MARGIN ;
	chambre[0].y = src.y + 2*MARGIN ;
	chambre[0].w = ch_W;
	chambre[0].h = ch_H;
	SDL_SetRenderDrawColor(renderer, 177, 190, 167, 255) ;
	SDL_RenderFillRect(renderer, &chambre[0]) ;
		
	chambre[1].x = src.x + ch_W ;
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
		//drawCadre(window, renderer, chambre, button); 	
		SDL_RenderCopy(renderer, texture, &state, &dst) ;
		SDL_RenderPresent(renderer) ;
		SDL_Delay(30) ;
	}	

}


barLevel_t changeState(barLevel_t barre, int action, int pas, int prec, int cible) {
	srand(time(NULL)) ;
	if (prec == action ) {
		if (cible == 0 && action == 0) { // manger
			barre.i += pas ;
			if (rand() % 2 == 0) {
				barre.j -= pas ;
			} else {
				barre.k -= pas ;
			}	
		}
		if (action == 2 && cible == 2) { // dormir
			barre.j += pas ;
			if (rand() % 2 == 0) {
				barre.i -= pas ;
			} else {
				barre.k -= pas ;
			}	
		}
		if (action == 4 && cible == 4) { // jouer
			barre.k += pas ;
			if (rand() % 2 == 0) {
				barre.j -= pas ;
			} else {
				barre.i -= pas ;
			}	
		}
	} else {  // Aller gauche <-> droite
		if (action == 1 || action == 3 || action == 5 || action == 6) { 
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
	}

	if (barre.i < 0) barre.i = 0 ;
	if (barre.i > 10) barre.i = 10 ;
	if (barre.j < 0) barre.j = 0 ;
	if (barre.j > 10) barre.j = 10 ;
	if (barre.k < 0) barre.k = 0 ;
	if (barre.k > 10) barre.k = 10 ;
	
	return barre ;
}
