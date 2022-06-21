#include <stdio.h>
#include <stdlib.h>
 
 
int compteVoisin(int ** tab, int n, int i, int j)
{
  int compte = 0;
  int borneL, borneC;
  for (borneL = i - 1; borneL <= i + 1; borneL++)
  {
      for (borneC = j - 1; borneC <= j + 1; borneC++)
      {
          if (borneC >= 0 && borneL >= 0 && borneC < 2 * n && borneL < n && (borneC != j || borneL != i))
          {
              if (tab[borneL][borneC] == 1)
               {
                   compte++;
               }
          }
      }
  }
  return compte;
}




int compteVoisinDirect(int ** tab, int i, int j)
{
   int compte = 0;
    if(tab[i-1][j]==1)
	    compte ++;
    if(tab[i+1][j]==1)
	    compte ++;
    if(tab[i][j-1]==1)
	    compte ++;
     if (tab[i][j+1]==1)
	 compte ++;
   return compte;
}







void jeudelavie(int ** tab,int n)
{
   int i ,j;
   int ** tmp = malloc(2 * n * sizeof(int*));
   for (i = 0; i < n ; i++)
   {
       tmp[i] = malloc( 2 * n * sizeof(int));
   }
   for( i = 0; i < n; i ++)
  {
      for( j = 0 ; j < 2 * n ; j++)
      {
          tmp[i][j] = tab[i][j];
      }
  }
 
for( i = 0; i < n; i ++)
  {
      for( j = 0 ; j < 2 * n ; j++)
      {
          if (tmp[i][j]==1)
          {
              if (compteVoisin(tmp,n,i,j) > 3 || compteVoisin(tmp,n,i,j)< 2)
              {
                  tab[i][j]=0;
              }
          }
          else
          {
              if (compteVoisin(tmp,n,i,j)==3)
              {
               tab[i][j] = 1;
              }
          }
      }
  }
  for (i = 0; i < n; i++)
  {
      free(tmp[i]);
      
  }
free(tmp);
 
}





void ulman(int ** tab,int n)
{
   int i ,j;
   int ** tmp = malloc( n * sizeof(int*));
   for (i = 0; i < n ; i++)
   {
       tmp[i] = malloc(2 *  n * sizeof(int));
   }
   for( i = 0; i < n; i ++)
  {
      for( j = 0 ; j < 2 * n ; j++)
      {
          tmp[i][j] = tab[i][j];
      }
  }
 
   for( i = 1; i < n -1; i ++)
  {
      for( j = 1; j < 2 * n -1; j++)
      {
          if (tmp[i][j]==0)
          {
	    if (compteVoisinDirect(tmp,i,j)==1)
              {
		tab[i][j] = 1;
	      }
          }
      }
  }
  for (i = 0; i < n; i++)
  {
      free(tmp[i]);
  }
  free(tmp);
}


void parite(int ** tab,int n, int nbIte)
{
   int i ,j;
   int ** tmp = malloc( n * sizeof(int*));
   for (i = 0; i <  n ; i++)
   {
       tmp[i] = malloc( 2 * n * sizeof(int));
   }
   for( i = 0; i < n; i ++)
  {
      for( j = 0 ; j < 2 * n ; j++)
      {
          tmp[i][j] = tab[i][j];
      }
  }
 
   if (nbIte % 2 == 0)
   {
       for (i=1; i<n-1;i++)
       {
           for (j=1; j < 2 * n -1; j++)
           {
	     if (compteVoisinDirect(tmp,i,j) == 1)
               {
                   tab[i][j] = 1;
               }
           }
       }
   }
   else
   {
       for (i=0; i<n;i++)
       {
           for (j=0; j < 2 * n; j++)
           {
               if (compteVoisin(tmp,n,i,j) == 1)
               {
                   tab[i][j] = 1;
               }
           }
       }
   }
   for (i = 0; i < n; i++)
   {
      free(tmp[i]);
   }
  free(tmp);
}
