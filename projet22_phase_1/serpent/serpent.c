
#include <SDL2/SDL.h>

#include <math.h>

#include <stdio.h>

#include <string.h>

#include <stdlib.h>


void end_sdl(char ok,  SDL_Window* window,   SDL_Renderer* renderer)                                            
{
  if (renderer != NULL) SDL_DestroyRenderer(renderer);
  if (window != NULL)   SDL_DestroyWindow(window);

  SDL_Quit();

}






void draw(SDL_Renderer* renderer, int a, int b, int w, int h) 
{ 

   SDL_Rect rectangle;
   SDL_SetRenderDrawColor(renderer,0,0,255,255) ; // le noir ,opaque

                               
  

  rectangle.x = a;                                                    // x haut gauche du rectangle
  rectangle.y =b;                                                    // y haut gauche du rectangle
  rectangle.w = w;                                                  // sa largeur (w = width)
  rectangle.h = h;                                                 // sa hauteur (h = height)

 

  SDL_RenderFillRect(renderer, &rectangle);
  SDL_SetRenderDrawColor(renderer, 0 , 0, 0, 255);
//   SDL_RenderDrawLine(renderer,0,0,400,400) ; // x,y du point de la première extrémité

 //SDL_DestroyRenderer(renderer);
  }

int main()
{
    // initialiser window et renderer
     SDL_Window* window = NULL;
     SDL_Renderer* renderer = NULL;


     SDL_DisplayMode screen;  // calcul de demension !! tres utiiiiiiiiiile 




/*                         Initialisation de la SDL  + gestion de l'échec possible                                   */

    if (SDL_Init(SDL_INIT_VIDEO) != 0) end_sdl(0, window, renderer);


     SDL_GetCurrentDisplayMode(0, &screen);
    printf("Résolution écran\n\tw : %d\n\th : %d\n", screen.w, screen.h);  // avoir la résolution de l'ecran


    /* Création de la fenêtre */

     window = SDL_CreateWindow("Premier dessin",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen.w * 0.66, screen.h * 0.66,SDL_WINDOW_OPENGL);
     if (window == NULL) end_sdl(0, window, renderer);


  /* Création du renderer */

  renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (renderer == NULL) end_sdl(0, window, renderer);


  
  
    int i= 0 ;

    for( i=0;i<1000;i+=10)
    {
        
        draw(renderer, i, 10, 60,10);                                                    // appel de la fonction qui crée l'image
        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);    // affichage
        SDL_Delay(100);    
    } 
        draw(renderer, i, 10, 30,10);  
        draw(renderer, i+30, 10, 10,30);                                                   // appel de la fonction qui crée l'image
        SDL_RenderPresent(renderer);
        // SDL_RenderClear(renderer);    // affichage
        // SDL_Delay(50);
        // draw(renderer, i+10, 10, 30,10);  
         SDL_RenderPresent(renderer);
        SDL_Delay(100);                                                         // appel de la fonction qui crée l'image
        // SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);    // affichage
        SDL_Delay(100);                                      
 



    for(int j=30;j<500;j+=10)
    {
        draw(renderer,1030 ,j , 10, 60);                                                    // appel de la fonction qui crée l'image
        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);// affichage
        SDL_Delay(100);    
    }




        draw(renderer, 1030, 550, 10,30);  
        draw(renderer, 1010, 580, 30,10);                                                   // appel de la fonction qui crée l'image
        SDL_RenderPresent(renderer);
        // SDL_RenderClear(renderer);    // affichage
        // SDL_Delay(50);
        // draw(renderer, i+10, 10, 30,10);  
         SDL_RenderPresent(renderer);
        SDL_Delay(100);                                                         // appel de la fonction qui crée l'image
        // SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);    // affichage
        SDL_Delay(100);   

  

    for(int r=1010;r>=10;r-=10)
  {
    draw(renderer,r ,580, 60, 10);                                                    // appel de la fonction qui crée l'image
    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);// affichage
    SDL_Delay(50); 
    }
      




    for(int l=500;l>=0;l-=10)
    {
        draw(renderer, 1,l, 10,60);                                                    // appel de la fonction qui crée l'image
        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);// affichage
        SDL_Delay(50);    
    }
   
  /*********************************************************************************************************************/

  /* on referme proprement la SDL */

  end_sdl(1, window, renderer);

  return EXIT_SUCCESS;

}
