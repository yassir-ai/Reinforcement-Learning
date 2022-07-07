#include "markov.h"



int main()
{
	int NB_TOURS = 10 ;        
	int score = 0 ;

	srand(time(NULL));

	SDL_Window* window=NULL;
	SDL_Renderer* renderer=NULL;
	SDL_Texture* my_texture=NULL;
	SDL_bool program_on=SDL_TRUE;
	SDL_Event event;

	if (TTF_Init() < 0) end_sdl(0, "Couldn't initialize SDL TTF", window, renderer);
    TTF_Font *font = NULL;                                                                            // la variable 'police de caractère'

    //font = TTF_OpenFont("./BebasNeue-Regular.ttf", 20); // La police à charger, la taille désirée
    font = TTF_OpenFont("./FTTF.ttf", 20); 

    if (font == NULL) end_sdl(0, "Can't load font", window, renderer);

	TTF_SetFontStyle(font, TTF_STYLE_NORMAL);                                         // en gras

	window = SDL_CreateWindow("Chef d'oeuvre: Rock Paper Scissors",
                            SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, 640,
                            480,
                            SDL_WINDOW_OPENGL);
	
	renderer = SDL_CreateRenderer(window, -1,
                                SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	SDL_SetRenderDrawColor(renderer,255, 255, 255,255);
	my_texture = load_texture_from_image("./rockpaperscissor.jpg",window,renderer);                   //chargement d'image

	SDL_Rect destination_rock = {60,330,138,129}; SDL_Rect source_rock = {728,816,1384,1296};                   //arguments de la fonction RenderCopy pour afficher les images 
	SDL_Rect destination_scissor = {260,330,138,129}; SDL_Rect source_scissor = {2112,816,1384,1296};
	SDL_Rect destination_paper = {460,330,138,129}; SDL_Rect source_paper = {3496,816,1384,1296};

	FILE* fichier_markov = fopen("./matrice.txt","r");                  
	float matrice[3][3];  ExtraireMatrice(matrice,fichier_markov);                     // extraire la matrice de Markov
	choix utilisateur = scissor;

	choix machine = rock;                     // choix initialisé de la machine
	SDL_Rect source_choix;                    // choix de l'image dans la sprite sheet  
    SDL_Rect destination={250,-820,130,120};

	int x,y; SDL_bool afficherchoix=SDL_FALSE;

	while((program_on) && (NB_TOURS >= 0) )
	{	
		switch(machine)
         	{
                case 0:
                     source_choix=source_rock; break;
                case 1:
                     source_choix=source_paper; break;
                case 2:
                     source_choix=source_scissor; break;
         	}

		SDL_PollEvent(&event);

		switch(event.type)
		{
			case SDL_QUIT:
				program_on = SDL_FALSE;
				break;
			case SDL_MOUSEBUTTONDOWN:
				x=event.button.x;
				y=event.button.y;
				if(destination_rock.y < y && y < (destination_rock.y + destination_rock.h))
				{
				  if(destination_rock.x < x && x < (destination_rock.x + destination_rock.w))                    //clic sur the rock
				  	 {
						utilisateur=rock; printf("choix utilisateur=%d\n",utilisateur);
						afficherchoix=SDL_TRUE;
						machine = Markov(matrice,machine);                                                        // choix de la machine
				  	 }
				  else if(destination_scissor.x < x && x < (destination_scissor.x + destination_scissor.w))       //clic sur scissor
					  {
						utilisateur=scissor; printf("choix utilisateur=%d\n",utilisateur);
						afficherchoix=SDL_TRUE;
						machine = Markov(matrice,machine);
					  }
				  else if(destination_paper.x < x && x < (destination_paper.x + destination_paper.w)) 		      //clic sur the paper
					   {
						utilisateur=paper; printf("choix utilisateur=%d\n",utilisateur);
						afficherchoix=SDL_TRUE;
						machine = Markov(matrice,machine);
				       }
				}
				break;
		}

		affichage_vie(renderer,window,NB_TOURS,score,font) ;                                      // afficher le niveau de vie et du score

		play_with_texture_3(my_texture,renderer,destination_rock,source_rock);            
		play_with_texture_3(my_texture,renderer,destination_paper,source_paper);            
		play_with_texture_3(my_texture,renderer,destination_scissor,source_scissor);            
        play_with_texture_3(my_texture,renderer,destination,source_choix);

        if(afficherchoix==SDL_TRUE)   
		{ 
			destination.y+=10;                                                               //defilement du choix de la machine
		} 

		if(destination.y>=150)
		{	
			if( ((utilisateur == paper) && (machine==rock )) ||   ((utilisateur == rock) && (machine==scissor)) ||  ((utilisateur == scissor) && (machine==paper))) 
			{
				score++ ;                                                      // dans ces cas on gagne le tour mais pas la guerre ;)
			} 
			 

			SDL_Delay(2000);

			destination.y=-820; afficherchoix=SDL_FALSE;

			NB_TOURS = NB_TOURS - 1 ;                                     // on decremente le compteur
		}
		SDL_Delay(25);
		SDL_RenderClear(renderer);
	}

	//on ferme proprement les programmes 
	SDL_DestroyTexture(my_texture);
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
	return 0;
}
