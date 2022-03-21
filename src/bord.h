//
// Created by adzerake on 10/03/2022.
//

#ifndef TOCK_CLIENT_BORD_H
#define TOCK_CLIENT_BORD_H

#include <SDL.h>
#include "linkedlist.h"
#include "card.h"

typedef struct Bord Bord;
struct Bord {
    int * bord;
    int nbPlayer;
};


/* ---------- Constructor ---------- */

Bord * bordFactory(int nbPlayer);
void initBord(Bord * bord);

/* ---------- Getter ---------- */

int getNbPlayer(Bord * bord);
int getLen(Bord * bord);
Linkedlist * getPlayerPansLocation(Bord * bord,int playerId );
int getStart(int pId);
int getHomeEntry(int pId);
int getHomeStart(int pId);

/* ---------- Tests ---------- */

bool isOnBord(Bord * bord, int location);
bool pawnOnPath(Bord * bord, int location, int step);

/* ---------- Utilities ---------- */

bool forward(Bord * bord, int location, int step);
void move(Bord * bord, int from, int to);
bool outPawn(Bord * bord, int pId);


void drawBord(Bord * bord, SDL_Renderer *renderer, int x, int y);


#endif //TOCK_CLIENT_BORD_H
