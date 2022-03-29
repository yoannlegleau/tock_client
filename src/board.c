//
// Created by adzerake on 10/03/2022.
//

#include <stdio.h>
#include "board.h"
#include "mainSDL.h"
#include "Color.h"

#define PLAYERBORDLENTH 18

int getBoardLen(Board * board);
int heuristicPlayer(Board * board,int IdPlayer);

/* ---------- Constructor ---------- */

Board * boardFactory(int nbPlayer){
    Board * board = malloc(sizeof(Board));
    board->nbPlayer = nbPlayer;
    board->board = malloc(sizeof(int)*(getLen(board)));
    initBoard(board);
    return board;
}

Board * boardClone(Board * board){
    Board *newBord = boardFactory(board->nbPlayer);
    for (int i = 0; i < getLen(board); i++) {
        newBord->board[i] = board->board[i];
    }
    return newBord;
}

void initBoard(Board * board) {
    for (int i = 0; i < getLen(board); ++i) {
        board->board[i] = 0;
    }
}

/* ---------- Getter ---------- */

int getNbPlayer(Board * board){
    return board->nbPlayer;
}

int getLen(Board * board){
    return (getBoardLen(board)+(4*getNbPlayer(board)));
}

Linkedlist *getPlayerPawnsLocation(Board * board, int playerId) {
    Linkedlist * locations = linkedListFactory();
    int arrayLen = getLen(board) + 4* board->nbPlayer;
    for (int i = 0; i < arrayLen; i++) {
        if ( board->board[i] == playerId)
            addLast(locations, (void *) i);
    }
    return locations;
}

int getBoardLen(Board * board){
    return getNbPlayer(board) * PLAYERBORDLENTH;
}

int getStart(int pId){
    return ((18*pId)-18);
}

int getHomeEntry(int pId){
    return ((72+(pId*18)-20)%72);
}

int getHomeStart(Board * board, int pId){
    return getBoardLen(board)+(4*(pId-1));
}

int getInHomePosition(Board * board, int location){
    if (isOnBoard(board, location))
        return -1;
    return (location- getBoardLen(board))%4+1;
}

int getStepToHome(Board * board, int location, int pId){
    return (getHomeEntry(pId) - location +getBoardLen(board))% getBoardLen(board);
}

/* ---------- Tests ---------- */

bool isOnBoard(Board * board, int location){
    return (0 <= location && location < getBoardLen(board));
}

bool pawnOnPath(Board * board, int location, int step){
    bool ret = false;
    for (int i = location+1; i <= step+location; i++) {
        if (board->board[i] != 0)
            return true;
    }
    return ret;
}

bool isWin(Board * board, int pId){
    bool ret = true;
    int homeStart = getHomeStart(board,pId);
    for (int i = homeStart ; i < homeStart+4 ; i++) {
        if (board->board[i] != pId)
            return false;
    }
    return ret;
}

/* ---------- Utilities ---------- */

bool forward(Board * board, int location, int step){
    int player = board->board[location];

    //Si le pion est dans la maison
    if (location >= getBoardLen(board)){
        int inHomePosition = getInHomePosition(board, location);
        if (inHomePosition + step <= 4 && !pawnOnPath(board, location, step)) {
            move(board, location, location + step);
            return true;
        } else return false;
    }
    /*
    int stepToHome = getStepToHome(board,location,player);
    if(stepToHome < step &&
        step <= stepToHome+3 &&
        !pawnOnPath(board,getHomeStart(board,player)-1, step-stepToHome)){
        int destination = step - stepToHome;
        move(board,location, getHomeStart(board,player)+destination);
        return true;
    }
     */
    ///*
    int playerEntry = ((72+(player*18)-20)%72);
    if((location+step)>playerEntry && (location+step)<playerEntry+4){
        int destination = location+step-playerEntry-1;
        move(board,location,72+(4*(player-1)+destination));
        return true;
    }
    // */
    if (board->board[(location+step)% getBoardLen(board)] != 0)
        //printf("----- %i a tuer %i -----\n",player,board[(location+step)% getBoardLen(board)]);
    move(board, location,(location+step)%72);
    return  true;
}

bool backward(Board * board, int location, int step){
    if(!isOnBoard(board,location))
        return false;
    move(board,location,((location-step+ getBoardLen(board))% getBoardLen(board)));
    return true;
}

void move(Board * board, int from, int to){
    board->board[to] = board->board[from];
    board->board[from] = 0;
}

bool outPawn(Board * board, int pId) {
    bool ret = false;
    Linkedlist * pawns = getPlayerPawnsLocation(board, pId);
    if (length(pawns) < 4){
        board->board[getStart(pId)] = pId;
        ret= true;
    }
    destroy(pawns);
    return ret;
}

int heuristic(Board * board,int IdPlayer){
    int result = 0;
    for (int i = 1; i < board->nbPlayer; i++) {
        if (i != IdPlayer)
            result -= heuristicPlayer(board,i);
        else
            result += heuristicPlayer(board,i);
    }
    return result;
}

int heuristicPlayer(Board * board,int IdPlayer){
    Linkedlist * pawns = getPlayerPawnsLocation(board,IdPlayer);
    int const inHomeFactor = 100, startFactor = 20 ,toHomeFactor=1;
    int result = 0;

    for (int i = 0; i < length(pawns) ; i++) {
        int pawnLocation = (int) get(pawns, i);
        if (pawnLocation >= getBoardLen(board))
            result += getInHomePosition(board, pawnLocation) * inHomeFactor;
        else
            result += getBoardLen(board) - getStepToHome(board,pawnLocation,IdPlayer)*toHomeFactor + startFactor;
    }
    return result;
}

/* ---------- Old ---------- */
void drawBoard(Board * board, SDL_Renderer *renderer){
    SDL_Color couleurNoire = getSDLColor("Black");
    const int squareSize = SDLgetHeight(0.03611112);
    const int sercleSize = SDLgetHeight(0.0152777779);;
    const int widthSize = SDLgetHeight(0.004166667);

    const int matSize = 19;
    int boardMat[19][19];

    int x = (SDLgetWidth(0.5)-((squareSize*(matSize-1))/2)) , y = SDLgetHeight(0.1);

    for(int i = 0; i < 19; i++){
      for(int j = 0; j < 19; j++){
        boardMat[i][j] = -1;
      }
    }

    boardMat[7][18] = 10;
    for (int i = 14; i < 19; ++i) boardMat[9][i] = 10;
    boardMat[0][7] = 20;
    for (int i = 0; i < 5; ++i) boardMat[i][9] = 20;
    boardMat[11][0] = 30;
    for (int i = 0; i < 5; ++i) boardMat[9][i] = 30;
    boardMat[18][11] = 40;
    for (int i = 14; i < 19; ++i) boardMat[i][9] = 40;

    if (board->board[0] != 0)
        boardMat[7][18] = board->board[0];
    boardMat[7][17] = board->board[1];
    boardMat[7][16] = board->board[2];
    boardMat[7][15] = board->board[3];
    boardMat[7][14] = board->board[4];
    boardMat[6][14] = board->board[5];
    boardMat[5][14] = board->board[6];
    boardMat[4][14] = board->board[7];
    boardMat[4][13] = board->board[8];
    boardMat[4][12] = board->board[9];
    boardMat[4][11] = board->board[10];
    boardMat[3][11] = board->board[11];
    boardMat[2][11] = board->board[12];
    boardMat[1][11] = board->board[13];
    boardMat[0][11] = board->board[14];
    boardMat[0][10] = board->board[15];
    if (board->board[16] != 0)
        boardMat[0][9] = board->board[16];
    boardMat[0][8] = board->board[17];
    if (board->board[18] != 0)
        boardMat[0][7] = board->board[18];
    boardMat[1][7] = board->board[19];
    boardMat[2][7] = board->board[20];
    boardMat[3][7] = board->board[21];
    boardMat[4][7] = board->board[22];
    boardMat[4][6] = board->board[23];
    boardMat[4][5] = board->board[24];
    boardMat[4][4] = board->board[25];
    boardMat[5][4] = board->board[26];
    boardMat[6][4] = board->board[27];
    boardMat[7][4] = board->board[28];
    boardMat[7][3] = board->board[29];
    boardMat[7][2] = board->board[30];
    boardMat[7][1] = board->board[31];
    boardMat[7][0] = board->board[32];
    boardMat[8][0] = board->board[33];
    if (board->board[34] != 0)
        boardMat[9][0] = board->board[34];
    boardMat[10][0] = board->board[35];
    if (board->board[36] != 0)
        boardMat[11][0] = board->board[36];
    boardMat[11][1] = board->board[37];
    boardMat[11][2] = board->board[38];
    boardMat[11][3] = board->board[39];
    boardMat[11][4] = board->board[40];
    boardMat[12][4] = board->board[41];
    boardMat[13][4] = board->board[42];
    boardMat[14][4] = board->board[43];
    boardMat[14][5] = board->board[44];
    boardMat[14][6] = board->board[45];
    boardMat[14][7] = board->board[46];
    boardMat[15][7] = board->board[47];
    boardMat[16][7] = board->board[48];
    boardMat[17][7] = board->board[49];
    boardMat[18][7] = board->board[50];
    boardMat[18][8] = board->board[51];
    if (board->board[52] != 0)
        boardMat[18][9] = board->board[52];
    boardMat[18][10] = board->board[53];
    if (board->board[54] != 0)
        boardMat[18][11] = board->board[54];
    boardMat[17][11] = board->board[55];
    boardMat[16][11] = board->board[56];
    boardMat[15][11] = board->board[57];
    boardMat[14][11] = board->board[58];
    boardMat[14][12] = board->board[59];
    boardMat[14][13] = board->board[60];
    boardMat[14][14] = board->board[61];
    boardMat[13][14] = board->board[62];
    boardMat[12][14] = board->board[63];
    boardMat[11][14] = board->board[64];
    boardMat[11][15] = board->board[65];
    boardMat[11][16] = board->board[66];
    boardMat[11][17] = board->board[67];
    boardMat[11][18] = board->board[68];
    boardMat[10][18] = board->board[69];
    if (board->board[70] != 0)
        boardMat[9][18] = board->board[70];
    boardMat[8][18] = board->board[71];

    if (board->board[72] != 0)
        boardMat[9][17] = board->board[72];
    if (board->board[73] != 0)
        boardMat[9][16] = board->board[73];
    if (board->board[74] != 0)
        boardMat[9][15] = board->board[74];
    if (board->board[75] != 0)
        boardMat[9][14] = board->board[75];

    if (board->board[76] != 0)
        boardMat[1][9] = board->board[76];
    if (board->board[77] != 0)
        boardMat[2][9] = board->board[77];
    if (board->board[78] != 0)
        boardMat[3][9] = board->board[78];
    if (board->board[79] != 0)
        boardMat[4][9] = board->board[79];

    if (board->board[80] != 0)
        boardMat[9][1] = board->board[80];
    if (board->board[81] != 0)
        boardMat[9][2] = board->board[81];
    if (board->board[82] != 0)
        boardMat[9][3] = board->board[82];
    if (board->board[83] != 0)
        boardMat[9][4] = board->board[83];

    if (board->board[84] != 0)
        boardMat[17][9] = board->board[84];
    if (board->board[85] != 0)
        boardMat[16][9] = board->board[85];
    if (board->board[86] != 0)
        boardMat[15][9] = board->board[86];
    if (board->board[87] != 0)
        boardMat[14][9] = board->board[87];



    for (int i = 0; i < matSize ; ++i) {
        for (int j = 0; j < matSize ; ++j) {
            switch (boardMat[i][j]) {
                case 0: {

                    drawCircleBoarder(renderer, x + i * squareSize, y + j * squareSize, sercleSize, couleurNoire, widthSize , getSDLColor("Background"));
                }
                    break;
                case 1:
                    drawCircleBoarder(renderer, x+i*squareSize, y+j*squareSize, sercleSize, couleurNoire, widthSize   , getSDLColor("Player1"));
                    break;
                case 10:
                    drawCircleBoarder(renderer, x+i*squareSize, y+j*squareSize, sercleSize, couleurNoire, widthSize   , getSDLColor("Player1Light"));
                    break;
                case 2:
                    drawCircleBoarder(renderer, x+i*squareSize, y+j*squareSize, sercleSize, couleurNoire, widthSize , getSDLColor("Player2"));
                    break;
                case 20:
                    drawCircleBoarder(renderer, x+i*squareSize, y+j*squareSize, sercleSize, couleurNoire, widthSize , getSDLColor("Player2Light"));
                    break;
                case 3:
                    drawCircleBoarder(renderer, x+i*squareSize, y+j*squareSize, sercleSize, couleurNoire, widthSize , getSDLColor("Player3"));
                    break;
                case 30:
                    drawCircleBoarder(renderer, x+i*squareSize, y+j*squareSize, sercleSize, couleurNoire, widthSize , getSDLColor("Player3Light"));
                    break;
                case 4:
                    drawCircleBoarder(renderer, x+i*squareSize, y+j*squareSize, sercleSize, couleurNoire, widthSize , getSDLColor("Player4"));
                    break;
                case 40:
                    drawCircleBoarder(renderer, x+i*squareSize, y+j*squareSize, sercleSize, couleurNoire, widthSize , getSDLColor("Player4Light"));
                    break;

            }
        }
    }
}





