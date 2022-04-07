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

/* ---------- Includes ---------- */

#include "board.h"


/* ---------- Structure ---------- */

/**
 * \brief Structure représentent une partie de jeu
 */
typedef struct Game Game;
struct Game {
    /** \brief Plateau de jeu*/
    Board * board;

    /** \brief List des joueurs de la partie*/
    Linkedlist * players;

    /** \brief Est vrai si la parie est en cour*/
    bool running;
};


/* ---------- Constructor ---------- */

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
  * \brief libere toutes les variable
  */
void destroyGame(Game ** game);


/* ---------- Utilities ---------- */

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


#endif //TOCK_CLIENT_GAME_H
