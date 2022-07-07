#include "markov.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int ExtraireMatrice(float matrice[3][3],FILE* fichier)                             //Extraire les donnees à partir du chiane de Markov
{	
	int succes=0;
	float temp[3][3];

	if(fichier==NULL)
	{
		printf("Erreur! Echoue d'ouverture du fichier!\n");
		succes=1;
	}
	else
	{
		for(int i=0;i<3;i++)
		{
			fscanf(fichier,"%f %f %f\n",&(temp[i][0]),&(temp[i][1]),&(temp[i][2]));
		}
		for(int i=0;i<3;i++)
		{
			for(int j=0;j<3;j++)
			{
			matrice[i][j]=temp[i][j];
			}
		}
	}

	return succes;
}

choix Markov(float matrice[][3],choix prec)                                      // choix suivant la loi aléatoire défini par la matrice de Markov
{
	choix resultat = paper ;
	float nb_aleat= (float)rand() / (float)RAND_MAX ;                          //generer un num aleatoire suivant la loi uniforme (0,1) 

	if(nb_aleat<=matrice[prec][0])
	{
		resultat=rock ;
	}
	else if(nb_aleat <= (matrice[prec][0] + matrice[prec][1]))
	{
		resultat=paper ;
	}
	else
	{
		resultat=scissor ;
	}
	return resultat;
}

void end_sdl(char ok,                                               // fin normale : ok = 0 ; anormale ok = 1
             char const* msg,                                       // message à afficher
             SDL_Window* window,                                    // fenêtre à fermer
             SDL_Renderer* renderer) {                              // renderer à fermer
  char msg_formated[255];                                                         
  int l;                                                                          

  if (!ok) 
  {                                                                // Affichage de ce qui ne va pas
    strncpy(msg_formated, msg, 250);                                              
    l = strlen(msg_formated);                                                     
    strcpy(msg_formated + l, " : %s\n");                                          
    SDL_Log(msg_formated, SDL_GetError());                                        
  }                                                                               

  if (renderer != NULL) 
  {                                                                 // Destruction si nécessaire du renderer
    SDL_DestroyRenderer(renderer);                                  // Attention : on suppose que les NULL sont maintenus !!
    renderer = NULL;
  }

  if (window != NULL)   											// Destruction si nécessaire de la fenêtre
  {                                           
    SDL_DestroyWindow(window);                                      // Attention : on suppose que les NULL sont maintenus !!
    window= NULL;
  }

  SDL_Quit();                                                  //on ferme proprement comme d'hab ;)                                                    

  if (!ok) 
  {                                                        // On quitte si cela ne va pas                
    exit(EXIT_FAILURE);                                                           
  }                                                                               
}

SDL_Texture* load_texture_from_image(char  *  file_image_name, SDL_Window *window, SDL_Renderer *renderer )
{
    SDL_Surface *my_image = NULL;                                                    // Variable de passage
    SDL_Texture* my_texture = NULL;                                                  // La texture

    my_image = IMG_Load(file_image_name);                                                       // Chargement de l'image dans la surface
                                                                                                // image=SDL_LoadBMP(file_image_name); fonction standard de la SDL, 
                                                                                                 // uniquement possible si l'image est au format bmp */
    if (my_image == NULL) end_sdl(0, "Chargement de l'image impossible", window, renderer);

    my_texture = SDL_CreateTextureFromSurface(renderer, my_image);                                                // Chargement de l'image de la surface vers la texture
    SDL_FreeSurface(my_image);                                                                                    // la SDL_Surface ne sert que comme élément transitoire 

    if (my_texture == NULL) end_sdl(0, "Echec de la transformation de la surface en texture", window, renderer);     // gestion d'erreur ;)

    return my_texture;
  }

void play_with_texture_3(SDL_Texture* my_texture,
                            SDL_Renderer* renderer,SDL_Rect destination,SDL_Rect source) {

     SDL_RenderCopy(renderer, my_texture,                                                    // Préparation de l'affichage  
                    &source,
                    &destination);            
     SDL_RenderPresent(renderer);             

   }  


void AfficherChoixMachine(choix machine,SDL_Texture* my_texture ,SDL_Renderer* renderer)
{
	SDL_Rect source_rock = {728,816,1384,1296};                              //dimension des photos dans la sprite sheet
 	SDL_Rect source_scissor = {2112,816,1384,1296};
 	SDL_Rect source_paper = {3496,816,1384,1296};
	SDL_Rect source_choix;

	switch(machine)
	{
		case 0:
			source_choix=source_rock; break;
		case 1:
			source_choix=source_paper; break;
		case 2:
			source_choix=source_scissor; break;
	}

	SDL_Rect destination={250,-820,130,120};

	for(int i=0;i<1000;i+=10)
	{
		play_with_texture_3(my_texture,renderer,destination,source_choix);
		SDL_Delay(40);
		destination.y+=i;                                                            //defilement du choix de la machine 
	}
}  


void affichage_vie(SDL_Renderer *renderer, SDL_Window *window, int vie,int score,TTF_Font *font)
{
    SDL_Color color = {255, 0, 0, 255};                                                           // la couleur du texte de vie
    SDL_Color colore = {0 , 255, 0, 255};                                                          // la couleur du texte de score
 
    SDL_Surface *text_surface = NULL;                                                              // la surface  (uniquement transitoire)
    char phrase[20];
	char phrase2[20];     

	
    sprintf(phrase, "Nombre de tours : %d" ,vie);
	sprintf(phrase2,"Score : %d",score);

    text_surface = TTF_RenderText_Blended(font, phrase, color);                                                              // création du texte dans la surface
	SDL_Surface *text_surfacee = TTF_RenderText_Blended(font, phrase2, colore);    

    if (text_surface == NULL) end_sdl(0, "Can't create text surface", window, renderer);

    SDL_Texture *text_texture = NULL;                                                                                         // la texture qui contient le texte
    text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);                                                      // transfert de la surface à la texture
	SDL_Texture *text_texturee =  SDL_CreateTextureFromSurface(renderer, text_surfacee);                                      // creation de la texture pour la deuxieme surface

    if (text_texture == NULL) end_sdl(0, "Can't create texture from surface", window, renderer);                              //gestion d'erreur ;)

    SDL_FreeSurface(text_surface);                                                                                           // la texture ne sert plus à rien
	SDL_FreeSurface(text_surfacee);                                                                                           

    SDL_Rect pos = {30, 30, 40, 40}; 	                                                                                     // rectangle où le texte va être prositionné
    SDL_Rect pos2 = {55, 50, 50, 50};                                                                                       // rectangle où le texte va être prositionné                       
	                               
    SDL_QueryTexture(text_texture, NULL, NULL, &pos.w, &pos.h);                                                            // récupération de la taille (w, h) du texte
	SDL_QueryTexture(text_texturee, NULL, NULL, &pos2.w, &pos2.h) ;   
    
	pos.x = S_WIDTH - pos.w - 30;
	pos2.x = S_WIDTH - pos2.w - 30; 

	if (vie == 0)
	{
		SDL_Color colore2 = {0 , 0, 255 , 255}; // la couleur du texte de score
		SDL_Surface * text_surface2 = NULL ; 

		char phrase3[70];                                                                                                // la dernière phrase

		sprintf(phrase3,"Votre partie est terminee !!  Votre score finale est : %d",score) ;
		text_surface2 = TTF_RenderText_Blended(font, phrase3, colore2);                                                 // création du texte dans la surface
   		if (text_surface2 == NULL) end_sdl(0, "Can't create text surface", window, renderer);

		SDL_Texture *text_texture2 = NULL;                                                                               // la texture qui contient le texte
		
		text_texture2 = SDL_CreateTextureFromSurface(renderer, text_surface2);                                           // transfert de la surface à la texture

		if (text_texture2 == NULL) end_sdl(0, "Can't create texture from surface", window, renderer);

		SDL_FreeSurface(text_surface2);                                                                               // la texture ne sert plus à rien
		
   		SDL_Rect pos3 = {160, 240, 70, 70}; 	                                                                  // rectangle où le texte va être prositionné

		SDL_QueryTexture(text_texture2, NULL, NULL, &pos3.w, &pos3.h) ;                                             // récupération de la taille (w, h) du texte
		SDL_RenderCopy(renderer, text_texture2, NULL, &pos3) ;                                                       // Ecriture du texte dans le renderer
		SDL_DestroyTexture(text_texture2);

	} 

    SDL_RenderCopy(renderer, text_texture, NULL, &pos) ;                                                        // Ecriture du texte dans le renderer
	SDL_RenderCopy(renderer, text_texturee, NULL, &pos2) ; 

    SDL_DestroyTexture(text_texture);                                                                           // On n'a plus besoin de la texture avec le texte
	SDL_DestroyTexture(text_texturee); 			                                                               // On n'a plus besoin de la texture avec le texte
}
