/**
 * \file game.h
 * \brief gestionaire de partie
 * \author SINGLANDE Thomas
 * \date 20/01/2022
 * \version 1
 * \image html assets\img\appState.png
 */

#ifndef TOCK_CLIENT_GAME_H
#define TOCK_CLIENT_GAME_H

#include "bord.h"

typedef struct Game Game;
struct Game {
    Bord * bord;
    Linkedlist * players;
};

/**
 * \brief initialise la liste
 */
Game * gameCreate(int nbPlayer);

/**
 * \brief ajoute des joueur a la partie
 * \param game
 * \param nbPlayer
 */
void addPlayer(Game * game, int nbPlayer);

/**
 * \brief lancer le deroulement du jeux
 */
int gameStart(Game* game);

/**
 * \brief reprande le jeu apres une pause
 */
void gameResume();

/**
 * \brief metre en pose le jeux
 */
void gamePause();

/**
 * \brief arreter le jeux (posible start pour une nouvelle partie)
 */
void gameStop();

/**
 * \brief libere toutes les variable
 */
void gameDestroy();


#endif //TOCK_CLIENT_GAME_H