/**
 * \file main.c
 * \brief Programme d'apprentisage par renforcement de fin d'année ZZ1.
 * \author Yassir Mrani Alaoui, Oussama Diai, Anas Elhoudri
 * \version Phase 2
 * \date 1 juillet 2022
 *
 * Programme de champs de mines. Un robot (agent) explore un environment dont le but est de trouver l'étoile (état final).
 * Le robot rencontre des bombes, ce qui crée un défis pour lui. Le but de ce programme est de démontrer comment ce robot peut
 * apprendre à arriver à la fin en passant par un chemin optimal.
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <time.h>
#include "code.h"



int main()
{
    srand(time(NULL));
 
    float Q_matrice[NB_ETAT][NB_ACTION] = {0} ;

    float Recomp_matrice[NB_ETAT][NB_ACTION] =    {{-2, -1, -1, -2} ,
                                                    {-2, -5, -1, -1},
                                                    {-2, -1, -1, -1},
                                                    {-2, -1, -1, -1},
                                                    {-2, -5, -2, -1},
                                                    {-1, -1, -5, -2},
                                                    {-1, -1, -1, -1},
                                                    {-1, -1, -1, -5},
                                                    {-1, -1, -5, -1},
                                                    {-1, -1, -2, -1},
                                                    {-1, -1, -1, -2},
                                                    {-5, -5, -1, -1},
                                                    {-1, -1, -1, -1},
                                                    {-1, -5, -1, -1},
                                                    {-5, -1, -2, -1},
                                                    {-1, -5, -5, -2},
                                                    {-1, -1, -1, -1},
                                                    {-1, -1, -5, -5},
                                                    {-1, -1, -1, -1},
                                                    {-1, -1, -2, -5},
                                                    {-1, -1, -1, -2},
                                                    {-5, -1, -1, -5},
                                                    {-1, -1, -1, -1},
                                                    {-5, -1, -1, -1},
                                                    {-1, 15, -2, -1},
                                                    {-5, -2, -1, -2},
                                                    {-1, -2, -1, -1},
                                                    {-1, -2, -1, -1},
                                                    {-1, -2, 15, -1}  ,
                                                    {-1, -2, -2, -1}};

    SDL_Window* window=NULL;
	SDL_Renderer* renderer=NULL;

	SDL_Texture* my_texture=NULL;
	SDL_Texture* my_robot=NULL;                      // pret 
	SDL_Texture* my_robot2=NULL;                     //entrainement
	SDL_Texture* options =NULL;
    SDL_Texture* qui =NULL;
	SDL_Texture* interface =NULL;

    SDL_bool program_on=SDL_TRUE;
    SDL_bool play = SDL_FALSE ;

    SDL_Event event;

    int choix_execution = 0 ;                        //  0 : elle va apprendre     , 1 : elle est deja pret
    int a = 0;                                       // l'etat suivant 
    int etat = 0 ;                                   // l'etat 
    int etat_prec = 0;                               // l'etat courant
    int compteur = 0;                                // compteur d'episode 
    int x=0 , y=0 ;
    int x1 = 0 , y1 = 0 ;
    int click = 0 ;                                  // pour verification du click
    int mouvement = 0 ;                              // compteur de mouvement 
    
    float aleatoir = 0 ;                             //generer un nombre aleatoire entre 0 et 1
    float greedy = 0 ;                               // epsilon de e-greedy : pour le % d'alatoire
    float zoom = 0.24 ;                              //  =  960 / 4000

    action act = 0 ; 
    
    window = SDL_CreateWindow("jeu GOD ROBOT",
                            SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, 960,
                            600,
                            SDL_WINDOW_OPENGL);
	
	renderer = SDL_CreateRenderer(window, -1,
                                SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    //afficher le grille , le robot , l'interface et options
    my_texture = load_texture_from_image("./nv.png",window,renderer);
    my_robot   = load_texture_from_image("./robot.png",window,renderer);
    my_robot2  = load_texture_from_image("./robotJ.png",window,renderer);
    interface  = load_texture_from_image("./interface.png",window,renderer);
    options    = load_texture_from_image("./menu_player.png",window,renderer);

	SDL_Rect destination_grille = {0,0,475,564}; SDL_Rect source_grille = {0,0,1384,1296};
	SDL_Rect destination_robot = {0 ,0 ,95 ,95};  SDL_Rect source_robot = {0,0,600,500};
    SDL_Rect destination_interface = {0,0,960,600}; SDL_Rect source_interface = {0,0,4000,2667};

    qui = my_robot2 ;                          // par defaut : c'est entrainement 

    // gestion d'interface MENU
    while( !play )
     {
       play_with_texture_3(interface ,renderer,destination_interface,source_interface);

        while(SDL_PollEvent(&event))
        {
          switch(event.type)
          {
            case SDL_QUIT:                                     //fermeture du fenetre 
                play = SDL_TRUE ;
                program_on = SDL_FALSE;
                break;

            case SDL_MOUSEBUTTONDOWN  :
                x=event.button.x;
                y=event.button.y;

                if(  ( x < (304 + 796) * zoom )  &&  ( x  > (304 * zoom )))
                {
                    if(  ( y < (968+ 248) * zoom )  &&  ( y > (968 * zoom )  ))                   // bouton play
                    {
                        play = SDL_TRUE ;
                        SDL_SetWindowSize(window,475,564) ;                                 // redimensionner la fenetre                   
                    }  
                    else if(  ( y < (1344 + 248) * zoom )  &&  ( y > (1344 * zoom )  ))           //bouton options
                    {
                        while(click == 0)
                        { 
                            play_with_texture_3(options ,renderer,destination_interface,source_interface);
                            SDL_PollEvent(&event) ;

                            switch(event.type)
                            {
                                case SDL_QUIT:                                     //fermeture du fenetre 
                                    play = SDL_TRUE ;
                                    program_on = SDL_FALSE;
                                    click = 1 ;
                                    break;

                                case SDL_MOUSEBUTTONDOWN  :
                                    x1 =event.button.x;
                                    y1 =event.button.y;
                        
                                    if(  ( y1 < (1828 + 340) * zoom )  &&  ( y1 > (1828 * zoom )  )) 
                                    {
                                        if(  ( x1 < (408 + 980) * zoom )  &&  ( x1  > (408 * zoom )))            // choix 0 :  il va apprendre
                                        {
                                                click = 1 ;
                                                choix_execution = 0 ;
                                                qui = my_robot2 ;                     //robot d'entrainement   
                                        } 
                                        else if(  ( x1 < (2616 + 996) * zoom )  &&  ( x1  > (2616 * zoom )))                   // il est deja NAAAAAADI suiiiiiiiiiiiiiii
                                        {
                                                click = 1 ;
                                                choix_execution = 1 ;
                                                qui = my_robot ;                     //robot pret 
                                        } 
                                        printf("------VOTRE CHOIX D'EXECUTION    EST   %d\n",choix_execution) ;
                                    } 
                                    break ;
                            } 
                        } 
                        click = 0 ;    //pour pouvoir renter dans le MENU
                    } 
                    else if(  ( y < (1696 + 264 )* zoom  ) &&  (y > (1696 * zoom )  ))                  // bouton exit
                    {
                        play = SDL_TRUE ;                                                               // on va quitter le programme 
                        program_on = SDL_FALSE;
                    } 
                } 
                break ;
           }
        }
     }

    //appui sur PLAY sans avoir passer par options 
    if(qui == my_robot2)
    {
            destination_robot.w = 150 ;
            destination_robot.x = -9 ;
    } 


    // gestion d'interface JEU

    while( program_on )
	{	
		SDL_PollEvent(&event);

		switch(event.type)
		{
			case SDL_QUIT:
				program_on = SDL_FALSE;
				break;
		}

        play_with_texture_3(my_texture ,renderer,destination_grille,source_grille);
        play_with_texture_3(qui,renderer,destination_robot,source_robot);

        mouvement++ ;

        //generer un nombre aleatoire entre 0 et 1
        aleatoir = (float)rand() / (float)RAND_MAX ;

        if(choix_execution == 0)                                                        // elle va apprendre depuis le debut
        {
            greedy = suite_epsilon(compteur) ;
        } 
        else                                                                            // = 1  : alors il est pret 
        {
            greedy = 0 ;                                                               // pas d'alatoire , il utilise selement ce qui est aquis dans la Q_table
            lecture_Q_matrice("Qmat_pret.txt",Q_matrice) ;                             
        } 

        if(aleatoir < greedy)
        {
            act = rand() % 4 ;                                                        // generer act alea avec un pourcentage greedy du temps
        } 
        else
        {
            act = max_q_etat(Q_matrice , etat) ;

        } 

        if(etat == 29) 
        {
            compteur++ ;                                                    //MAJ compt

            printf("******* VOUS ETES ARRIVES À VOTRE DESTINATION , IL S'AGIT DE VOTRE EPISODE NUMERO :   %d\n",compteur);

            etat = 0 ;

            destination_robot.x = 0;
            destination_robot.y = 0;

            ecriture_fichier("trainin_Qmat.txt",Q_matrice , compteur) ;
            ecriture_data("data.txt" ,compteur,mouvement-1)   ;

            mouvement = 0 ;                                                  //init compt
        }

         a = progress_etat(etat,act) ; 

         etat_prec = etat ;                                                    // svg etat prec
         etat = a!=100 ? a : etat ;                                            // gestion de cas limite 

         qualite_des_actions(Q_matrice , Recomp_matrice,etat_prec,etat,act) ;   // MAJ de Q table 
        
        
        // gestion du cas non limite
        if(a != 100)
        {
            //mouvement en graphique 
            switch(act)  
            {
                case up :
                    destination_robot.y-= 95 ;
                    break ;
                case down :
                    destination_robot.y += 95 ;
                    break ;
                case right :
                    destination_robot.x += 97 ;
                    break ;
                case left :
                    destination_robot.x -= 97 ;
                    break ;
            } 
        } 
        
        SDL_Delay(40) ;
		SDL_RenderClear(renderer);
	}

    // une fermeture bien propre ;)
	SDL_DestroyTexture(my_texture);
	SDL_DestroyTexture(my_robot);
	SDL_DestroyTexture(my_robot2);
	SDL_DestroyTexture(options);
	SDL_DestroyTexture(interface);
	SDL_DestroyTexture(qui);

	IMG_Quit();
	SDL_Quit();

    return 0 ;
} 
