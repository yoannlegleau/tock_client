/**
 * \file mainSDL.h
 * \author LE GLEAU yoann
 * \date 20/01/2022
 */

#include <SDL2/SDL.h>

#ifndef TOCK_CLIENT_MAINSDL_H
#define TOCK_CLIENT_MAINSDL_H

SDL_Window *window;

void winCreate();
void winDestroy();
SDL_Window * getWindow();

#endif //TOCK_CLIENT_MAINSDL_H