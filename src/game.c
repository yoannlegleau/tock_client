/**
 * \file game.h
 * \brief gestionaire de partie
 * \author SINGLANDE Thomas
 * \date 20/01/2022
 * \version 1.1
 */

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
#include "Player/player.h"
#include "bord.h"

//#include <xmllite.h>

/**
 * \brief Se tableux represente toutes les cases du plateu
 * \details la longeur varie selon le nombre de joueur car chaque jouer posed 18 plus 4 donc pour 4j 88 et 132 pour 6.
 * Les int represantes les ID de chaques jouers
 * \image html assets/img/Tock.io-BordArray.jpg
 */

void drawPlayerHUD(SDL_Renderer *renderer, Player * player, TTF_Font *police, int x, int y);

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

SDL_Rect txtDestRect,imgDestRect;
TTF_Font *police = NULL;
SDL_Texture *image_tex;
Linkedlist *players;

void playOnce(Linkedlist *players);

Linkedlist *getPlayerPansLocation();

void rendererAll(SDL_Renderer *pRenderer);

/**
 * \brief demonstration du fonctionnement des librairie graphiques baser sur l'example de cours
 * \param window fenêtre principal
 */
void gameCreate(SDL_Window *window, SDL_Renderer* renderer) {
  SDL_RenderClear(renderer);

    bord[88];
    initBord(bord);


    players = linkedListFactory(sizeof(Player));

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



    // Le pointeur vers notre police
    // Une variable de couleur noire





    if( (police = TTF_OpenFont("assets/fonts/NewHiScore.ttf", 30)) == NULL){
        fprintf(stderr, "erreur chargement font\n");
        exit(EXIT_FAILURE);
    }

    // load sample.png into image

    SDL_RWops *rwop=SDL_RWFromFile("assets/Design_Cartes/Carte_2.png", "rb");
    image=IMG_LoadPNG_RW(rwop);
    if(!image) {
        printf("IMG_LoadPNG_RW: %s\n", IMG_GetError());
    }

    image_tex = SDL_CreateTextureFromSurface(renderer, image);
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

                                //dessin du plateux


                                /* Ajout de la seconde image à une certaine position */
                                imgDestRect.y = 600;
                                imgDestRect.x = 640;
                                SDL_QueryTexture(image_tex, NULL, NULL, &(imgDestRect.w), &(imgDestRect.h));


                                // Ajout de la seconde image à une autre position
                                SDL_RenderCopy(renderer, image_tex, NULL, &imgDestRect);


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
                play(get(players,i));
                rendererAll(renderer);
            }

        }
    } else {
        fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());
    }
}

void rendererAll(SDL_Renderer *renderer) {
    drawPlayerHUD(renderer,get(players,0),police, 10, 40);
    drawPlayerHUD(renderer,get(players,1),police, 10, 500);
    drawPlayerHUD(renderer,get(players,2),police, 1000, 40);
    drawPlayerHUD(renderer,get(players,3),police, 1000, 500);
    drawBord(renderer, 394, 64, bord);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderCopy(renderer, image_tex, NULL, &imgDestRect);

    drawBord(renderer, 394, 64, bord);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);

    #ifdef __unix__
      sleep(1);
    #endif
    #ifdef _WIN32
      Sleep(100);
    #endif
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

void drawPlayerHUD(SDL_Renderer *renderer, Player * player, TTF_Font *police, int x, int y) {
    char output[1024];
    char carte[1024];
    SDL_Surface *texte=NULL;
    SDL_Rect txtDestRect;
    int *card;
    txtDestRect.x = x;
    txtDestRect.y = y;
    const SDL_Color couleurNoire = {0, 0, 0};

    snprintf(output,1024,"Player numéro : %d",player->idPlayer);
    texte = TTF_RenderUTF8_Blended(police, output, couleurNoire);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_Texture *texte_tex = SDL_CreateTextureFromSurface(renderer, texte);
    SDL_FreeSurface(texte);
    SDL_QueryTexture(texte_tex, NULL, NULL, &(txtDestRect.w), &(txtDestRect.h));
    SDL_RenderCopy(renderer, texte_tex, NULL, &txtDestRect);
    for (int j = 0; j < length(player->cards); j++) {
        txtDestRect.y += 30;
        card = get(player->cards,j);
        snprintf(carte,1024,"Carte numéro %d : %d",j,*card);
        texte = TTF_RenderUTF8_Blended(police, carte, couleurNoire);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_Texture *test = SDL_CreateTextureFromSurface(renderer, texte);
        SDL_FreeSurface(texte);
        SDL_QueryTexture(test, NULL, NULL, &(txtDestRect.w), &(txtDestRect.h));
        SDL_RenderCopy(renderer, test, NULL, &txtDestRect);
    }

}
