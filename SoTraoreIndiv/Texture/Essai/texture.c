#include "texture.h"

void SDL_ErrorCase(char * msg) {
	SDL_Log("%s %s\n", msg, SDL_GetError()) ;
	exit(EXIT_FAILURE) ;
}


SDL_Texture * loadTextureFromImage(char * img, SDL_Renderer * renderer) 
{
	SDL_Texture * texture ;
	SDL_Surface * surface ;

	surface = IMG_Load(img) ;

	if (NULL == surface) 
		SDL_ErrorCase("Trouble with load image") ;

	texture = SDL_CreateTextureFromSurface(renderer, surface) ;
	SDL_FreeSurface(surface) ;

	if (NULL == texture) 
		SDL_ErrorCase("Trouble with texture") ;

	return texture ;
}

// IMG_Quit(); dans le main à ne pas oublier

// Affichager d'une texture sur la totalité de la fénètre

void play_with_texture_1(SDL_Texture * texture, SDL_Window * window, 
					SDL_Renderer * renderer) 
{
	SDL_Rect source = {0},
		 window_dimensions = {0},
		 destination = {0} ;

	SDL_GetWindowSize(window, &window_dimensions.w,
				&window_dimensions.h
			) ;

	SDL_QueryTexture(texture, NULL, NULL,
				&source.w, &source.h
			) ;

	destination = window_dimensions ;
	SDL_RenderPresent(renderer) ;
	SDL_Delay(2000) ;

	SDL_RenderClear(renderer) ;
}


// Affichage d'une partie d'une texture à un endroit choisi

void play_with_texture_2(SDL_Texture * texture, SDL_Window * window,
					SDL_Renderer * renderer) 
{
	SDL_Rect source = {0},
		 window_dimensions = {0},
		 destination = {0} ;

	SDL_GetWindowSize(window, &window_dimensions.w,
				&window_dimensions.h
			) ;

	SDL_QueryTexture(texture, NULL, NULL,
				&source.w, &source.h
			) ;

	float zoom = 1.5 ;
	
	destination.w = source.w * zoom ;
	destination.h = source.h * zoom ;
	destination.x = 
		(window_dimensions.w - destination.w)/2 ;
	destination.y = 
		(window_dimensions.h - destination.h)/2 ;

	SDL_RenderCopy(renderer, texture, &source, &destination) ;

	SDL_RenderPresent(renderer) ;
	SDL_Delay(1000) ;

	SDL_RenderClear(renderer) ;
}


// Créer une premiere animation

void play_with_texture_3(SDL_Texture * texture, SDL_Window * window,
				SDL_Renderer * renderer) {
	
	SDL_Rect source = {0},
		 window_dimensions = {0},
		 destination = {0} 
	;

	SDL_GetWindowSize(window, &window_dimensions.w,
				&window_dimensions.h
			) ;

	SDL_QueryTexture(texture, NULL, NULL,
				&source.w, &source.h
			) ;

	float zoom = 1.5 ;
	
	destination.w = source.w * zoom ;
	destination.h = source.h * zoom ;
	destination.x = 
		(window_dimensions.w - destination.w)/2 ;
	destination.y = 
		(window_dimensions.h - destination.h)/2 ;

	float h = window_dimensions.h - destination.h ;

	int i , nb_it = 200 ;

	for (i=0; i < nb_it; ++i) {
		destination.y = h * (1 - exp(-5.0*i/nb_it) / 2 *
				(1 + cos(10.0*i/nb_it*2*M_PI))) ;
		SDL_RenderClear(renderer) ;
		SDL_SetTextureAlphaMod(texture, (1.0-1.0*i/nb_it)*255) ;
		SDL_RenderCopy(renderer, texture, &source, &destination) ;
		SDL_RenderPresent(renderer) ;
		SDL_Delay(30) ;
	}

	SDL_RenderClear(renderer) ;
}

// Si on veut animer un sprite 


void play_with_texture_4(SDL_Texture *texture, SDL_Window * window,
				SDL_Renderer * renderer) 
{
	SDL_Rect source = {0},
		 window_dimensions = {0},
		 destination = {0},
		 state = {0} 
       	;

	SDL_GetWindowSize(window, &window_dimensions.w,
				&window_dimensions.h
			) ;

	SDL_QueryTexture(texture, NULL, NULL,
				&source.w, &source.h
			) ;
	
	int nb_images = 0 ;
	float zoom = 2 ;
	int offset_x = source.w / nb_images,
	    offset_y = source.h / 4 ;

	state.x = 0 ;
	state.y = 3 * offset_y ;
	state.w = offset_x ;
	state.h = offset_y ;

	destination.w = offset_x * zoom ;
	destination.h = offset_y * zoom ;

	destination.y =
		(window_dimensions.h - destination.h)/2 ;
	
	int speed = 9 , x;
	for (x=0 ; x < window_dimensions.w-destination.w; x += speed)
	{
		destination.x = x ;
		state.x += offset_x ;
		state.x %= source.w ;

		SDL_RenderClear(renderer) ;
		SDL_RenderCopy(renderer,  texture, &state, &destination) ;
		SDL_RenderPresent(renderer) ;
		SDL_Delay(80) ;
	}

	SDL_RenderClear(renderer) ;
}

// Et le fond ?

void play_with_texture_5(SDL_Texture *bg_texture, SDL_Texture * texture, 
				SDL_Window * window, SDL_Renderer * renderer) 
{
	SDL_Rect source = {0},
		 window_dimensions = {0},
		 destination = {0}
       	;

	SDL_GetWindowSize(window, &window_dimensions.w,
				&window_dimensions.h
			) ;

	SDL_QueryTexture(texture, NULL, NULL,
				&source.w, &source.h
			) ;
	
	int nb_images = 40 ;
	int nb_images_animations = 1 * nb_images ;
	float zoom = 2 ;
	int offset_x = source.w / 4 ,
	    offset_y = source.h / 5 ;
	
	SDL_Rect state[40] ;
	
	int i = 0, y , cpt, x ;
	for (y=0; y<source.h; y+=offset_y) {
		for (x=0; x<source.w; x+=offset_x) {
			state[i].x = x ;
			state[i].y = y ;
			state[i].w = offset_x ;
			state[i].h = offset_y ;
			++i ;
		}
	}

	state[15] = state[14] = state[13] ;

	for (; i<nb_images; ++i) {
		state[i] = state[39-i] ;
	}

	destination.w = offset_x * zoom ;
	destination.h = offset_y * zoom ;
	destination.x = window_dimensions.w * 0.75 ;
	destination.y = window_dimensions.h * 0.7 ;
	
	i = 0 ;
	for (cpt=0; cpt < nb_images_animations; ++cpt) {
		play_with_texture_1(bg_texture, window, renderer) ;
		SDL_RenderCopy(renderer, texture, &state[i], &destination) ;
		i = (i + 1) % nb_images ;
		SDL_RenderPresent(renderer) ;
		SDL_Delay(100) ;
	}

	SDL_RenderClear(renderer) ;
}
