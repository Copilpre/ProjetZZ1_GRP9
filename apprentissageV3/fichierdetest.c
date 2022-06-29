#include <time.h>
#include <stdio.h>
#include <stdlib.h>



    // variable pour faire fonctionner l'IA
    int Qmax;
    int ActionMax;

 float barreD = (rand()%9);
    barreD = barreD/10+0.2;
    float barreM = (rand()%9);
    barreM = barreM/10+0.2;
    float barreJ = (rand()%9);
    barreJ = barreJ/10+0.2;
    /*Qmax = Qtable[(int)barreM*10][(int)barreD*10][(int)barreJ*10][0];
        ActionMax = 0;
        for(a = 1; a < 3 ; a++){
            if (Qtable[(int)barreM*10][(int)barreD*10][(int)barreJ*10][a] > Qmax){
                Qmax = Qtable[(int)barreM*10][(int)barreD*10][(int)barreJ*10][a];
                ActionMax = a;
            } 
        } */

           FILE * fichier = fopen("Qtable.txt","r");      //chargement d'un fichier
    float Qtable[11][11][11][3];
    
    for(i = 0; i < 11; i++){
        for (j = 0; j < 11 ; j++){
            for (k = 0; k < 11 ; k++){
  
                    fscanf(fichier,"%*d %*d %*d %*d %f %f %f", &Qtable[i][j][k][0],&Qtable[i][j][k][1],&Qtable[i][j][k][2]);
                 
            }
        } 
    }

