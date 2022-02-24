//
// Created by adzerake on 23/02/2022.
//

#include <stdio.h>
#include <malloc.h>
#include "Player.h"
#include "card.h"


Player * playerFactory( int id){
    Player * player = malloc(sizeof(Player));
    player->idPlayer = id;
    player->nbPionRantrer = 0;
    player->cards = linkedListFactory(sizeof(enum Card));
    return player;
}

void drawPlayer(const Player *player) {
    printf("player %i: a renter %i pions\n Cartes:%i\n",player->idPlayer,player->nbPionRantrer,length(player->cards));
    drawListe(player->cards,drawCard);
}
