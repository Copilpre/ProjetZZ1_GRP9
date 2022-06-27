#include <stdio.h>
#include <stdlib.h>


int main(){

    int Qtable[11][11][11][3];
    int i,j,k,a;
    for(i = 0; i<11; i++){
        for(j = 0; j<11; j++){
            for(k = 0; k<11; k++){
                for(a = 0; a<3; a++){
                    Qtable[i][j][k][a] = 0; 
                } 
            } 
        } 
    } 

    FILE *fichier = fopen ("Qtable.txt", "w" );
    if (fichier == NULL){
        printf("erreur lors de l'ouverture du fichier");
        }
    else{
        for(i = 0; i<11; i++){
                for(j = 0; j<11; j++){
                    for(k = 0; k<11; k++){
                        fprintf (fichier, "%d %d %d",i, j, k);
                        for(a = 0; a<3; a++){
                            fprintf (fichier, " %d", Qtable[i][j][k][a]);
                            Qtable[i][j][k][a] = 0; 
                        }
                        fprintf (fichier, "\n" );
                    } 
                } 
            } 
        } 
}
