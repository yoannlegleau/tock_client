/**
 * \file main.c
 * \brief gestion de l'application
 * \author LE GLEAU yoann
 * \date 21/03/2022
 *
 */

#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include "mainSDL.h"
#include "game.h"

/**
 * \brief lancement du server de jeux (pour le moment un seule partie)
 * \param argc
 * \param args
 * \return
 */
int main(int argc, char* args[]) {
    //lance le jeu
    Game *game = gameCreate(4);
    gameStart(game);

    return 0;
}
