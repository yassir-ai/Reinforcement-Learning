#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
// #include"time.h"
#include"vie.h"

int tabsurvie[9]={0,1,1,0,0,0,0,0,0};
int tabnais[9]={0,0,1,0,0,0,0,0,0};

void end_sdl(char ok,char const* msg,SDL_Window* window,SDL_Renderer* renderer) 
{ 
    char msg_formated[255]; 
    int l; 

    if (!ok) { 
    strncpy(msg_formated, msg, 250); 
    l = strlen(msg_formated); 
    strcpy(msg_formated + l, " : %s\n"); 

    SDL_Log(msg_formated, SDL_GetError()); 
} 

 if (renderer != NULL) SDL_DestroyRenderer(renderer); 
 if (window != NULL) SDL_DestroyWindow(window); 

 SDL_Quit(); 

 if (!ok) { 
 exit(EXIT_FAILURE); 
 } 
} 


void initialisermatrice(int mat[50][50])
{
    srand(time(NULL));
    for (int i=0;i<50;i++)
    {
        for (int j=0;j<50;j++)
        {
            mat[i][j]= 0 ; 
        }
    }
}
void affichermatrice(int mat[50][50])
{
    for (int i=0;i<50;i++)
    {
        for (int j=0;j<50;j++)
        {  
            printf("%d ",mat[i][j]);
        }
        printf("\n");
    }
}


int nbvoisins(int mat[50][50],int i,int j)
{
  int count=0;
  for (int x=-1;x<2;x++)
  {
      for (int y=-1;y<2;y++)
      {
          count = count + mat[(i+50+x)%50][(j+y+50)%50];
      }
  }
  
  count -= mat[i][j];
  return count;
}

void regle(int mat[50][50],int i,int j,int mat2[50][50])
{
    int voisin = nbvoisins(mat,i,j);
    
    if (mat[i][j]==1)
    {
        mat2[i][j]=tabsurvie[voisin];
    }
    else // elemnet mort
    {
        mat2[i][j]=tabnais[voisin];
    } 
}


void nouveauemplaire(int mat[50][50],int mat2[50][50])
    {
      for (int i=0;i<50;i++)
      {
        for (int j=0;j<50;j++)
        {
          regle(mat,i,j,mat2);
        }
      }

    for (int k=0;k<50;k++)
    {
      for (int l=0;l<50;l++)
      {
        mat[k][l]=mat2[k][l];
      }
    }
}

void colorier_surface(int mat[50][50],int x,int y ,int w,int h,SDL_Renderer* renderer)
{
  int i=0 ,j=0;
   while(i<50)
  {
      while(j<50)
      {
        SDL_Rect rectangle={x,y,w,h};
          
        x=x+20;
        SDL_SetRenderDrawColor(renderer,0,50,50,255);  //fond
        
        if (mat[i][j]==0)
        {
          SDL_RenderFillRect(renderer,&rectangle);
          
        }
        else
        {
          SDL_SetRenderDrawColor(renderer,255,0,0,255);
          SDL_RenderFillRect(renderer,&rectangle);
        }
        j++;
      }

    
      y=y+20;
      j=0; // passer à le deuxième ligne de la matrice
      x=0;

      i++;
  }

  SDL_RenderPresent(renderer); // afficher fond 
}

 

  
int main(int argc, char** argv) 
{
    (void)argc;
    (void)argv;
    int mat[50][50];
    int mat2[50][50];
    int i=0;
    int j=0;
    int x=0;
    int y=0;
    int w=20;
    int h=20;
    int k ,l ;
    int fait =0 ;


    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    SDL_DisplayMode screen;
    if (SDL_Init(SDL_INIT_VIDEO) != 0) end_sdl(0, "ERROR SDL INIT", window, renderer);

    SDL_GetCurrentDisplayMode(0, &screen);
    printf("Résolution écran\n\tw : %d\n\th : %d\n", screen.w, screen.h);
    window = SDL_CreateWindow("Premier dessin",SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED, screen.w * 0.66,screen.h * 0.66,SDL_WINDOW_OPENGL);
    if (window == NULL) end_sdl(0, "ERROR WINDOW CREATION", window, renderer);

    /* Création du renderer */
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) end_sdl(0, "ERROR RENDERER CREATION", window, renderer);
    
    initialisermatrice(mat);


    SDL_bool program_on = SDL_TRUE;               // Booléen pour dire que le programme doit continuer
    SDL_Event event;                              // c'est le type IMPORTANT !!
    // gestion du début
    SDL_bool go = SDL_FALSE ;

    while(!go)
     {
       colorier_surface(mat,x,y,w,h,renderer);
        while(SDL_PollEvent(&event))
        {
          switch(event.type)
          {
            case SDL_MOUSEBUTTONDOWN  :
                k = event.button.x /20 ;
                l = event.button.y /20 ;
                printf("x vaut %d et y vaut %d \n",l,k);
                mat[l][k]= 1 ;
                break ;
            case SDL_KEYDOWN :
                if(event.key.keysym.sym == SDLK_KP_ENTER) 
                 {
                    go = SDL_TRUE ;
                    fait = 1 ;
                     break ;
                 }
          }
        }
        
        if(fait == 1)
        {
            colorier_surface(mat,x,y,w,h,renderer) ;
            printf("le jeu va commencé dans 10 secondes \n");
            SDL_Delay(10000);
            
        }
        
     }

    





    // gestion d'evenement




    while (program_on)
    {                           // Voilà la boucle des évènements 


      while(SDL_PollEvent(&event))
      {                 // si la file d'évènements n'est pas vide : défiler l'élément en tête
                                                  // de file dans 'event'
        switch(event.type)
        {                       // En fonction de la valeur du type de cet évènement
          case SDL_QUIT :                           // Un évènement simple, on a cliqué sur la x de la fenêtre
            program_on = SDL_FALSE;                 // Il est temps d'arrêter le programme
            break ;

            


          default:                                  // L'évènement défilé ne nous intéresse pas
            break;
        }
      }
  // Affichages et calculs souvent ici
          nouveauemplaire(mat,mat2);

          // soit on fait :
          colorier_surface(mat,x,y,w,h,renderer) ;


        // ou faire 
        //   SDL_SetRenderDrawColor(renderer,0,50,50,255); // les elements vivants 
        //   SDL_RenderClear(renderer);

          
        //   while(i<50)
        //   {
        //       while(j<50)
        //       {
        //         SDL_Rect rectangle={x,y,w,h};
                  
        //         x=x+20;
        //         SDL_SetRenderDrawColor(renderer,250,0,0,255);  //fond
                
        //         if (mat[i][j]!=0)
        //         {
        //           printf("aaaaaa \n") ;
        //           SDL_RenderFillRect(renderer,&rectangle);
        //         }
        //         j++;
        //       }

            
        //       y=y+20;
        //       j=0; // passer à le deuxième ligne de la matrice
        //       x=0;

        //       i++;
        //   }

        //   SDL_RenderPresent(renderer);
          // i=0;
          // j=0;


          SDL_Delay(100);
          x=0;
          y=0;

}  




    
    SDL_Quit();
    return 0;
} 
