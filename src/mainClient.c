/**
 * \file main.c
 * \brief gestion de l'application
 * \author JARRIER Allan
 * \date 20/01/2022
 *
 */

#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include "mainSDL.h"
#include "game.h"
#include "parser.h"



/**
 * \brief lancement du jeu et fermeture
 * \param argc
 * \param args
 * \return
 */
 int main(int argc, char* args[]) {
    //lance le jeu dans la fenêtre principal
    /*
    getWindow();
    Game *game = gameCreate(4);
    gameStart(game);
     */

    parsByKey("assets/Style","SDL_ColorPlayer1");
    // ferme le jeu
    winDestroy();

    return 0;
}
