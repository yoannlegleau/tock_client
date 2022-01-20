/**
 * \file game.c
 * \author LE GLEAU yoann
 * \date 20/01/2022
 */

#include <stdio.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include "game.h"
#include "mainSDL.h"

#define EXIT_FAILURE 0

/**
 * \brief demonstration du fonctionnement des librairie graphiques baser sur l'example de cours
 * \param window fenêtre principal
 */
void gameCreate(SDL_Window *window) {
//Le pointeur vers la surface incluse dans la fenetre
    SDL_Surface *texte=NULL, *image=NULL;
    SDL_Renderer *renderer=NULL;
    SDL_Rect txtDestRect,imgDestRect;

    // Le pointeur vers notre police
    TTF_Font *police = NULL;
    // Une variable de couleur noire
    SDL_Color couleurNoire = {0, 0, 0};


    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == NULL){
        fprintf(stderr, "Erreur à la création du renderer\n");
        exit(EXIT_FAILURE);
    }


    if( (police = TTF_OpenFont("assets/fonts/ChowFun.ttf", 20)) == NULL){
        fprintf(stderr, "erreur chargement font\n");
        exit(EXIT_FAILURE);
    }
    texte = TTF_RenderUTF8_Blended(police, "Vive la programmation !", couleurNoire);
    if(!texte){
        fprintf(stderr, "Erreur à la création du texte : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_Texture *texte_tex = SDL_CreateTextureFromSurface(renderer, texte);
    if(!texte_tex){
        fprintf(stderr, "Erreur à la création du rendu du texte : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_FreeSurface(texte); /* on a la texture, plus besoin du texte */
    /* Position ou sera mis le texte dans la fenêtre */
    txtDestRect.x = txtDestRect.y = 10;
    SDL_QueryTexture(texte_tex, NULL, NULL, &(txtDestRect.w), &(txtDestRect.h));

    // load sample.png into image
    SDL_RWops *rwop=SDL_RWFromFile("assets/img/controleur1024.png", "rb");
    image=IMG_LoadPNG_RW(rwop);
    if(!image) {
        printf("IMG_LoadPNG_RW: %s\n", IMG_GetError());
    }
    SDL_Texture *image_tex = SDL_CreateTextureFromSurface(renderer, image);
    if(!image_tex){
        fprintf(stderr, "Erreur a la creation du rendu de l'image : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_FreeSurface(image); /* on a la texture, plus besoin de l'image */




    if( window )
    {
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
                                /* Le fond de la fenêtre sera blanc */
                                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                                SDL_RenderClear(renderer);

                                /* Ajout du texte en noir */
                                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                                SDL_RenderCopy(renderer, texte_tex, NULL, &txtDestRect);

                                /* Ajout de la seconde image à une certaine position */
                                imgDestRect.x = 100;
                                imgDestRect.y = 50;
                                SDL_QueryTexture(image_tex, NULL, NULL, &(imgDestRect.w), &(imgDestRect.h));
                                SDL_RenderCopy(renderer, image_tex, NULL, &imgDestRect);

                                /* Ajout de la seconde image à une autre position */
                                imgDestRect.x = 250;
                                SDL_RenderCopy(renderer, image_tex, NULL, &imgDestRect);

                                /* On fait le rendu ! */
                                SDL_RenderPresent(renderer);

                                break;
                        }
                        break;
                }
            }
        }
    } else {
        fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());
    }
}
