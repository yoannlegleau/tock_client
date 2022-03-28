//
// Created by adzerake on 27/03/2022.
//

#include <stdio.h>
#include "Color.h"
#include "linkedlist.h"
#include "parser.h"
#include <string.h>
#include <stdlib.h>

#define STYLE_PATH "assets/Style"
#define COLOR_SPLITER ","

char** str_split(char* a_str, const char a_delim);
void colorInit();


/**
 * \brief (singleton) liste contenant les clefs valuers des couleur
 */
Linkedlist * colors;

void colorInit(){
    if(colors == NULL)
        colors = loadFromPath(STYLE_PATH);
}

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
