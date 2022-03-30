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

#include "board.h"

typedef struct Game Game;
struct Game {
    Board * board;
    Linkedlist * players;
};

/**
 * \brief initialise la liste
 */
Game * gameCreate(int nbPlayer);

/**
 * \brief ajoute des joueur a la partie et complette avec des bots
 * \param game
 * \param nbPlayer nombre de vrais joueurs
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
void destroyGame(Game ** game);
/**
  * \brief évite les warnings de compilation
  */
void destroyGameVoid(void * game);


#endif //TOCK_CLIENT_GAME_H
