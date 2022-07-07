#ifndef MARKOV_H
#define MARKOV_H


#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_ttf.h>


#define S_WIDTH 180
#define S_HEIGHT 768

//les états possibles 
typedef enum choix{ rock,paper,scissor }choix;

int ExtraireMatrice(float matrice[3][3],FILE* fichier);

choix Markov(float matrice[][3],choix prec);

void end_sdl(char ok,                                               
               char const* msg,                                    
               SDL_Window* window,                                    
               SDL_Renderer* renderer);

SDL_Texture* load_texture_from_image(char  *  file_image_name, SDL_Window *window, SDL_Renderer *renderer );

void play_with_texture_3(SDL_Texture* my_texture,
			SDL_Renderer* renderer,
			SDL_Rect destination,
			SDL_Rect source);

void AfficherChoixMachine(choix machine,SDL_Texture* my_texture ,SDL_Renderer* renderer);

void affichage_vie(SDL_Renderer *renderer, SDL_Window *window, int vie,int score,TTF_Font *font);

#endif // MARKOV_H
