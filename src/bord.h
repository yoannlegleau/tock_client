//
// Created by adzerake on 10/03/2022.
//

#ifndef TOCK_CLIENT_BORD_H
#define TOCK_CLIENT_BORD_H

#include <SDL.h>
#include "linkedlist.h"

typedef struct Bord Bord;
struct Bord {
    int ** bord;
    int nbPlayer;
};


/* ---------- Constructor ---------- */

Bord * bordFactory(int nbPlayer);
void initBord(Bord * bord);

/* ---------- Getter ---------- */

int getNbPlayer(Bord * bord);
int getLen(Bord * bord);

/* ---------- Utilities ---------- */

Linkedlist * getPlayerPansLocation(Bord * bord,int playerId );

void drawBord(Bord * bord, SDL_Renderer *renderer, int x, int y);

bool playCard(Bord * bord, enum Card * card,int location);

#endif //TOCK_CLIENT_BORD_H
