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
#include "Color.h"


#include <xmllite.h>

/**
 * \brief Se tableux represente toutes les cases du plateu
 * \details la longeur varie selon le nombre de joueur car chaque jouer posed 18 plus 4 donc pour 4j 88 et 132 pour 6.
 * Les int represantes les ID de chaques jouers
 * \image html assets/img/Tock.io-BoardArray.jpg
 */

void drawPlayerHUD(SDL_Renderer *renderer, Player * player, TTF_Font *police, int x, int y);
void drawMainOpponentHUD(SDL_Renderer *renderer, Player * player);
void drawMainPlayerHUD(SDL_Renderer *renderer, Player * player);
void rendererAll(Game *game, SDL_Renderer *pRenderer);


//TODO Trouver une meilleur organisation
typedef struct Rule Rule;
struct Rule {
    bool ruleV;
};

TTF_Font *police = NULL;



Game * gameCreate(int nbPlayer){
    Game * game = malloc(sizeof(Game));
    game->board = boardFactory(nbPlayer);
    game->players = linkedListFactory();
    return game;
}

void addPlayer(Game * game, int nbPlayer){
  int i;
  Player * player;
  for(i = 0; i < nbPlayer; i++){
    player = playerFactory(i+1);
    addLast(game->players,player);
  }
  for(i = nbPlayer; i < 4; i++){
    player = playerFactory(i+1);
    addLast(game->players,player);
  }
}

/**
 * \brief demonstration du fonctionnement des librairie graphiques baser sur l'example de cours
 * \param window fenêtre principal
 */
int gameStart(Game * game) {

    Linkedlist * gameRules = linkedListFactory();

    Linkedlist * cards = linkedListFactory();


    //printf("cartes:%i\n",length(cards));

    //printf("---- distribution 1 ----\n");

    //printf("cartes restantes:%i\n",length(cards));
    //foreach(game->players,drawPlayer);



//Le pointeur vers la surface incluse dans la fenetre
    SDL_Renderer *renderer=NULL;


    // Le pointeur vers notre police
    // Une variable de couleur noire



    if(isWinCreat()){

        renderer = SDL_GetRenderer(window);

        if( (police = TTF_OpenFont("assets/fonts/NewHiScore.ttf", 30)) == NULL){
            fprintf(stderr, "erreur chargement font\n");
            exit(EXIT_FAILURE);
        }


    }
    int running = 1;
    while(running) {
        SDL_Event e;
        while(SDL_PollEvent(&e)) {
            switch(e.type) {
                case SDL_QUIT:
                    running = 0;
                    return 1;
                case SDL_KEYDOWN:
                case SDLK_END:
                    return -1;
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

                            // Ajout de la seconde image à une autre position



                            /* On fait le rendu ! */


                            break;
                    }
                    break;
            }
        }
        Player * p = getFirst(game->players);
        if (isEmpty(p->cards)){
            if(isEmpty(cards))
                makeDeck(cards, gameRules);
            distributeCards(cards, game->players);
        }


        for (int i = 0; i < length(game->players) ; i++) {
            p = get(game->players, i);
            play(p, game->board);
            if (isWin(game->board, p->idPlayer)) {
                printf("---------- joueur %i a gagner ----------", p->idPlayer);
                return p->idPlayer;
            }
            if(isWinCreat())
                rendererAll(game,renderer);
        }

    }
    return 0;
}

void rendererAll(Game *game, SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderDrawLine(renderer, SDLgetWidth(0.5),0,SDLgetWidth(0.5),SDLgetHeight(1)),
    SDL_RenderDrawLine(renderer,0,SDLgetHeight(0.5),SDLgetWidth(1),SDLgetHeight(0.5)),

    drawMainPlayerHUD(renderer,get(game->players,0));
    drawMainOpponentHUD(renderer, get(game->players,2));

    drawPlayerHUD(renderer,get(game->players,0),police, 10, 40);
    drawPlayerHUD(renderer,get(game->players,1),police, 10, 500);
    drawPlayerHUD(renderer,get(game->players,2),police, 1000, 40);
    drawPlayerHUD(renderer,get(game->players,3),police, 1000, 500);

    drawBoard(game->board,renderer);

    SDL_Color background = getSDLColor("Background");
    SDL_SetRenderDrawColor(renderer, background.r , background.g , background.b,background.a );
    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);

#ifdef __unix__
    sleep(100);
#endif
#ifdef _WIN32
    //Sleep(100);
#endif
}



void drawPlayerHUD(SDL_Renderer *renderer, Player * player, TTF_Font *police, int x, int y) {
    char output[1024];
    char carte[1024];
    SDL_Surface *texte=NULL;
    SDL_Rect txtDestRect;
    int *card;
    txtDestRect.x = x;
    txtDestRect.y = y;
    const SDL_Color couleurNoire = getSDLColor("Text");

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

void drawMainPlayerHUD(SDL_Renderer *renderer, Player * player){
    //FIXME centre les cartes
    SDL_Texture *image_tex;
    SDL_Rect imgDestRect ;
    SDL_Surface *image=NULL;
    int center = 1280/2;
    int bottom = 720;
    int cardx = 80;
    int cardy = 120;
    int cardslen = cardx*length(player->cards);
    int xStart = center - (cardslen/2) ;
    int yStart = bottom - cardy;

    imgDestRect.y = yStart;
    imgDestRect.w = 10;

    for (int i = 0; i < length(player->cards); i++) {

        imgDestRect.x = xStart + (cardx*i);

        const char *path = getAsset(get(player->cards,i));
        SDL_RWops *rwop=SDL_RWFromFile(path , "rb");
        image=IMG_LoadPNG_RW(rwop);
        if(!image) {
            printf("IMG_LoadPNG_RW: %s\n", IMG_GetError());
        }

        image_tex = SDL_CreateTextureFromSurface(renderer, image);
        if(!image_tex){
            fprintf(stderr, "Erreur a la creation du rendu de l'image : %s\n", SDL_GetError());
            exit(EXIT_FAILURE);
        }


        SDL_QueryTexture(image_tex, NULL, NULL, &(imgDestRect.w), &(imgDestRect.h));
        SDL_RenderCopy(renderer, image_tex, NULL, &imgDestRect);
        SDL_FreeSurface(image);
        SDL_DestroyTexture(image_tex);
    }


}

void drawMainOpponentHUD(SDL_Renderer *renderer, Player * player){
    SDL_Texture *image_tex;
    SDL_Rect imgDestRect ;
    SDL_Surface *image=NULL;
    int center = 1280/2;
    int bottom = 720;
    int cardx = 80;
    int cardy = 120;
    int ofset = 20;

    int cardslen = cardx*length(player->cards) - (ofset* (length(player->cards) - 1));
    int xStart = center - (cardslen/2);
    int yStart = bottom - cardy;

    imgDestRect.y = -80;


    for (int i = 0; i < length(player->cards); i++) {

        imgDestRect.x = xStart + (cardx*i) - (ofset*i);
        imgDestRect.w = i;

        SDL_RWops *rwop=SDL_RWFromFile(getAsset(NULL) , "rb");
        image=IMG_LoadPNG_RW(rwop);
        if(!image) {
            printf("IMG_LoadPNG_RW: %s\n", IMG_GetError());
        }

        image_tex = SDL_CreateTextureFromSurface(renderer, image);
        if(!image_tex){
            fprintf(stderr, "Erreur a la creation du rendu de l'image : %s\n", SDL_GetError());
            exit(EXIT_FAILURE);
        }


        SDL_QueryTexture(image_tex, NULL, NULL, &(imgDestRect.w), &(imgDestRect.h));
        SDL_RenderCopy(renderer, image_tex, NULL, &imgDestRect);
        SDL_FreeSurface(image);
        SDL_DestroyTexture(image_tex);

    }


}