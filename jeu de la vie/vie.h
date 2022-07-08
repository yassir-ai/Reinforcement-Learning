#ifndef VIE2_H
#define VIE2_H
#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

void end_sdl(char ok,char const* msg,SDL_Window* window,SDL_Renderer* renderer);
void initialisermatrice(int mat[50][50]);
void affichermatrice(int mat[50][50]);
int nbvoisins(int mat[50][50],int i,int j);
void regle(int mat[50][50],int i,int j,int mat2[50][50]);
void nouveauemplaire(int mat[50][50],int mat2[50][50]);
void colorier_surface(int mat[50][50],int x,int y ,int w,int h,SDL_Renderer* renderer) ;

#endif
