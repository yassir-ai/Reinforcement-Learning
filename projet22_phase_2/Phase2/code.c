/**
 * \file code.c
 * \brief fichier de fonctions.
 * \author Yassir Mrani Alaoui, Oussama Diai, Anas Elhoudri
 * \date 1 juillet 2022
 *
 * Fichier de fonctions support pour le projet d'apprentissage par renforcement
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include "code.h"

/**
 * \fn void play_with_texture_3(SDL_Texture* my_texture,SDL_Renderer* renderer,SDL_Rect destination,SDL_Rect source)
 * \brief Fonction d'affichage d'une portion d'une image dans une partie précise de la fenetre
 *
 * \param my_texture texture SDL à afficher
 * \param renderer un SDL_Renderer pour affichage
 * \param destination désigne la position et la taille de l'affichage de la texture dans la fenetre
 * \param source désigne la position et la taille de la partie de la texture à afficher
 */

void play_with_texture_3(SDL_Texture* my_texture,
                            SDL_Renderer* renderer,SDL_Rect destination,SDL_Rect source) {

     SDL_RenderCopy(renderer, my_texture,     // Préparation de l'affichage  
                    &source,
                    &destination);            
     SDL_RenderPresent(renderer);             

   } 

/**
 * \fn SDL_Texture* load_texture_from_image(char  *  file_image_name, SDL_Window *window, SDL_Renderer *renderer )
 * \brief Fonction de création de texture à partir d'un fichier image
 *
 * \param file_image_name nom du fichier image
 * \param window La fenetre SDL_Window dans laquelle l'affichage aura lieu
 * \param renderer le SDL_Renderer pour affichage
 * \return la texture crée à partie du fichier image
 */



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


/**
 * \fn void end_sdl(char ok,char const* msg,SDL_Window* window,SDL_Renderer* renderer)
 * \brief Fonction de gestion des erreurs de chargement et intialisation des variables d'affichage
 *
 * \param ok caractère indicant la fin normale ou anormale du programme
 * \param msg chaine de caractères agissant comme message d'erreur
 * \param window fenetre d'affichage
 * \param renderer le SDL_Renderer pour affichage
 */


void end_sdl(char ok,                                               // fin normale : ok = 0 ; anormale ok = 1
             char const* msg,                                       // message à afficher
             SDL_Window* window,                                    // fenêtre à fermer
             SDL_Renderer* renderer) {                              // renderer à fermer
  char msg_formated[255];                                                         
  int l;                                                                          

  if (!ok) {                                                        // Affichage de ce qui ne va pas
    strncpy(msg_formated, msg, 250);                                              
    l = strlen(msg_formated);                                                     
    strcpy(msg_formated + l, " : %s\n");                                          

    SDL_Log(msg_formated, SDL_GetError());                                        
  }                                                                               

  if (renderer != NULL) {                                           // Destruction si nécessaire du renderer
    SDL_DestroyRenderer(renderer);                                  // Attention : on suppose que les NULL sont maintenus !!
    renderer = NULL;
  }
  if (window != NULL)   {                                           // Destruction si nécessaire de la fenêtre
    SDL_DestroyWindow(window);                                      // Attention : on suppose que les NULL sont maintenus !!
    window= NULL;
  }

  SDL_Quit();                                                                     

  if (!ok) {                                                        // On quitte si cela ne va pas                
    exit(EXIT_FAILURE);                                                           
  }                                                                               
}



/**
 * \fn int max_l(float  Q_matrice[NB_ETAT][NB_ACTION] , int etat_cour)
 * \brief Fonction qui trouve l'action de la plus grande qualité entre les actions possible dans cet état
 *
 * \param Q_matrice matrice des qualités des actions suivant les différents états
 * \param etat_cour l'etat courant à traiter
 * \return Le résultat de la fonction étant l'action ayant la plus grande qualité pour l'état courant
 */


int max_l(float  Q_matrice[NB_ETAT][NB_ACTION] , int etat_cour)
{
  int result = Q_matrice[etat_cour][0];

  for(int i = 0;i<4;i++)
  {
      result = result < Q_matrice[etat_cour][i] ?   Q_matrice[etat_cour][i] : result ; 
  } 

  return result ;
} 


// retourner l'action  qui a la qualite la plus grande  dans la matrice dans un eligne donnée
int max_q_etat(float  Q_matrice[NB_ETAT][NB_ACTION] , int etat_cour)
{
  int result = Q_matrice[etat_cour][0];
  int i = 0 ;
  int j= 0;

  for(i = 0;i<4;i++)
  {
    if( result < Q_matrice[etat_cour][i])
    {
        result = Q_matrice[etat_cour][i] ;
        j=i ;
    } 
  } 

  return j ;
} 



// La mise à jour de la Q_matrice
void qualite_des_actions(float Q_matrice[NB_ETAT][NB_ACTION] , 
                      float Recomp_matrice[NB_ETAT][NB_ACTION] ,    
                      int etat_prec ,
                      int etat_cour ,
                      action act)
{
  // formule de BELLMAN
     Q_matrice[etat_prec][act] += epsilon * ( Recomp_matrice[etat_prec][act]  + (alpha * max_l(Q_matrice,etat_cour) ) - Q_matrice[etat_prec][act] ) ;
} 



/**
 * \fn int progress_etat(int etat_prec , action act)
 * \brief Fonction de détermination de l'état courant à partir de l'état précedant et l'action prise
 *
 * \param etat_prec Etat précedant
 * \param act Action prise à l'état précedant
 * \return Retourne l'etat produit de l'action prise et de l'état précedant. Prends la valeur 100 si l'action est impossible.
 */

int progress_etat(int etat_prec , action act)
{
    int impossible = 100 ;
    int result = 0;

    if((etat_prec < 5) && (act == up)) result=impossible;
    else if((etat_prec > 24) && (act == down)) result=impossible;
    else if(((etat_prec % 5)==0) && (act == left)) result=impossible;
    else if((((etat_prec +1)%5)==0) && (act == right)) result=impossible;
    else
    {
      switch(act)
      {
        case up :
          result = etat_prec - 5;
          break;
        case down :
          result = etat_prec + 5;
          break;
        case left :
          result = etat_prec - 1;
          break;
        case right :
          result = etat_prec + 1;
          break;
      } 
    }
      return result;
} 




// la suite de epsilon dans e-greedy 
float suite_epsilon(float n)
{
  return a_suite / (2*(n+ a_suite)) ;
} 




// ecriture de la Q_matrice dans le fichier avec le compteur chaque fois qu'on atteint le but (star) 
void ecriture_fichier(char *nom ,float Q_matrice[NB_ETAT][NB_ACTION] , int compteur)
{
  FILE * file = fopen(nom,"w+") ;

  if(file == NULL)  printf("Echec d'ouverture du fichier\n") ;
  

  else
  {
      int i=0 , j=0 ;

      for(i=0;i<NB_ETAT;i++)
      {
        for(j=0;j<NB_ACTION;j++)
        {
            fprintf(file,"%f ", Q_matrice[i][j]); 
        } 
        fprintf(file,"\n") ;
      } 

      fprintf(file,"\n") ;
      fprintf(file,"IL S'AGIT DE VOTRE EPISODE NUMERO : %d ",compteur) ;

      fclose(file) ;
  } 
} 


/**
 * \fn void lecture_Q_matrice(char *nom , float Q_matrice[NB_ETAT][NB_ACTION])
 * \brief Fonction de lecture de la matrice de qualités à partir d'un fichier texte
 *
 * \param nom Le nom du fichier duquel la lecture de la matrice de qualité aura lieu
 * \param Q_matrice matrice des qualités
 */


void lecture_Q_matrice(char* nom , float Q_matrice[NB_ETAT][NB_ACTION])
{
	float temp[NB_ETAT][NB_ACTION];

  FILE *fichier = fopen(nom,"r") ;

	if(fichier==NULL)
	{
		printf("Erreur! Echoue d'ouverture du fichier!\n");
	}
	else
	{
		for(int i=0;i<NB_ETAT;i++)
		{
			  fscanf(fichier,"%f %f %f %f\n",&(temp[i][0]),&(temp[i][1]),&(temp[i][2]),&(temp[i][3]));
		}

		for(int i=0;i<NB_ETAT;i++)
		{
			for(int j=0;j<NB_ACTION;j++)
			{
			  Q_matrice[i][j]=temp[i][j];
			}
		}

    fclose(fichier) ;
	}
} 


/**
 * \fn void ecriture_data(char * nom ,int a, int b)
 * \brief Fonction d'écriture de deux entiers dans un fichier (ajoute des données, n'écrase pas)
 *
 * \param nom Nom du fichier dans lequel l'écriture aura lieu
 * \param a premier entier à écrire
 * \param b deuxieme entier à écrire
 */

void ecriture_data(char * nom ,int a, int b)  
{
    FILE *file =fopen(nom,"a") ;

    if(file==NULL)
	{
		printf("Erreur! Echoue d'ouverture du fichier!\n");
	}
  else 
  {
    fprintf(file,"%d  %d\n",a,b) ;
    fclose(file) ;
  } 
} 




