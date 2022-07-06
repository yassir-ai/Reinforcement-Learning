
#include <SDL2/SDL.h>
#include <stdio.h>




int main(int argc, char **argv) {
  (void)argc;
  (void)argv;
  int i =0 , j=0 , h=0 , k=0 , a=0 , b=0 ;
  
  SDL_Window *window_1 = NULL, *window_2 = NULL;                      

  /* Initialisation de la SDL  + gestion de l'échec possible */
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    SDL_Log("Error : SDL initialisation - %s\n", SDL_GetError());      // l'initialisation de la SDL a échoué 
    exit(EXIT_FAILURE);
  }

  /* Création de la fenêtre de gauche */
 
 for(j=0 ; j<900;j+=20)
{
  window_1 = SDL_CreateWindow(
      "Fenêtre à gauche",                    // codage en utf8, donc accents possibles
      0, j,                                  // coin haut gauche en haut gauche de l'écran
      100, 100,                              // largeur = 400, hauteur = 300
      SDL_WINDOW_RESIZABLE);
      SDL_Delay(50);
}               // redimensionnable



 for(h=0 ; h<1440;h+=20)
{
    window_1 = SDL_CreateWindow(
      "Fenêtre à gauche",                    // codage en utf8, donc accents possibles
      h, j,                                  // coin haut gauche en haut gauche de l'écran
      100, 100,                              // largeur = 400, hauteur = 300
      SDL_WINDOW_RESIZABLE);
      SDL_Delay(50);

}               // redimensionnable


  
for(i=900 ; i>0; i-=20)
{  
  
window_2 = SDL_CreateWindow(
      "Fenêtre à droite",                    // codage en utf8, donc accents possibles
      h, i,                                // à droite de la fenêtre de gauche
      100, 100,                              // largeur = 500, hauteur = 300
      0);
      SDL_Delay(50);

}

for(k=h ; k>0; k-=20)
{  
  
window_2 = SDL_CreateWindow(
      "Fenêtre à droite",                    // codage en utf8, donc accents possibles
      k, i,                                // à droite de la fenêtre de gauche
      100, 100,                              // largeur = 500, hauteur = 300
      0);
      SDL_Delay(50);

}

for(a=0 ; a < 900 ; a+=20)
{
    window_2 = SDL_CreateWindow(
      "Fenêtre à droite",                    // codage en utf8, donc accents possibles
      a *1440 /900, a,                                // à droite de la fenêtre de gauche
      100, 100,                              // largeur = 500, hauteur = 300
      0);
      SDL_Delay(50);

}
// int n= 0
// for(b=a ; b > 0 ; b-=20)
// {
//     window_2 = SDL_CreateWindow(
//       "Fenêtre à droite",                    // codage en utf8, donc accents possibles
//       b *1440 /900, 0,                                // à droite de la fenêtre de gauche
//       100, 100,                              // largeur = 500, hauteur = 300
//       0);
// }









    if (window_1 == NULL) {
    SDL_Log("Error : SDL window 1 creation - %s\n", SDL_GetError());   // échec de la création de la fenêtre
    SDL_Quit();
    exit(EXIT_FAILURE);
  }




  if (window_2 == NULL) {
    /* L'init de la SDL : OK
       fenêtre 1 :OK
       fenêtre 2 : échec */
    SDL_Log("Error : SDL window 2 creation - %s\n", SDL_GetError());   // échec de la création de la fenêtre 
    SDL_DestroyWindow(window_1);
    SDL_Quit();
    exit(EXIT_FAILURE);
  }

  /* Normalement, on devrait ici remplir les fenêtres... */
  SDL_Delay(4000);                           // Pause exprimée  en ms

  /* et on referme tout ce qu'on a ouvert en ordre inverse de la création */
  SDL_DestroyWindow(window_2);
  SDL_DestroyWindow(window_1);

  SDL_Quit();
  return 0;
}

