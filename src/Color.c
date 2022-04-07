/**
 * \file Color.c
 * \brief Gestion des Couleurs / Style
 * \author LE GLEAU Yoann
 * \date 27/03/2022
 * \version 2
 */

/* ---------- Includes ---------- */

#include <stdio.h>
#include "Color.h"
#include "linkedlist.h"
#include "parser.h"
#include <string.h>
#include <stdlib.h>


/* ---------- Sub Declaration ---------- */

/**
 * \brief chemin d'acces du ficher de style par default
 */
#define STYLE_PATH "assets/Style"

/**
 * \brief séparateur endre les valeurs RGB dans la feuille de style
 */
#define COLOR_SPLITER ","

/**
 * \brief (singleton) liste contenant les clefs valuers des couleur
 */
Linkedlist * colors;

/**
 * \brief
 * \param a_str
 * \param a_delim
 * \return
 */
char** str_split(char* a_str, const char a_delim);


/* ---------- Constructor ---------- */

void colorInit(){
    if(colors == NULL)
        colors = loadFromPath(STYLE_PATH);
}


/* ---------- Getters ---------- */

SDL_Color getSDLColor(char * colorKey){
    colorInit();
    SDL_Color sdlColor;

    char * val = malloc(100);
    strcpy(val, getByKey(colors,colorKey));


    char *token = strtok(val, COLOR_SPLITER);
    if ( token != NULL )
        sdlColor.r = atoi(token);

    token = strtok(NULL, COLOR_SPLITER);
    if ( token != NULL )
        sdlColor.g = atoi(token);

    token = strtok(NULL, COLOR_SPLITER);
    if ( token != NULL )
        sdlColor.b = atoi(token);

    token = strtok(NULL, COLOR_SPLITER);
    if ( token != NULL )
        sdlColor.a = atoi(token);

    free(val);
    return sdlColor;
}
