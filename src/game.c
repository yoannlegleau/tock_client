/**
 * \file game.h
 * \brief gestionaire de partie
 * \author SINGLANDE Thomas
 * \date 20/01/2022
 * \version 1.1
 */
#include <unistd.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>

#include "game.h"
#include "mainSDL.h"
#include "linkedlist.h"
#include "card.h"
#include "gameRule.h"
#include "Player/player.h"



/**
 * \brief Se tableux represente toutes les cases du plateu
 * \details la longeur varie selon le nombre de joueur car chaque jouer posed 18 plus 4 donc pour 4j 88 et 132 pour 6.
 * Les int represantes les ID de chaques jouers
 * \image html assets/img/Tock.io-BordArray.jpg
 */

void drawPlayerHUD(SDL_Renderer *renderer, Player * player, TTF_Font *police, int x, int y);
void rendererAll(Game *game, SDL_Renderer *pRenderer);


//TODO Trouver une meilleur organisation
typedef struct Rule Rule;
struct Rule {
    bool ruleV;
};

SDL_Rect txtDestRect,imgDestRect;
TTF_Font *police = NULL;
SDL_Texture *image_tex;


Game * gameCreate(int nbPlayer){
    Game * game = malloc(sizeof(Game));
    game->bord = bordFactory(nbPlayer);
    game->players = linkedListFactory(sizeof(Player));
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

void addPlayerClient(Game * game, int nbPlayer, int socket){
  int i;
  Player * player;
  printf("NB Player : %i\n", nbPlayer);
  printf("Socket ID : %i\n", socket);
  player = clientFactory(nbPlayer,socket);
  addLast(game->players,player);
}

void addPlayerClientServer(Game * game, int nbPlayer, int socket){
  int i;
  Player * player;
  for(i = 1; i < nbPlayer; i++){
    player = clientServerFactory(i+1,socket);
    addLast(game->players,player);
  }
}

void addPlayerBot(Game * game, int nbPlayer){
  int i;
  Player * player;
  for(i = nbPlayer; i < 4; i++){
    player = botFactory(i+1);
    addLast(game->players,player);
  }
}

/**
 * \brief demonstration du fonctionnement des librairie graphiques baser sur l'example de cours
 * \param window fenêtre principal
 */
void gameStart(Game * game) {

    Linkedlist * gamRules = linkedListFactory(sizeof(enum GameRule));

    Linkedlist * cards = linkedListFactory(sizeof(enum Card));

    //printf("cartes:%i\n",length(cards));

    //printf("---- distribution 1 ----\n");

    //printf("cartes restantes:%i\n",length(cards));
    //foreach(game->players,drawPlayer);



//Le pointeur vers la surface incluse dans la fenetre
    SDL_Surface *texte=NULL, *image=NULL;
    SDL_Renderer *renderer=NULL;


    // Le pointeur vers notre police
    // Une variable de couleur noire



    if(isWinCreat()){
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if(renderer == NULL){
            fprintf(stderr, "Erreur à la création du renderer\n");
            exit(EXIT_FAILURE);
        }

        if( (police = TTF_OpenFont("assets/fonts/NewHiScore.ttf", 30)) == NULL){
            fprintf(stderr, "erreur chargement font\n");
            exit(EXIT_FAILURE);
        }

        // load sample.png into image

        SDL_RWops *rwop=SDL_RWFromFile("assets/Carte_2.png", "rb");
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
    }
    int running = 1;
    while(running) {
        SDL_Event e;
        while(SDL_PollEvent(&e)) {
            switch(e.type) {
                case SDL_QUIT: running = 0;
                    return;
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
        Player * p = getFirst(game->players);

        if (isEmpty(p->cards)){
            if(isEmpty(cards)){
                makeDeck(cards, gamRules);;
            }
            distributeCards(cards, game->players);
        }
        for(int i = 0; i < length(game->players); i++){
          Player * pp = get(game->players, i);
          if(pp->socket != 0){
            char output[64];
            snprintf(output,64,"CARD ");
            for(int j = 0 ; j < length(pp->cards); j++){
              output = strcat(output,itoa(*((int*)(get(pp->cards, j)))));
              output = strcat(output," ");
            }
            send(p->socket,output,64,0);
          }
        }
        //drawPlayer(p);
        //TODO
        //playOnce(players);

        // TODO ajouter l'affichage en simultaner
        //foreach(players,p->play);

        for (int i = 0; i < length(game->players) ; i++) {
            p = get(game->players, i);
            p->pt(p, game->bord);
            if(isWin(game->bord,p->idPlayer))
                return ;
            rendererAll(game,renderer);
        }

    }
}

void rendererAll(Game *game, SDL_Renderer *renderer) {
    drawPlayerHUD(renderer,get(game->players,0),police, 10, 40);
    drawPlayerHUD(renderer,get(game->players,1),police, 10, 500);
    drawPlayerHUD(renderer,get(game->players,2),police, 1000, 40);
    drawPlayerHUD(renderer,get(game->players,3),police, 1000, 500);
    drawBord(game->bord,renderer, 394, 64);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderCopy(renderer, image_tex, NULL, &imgDestRect);

    drawBord(game->bord,renderer, 394, 64);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);

#ifdef __unix__
    usleep(1);
#endif
#ifdef _WIN32
    Sleep(100);
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
