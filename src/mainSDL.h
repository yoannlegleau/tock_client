/**
 * \file mainSDL.c
 * \brief gestion de la fenetre principale
 * \author JARRIER Allan
 * \date 20/01/2022
 * \version 1
 */

#include <SDL2/SDL.h>

#ifndef TOCK_CLIENT_MAINSDL_H
#define TOCK_CLIENT_MAINSDL_H

SDL_Window *window;

void winCreate();
void winDestroy();
SDL_Window * getWindow();

#endif //TOCK_CLIENT_MAINSDL_H