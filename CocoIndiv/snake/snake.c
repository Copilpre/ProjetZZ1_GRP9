#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>

#define MAX 255




void draw(SDL_Renderer *renderer)
{
  SDL_Rect rectangle;                                                             



  SDL_SetRenderDrawColor(renderer,rand() % MAX, rand() % MAX, rand() % MAX, 255);                                      
  
  
  
  rectangle.x = rand() % 500;                                                  
  rectangle.y = rand() % 500;                                                 
  rectangle.w = rand() % 100;                                                
  rectangle.h = rand() % 100;                                                

  SDL_RenderFillRect(renderer, &rectangle);                            
}





int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;



    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    int statut = EXIT_FAILURE;
    SDL_Color noir = {0, 0, 0, 255};
    
    /* Initialisation, création de la fenêtre et du renderer. */
    if(0 != SDL_Init(SDL_INIT_VIDEO))
    {
        fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());
        goto Quit;
    }
    window = SDL_CreateWindow("SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              500, 500, SDL_WINDOW_SHOWN);
    if(NULL == window)
    {
        fprintf(stderr, "Erreur SDL_CreateWindow : %s", SDL_GetError());
        goto Quit;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(NULL == renderer)
    {
        fprintf(stderr, "Erreur SDL_CreateRenderer : %s", SDL_GetError());
        goto Quit;
    }
    
    /* C’est à partir de maintenant que ça se passe. */
    if(0 != SDL_SetRenderDrawColor(renderer, noir.r, noir.g, noir.b, noir.a))
    {
        fprintf(stderr, "Erreur SDL_SetRenderDrawColor : %s", SDL_GetError());
        goto Quit;
    }
    
    if(0 != SDL_RenderClear(renderer))
    {
        fprintf(stderr, "Erreur SDL_SetRenderDrawColor : %s", SDL_GetError());
        goto Quit;
    }
    

        
    
    SDL_RenderPresent(renderer);
    SDL_Delay(1000);

    
    
    for(int i=0;i<100;i++)
    {   
      
      
      draw(renderer);
      SDL_RenderPresent(renderer);
      SDL_Delay(100);
    }











    statut = EXIT_SUCCESS;

Quit:
    if(NULL != renderer)
        SDL_DestroyRenderer(renderer);
    if(NULL != window)
        SDL_DestroyWindow(window);
    SDL_Quit();
    return statut;
}