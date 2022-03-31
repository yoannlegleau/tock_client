/**
 * \file Player.c
 * \brief gestion des joueurs
 * \author LE GLEAU Yoann
 * \date 23/02/2022
 * \version 1
 */

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <SDL2/SDL_image.h>
#include "player.h"
#include "../mainSDL.h"
#include "PlayerBot.c"
#include "PlayerReal.c"



int play(Player *p, Board * board);

Player * playerFactory( int id){
    Player * player = malloc(sizeof(Player));
    player->idPlayer = id;
    player->cards = linkedListFactory((void (*)(void *)) destroyCard);
    return player;
}

Player * playerClone(Player * p){
    Player * clone = playerFactory(p->idPlayer);
    clone->play = p->play;
    Linkedlist *cardsClone = linkedListFactory((void (*)(void *)) destroyCard);
    enum Card*card;
    for (int i = 0; i < length(p->cards); i++) {
        card = malloc(sizeof(enum Card*));
        *card = *((enum Card*)(get(p->cards,i)));
        addFirst(cardsClone, card);
    }
    clone->cards = cardsClone;
    return clone;
}

void destroyPlayerVoid(void * player){
    destroyPlayer(player);
}

void destroyPlayer(Player ** player){
    destroyLinkedList((*player)->cards);
    free(*player);
}

void drawPlayer(const Player *player) {
    printf("player %i:\n Cartes:%i\n",player->idPlayer,length(player->cards));
    foreach(player->cards,drawCard);
}

void drawMainPlayerHUD(Player * player,...){
    va_list ap;
            va_start(ap, player);
    int highlight = va_arg(ap, int );
    int const defaultHighlight = -858993460;

    SDL_Texture *image_tex;
    SDL_Rect imgDestRect ;
    SDL_Surface *image=NULL;
    int center = SDLgetWidth(0.5);
    int bottom = SDLgetHeight(1);
    int cardx = 160;
    int cardy = 240;
    int idealCardy = SDLgetHeight(0.2);
    int idealCardx = ((float)cardx/(float)cardy)*idealCardy;
    int cardslen = idealCardx*length(player->cards);
    int xStart = center - (cardslen/2) ;
    int yStart = bottom - idealCardy;
    float highlightOfset = 0.025;

    imgDestRect.y = yStart;
    imgDestRect.w = 10;

    for (int i = 0; i < length(player->cards); i++) {

        imgDestRect.x = xStart + (idealCardx*i);
        if (defaultHighlight != highlight && i == highlight)
            imgDestRect.y = yStart - SDLgetHeight(highlightOfset);
        else
            imgDestRect.y = yStart;

        const char *path = getAsset(get(player->cards,i));
        SDL_RWops *rwop=SDL_RWFromFile(path , "rb");
        image=IMG_LoadPNG_RW(rwop);
        if(!image) {
            printf("IMG_LoadPNG_RW: %s\n", IMG_GetError());
        }

        image_tex = SDL_CreateTextureFromSurface(SDLgetRender(), image);
        if(!image_tex){
            printf("test");
            fprintf(stderr, "Erreur a la creation du rendu de l'image : %s\n", SDL_GetError());
            exit(EXIT_FAILURE);
        }



        SDL_QueryTexture(image_tex, NULL, NULL, &(imgDestRect.w), &(imgDestRect.h));
        imgDestRect.h = idealCardy;
        imgDestRect.w = idealCardx;
        SDL_RenderCopy(SDLgetRender(), image_tex, NULL, &imgDestRect);
        SDL_FreeSurface(image);
        SDL_DestroyTexture(image_tex);
    }


}

int play(Player *p, Board * board) {
    Linkedlist * pownsLocations = getPlayerPawnsLocation(board, p->idPlayer);
    bool played = false;
    int pownLocation;
    for (int i = length(pownsLocations) ; i >= 0 ; i--) {
        if (get(pownsLocations, i) != NULL)
            pownLocation = *((int*) get(pownsLocations, i));
        else
            pownLocation = -1;
        for (int j = 0; j <= length(p->cards); j++) {
            played = playCard(p, board, get(p->cards, j), pownLocation);
            if (played) {
                removeElem(p->cards, j);
                return true;
            }
        }
    }
    if (!played && !isEmpty(p->cards)){
        printf("player %i a jeter ",p->idPlayer);
        drawCard(getFirst(p->cards));
        pollFirst(p->cards);
    }
    return false;
}

bool isCardPlayable(Player *p, Board *board ,enum Card* card){
    Board *boardCopy = boardClone(board);
    Player *playerCopy = playerClone(p);
    clear(playerCopy->cards);

    enum Card * cardCopy = malloc(sizeof(enum Card*));
    *cardCopy = *card;
    addFirst(playerCopy->cards,cardCopy);

    return playSmart(playerCopy,boardCopy);
    /*
    va_list ap;
            va_start(ap, card);
    int location1 = va_arg(ap, int );
    int location2 = va_arg(ap, int );

    if (!isComposed(card)) {
        return playCard(idPlayer, boardCopy, card, location1,location2);
    } else{
        Linkedlist *compose = getCardCompose(card);
        bool compplayed = false;
        for (int i = 0; i < length(compose); i++){
            if (isComposedSplittable(card))
                boardCopy = boardClone(board);
            compplayed = playCard(idPlayer, boardCopy, get(compose, i), location1,location2);
            if (compplayed && isComposedSplittable(card))
                break;
            if (!compplayed && !isComposedSplittable(card))
                break;
        }
        destroyLinkedList(compose);
        return compplayed;
    }
    */
}

bool playCard(int idPlayer, Board *board, enum Card *card, ... ) {
    va_list ap;
            va_start(ap, card);
    int location1 = va_arg(ap, int );
    int location2 = va_arg(ap, int );

    switch (*card) {
        case one:
            return forward(board, location1, 1);
        case two:
            return forward(board, location1, 2);
        case three:
            return forward(board, location1, 3);
        case four:
            return backward(board,location1, 4);
        case five:
            return forward(board,location1, 5);
        case six:
            return forward(board, location1, 6);
        case seven:
            return forward(board, location1, 7);
        case eight:
            return forward(board, location1, 8);
        case nine:
            return forward(board, location1, 9);
        case ten:
            return forward(board, location1, 10);
        case eleven:
            return forward(board, location1, 11);
        case twelve:
            return forward(board, location1, 12);
        case thirteen:
            return forward(board, location1, 13);
        case out:
            return outPawn(board, idPlayer);
        default:
            return false;
    }
}

