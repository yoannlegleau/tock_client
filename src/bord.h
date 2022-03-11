//
// Created by adzerake on 10/03/2022.
//

#ifndef TOCK_CLIENT_BORD_H
#define TOCK_CLIENT_BORD_H

#include <SDL.h>

#include "Player/player.h"

typedef struct Bord Bord;
struct Bord {
    int ** bord;
    int nbPlayer;
};

/* ---------- Constructor ---------- */

Bord * bordFactory(int nbPlayer);


/* ---------- Getter ---------- */

int getNbPlayer(Bord * bord);
int getLen(Bord * bord);

/* ---------- old ---------- */

void initBord(Bord * bord);
Linkedlist *getPlayerPansLocation(Player * player);

void drawBord(SDL_Renderer *renderer, int x, int y,int bord[]);

bool forward(int location, int step);
void move(int from, int to);

#endif //TOCK_CLIENT_BORD_H
