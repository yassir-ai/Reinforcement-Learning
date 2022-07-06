#include <SDL2/SDL_image.h>
#include <SDL2/SDL_image.h>               // Nécessaire pour la fonction IMG_Load
                                           // Penser au flag -lsdl2_image à la compilation


void end_sdl(char ok, char const* msg, SDL_Window* window,SDL_Renderer* renderer) ;





SDL_Texture* load_texture_from_image(char  *  file_image_name, SDL_Window *window, SDL_Renderer *renderer );


// // identique à play_with_texture_1, où on a enlevé l'affichage et la pause
// void play_with_texture_1_1(SDL_Texture *my_texture, SDL_Window *window,
//                          SDL_Renderer *renderer) ;






// // affichage IMAGE 
// void play_with_texture_1(SDL_Texture *bg,SDL_Texture * mytex, SDL_Window *window,SDL_Renderer *renderer) ;

// // pour le ZOOOOOOOOOOOOOOOOOOOOOOOOOOOM
// void play_with_texture_2(SDL_Texture* my_texture,SDL_Window* window, SDL_Renderer* renderer) ;


// // faire sauter une image avec gestion de zoom et d alphamod
// void play_with_texture_3(SDL_Texture* my_texture,SDL_Window* window,SDL_Renderer* renderer) ;


// // mouvement du bonhomme

// void play_with_texture_4(SDL_Texture* my_texture,SDL_Texture* bg,SDL_Window* window,SDL_Renderer* renderer) ;

// void play_with_texture_5(SDL_Texture *bg_texture,SDL_Texture *my_texture,SDL_Window *window,SDL_Renderer *renderer) ;



void play_with_texture_1_1(SDL_Texture *my_texture, SDL_Window *window,
                         SDL_Renderer *renderer);





void play_with_texture_5_1(SDL_Texture *bg_texture,
                           SDL_Texture *my_texture,
                           SDL_Window *window,
                           SDL_Renderer *renderer);