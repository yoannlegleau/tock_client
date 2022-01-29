/**
 * \file main.c
 * \author LE GLEAU yoann
 * \date 20/01/2022
 * \image
 */

#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include "mainSDL.h"
#include "game.h"
#include "linkedlist.h"

/**
 * \brief lancement du jeu et fermeture
 * \param argc
 * \param args
 * \return
 */
 int main(int argc, char* args[]) {
    //Le pointeur vers la fenetre
    SDL_Window* pWindow = getWindow();

    //lance le jeu dans la fenêtre principal
    gameCreate(window);

    Linkedlist * listInt = linkedListFactory(sizeof(int));


    // ferme le jeu
    winDestroy();

    return 0;
}
