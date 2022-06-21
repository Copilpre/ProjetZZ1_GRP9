#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>

#define HEIGHT 601
#define WIDTH 1201


void matriceensql(int ** mat,int hauteur,SDL_Surface * ecran)
{

  SDL_Rect position ;
   
  int LC = HEIGHT/hauteur;
 
  SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format, 45,50,50) ) ;
  SDL_Surface * rectangle = NULL;
  SDL_Surface *  rectangle2 = NULL;
  int a = 0;
  if(hauteur < 51)
  {
    rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE, LC -1  ,LC - 1, 32,0,0,0,0) ;
    rectangle2 = SDL_CreateRGBSurface(SDL_HWSURFACE, LC -1 ,LC - 1, 32,0,0,0,0) ;
    a = 1;
  }
  else
  {
    rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE, LC  ,LC , 32,0,0,0,0) ;
    rectangle2 = SDL_CreateRGBSurface(SDL_HWSURFACE, LC ,LC, 32,0,0,0,0) ;
  }

  SDL_FillRect(rectangle,NULL,SDL_MapRGB(rectangle->format,0,100,0) );
  SDL_FillRect(rectangle2,NULL,SDL_MapRGB(rectangle2->format,0,0,0) );

  position.x = a;
  position.y = a;
  
  for(int i = 0; i < hauteur ;i++)
  {
    for(int j = 0 ;j < 2 *  hauteur;j++)
    {
      if(mat[i][j] == 0)
      {
        SDL_BlitSurface(rectangle2,NULL,ecran,&position);
      }
      else if(mat[i][j] == 1)
      {
	      SDL_BlitSurface(rectangle,NULL,ecran,&position);
      }
      position.x += LC;
    }
    position.x = a;
    position.y += LC;
  }
}
