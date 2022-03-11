/**
 * \file game.h
 * \brief gestionaire de partie
 * \author SINGLANDE Thomas
 * \date 20/01/2022
 * \version 1.1
 */

#include <stdio.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <stdbool.h>

#include "game.h"
#include "mainSDL.h"
#include "linkedlist.h"
#include "card.h"
#include "gameRule.h"
#include "Player/player.h"
#include "bord.h"

#include <xmllite.h>

/**
 * \brief Se tableux represente toutes les cases du plateu
 * \details la longeur varie selon le nombre de joueur car chaque jouer posed 18 plus 4 donc pour 4j 88 et 132 pour 6.
 * Les int represantes les ID de chaques jouers
 * \image html assets/img/Tock.io-BordArray.jpg
 */



typedef struct Pawn Pawn;
struct Pawn {
    int IDplayer;
    int location; //index du tableau du plateau (principalement en prevision de l'envoi de données au server)
    bool invincibility;
};

//TODO Trouver une meilleur organisation
typedef struct Rule Rule;
struct Rule {
   bool ruleV;
};

void playOnce(Linkedlist *players);

Linkedlist *getPlayerPansLocation();

void rendererAll(SDL_Renderer *pRenderer);

/**
 * \brief demonstration du fonctionnement des librairie graphiques baser sur l'example de cours
 * \param window fenêtre principal
 */
void gameCreate(SDL_Window *window) {

    bord[88];
    initBord(bord);







    Linkedlist * players = linkedListFactory(sizeof(Player));

    Player * player1 = playerFactory(1);
    bord[0] = 1;
    addLast(players,player1);
    Player * player2 = playerFactory(2);
    bord[18] = 2;
    addLast(players,player2);
    Player * player3 = playerFactory(3);
    bord[36] = 3;
    addLast(players,player3);
    Player * player4 = playerFactory(4);
    bord[54] = 4;
    addLast(players,player4);



    Linkedlist * gamRules = linkedListFactory(sizeof(enum GameRule));

    Linkedlist * cards = linkedListFactory(sizeof(enum Card));


    //printf("cartes:%i\n",length(cards));

    //printf("---- distribution 1 ----\n");

    //printf("cartes restantes:%i\n",length(cards));
    //drawListe(players,drawPlayer);



//Le pointeur vers la surface incluse dans la fenetre
    SDL_Surface *texte=NULL, *image=NULL;
    SDL_Renderer *renderer=NULL;
    SDL_Rect txtDestRect,imgDestRect;


    // Le pointeur vers notre police
    TTF_Font *police = NULL;
    // Une variable de couleur noire



    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == NULL){
        fprintf(stderr, "Erreur à la création du renderer\n");
        exit(EXIT_FAILURE);
    }

    //drawCircle(renderer, 100, 100, 50, couleurBlanc);

    if( (police = TTF_OpenFont("assets/fonts/ChowFun.ttf", 20)) == NULL){
        fprintf(stderr, "erreur chargement font\n");
        exit(EXIT_FAILURE);
    }
    const SDL_Color couleurNoire = {0, 0, 0};
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
                                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                                SDL_RenderCopy(renderer, texte_tex, NULL, &txtDestRect);

                                //dessin du plateux


                                /* Ajout de la seconde image à une certaine position */
                                /*
                                imgDestRect.x = 100;
                                imgDestRect.y = 50;
                                SDL_QueryTexture(image_tex, NULL, NULL, &(imgDestRect.w), &(imgDestRect.h));
                                SDL_RenderCopy(renderer, image_tex, NULL, &imgDestRect);


                                // Ajout de la seconde image à une autre position
                                imgDestRect.x = 250;
                                SDL_RenderCopy(renderer, image_tex, NULL, &imgDestRect);

                                */
                                /* On fait le rendu ! */


                                break;
                        }
                        break;
                }
            }


            Player * p = getFirst(players);
            if (isEmpty(p->cards)){
                if(isEmpty(cards))
                    makeDeck(cards, gamRules);
                distributeCards(cards, players);
            }
            drawPlayer(p);
            //TODO
            //playOnce(players);

            // TODO ajouter l'affichage en simultaner
            //foreach(players,p->play);


            for (int i = 0; i < length(players) ; i++) {
                if(play(get(players,i)))
                    rendererAll(renderer);
            }


        }
    } else {
        fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());
    }
}

void rendererAll(SDL_Renderer *renderer) {
    drawBord(renderer, 394, 64, bord);
    SDL_RenderPresent(renderer);
    Sleep(100);
}

void playOnce(Linkedlist *players) {
    int nbPlayer = length(players);
    Player * p;
    for (int i = 0; i < nbPlayer; i++) {
        p = get(players,i);
        Linkedlist * pownsLocations = getPlayerPansLocation(p);
        bool played = false;
        if (!isEmpty(pownsLocations))
        for (int j = 0; j <= length(p->cards); j++) {
            played = playCard(get(p->cards,j), (int)getFirst(pownsLocations));
            if(played){
                printf("player %i a jouer ",p->idPlayer);
                drawCard(get(p->cards,j));
                removeElem(p->cards,j);

                break;
            }
        }
        if (!played && !isEmpty(p->cards)){
            printf("player %i a jeter ",p->idPlayer);
            drawCard(getFirst(p->cards));
            pollFirst(p->cards);
        }
    }
}



