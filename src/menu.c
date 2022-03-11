#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <unistd.h>

#include "game.h"
#include "mainSDL.h"
#include "linkedlist.h"
#include "card.h"
#include "gameRule.h"
#include "Player.h"

int menu(SDL_Window * pWindow){

  //initialisations de base------------------------------------------------------------------------------------------------------
	// Variable de couleur
	SDL_Color couleurNoire = {0, 0, 0};
	SDL_Color couleurBlanche = {255, 255, 255};
	SDL_Color couleurGold = {255, 215, 0};

	// Le pointeur vers notre police
	TTF_Font* police = NULL;


	//Le pointeur vers la fenetre
	//SDL_Window* pWindow = NULL;


	/* Création de la fenêtre */
	//pWindow = SDL_CreateWindow("univ-arenaaa",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1600, 900, SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE);

	/* renderer */
	SDL_Renderer* renderer_menu = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);

	if(renderer_menu == NULL){
		fprintf(stderr, "Erreur à la création du renderer 1\n");
		exit(EXIT_FAILURE);
	}


  /* Initialisation TTF - POLICE */
	if(TTF_Init() == -1) {
		fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
		exit(EXIT_FAILURE);
	}

	/* Choix de la police */
	if((police = TTF_OpenFont("assets/fonts/NewHiScore.ttf", 20)) == NULL){
		fprintf(stderr, "erreur chargement font\n");
		exit(EXIT_FAILURE);
	}

	/*Surface du bouton jouer en solo*/
	SDL_Surface* txt_optn1_S = TTF_RenderUTF8_Blended(police, "JOUER EN SOLO", couleurNoire);
	SDL_Surface* txt_optn1_Hover_S = TTF_RenderUTF8_Blended(police, "JOUER EN SOLO", couleurGold);

	if(!txt_optn1_S || !txt_optn1_Hover_S){
		fprintf(stderr, "Erreur à la création du texte ''option 1 '': %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	/*Texture du bouton jouer en solo*/
	SDL_Texture *txt_optn1_T = SDL_CreateTextureFromSurface(renderer_menu, txt_optn1_S);
	SDL_Texture *txt_optn1_Hover_T = SDL_CreateTextureFromSurface(renderer_menu, txt_optn1_Hover_S);
	if(!txt_optn1_T || !txt_optn1_Hover_T){
		fprintf(stderr, "Erreur à la création du rendu du texte : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	SDL_FreeSurface(txt_optn1_S); /* on a la texture, plus besoin du texte via surface */
	SDL_FreeSurface(txt_optn1_Hover_S); /* on a la texture, plus besoin du texte via surface */

	SDL_Rect txt_optn1_R;
	txt_optn1_R.x=200;
	txt_optn1_R.y=200;
  txt_optn1_R.w=400;
	txt_optn1_R.h=100;




	/*Surface du bouton quitter*/
	SDL_Surface* txt_optn4_S = TTF_RenderUTF8_Blended(police, "QUITTER ?", couleurNoire);
	SDL_Surface* txt_optn4_Hover_S = TTF_RenderUTF8_Blended(police, "NOOOOOO !", couleurGold);

	if(!txt_optn4_S || !txt_optn4_Hover_S){
		fprintf(stderr, "Erreur à la création du texte ''option 4'': %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	/*Texture du bouton jouer en multi*/
	SDL_Texture *txt_optn4_T = SDL_CreateTextureFromSurface(renderer_menu, txt_optn4_S);
	SDL_Texture *txt_optn4_Hover_T = SDL_CreateTextureFromSurface(renderer_menu, txt_optn4_Hover_S);
	if(!txt_optn4_T || !txt_optn4_T){
		fprintf(stderr, "Erreur à la création du rendu du texte : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	SDL_FreeSurface(txt_optn4_S); /* on a la texture, plus besoin du texte via surface */
	SDL_FreeSurface(txt_optn4_Hover_S); /* on a la texture, plus besoin du texte via surface */

	SDL_Rect txt_optn4_R;
	txt_optn4_R.x=200;
	txt_optn4_R.y=400;
	txt_optn4_R.w=400;
	txt_optn4_R.h=100;



//récupération des données de sauvegarde (quelles cartes possède le joueur / quelles sont toutes les cartes qui existent)-------------------------------------------

	/*carte_t * tab_cartes_total[N]; //tableau qui repertorie toutes les cartes qui existent
	carte_t * tab_sauvegarde[N]; //tableau qui repertorie les cartes que possède le joueur
	init_cartes(tab_cartes_total);
	recup_sauvegarde(tab_sauvegarde, tab_cartes_total);*/

//gestion des evenements---------------------------------------------------------------------------------------------------------------------------------------------
		//oldHover: Variable qui permet d'éviter de render toutes les frames, si pas besoin
		int oldHover=0;

if(pWindow){
  int running = 1;
  while(running) {
    SDL_Event e;
    while(SDL_PollEvent(&e)) {
      switch(e.type) {
        case SDL_QUIT: running = 0;
        break;
        case SDL_WINDOWEVENT:
          switch(e.window.event){
            case SDL_WINDOWEVENT_EXPOSED:
            case SDL_WINDOWEVENT_SIZE_CHANGED:
            case SDL_WINDOWEVENT_RESIZED:
            case SDL_WINDOWEVENT_SHOWN:
              // Le fond de la fenêtre sera blanc
              SDL_SetRenderDrawColor(renderer_menu, 255, 255, 255, 255);
              SDL_RenderClear(renderer_menu);
							//Render de toutes les options du menu principal
							//OPTION 1
							SDL_RenderCopy(renderer_menu, txt_optn1_T, NULL, &txt_optn1_R);
							//OPTION 4
							SDL_RenderCopy(renderer_menu, txt_optn4_T, NULL, &txt_optn4_R);
             //On fait le rendu !
              SDL_RenderPresent(renderer_menu);

            break;
          }
        case SDL_MOUSEBUTTONDOWN:
			printf("x: %i\ny: %i\n",e.button.x,e.button.y);
			if(e.button.x >= txt_optn1_R.x && e.button.x <= txt_optn1_R.x+txt_optn1_R.w && e.button.y >= txt_optn1_R.y && e.button.y <= txt_optn1_R.y+txt_optn1_R.h){
				//Si on clique sur le bouton 1
        printf("Test on clique sur le bouton 1\n\n");

			}
			else if(e.button.x >= txt_optn4_R.x && e.button.x <= txt_optn4_R.x+txt_optn4_R.w && e.button.y >= txt_optn4_R.y && e.button.y <= txt_optn4_R.y+txt_optn4_R.h){
				//Si on clique sur le bouton 4
				running=0; //Quitter le jeu
			}
		case SDL_MOUSEMOTION:
			//SOURIS QUI HOVER SUR LE BOUTON 1
			if(e.button.x >= txt_optn1_R.x && e.button.x <= txt_optn1_R.x+txt_optn1_R.w && e.button.y >= txt_optn1_R.y && e.button.y <= txt_optn1_R.y+txt_optn1_R.h){
				SDL_RenderCopy(renderer_menu, txt_optn1_Hover_T, NULL, &txt_optn1_R);
				SDL_RenderPresent(renderer_menu);
				//oldHover: Variable qui permet d'éviter de render toutes les frames, si pas besoin
				oldHover=1;
			}
			//SOURIS QUI HOVER SUR LE BOUTON 4
			else if(e.button.x >= txt_optn4_R.x && e.button.x <= txt_optn4_R.x+txt_optn4_R.w && e.button.y >= txt_optn4_R.y && e.button.y <= txt_optn4_R.y+txt_optn4_R.h){
				// On clear le render, et on raffiche tout ici, car on modifie le texte du quitter qui devient noooo, sinon même chose que les autres detections 1/2/3
				SDL_RenderClear(renderer_menu);
				SDL_RenderCopy(renderer_menu, txt_optn1_T, NULL, &txt_optn1_R);
				SDL_RenderCopy(renderer_menu, txt_optn4_Hover_T, NULL, &txt_optn4_R);
				//On fait le rendu !
				SDL_RenderPresent(renderer_menu);
				//oldHover: Variable qui permet d'éviter de render toutes les frames, si pas besoin
				oldHover=1;
			}
			//Si on a deja effectué des hovers
			else if(oldHover){
				SDL_RenderClear(renderer_menu);
				//Render de toutes les options du menu principal
				//OPTION 1
				SDL_RenderCopy(renderer_menu, txt_optn1_T, NULL, &txt_optn1_R);
				//OPTION 4
				SDL_RenderCopy(renderer_menu, txt_optn4_T, NULL, &txt_optn4_R);
				//On fait le rendu !
				SDL_RenderPresent(renderer_menu);
				//oldHover: Variable qui permet d'éviter de render toutes les frames, si pas besoin
				oldHover=0;
				printf("Reset actuel\n\n\n");
			}
		break;
    	}
    }
  }
} else {
  fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());
}

//Destruction de la fenetre
SDL_DestroyWindow(pWindow);

TTF_CloseFont(police); //Doit être avant TTF_Quit()
TTF_Quit();
  SDL_Quit();
  return 0;
}

void main() {
  SDL_Window * pWindow = getWindow();
  menu(pWindow);
}
