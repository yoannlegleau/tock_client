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


bool playCard(Player *p, Board * board, enum Card * card, int location );
int playSmart(Player *p, Board * board);


Player * playerFactory( int id){
    Player * player = malloc(sizeof(Player));
    player->idPlayer = id;
    player->cards = linkedListFactory();
    player->pt = &playSmart;
    return player;
}

void drawPlayer(const Player *player) {
    printf("player %i:\n Cartes:%i\n",player->idPlayer,length(player->cards));
    foreach(player->cards,drawCard);
}

int play(Player *p, Board * board) {
    Linkedlist * pownsLocations = getPlayerPawnsLocation(board, p->idPlayer);
    bool played = false;
    for (int i = length(pownsLocations) ; i >= 0 ; i--) {
        int pownLocation = (int) get(pownsLocations, i);
        for (int j = 0; j <= length(p->cards); j++) {
            played = playCard(p, board, get(p->cards, j), pownLocation);
            if (played) {
                //printf("player %i a jouer ", p->idPlayer);
                //drawCard(get(p->cards, j));
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
    Linkedlist * pownsLocations = getPlayerPawnsLocation(board, p->idPlayer);
    Board *boardCopy = boardClone(board);
    bool played = false;
    int pownLocation,h;

    int maxh = -2147483648  , maxi , maxj;

    for (int i = length(pownsLocations) ; i >= 0 ; i--) {
        pownLocation = (int) get(pownsLocations, i);
        for (int j = 0; j <= length(p->cards); j++) {
            played = playCard(p, boardCopy, get(p->cards, j), pownLocation);
            if (played) {
                h = heuristic(boardCopy, p->idPlayer);
                if (h > maxh){
                    maxh = h;
                    maxi = i;
                    maxj = j;
                }
            }
        }
    }
    if (!played && !isEmpty(p->cards)){
        printf("player %i a jeter ",p->idPlayer);
        drawCard(getFirst(p->cards));
        pollFirst(p->cards);
    } else {
        playCard(p, board, get(p->cards, maxj), (int) get(pownsLocations, maxi));
        removeElem(p->cards, maxj);
    }
    return played;
}

bool playCard(Player *p, Board *board, enum Card *card, int location) {
    switch (*card) {
        case one:
            return forward(board, location, 1);
        case two:
            return forward(board, location, 2);
        case three:
            return forward(board, location, 3);
        case four:
            return forward(board,location, 4);
        case five:
            return forward(board,location, 5);
        case six:
            return forward(board, location, 6);
        case seven:
            return forward(board, location, 7);
        case eight:
            return forward(board, location, 8);
        case nine:
            return forward(board, location, 9);
        case ten:
            return forward(board, location, 10);
        case eleven:
            return forward(board, location, 11);
        case twelve:
            return forward(board, location, 12);
        case thirteen:
            return forward(board, location, 13);
        case thirteen_out:
            if(outPawn(board, p->idPlayer))
                return true;
            if(forward(board, location, 13))
                return true;
        default:
            return false;
    }
}

int getHeuristic(Board * board, Player * player, enum Card * card){

    return 0;
}