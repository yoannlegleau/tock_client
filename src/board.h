//
// Created by adzerake on 10/03/2022.
//

#ifndef TOCK_CLIENT_BOARD_H
#define TOCK_CLIENT_BOARD_H

#include <SDL.h>
#include "linkedlist.h"
#include "card.h"

typedef struct Board Board;
struct Board {
    int * board;
    int nbPlayer;
};


/* ---------- Constructor ---------- */

Board * boardFactory(int nbPlayer);
Board * boardClone(Board * board);

void initBoard(Board * board);

/* ---------- Getter ---------- */

int getNbPlayer(Board * board);
int getLen(Board * board);
Linkedlist * getPlayerPawnsLocation(Board * board, int playerId );
int getStart(int pId);
int getHomeEntry(int pId);
int getHomeStart(Board * board, int pId);
int getInHomePosition(Board * board, int location);
int getStepToHome(Board * board, int location, int pId);


/* ---------- Tests ---------- */

bool isOnBoard(Board * board, int location);
bool pawnOnPath(Board * board, int location, int step);
bool isWin(Board * board, int pId);

/* ---------- Utilities ---------- */

/**
 * \brief Fais avencer un pion sur le plateau
 * \param board le plateau
 * \param location position du pion a faire avencer
 * \param step distance a parcourire
 * \return true si le pion a bien pue avencer
 */
bool forward(Board * board, int location, int step);
bool backward(Board * board, int location, int step);
void move(Board * board, int from, int to);
bool outPawn(Board * board, int pId);
/**
 * \brief libere toutes les variables
 */
void destroyBoard(Board ** board);
/**
 * \brief évite les warnings de compilation
 */
void destroyBoardVoid(void * board);
int heuristic(Board * board,int IdPlayer);

void drawBoard(Board * board, SDL_Renderer *renderer);


#endif //TOCK_CLIENT_BOARD_H
