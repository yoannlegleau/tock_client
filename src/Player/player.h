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

    int (*play)(Player *, Board *);
};

/**
 * \brief Constructeur general de Player
 * \param id idantifien du joueur
 * \return Player nouveux joueur
 * \attention la fonction play n'est pas definie
 */
Player * playerFactory( int id);

/**
 * \brief constructeur de Player avec la fonction d'entres utilisateur
 * \param id idantifient du joueur
 * \return Player crée
 */
Player * playerRealFactory( int id);

/**
 * \brief constructeur de Player avec la fonction d'inteligence artificiel
 * \param id idantifient du joueur
 * \return Player crée
 */
Player * playerBotFactory( int id);

/**
 * \brief duplique un joueur avec sont id et c'est cartes
 * \param p
 * \return Player copie du joueur
 */
Player * playerClone(Player * p);

void drawPlayer(const Player *player);

void drawMainPlayerHUD(Player * player,...);

void destroyPlayerVoid(void * player);

void destroyPlayer(Player ** player);

/**
 * \brief efectuer l'action d'une carte sur un ou plusieurs pion sur un plateau
 * \param idPlayer idantifien du joueur
 * \param board plateau
 * \param card carte a jouer
 * \param ... int coordonner du/des pions concerner par la carte
 * \return bool vrais si la carte a bien pue aitre jouer
 */
bool playCard(int idPlayer, Board * board, enum Card * card, ...);

#endif //TOCK_CLIENT_PLAYER_H
