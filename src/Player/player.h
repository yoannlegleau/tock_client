/**
 * \file Player.h
 * \brief gestion des joueurs
 * \author LE GLEAU Yoann
 * \date 23/02/2022
 * \version 1
 */

#ifndef TOCK_CLIENT_PLAYER_H
#define TOCK_CLIENT_PLAYER_H


#include "../linkedlist.h"
#include "../card.h"
#include "../board.h"
#include "stdbool.h"

/**
 * \brief structure represante un joueur
 */

typedef struct Player Player;
struct Player {
    /** \brief Id unique d'un joueur */
    int idPlayer;

    /** \brief liste de carte representent la main du joueur */
    Linkedlist * cards;

    int (*pt)(Player *, Board *);
};

Player * playerFactory( int id);

void drawPlayer(const Player *player);

int play(Player *p, Board * board);


#endif //TOCK_CLIENT_PLAYER_H
