//
// Created by adzerake on 23/02/2022.
//

#ifndef TOCK_CLIENT_PLAYER_H
#define TOCK_CLIENT_PLAYER_H


#include "linkedlist.h"

/**
 * \brief structure represante un joueur
 */

typedef struct Player Player;
struct Player {
    /** \brief Id unique d'un joueur */
    int idPlayer;

    /** \brief nombre de pion que le joueur a reusit a meter dans l'arriver */
    int nbPionRantrer; //TODO trouver un meilleur nom

    /** \brief liste de carte representent la main du joueur */
    Linkedlist * cards;
};

Player * playerFactory( int id);

void drawPlayer(const Player *player);

//TODO player destroyPlayer

#endif //TOCK_CLIENT_PLAYER_H
