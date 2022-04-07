/**
 * \file game.c
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
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#endif

/* ---------- Includes ---------- */

#include "game.h"
#include "SDL/mainSDL.h"
#include "linkedlist.h"
#include "card.h"
#include "gameRule.h"
#include "Player/player.h"
#include "Color.h"
#include "SDL/Drawable.h"


/* ---------- Sub Declaration ---------- */

/**
 * \brief Affiche une interface dédier au developers pairmeten de visualiser les cartes des adversaires
 * \param renderer De l'écran
 * \param player
 * \param police
 * \param x
 * \param y
 */
void drawPlayerHUD(SDL_Renderer *renderer, Player * player, TTF_Font *police, int x, int y);

void rendererAllPlayerHUD(Game *game);

//TODO Trouver une meilleur organisation
typedef struct Rule Rule;
struct Rule {
    bool ruleV;
};

TTF_Font *police = NULL;



Game * gameCreate(int nbPlayer){
    Game * game = malloc(sizeof(Game));
    game->board = boardFactory(nbPlayer);
    game->players = linkedListFactory((void (*)(void *)) destroyPlayer);
    game->running = false;
}


void addPlayer(Game * game, int nbPlayer){

  int i;
  Player * player;
  for(i = 0; i < nbPlayer; i++){
    player = playerRealFactory(i+1);
    addLast(game->players,player);
  }
  for(i = nbPlayer; i < 4; i++){
    player = playerBotFactory(i+1);
    addLast(game->players,player);
  }
}

/**
 * \brief demonstration du fonctionnement des librairie graphiques baser sur l'example de cours
 * \param window fenêtre principal
 */
int gameStart(Game * game) {

    Linkedlist * gameRules = linkedListFactory(destroyGameRuleVoid);

    Linkedlist * cards = linkedListFactory((void (*)(void *)) destroyCard);

    if(isWinCreat()){
        if( (police = TTF_OpenFont("assets/fonts/NewHiScore.ttf", 30)) == NULL){
            fprintf(stderr, "erreur chargement font\n");
            exit(EXIT_FAILURE);
        }

        //ajout des objets eu drawables
        addDrawable(game->board, (void (*)(void *)) drawBoard);
        for (int i = 0; i < length(game->players) ; i++) {
            addDrawable(get(game->players,i), (void (*)(void *)) drawPlayer);
        }
        //interface de tricheur ^^
        //addDrawable(game,rendererAllPlayerHUD);
    }

    RenderAllDrawable();

    game->running = true;

    int t = 0;
    while(game->running) {
        SDL_Event e;
        while(SDL_PollEvent(&e)) {
            switch(e.type) {
                case SDL_QUIT:
                    game->running = false;
                case SDL_KEYDOWN:
                case SDL_WINDOWEVENT:
                    switch(e.window.event){
                        case SDL_WINDOWEVENT_EXPOSED:
                        case SDL_WINDOWEVENT_SIZE_CHANGED:
                        case SDL_WINDOWEVENT_RESIZED:
                        case SDL_WINDOWEVENT_SHOWN:
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
            p->play(p, game->board);

            if (isWin(game->board, p->idPlayer)&& isWin(game->board, getIdTeamMember(game->board,p->idPlayer))) {
                printf("---------- joueur %i a gagner ----------", p->idPlayer);
                game->running= false;
            }
            RenderAllDrawable();
        #ifdef __unix__
                    sleep(100);
        #endif
        #ifdef _WIN32
                    Sleep(0);
        #endif
        }
    }
    return 0;
}

void rendererAllPlayerHUD(Game *game) {
    SDL_Renderer *renderer = SDLgetRender();
    drawPlayerHUD(renderer,get(game->players,1),police, SDLgetWidth(0.1), SDLgetHeight(0.1));
    drawPlayerHUD(renderer,get(game->players,0),police, SDLgetWidth(0.1), SDLgetHeight(0.7));
    drawPlayerHUD(renderer,get(game->players,2),police, SDLgetWidth(0.7), SDLgetHeight(0.1));
    drawPlayerHUD(renderer,get(game->players,3),police, SDLgetWidth(0.7), SDLgetHeight(0.7));
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

