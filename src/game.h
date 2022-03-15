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



/**
 * \brief initialise la liste
 * \param window fenetre d'affichage
 */
void gameCreate(SDL_Window *window,SDL_Renderer* renderer);

/**
 * \brief lancer le deroulement du jeux
 */
void gameStart();

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
