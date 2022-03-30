//
// Created by adzerake on 10/03/2022.
//

#include <stdio.h>
#include "bord.h"
#include "mainSDL.h"
#include "Color.h"

#define PLAYERBORDLENTH 18

/* ---------- Constructor ---------- */

Bord * bordFactory(int nbPlayer){
    Bord * bord = malloc(sizeof(Bord));
    bord->nbPlayer = nbPlayer;
    bord->bord = malloc(sizeof(int)*(getLen(bord)));
    initBord(bord);
    return bord;
}

void initBord(Bord * bord) {
    for (int i = 0; i < getLen(bord); ++i) {
        bord->bord[i] = 0;
    }
}

/* ---------- Getter ---------- */

int getNbPlayer(Bord * bord){
    return bord->nbPlayer;
}

int getLen(Bord * bord){
    return ((18*getNbPlayer(bord))+(4*getNbPlayer(bord)));
}

Linkedlist *getPlayerPansLocation(Bord * bord, int playerId) {
    Linkedlist * locations = linkedListFactory(sizeof(int));
    int arrayLen = getLen(bord) + 4* bord->nbPlayer;
    for (int i = 0; i < arrayLen; i++) {
        if ( bord->bord[i] == playerId)
            addLast(locations, (void *) i);
    }
    return locations;
}

int getBordLen(Bord * bord){
    return getNbPlayer(bord) * PLAYERBORDLENTH;
}

int getStart(int pId){
    return ((18*pId)-18);
}

int getHomeEntry(int pId){
    return ((72+(pId*18)-20)%72);
}

int getHomeStart(Bord * bord, int pId){
    return getBordLen(bord)+(4*(pId-1));
}

int getInHomePosition(Bord * bord, int location){
    if (isOnBord(bord, location))
        return -1;
    return (location- getBordLen(bord))%4+1;
}

int getStepToHome(Bord * bord, int location, int pId){
    return (getHomeEntry(pId) - location +getBordLen(bord))% getBordLen(bord);
}

/* ---------- Tests ---------- */

bool isOnBord(Bord * bord, int location){
    return (0 <= location && location < getBordLen(bord));
}

bool pawnOnPath(Bord * bord, int location, int step){
    bool ret = false;
    for (int i = location+1; i <= step+location; i++) {
        if (bord->bord[i] != 0)
            return true;
    }
    return ret;
}

bool isWin(Bord * bord, int pId){
    bool ret = true;
    int homeStart = getHomeStart(bord,pId);
    for (int i = homeStart ; i < homeStart+4 ; i++) {
        if (bord->bord[i] != pId)
            return false;
    }
    return ret;
}

/* ---------- Utilities ---------- */

bool forward(Bord * bord, int location, int step){
    int player = bord->bord[location];

    //Si le pion est dans la maison
    if (location >= getBordLen(bord)){
        int inHomePosition = getInHomePosition(bord, location);
        if (inHomePosition + step <= 4 && !pawnOnPath(bord, location, step)) {
            move(bord, location, location + step);
            return true;
        } else return false;
    }
    /*
    int stepToHome = getStepToHome(bord,location,player);
    if(stepToHome < step &&
        step <= stepToHome+3 &&
        !pawnOnPath(bord,getHomeStart(bord,player)-1, step-stepToHome)){
        int destination = step - stepToHome;
        move(bord,location, getHomeStart(bord,player)+destination);
        return true;
    }
    */
    
    int playerEntry = ((72+(player*18)-20)%72);
    if((location+step)>playerEntry && (location+step)<playerEntry+4){
        int destination = location+step-playerEntry-1;
        move(bord,location,72+(4*(player-1)+destination));
        return true;
    }
    if (bord->bord[(location+step)% getBordLen(bord)] != 0)
        printf("----- %i a tuer %i -----\n",player,bord[(location+step)% getBordLen(bord)]);
    move(bord, location,(location+step)%72);
    return  true;
}

bool backward(Bord * bord, int location, int step){
    if(!isOnBord(bord,location))
        return false;
    move(bord,location,((location-step+ getBordLen(bord))% getBordLen(bord)));
    return true;
}

void move(Bord * bord, int from, int to){
    bord->bord[to] = bord->bord[from];
    bord->bord[from] = 0;
}

bool outPawn(Bord * bord, int pId) {
    bool ret = false;
    Linkedlist * pawns = getPlayerPansLocation(bord, pId);
    if (length(pawns) < 4){
        bord->bord[getStart(pId)] = pId;
        ret= true;
    }
    destroy(pawns);
    return ret;
}

/* ---------- Old ---------- */

void drawBord(Bord * bord, SDL_Renderer *renderer, int x, int y){
    const int squareSize = 26;
    const int sercleSize = 23/2;
    const int widthSize = 3;
    const int matSize = 19;
    int bordMat[19][19];

    for(int i = 0; i < 19; i++){
      for(int j = 0; j < 19; j++){
        bordMat[i][j] = -1;
      }
    }

    bordMat[7][18] = 10;
    for (int i = 14; i < 19; ++i) bordMat[9][i] = 10;
    bordMat[0][7] = 20;
    for (int i = 0; i < 5; ++i) bordMat[i][9] = 20;
    bordMat[11][0] = 30;
    for (int i = 0; i < 5; ++i) bordMat[9][i] = 30;
    bordMat[18][11] = 40;
    for (int i = 14; i < 19; ++i) bordMat[i][9] = 40;

    if (bord->bord[0] != 0)
        bordMat[7][18] = bord->bord[0];
    bordMat[7][17] = bord->bord[1];
    bordMat[7][16] = bord->bord[2];
    bordMat[7][15] = bord->bord[3];
    bordMat[7][14] = bord->bord[4];
    bordMat[6][14] = bord->bord[5];
    bordMat[5][14] = bord->bord[6];
    bordMat[4][14] = bord->bord[7];
    bordMat[4][13] = bord->bord[8];
    bordMat[4][12] = bord->bord[9];
    bordMat[4][11] = bord->bord[10];
    bordMat[3][11] = bord->bord[11];
    bordMat[2][11] = bord->bord[12];
    bordMat[1][11] = bord->bord[13];
    bordMat[0][11] = bord->bord[14];
    bordMat[0][10] = bord->bord[15];
    if (bord->bord[16] != 0)
        bordMat[0][9] = bord->bord[16];
    bordMat[0][8] = bord->bord[17];
    if (bord->bord[18] != 0)
        bordMat[0][7] = bord->bord[18];
    bordMat[1][7] = bord->bord[19];
    bordMat[2][7] = bord->bord[20];
    bordMat[3][7] = bord->bord[21];
    bordMat[4][7] = bord->bord[22];
    bordMat[4][6] = bord->bord[23];
    bordMat[4][5] = bord->bord[24];
    bordMat[4][4] = bord->bord[25];
    bordMat[5][4] = bord->bord[26];
    bordMat[6][4] = bord->bord[27];
    bordMat[7][4] = bord->bord[28];
    bordMat[7][3] = bord->bord[29];
    bordMat[7][2] = bord->bord[30];
    bordMat[7][1] = bord->bord[31];
    bordMat[7][0] = bord->bord[32];
    bordMat[8][0] = bord->bord[33];
    if (bord->bord[34] != 0)
        bordMat[9][0] = bord->bord[34];
    bordMat[10][0] = bord->bord[35];
    if (bord->bord[36] != 0)
        bordMat[11][0] = bord->bord[36];
    bordMat[11][1] = bord->bord[37];
    bordMat[11][2] = bord->bord[38];
    bordMat[11][3] = bord->bord[39];
    bordMat[11][4] = bord->bord[40];
    bordMat[12][4] = bord->bord[41];
    bordMat[13][4] = bord->bord[42];
    bordMat[14][4] = bord->bord[43];
    bordMat[14][5] = bord->bord[44];
    bordMat[14][6] = bord->bord[45];
    bordMat[14][7] = bord->bord[46];
    bordMat[15][7] = bord->bord[47];
    bordMat[16][7] = bord->bord[48];
    bordMat[17][7] = bord->bord[49];
    bordMat[18][7] = bord->bord[50];
    bordMat[18][8] = bord->bord[51];
    if (bord->bord[52] != 0)
        bordMat[18][9] = bord->bord[52];
    bordMat[18][10] = bord->bord[53];
    if (bord->bord[54] != 0)
        bordMat[18][11] = bord->bord[54];
    bordMat[17][11] = bord->bord[55];
    bordMat[16][11] = bord->bord[56];
    bordMat[15][11] = bord->bord[57];
    bordMat[14][11] = bord->bord[58];
    bordMat[14][12] = bord->bord[59];
    bordMat[14][13] = bord->bord[60];
    bordMat[14][14] = bord->bord[61];
    bordMat[13][14] = bord->bord[62];
    bordMat[12][14] = bord->bord[63];
    bordMat[11][14] = bord->bord[64];
    bordMat[11][15] = bord->bord[65];
    bordMat[11][16] = bord->bord[66];
    bordMat[11][17] = bord->bord[67];
    bordMat[11][18] = bord->bord[68];
    bordMat[10][18] = bord->bord[69];
    if (bord->bord[70] != 0)
        bordMat[9][18] = bord->bord[70];
    bordMat[8][18] = bord->bord[71];

    if (bord->bord[72] != 0)
        bordMat[9][17] = bord->bord[72];
    if (bord->bord[73] != 0)
        bordMat[9][16] = bord->bord[73];
    if (bord->bord[74] != 0)
        bordMat[9][15] = bord->bord[74];
    if (bord->bord[75] != 0)
        bordMat[9][14] = bord->bord[75];

    if (bord->bord[76] != 0)
        bordMat[1][9] = bord->bord[76];
    if (bord->bord[77] != 0)
        bordMat[2][9] = bord->bord[77];
    if (bord->bord[78] != 0)
        bordMat[3][9] = bord->bord[78];
    if (bord->bord[79] != 0)
        bordMat[4][9] = bord->bord[79];

    if (bord->bord[80] != 0)
        bordMat[9][1] = bord->bord[80];
    if (bord->bord[81] != 0)
        bordMat[9][2] = bord->bord[81];
    if (bord->bord[82] != 0)
        bordMat[9][3] = bord->bord[82];
    if (bord->bord[83] != 0)
        bordMat[9][4] = bord->bord[83];

    if (bord->bord[84] != 0)
        bordMat[17][9] = bord->bord[84];
    if (bord->bord[85] != 0)
        bordMat[16][9] = bord->bord[85];
    if (bord->bord[86] != 0)
        bordMat[15][9] = bord->bord[86];
    if (bord->bord[87] != 0)
        bordMat[14][9] = bord->bord[87];



    for (int i = 0; i < matSize ; ++i) {
        for (int j = 0; j < matSize ; ++j) {
            switch (bordMat[i][j]) {
                case 0:
                    drawCircleBorder(renderer, x+i*squareSize, y+j*squareSize, sercleSize, couleurNoire, widthSize , couleurBlanc);
                    break;
                case 1:
                    drawCircleBorder(renderer, x+i*squareSize, y+j*squareSize, sercleSize, couleurNoire, widthSize   , colorPlayer1);
                    break;
                case 10:
                    drawCircleBorder(renderer, x+i*squareSize, y+j*squareSize, sercleSize, couleurNoire, widthSize   , colorPlayer1Light);
                    break;
                case 2:
                    drawCircleBorder(renderer, x+i*squareSize, y+j*squareSize, sercleSize, couleurNoire, widthSize , colorPlayer2);
                    break;
                case 20:
                    drawCircleBorder(renderer, x+i*squareSize, y+j*squareSize, sercleSize, couleurNoire, widthSize , colorPlayer2Light);
                    break;
                case 3:
                    drawCircleBorder(renderer, x+i*squareSize, y+j*squareSize, sercleSize, couleurNoire, widthSize , colorPlayer3);
                    break;
                case 30:
                    drawCircleBorder(renderer, x+i*squareSize, y+j*squareSize, sercleSize, couleurNoire, widthSize , colorPlayer3Light);
                    break;
                case 4:
                    drawCircleBorder(renderer, x+i*squareSize, y+j*squareSize, sercleSize, couleurNoire, 3 , colorPlayer4);
                    break;
                case 40:
                    drawCircleBorder(renderer, x+i*squareSize, y+j*squareSize, sercleSize, couleurNoire, 3 , colorPlayer4Light);
                    break;

            }
        }
    }
}




