#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <time.h>
#include "matriceensql.h"
#include "jeudelavie.h"
#include "figuresjeudelavie.h"


#define HEIGHT 601
#define WIDTH 1201









int main(){
 
  int n;
  printf("Quelle hauteur(1/2 * largeur) votre jeu aura t'il(max 600)\n");
  scanf("%d",&n);

  
  int ** mat = malloc(sizeof(int*)*n);
  for(int i = 0 ; i < n ; i++){
    mat[i] = malloc(sizeof(int) * 2 * n);
  }


  


  
  float vitesse;
  printf("Combien de secondes entre deux iterations(nombre reel) :\n");
  scanf("%f",&vitesse);



    int choix;
    printf("Quel configuration voulez-vous :\n  1 - Une configuration aleatoire\n  2 - Une petite floraison\n  3 - Des petis oscillateurs\n  4 - L'oscillateur Pulsar\n");
    scanf("%d",&choix);


    switch(choix){
    case 1:
      aleatoire(mat,n);
      break;
    case 2:
      petitefloraison(mat,n);
      break;
    case 3:
      petitsoscillateurs(mat,n);
      break;
    case 4:
      pulsar(mat,n);
      break;
    
  }

    int choixautomate;
    printf("Quel automate voulez vous : \n 1-Jeu de la vie\n 2-Automate d'Ulman\n 3-Automate de parite\n");
    scanf("%d",&choixautomate);

    int iterations = 0;
    int cont = 1;
    int constante;
    SDL_Event event ;
      
    clock_t t1,t2;

       SDL_Surface * ecran = NULL ;//Le fond
      if(SDL_Init(SDL_INIT_VIDEO) !=0){
    fprintf(stderr,"\nUnable to initialize SDL:  %s\n", SDL_GetError()  );
    exit(EXIT_FAILURE) ;
  }
  if((ecran = SDL_SetVideoMode(WIDTH,HEIGHT,32, SDL_HWSURFACE))==NULL){
    fprintf(stderr,"Erreur VideoMode %s\n",SDL_GetError());
    exit(EXIT_FAILURE) ;
  }


    
    matriceensql(mat,n,ecran);

    

    
    switch(choixautomate){//1
  case 1:
    
    while(cont){//2
      t1 = clock();
      t2 = clock();
      while(((t2 - t1) * 1000)/CLOCKS_PER_SEC < 1000 * vitesse + 1){//3
	constante = 1;
	t2 = clock();
	while(SDL_PollEvent(&event)){//4
	  if(event.type == SDL_KEYDOWN){//5
	    if(event.key.keysym.sym == 'q'){//6
	      cont = 0;}//5
	    else if( event.key.keysym.sym == SDLK_SPACE){//6
	 
	      while(constante){//7
	 
		while(SDL_PollEvent(&event)){//8
		  if(event.type == SDL_KEYDOWN){//9
		    if(event.key.keysym.sym == 'q'){//10
		      cont = 0;}//9
		    else if( event.key.keysym.sym == SDLK_SPACE){//10
		      constante = 0;}//9
	   
		  }}}//6
	      break;
	
            
       
	    }}}}//2
    
      matriceensql(mat,n,ecran);
      SDL_Flip(ecran);
      iterations += 1;
      jeudelavie(mat,n);
    }//1
      break;
    case 2:
      while(cont){
      t1 = clock();
      t2 = clock();
      while(((t2 - t1) * 1000)/CLOCKS_PER_SEC < 1000 * vitesse + 1){
	constante = 1;
	t2 = clock();
	while(SDL_PollEvent(&event)){
	  if(event.type == SDL_KEYDOWN){
	    if(event.key.keysym.sym == 'q'){
	      cont = 0;}
	    else if( event.key.keysym.sym == SDLK_SPACE){
	 
	      while(constante){
	 
		while(SDL_PollEvent(&event)){
	     if(event.type == SDL_KEYDOWN){
	       if(event.key.keysym.sym == 'q'){
		 cont = 0;}
	       else if( event.key.keysym.sym == SDLK_SPACE){
		 constante = 0;}
	   
	     }}}
	      break;
	

	
      
       
       
	    }}}}
    
      matriceensql(mat,n,ecran);
      SDL_Flip(ecran);
      iterations += 1;
      ulman(mat,n);
      }
      break;
    case 3:
            
      while(cont){
	t1 = clock();
	t2 = clock();
	while(((t2 - t1) * 1000)/CLOCKS_PER_SEC < 1000 * vitesse + 1){
	  constante = 1;
	  t2 = clock();
	  while(SDL_PollEvent(&event)){
	    if(event.type == SDL_KEYDOWN){
	      if(event.key.keysym.sym == 'q'){
		cont = 0;}
	      else if( event.key.keysym.sym == SDLK_SPACE){
	 
		while(constante){
	 
		  while(SDL_PollEvent(&event)){
		  if(event.type == SDL_KEYDOWN){
		    if(event.key.keysym.sym == 'q'){
		      cont = 0;}
		    else if( event.key.keysym.sym == SDLK_SPACE){
		      constante = 0;}
	   
		  }}}
	   
	

	
      
       
       
	    }}}}
    
      matriceensql(mat,n,ecran);
      SDL_Flip(ecran);
      iterations += 1;
      parite(mat,n,iterations);
     
    
       
     
      
      }
      break;

      }//truc du switch automate


  for(int i = 0 ; i <  n ; i++){
    free(mat[i]);
    
  }
  free(mat);
  SDL_Quit();
  return 0;
}
