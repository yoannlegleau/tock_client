/**
 * \file Color.h
 * \brief Gestion des Couleurs / Style
 * \author LE GLEAU Yoann
 * \date 10/03/2022
 * \version 1
 */

#ifndef TOCK_CLIENT_COLOR_H
#define TOCK_CLIENT_COLOR_H


/* ---------- Includes ---------- */

#include <SDL.h>


/* ---------- Getters ---------- */

/**
 * \brief Récupère la valeur de la couleur selon la feuille de style
 * \param colorKey Identifient de la couleur
 * \return SDL_Color couleur
 */
SDL_Color getSDLColor(char * colorKey);

#endif //TOCK_CLIENT_COLOR_H


