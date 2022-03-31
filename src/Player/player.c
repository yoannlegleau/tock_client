/**
 * \file Player.c
 * \brief gestion des joueurs
 * \author LE GLEAU Yoann
 * \date 23/02/2022
 * \version 1
 */

#include <stdio.h>
#include <malloc.h>
#include "player.h"
#include "../mainSDL.h"


bool playCard(int idPlayer, Board * board, enum Card * card, ...);
int play(Player *p, Board * board);
int playSmart(Player *p, Board * board);


Player * playerFactory( int id){
    Player * player = malloc(sizeof(Player));
    player->idPlayer = id;
    player->cards = linkedListFactory((void (*)(void *)) destroyCard);
    player->play = &playSmart;
    return player;
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

int playSmart(Player *p, Board * board) {
    const int minint = -2147483648;
    int idPlayer = p->idPlayer, maxh = minint, cardPlayIndex, maxLocation, h = minint, pownLocation;
    enum Card * maxCard;
    if(isWin(board,p->idPlayer))
        idPlayer = getIdTeamMember(board,idPlayer);
    Linkedlist * pownsLocations = getPlayerPawnsLocation(board, idPlayer);
    Board *boardCopy;
    bool played = false;
    printf("\tnbPown:%i nbCard:%i\n",length(pownsLocations),length(p->cards));

    for (int i = length(pownsLocations) ; i >= 0 ; i--) {
        if (get(pownsLocations, i) != NULL)
            pownLocation = *((int*) get(pownsLocations, i));
        else
            pownLocation = -1;
        if(i == 0)
            pownLocation = -1;
        for (int j = 0; j < length(p->cards); j++) {
            boardCopy = boardClone(board);
            //gestion des cartes composé
            if (isComposed(get(p->cards, j))) {
                Linkedlist *compose = getCardCompose(get(p->cards, j));
                int compMaxh = minint,compMaxLocation;
                bool compplayed = false;
                enum Card * compmaxCard = NULL;
                for (int k = 0; k < length(compose); k++){
                    boardCopy = boardClone(board);
                    compplayed = playCard(idPlayer, boardCopy, get(compose, k), pownLocation);
                    if (compplayed) {
                        h = heuristic(boardCopy, idPlayer);
                        //TODO ferifier si onOUt ne casse pas le choi des autres cartes de la main (7.8.9)(les cartes normal)
                        printf("\t\th:%i location:%i carte:%s (%s)\n", h, pownLocation, cardToString((enum Card*)get(p->cards, j)), cardToString(get(compose, k)));
                        if (h > compMaxh) {
                            compMaxh = h;
                            compMaxLocation = pownLocation;
                            compmaxCard = get(compose, k);
                            compplayed = false;
                        }
                    }
                }
                printf("\th:%i location:%i carte:%s (%s)\n",compMaxh, pownLocation, cardToString((enum Card*)get(p->cards, j)), cardToString(compmaxCard));
                if (compMaxh > maxh) {
                    maxh = compMaxh;
                    maxLocation = compMaxLocation;
                    cardPlayIndex = j;
                    maxCard = compmaxCard;
                    played = false;
                }
            } else{
                played = playCard(idPlayer, boardCopy, get(p->cards, j), pownLocation);
                if (played) {
                    h = heuristic(boardCopy, idPlayer);
                    printf("\th:%i location:%i carte:", h, pownLocation);

                    drawCard(get(p->cards, j));
                    if (h > maxh) {
                        maxh = h;
                        maxLocation = pownLocation;
                        maxCard = get(p->cards, j);
                        cardPlayIndex = j;
                        played = false;
                    }
                }
            }
        }
    }

    if (h == minint && !isEmpty(p->cards)){
        printf("player %i a jeter ",p->idPlayer);
        drawCard(getFirst(p->cards));
        pollFirst(p->cards);
    } else {
        playCard(idPlayer, board, maxCard, maxLocation);
        printf("jouer h:%i location:%i carte:",maxh,maxLocation);
        drawCard(get(p->cards, cardPlayIndex));
        removeElem(p->cards, cardPlayIndex);
    }
    return played;
}

bool playCard(int idPlayer, Board *board, enum Card *card, ... ) {
    va_list ap;
            va_start(ap, card);
    int location1 = va_arg(ap, int );
    int location2 = va_arg(ap, int );
    int location3 = va_arg(ap, int );
    int location4 = va_arg(ap, int );

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

int getHeuristic(Board * board, Player * player, enum Card * card){

    return 0;
}