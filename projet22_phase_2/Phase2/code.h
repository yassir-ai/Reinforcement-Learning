/**
 * \file code.h
 * \brief Fichier de prototypes des fonctions de code.c et des variables globales et symboliques
 * \author Yassir Mrani Alaoui, Oussama Diai, Anas Elhoudri
 * \version Phase 2
 * \date 1 juillet 2022
 */

#ifndef ROBOT_H
#define ROBOT_H  

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>


#define NB_ETAT 30
#define NB_ACTION 4  
#define epsilon 1                          // facteur d'apprentissage : plus elle est grande : vitesse d'apprentiss est grand 
#define alpha 0.9                          // facteur d'actualisation : plus elle est grand : il voit les recomp futurs , sinon les recomp immedit
#define a_suite 200                       // plus a_suite est grande ; plus la decroissance de la suite est lente 





typedef enum action
{
	up,	/*!< Action de passage vers la case du haut */
	down,	/*!< Action de passage vers la case du bas */
	right,	/*!< Action de passage vers la case de la droite */
	left	/*!< Action de passage vers la case de la gauche */
}
action ;

void play_with_texture_3(SDL_Texture* my_texture,
                            SDL_Renderer* renderer,SDL_Rect destination,SDL_Rect source) ;

SDL_Texture* load_texture_from_image(char  *  file_image_name, SDL_Window *window, SDL_Renderer *renderer );

void end_sdl(char ok,                     // fin normale : ok = 0 ; anormale ok = 1
             char const* msg,             // message à afficher
             SDL_Window* window,          // fenêtre à fermer
             SDL_Renderer* renderer) ;

int max_q_etat(float  Q_matrice[NB_ETAT][NB_ACTION] , int etat_cour) ;

void qualite_des_actions(float Q_matrice[NB_ETAT][NB_ACTION] , 
                      float Recomp_matrice[NB_ETAT][NB_ACTION] ,    
                      int etat_prec ,
                      int etat_cour ,
                      action act) ;

int progress_etat(int etet_prec , action act  ) ;

float suite_epsilon(float n ) ;

void ecriture_fichier(char *nom ,float Q_matrice[NB_ETAT][NB_ACTION] , int compteur ) ;

void lecture_Q_matrice(char *nom , float Q_matrice[NB_ETAT][NB_ACTION]) ;

void ecriture_data(char * nom ,int a, int b)  ;


#endif 
