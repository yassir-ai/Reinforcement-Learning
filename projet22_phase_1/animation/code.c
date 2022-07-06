#include <SDL2/SDL_image.h>
#include <SDL2/SDL_image.h>               // Nécessaire pour la fonction IMG_Load
#include "animation.h"                                            // Penser au flag -lsdl2_image à la compilation





void end_sdl(char ok,                                                 // fin normale : ok = 0 ; anormale ok = 1
                  char const* msg,                                    // message à afficher
                  SDL_Window* window,                                 // fenêtre à fermer
                  SDL_Renderer* renderer)                             // renderer à fermer
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
  if (window != NULL)   SDL_DestroyWindow(window);                                        

  SDL_Quit();                                                     

  if (!ok) {                                                      
         exit(EXIT_FAILURE);                                              
  }                                                               
} 

SDL_Texture* load_texture_from_image(char  *  file_image_name, SDL_Window *window, SDL_Renderer *renderer ){
    SDL_Surface *my_image = NULL;           // Variable de passage
    SDL_Texture* my_texture = NULL;         // La texture

    my_image = IMG_Load(file_image_name);   // Chargement de l'image dans la surface
                                            // image=SDL_LoadBMP(file_image_name); fonction standard de la SDL, 
                                            // uniquement possible si l'image est au format bmp */
    if (my_image == NULL) end_sdl(0, "Chargement de l'image impossible", window, renderer);

    my_texture = SDL_CreateTextureFromSurface(renderer, my_image); // Chargement de l'image de la surface vers la texture
    SDL_FreeSurface(my_image);                                     // la SDL_Surface ne sert que comme élément transitoire 
    if (my_texture == NULL) end_sdl(0, "Echec de la transformation de la surface en texture", window, renderer);

    return my_texture;
  }
  
  
  



void play_with_texture_1_1(SDL_Texture *my_texture, SDL_Window *window,
                         SDL_Renderer *renderer) {
  SDL_Rect 
          source = {0},                         // Rectangle définissant la zone de la texture à récupérer
          window_dimensions = {0},              // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
          destination = {0};                    // Rectangle définissant où la zone_source doit être déposée dans le renderer

  SDL_GetWindowSize(
      window, &window_dimensions.w,
      &window_dimensions.h);                    // Récupération des dimensions de la fenêtre
  SDL_QueryTexture(my_texture, NULL, NULL,
                   &source.w, &source.h);       // Récupération des dimensions de l'image

  destination = window_dimensions;              // On fixe les dimensions de l'affichage à  celles de la fenêtre

  /* On veut afficher la texture de façon à ce que l'image occupe la totalité de la fenêtre */

  SDL_RenderCopy(renderer, my_texture,
                 &source,
                 &destination);                 // Création de l'élément à afficher
  //SDL_RenderPresent(renderer);                  // Affichage
  //SDL_Delay(2000);                              // Pause en ms

  //SDL_RenderClear(renderer);                    // Effacer la fenêtre
}








void play_with_texture_5_1(SDL_Texture *bg_texture,
                           SDL_Texture *my_texture,
                           SDL_Window *window,
                           SDL_Renderer *renderer) {
  SDL_Rect
    source = {0},                             // Rectangle définissant la zone de la texture à récupérer
    window_dimensions = {0},                  // Rectangle définissant la fenêtre, on  n'utilisera que largeur et hauteur
    destination = {0};                        // Rectangle définissant où la zone_source doit être déposée dans le renderer

  SDL_GetWindowSize(window,                   // Récupération des dimensions de la fenêtre
                    &window_dimensions.w, 
                    &window_dimensions.h); 
  SDL_QueryTexture(my_texture, NULL, NULL,    // Récupération des dimensions de l'image
                   &source.w, &source.h); 

  int nb_images = 13 ;                         //  Il y a 8 vignette dans la ligne qui nous intéresse
  int nb_images_animation = 1 * nb_images;    // 
  float zoom = 1;                             // zoom, car ces images sont un peu petites
  int offset_x = source.w / 13,                // La largeur d'une vignette de l'image
      offset_y = source.h / 4;                // La hauteur d'une vignette de l'image
  SDL_Rect state[100];                         // Tableau qui stocke les vignettes dans le bon ordre pour l'animation

  /* construction des différents rectangles autour de chacune des vignettes de la planche */
  int i = 0;                                   
  for (int y = 0; y < source.h ; y += offset_y) {
    for (int x = 0; x < source.w; x += offset_x) {
      state[i].x = x;
      state[i].y = y;
      state[i].w = offset_x;
      state[i].h = offset_y;
      ++i;
    }
  }
  

  destination.w = offset_x * zoom;            // Largeur du sprite à l'écran
  destination.h = offset_y * zoom;            // Hauteur du sprite à l'écran
  destination.x = window_dimensions.w * 0.75; // Position en x pour l'affichage du sprite
  destination.y = window_dimensions.h * 0.5;  // Position en y pour l'affichage du sprite

  i = 0;
  float d = 0 ;
  while(1)
  {     i = (i + 1) % nb_images;                  // Passage à l'image suivante, le modulo car l'animation est cyclique 
      d+= 0,01;
    destination.x = window_dimensions.w * d; // Position en x pour l'affichage du sprite


    while(i<100)
    { 
        play_with_texture_1_1(bg_texture,         // identique à play_with_texture_1, où on a enlevé l'affichage et la pause
                            window, renderer); 
        SDL_RenderCopy(renderer,                  // Préparation de l'affichage
                    my_texture, &state[10], &destination);
                    
        // i = (i + 1) % nb_images;                  // Passage à l'image suivante, le modulo car l'animation est cyclique 
        SDL_RenderPresent(renderer);              // Affichage
        SDL_Delay(50);                           // Pause en ms
         d+= 0.01 ;
         destination.x = window_dimensions.w * d;
         SDL_RenderClear(renderer);
         if(destination.x > window_dimensions.w) d = 0 ;
    }  
  }
   

}

