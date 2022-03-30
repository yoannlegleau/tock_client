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
#include "../bord.h"
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

    int (*pt)(Player *, Bord *);

    int socket;
};

Player * playerFactory( int id);

Player * clientFactory( int id, int socket);

Player * botFactory( int id);

Player * clientServerFactory( int id, int socket);

void drawPlayer(const Player *player);

int play(Player *p, Bord * bord);

int playClient(Player *p, Bord * bord);

int playBot(Player *p, Bord * bord);

int playClientServer(Player *p, Bord * bord);

#endif //TOCK_CLIENT_PLAYER_H
