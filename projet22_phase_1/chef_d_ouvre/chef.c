#include <SDL2/SDL_image.h>
#include <SDL2/SDL_image.h>               // Nécessaire pour la fonction IMG_Load
#include "../chef.h"                                           // Penser au flag -lsdl2_image à la compilation





int main()
{
    // creation windo & renderer
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    SDL_DisplayMode screen;
    if (SDL_Init(SDL_INIT_VIDEO) != 0) end_sdl(0, "ERROR SDL INIT", window, renderer);

    SDL_GetCurrentDisplayMode(0, &screen);
    printf("Résolution écran\n\tw : %d\n\th : %d\n", screen.w,screen.h);
    window = SDL_CreateWindow("Premier dessin",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,
    screen.w * 0.66, screen.h * 0.66,SDL_WINDOW_OPENGL);

    if (window == NULL) end_sdl(0, "ERROR WINDOW CREATION", window, renderer);

    /* Création du renderer */
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (renderer == NULL) end_sdl(0, "ERROR RENDERER CREATION", window, renderer);


    SDL_Texture *texture = load_texture_from_image("Vegeta.png",window, renderer );
    SDL_Texture * bg_texture = load_texture_from_image("vue.png",window, renderer );
    
    // play_with_texture_5( bg_texture,texture, window, renderer);
    play_with_texture_4( texture, window, renderer);






  //...
   IMG_Quit() ;                                            // Si on charge une librairie SDL, il faut penser à la décharger   
    return 0 ;
} 







