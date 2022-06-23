#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

SDL_Color gris = {155,155,155,255};
SDL_Color grisF = {120,120,120,255};
SDL_Color noir = {0,0,0,255};

int main(){
    
    SDL_Window 
       *window_1 = NULL;

    SDL_DisplayMode current;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Error : SDL initialisation - %s\n", 
            SDL_GetError());                // l'initialisation de la SDL a échoué 
        exit(EXIT_FAILURE);
    }

    SDL_GetCurrentDisplayMode(0, &current);

    int WindowW = current.h/2;
    int WindowH = 1.3*current.h/2;

    window_1 = SDL_CreateWindow("Tama!Go!CHI!",current.w/2-current.h/4,0,WindowW,WindowH,SDL_WINDOW_RESIZABLE);

    SDL_Renderer *renderer;
    
    SDL_Rect position,source;

    char salles[3][20]={{"./image/chambre.jpg"},{"./image/cuisine.png"},{"./image/stade.jpg"}};

    
    int currentRoom = 0;
    renderer = SDL_CreateRenderer(window_1, -1, SDL_RENDERER_ACCELERATED );
    SDL_bool program_on = SDL_TRUE;
    SDL_Event event;

    

    while(program_on||SDL_PollEvent(&event)){
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_LEFT:
                            currentRoom = (currentRoom-1+3)%3;
                            break;
                        case SDLK_RIGHT:
                            currentRoom = (currentRoom+1+3)%3;
                    }
                    break;
                case SDL_QUIT:
                    program_on = SDL_FALSE;
                    break;

                default:
                    break;
            }
        }
        //fond
        SDL_Texture * texture = IMG_LoadTexture(renderer,salles[currentRoom]);
        SDL_QueryTexture(texture,NULL,NULL,NULL,&source.h);
        source.x = 0;
        source.y= source.h/4;
        source.w=source.h;

        position.x = 0;
        position.y = 0;
        position.w = WindowW;
        position.h = WindowH;
        SDL_RenderCopy(renderer, texture, &source, &position);

        //tamagotchi
        texture = IMG_LoadTexture(renderer,"tama.png");

        SDL_QueryTexture(texture,NULL,NULL,NULL,&source.h);
        source.x = 0;
        source.y= 0;
        source.w=source.h;

        position.x = 0;
        position.y = 0;
        position.w = WindowW/2;
        position.h = WindowH/2;
        SDL_RenderCopy(renderer, texture, &source, &position);


        //barre du bas
        SDL_SetRenderDrawColor(renderer,gris.r,gris.g,gris.b,gris.a);
        position.x = 0;
        position.y = WindowH*0.7;
        position.h = WindowH*0.3;
        position.w = WindowW;
        SDL_RenderFillRect(renderer,&position);

        //boutons
        SDL_SetRenderDrawColor(renderer,grisF.r,grisF.g,grisF.b,grisF.a);
        position.y = WindowH*0.75;
        position.h = WindowH*0.2;
        position.w = WindowH*0.2;
        for (int i = 0; i < 3;i++){
            position.x= i * 100+50*(i+1);
            SDL_RenderFillRect(renderer,&position);
            }

        


        SDL_RenderPresent(renderer);
        SDL_Delay(50);
        
    }
    
    return 0;
}
