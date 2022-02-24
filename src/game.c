/**
 * \file game.h
 * \brief gestionaire de partie
 * \author SINGLANDE Thomas
 * \date 20/01/2022
 * \version 1.1
 */

#include <stdio.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <stdbool.h>

#include "game.h"
#include "mainSDL.h"
#include "linkedlist.h"
#include "card.h"
#include "gameRule.h"
#include "Player.h"

#include <xmllite.h>

/**
 * \brief Se tableux represente toutes les cases du plateu
 * \details la longeur varie selon le nombre de joueur car chaque jouer posed 18 plus 4 donc pour 4j 88 et 132 pour 6.
 * Les int represantes les ID de chaques jouers
 * \image html assets/img/Tock.io-BordArray.jpg
 */
int bord[88];

typedef struct Pawn Pawn;
struct Pawn {
    int IDplayer;
    int location; //index du tableau du plateau (principalement en prevision de l'envoi de données au server)
    bool invincibility;
};

//TODO Trouver une meilleur organisation
typedef struct Rule Rule;
struct Rule {
   bool ruleV;
};

const SDL_Color couleurNoire = {0, 0, 0};
const SDL_Color couleurBlanc = {255, 255, 255};
const SDL_Color colorPlayer1 = {2, 3, 230};
const SDL_Color colorPlayer2 = {223, 8 , 7};
const SDL_Color colorPlayer3 = {251, 249, 27};
const SDL_Color colorPlayer4 = {57, 147, 103};
const SDL_Color colorPlayer1Light = {65, 65, 244};
const SDL_Color colorPlayer2Light = {255, 98 , 98};
const SDL_Color colorPlayer3Light = {255, 254, 113};
const SDL_Color colorPlayer4Light = {146, 206, 177};



void drawBord(SDL_Renderer *renderer, int x, int y,int bord[]);

void drawCircle(SDL_Renderer *renderer, int x, int y, int radius, SDL_Color color);
void drawCircleBorder(SDL_Renderer *renderer, int x, int y, int radius, SDL_Color colorOut, int width , SDL_Color colorIn);

void distributeCards(Linkedlist *cards, Linkedlist *players);
bool playCard(enum Card * card,int location);
move(int location,int step);


void playOnce(Linkedlist *players);

Linkedlist *getPlayerPansLocation();


void initBord(int pInt[88]) {
    for (int i = 0; i < 88; ++i) {
        pInt[i] = 0;
    }
}

/**
 * \brief demonstration du fonctionnement des librairie graphiques baser sur l'example de cours
 * \param window fenêtre principal
 */
void gameCreate(SDL_Window *window) {

    bord[88];
    initBord(bord);







    Linkedlist * players = linkedListFactory(sizeof(Player));

    Player * player1 = playerFactory(1);
    bord[0] = 1;
    addLast(players,player1);
    /*
    Player * player2 = playerFactory(2);
    bord[18] = 2;
    addLast(players,player2);
    Player * player3 = playerFactory(3);
    bord[36] = 3;
    addLast(players,player3);
    Player * player4 = playerFactory(4);
    bord[54] = 4;
    addLast(players,player4);
     */



    Linkedlist * gamRules = linkedListFactory(sizeof(enum GamrRule));

    Linkedlist * cards = linkedListFactory(sizeof(enum Card));


    //printf("cartes:%i\n",length(cards));

    //printf("---- distribution 1 ----\n");

    //printf("cartes restantes:%i\n",length(cards));
    //drawListe(players,drawPlayer);



//Le pointeur vers la surface incluse dans la fenetre
    SDL_Surface *texte=NULL, *image=NULL;
    SDL_Renderer *renderer=NULL;
    SDL_Rect txtDestRect,imgDestRect;


    // Le pointeur vers notre police
    TTF_Font *police = NULL;
    // Une variable de couleur noire



    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == NULL){
        fprintf(stderr, "Erreur à la création du renderer\n");
        exit(EXIT_FAILURE);
    }

    drawCircle(renderer, 100, 100, 50, couleurBlanc);

    if( (police = TTF_OpenFont("assets/fonts/ChowFun.ttf", 20)) == NULL){
        fprintf(stderr, "erreur chargement font\n");
        exit(EXIT_FAILURE);
    }
    texte = TTF_RenderUTF8_Blended(police, "Vive la programmation !", couleurNoire);
    if(!texte){
        fprintf(stderr, "Erreur à la création du texte : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_Texture *texte_tex = SDL_CreateTextureFromSurface(renderer, texte);
    if(!texte_tex){
        fprintf(stderr, "Erreur à la création du rendu du texte : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_FreeSurface(texte); /* on a la texture, plus besoin du texte */
    /* Position ou sera mis le texte dans la fenêtre */
    txtDestRect.x = txtDestRect.y = 10;
    SDL_QueryTexture(texte_tex, NULL, NULL, &(txtDestRect.w), &(txtDestRect.h));

    // load sample.png into image

    SDL_RWops *rwop=SDL_RWFromFile("assets/img/controleur1024.png", "rb");
    image=IMG_LoadPNG_RW(rwop);
    if(!image) {
        printf("IMG_LoadPNG_RW: %s\n", IMG_GetError());
    }

    SDL_Texture *image_tex = SDL_CreateTextureFromSurface(renderer, image);
    if(!image_tex){
        fprintf(stderr, "Erreur a la creation du rendu de l'image : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_FreeSurface(image); /* on a la texture, plus besoin de l'image */


    if( window )
    {
        int running = 1;
        while(running) {
            SDL_Event e;
            while(SDL_PollEvent(&e)) {
                switch(e.type) {
                    case SDL_QUIT: running = 0;
                        break;
                    case SDL_WINDOWEVENT:
                        switch(e.window.event){
                            case SDL_WINDOWEVENT_EXPOSED:
                            case SDL_WINDOWEVENT_SIZE_CHANGED:
                            case SDL_WINDOWEVENT_RESIZED:
                            case SDL_WINDOWEVENT_SHOWN:
                                /* Le fond de la fenêtre sera blanc */
                                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                                SDL_RenderClear(renderer);

                                /* Ajout du texte en noir */
                                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                                SDL_RenderCopy(renderer, texte_tex, NULL, &txtDestRect);

                                //dessin du plateux


                                /* Ajout de la seconde image à une certaine position */
                                /*
                                imgDestRect.x = 100;
                                imgDestRect.y = 50;
                                SDL_QueryTexture(image_tex, NULL, NULL, &(imgDestRect.w), &(imgDestRect.h));
                                SDL_RenderCopy(renderer, image_tex, NULL, &imgDestRect);


                                // Ajout de la seconde image à une autre position
                                imgDestRect.x = 250;
                                SDL_RenderCopy(renderer, image_tex, NULL, &imgDestRect);

                                */
                                /* On fait le rendu ! */


                                break;
                        }
                        break;
                }
            }
            Player * p = getFirst(players);
            if (isEmpty(p->cards)){
                if(isEmpty(cards))
                    makeDeck(cards, gamRules);
                distributeCards(cards, players);
            }

            //TODO
            playOnce(players);


            drawBord(renderer, 394, 64, bord);

            SDL_RenderPresent(renderer);
            Sleep(1000);
        }
    } else {
        fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());
    }
}

move(int location,int step){
    bord[(location+step)%72] = bord[location];
    bord[location] = 0;
}

bool playCard(enum Card * card,int location) {
    switch (*card) {
        case one:
            move(location,1);
            break;
        case two:
            move(location,2);
            break;
        case three:
            move(location,3);
            break;
        case four:
            move(location,4);
            break;
        case five:
            move(location,5);
            break;
        case six:
            move(location,6);
            break;
        case seven:
            move(location,7);
            break;
        case eight:
            move(location,8);
            break;
        case nine:
            move(location,9);
            break;
        case ten:
            move(location,10);
            break;
        case eleven:
            move(location,11);
            break;
        case twelve:
            move(location,12);
            break;
        case thirteen:
            move(location,13);
            break;
        default:
            return false;
    }
    return true;
}

void playOnce(Linkedlist *players) {
    int nbPlayer = length(players);
    Player * p;
    for (int i = 0; i < nbPlayer; i++) {

        p = get(players,i);
        Linkedlist * pownsLocations = getPlayerPansLocation(p);
        bool played;
        for (int j = 0; j < length(p->cards); ++j) {
            played = playCard(get(p->cards,j), (int)getFirst(pownsLocations));
            if(played){
                printf("player %i a jouer ",p->idPlayer);
                drawCard(get(p->cards,j));
                removeElem(p->cards,j);



                break;
            }
        }
        if (!played && !isEmpty(p->cards))
            printf("player %i a jeter ",p->idPlayer);
            drawCard(getFirst(p->cards));
            pollFirst(p->cards);
    }
}



Linkedlist *getPlayerPansLocation(Player * player) {
    Linkedlist * locations = linkedListFactory(sizeof(int));
    for (int i = 0; i < 72; i++) {
        if (bord[i] == player->idPlayer)
            addLast(locations, i);
    }
    return locations;
}

void distributeCards(Linkedlist *cards, Linkedlist *players) {
    int nbPlayer = length(players);
    int nbDistributCards;
    if((length(cards)/length(players))%4 != 0) nbDistributCards = 5;
    else nbDistributCards = 4;
    Player * p;

    for (int i = 0; i < nbPlayer; i++) {
        p = get(players,i);
        for (int j = 0; j < nbDistributCards; j++) {
            addLast(p->cards, pollFirst(cards));
        }
    }

}


void drawBord(SDL_Renderer *renderer, int x, int y,int bord[]){
    const int squareSize = 26;
    const int sercleSize = 23/2;
    const int widthSize = 3;
    const int matSize = 19;
    int bordMat[19][19];

    bordMat[7][18] = 10;
    for (int i = 14; i < 19; ++i) bordMat[9][i] = 10;
    bordMat[0][7] = 20;
    for (int i = 0; i < 5; ++i) bordMat[i][9] = 20;
    bordMat[11][0] = 30;
    for (int i = 0; i < 5; ++i) bordMat[9][i] = 30;
    bordMat[18][11] = 40;
    for (int i = 14; i < 19; ++i) bordMat[i][9] = 40;

    if (bord[0] != 0)
    bordMat[7][18] = bord[0];
    bordMat[7][17] = bord[1];
    bordMat[7][16] = bord[2];
    bordMat[7][15] = bord[3];
    bordMat[7][14] = bord[4];
    bordMat[6][14] = bord[5];
    bordMat[5][14] = bord[6];
    bordMat[4][14] = bord[7];
    bordMat[4][13] = bord[8];
    bordMat[4][12] = bord[9];
    bordMat[4][11] = bord[10];
    bordMat[3][11] = bord[11];
    bordMat[2][11] = bord[12];
    bordMat[1][11] = bord[13];
    bordMat[0][11] = bord[14];
    bordMat[0][10] = bord[15];
    if (bord[16] != 0)
    bordMat[0][9] = bord[16];
    bordMat[0][8] = bord[17];
    if (bord[18] != 0)
    bordMat[0][7] = bord[18];
    bordMat[1][7] = bord[19];
    bordMat[2][7] = bord[20];
    bordMat[3][7] = bord[21];
    bordMat[4][7] = bord[22];
    bordMat[4][6] = bord[23];
    bordMat[4][5] = bord[24];
    bordMat[4][4] = bord[25];
    bordMat[5][4] = bord[26];
    bordMat[6][4] = bord[27];
    bordMat[7][4] = bord[28];
    bordMat[7][3] = bord[29];
    bordMat[7][2] = bord[30];
    bordMat[7][1] = bord[31];
    bordMat[7][0] = bord[32];
    bordMat[8][0] = bord[33];
    if (bord[34] != 0)
    bordMat[9][0] = bord[34];
    bordMat[10][0] = bord[35];
    if (bord[36] != 0)
    bordMat[11][0] = bord[36];
    bordMat[11][1] = bord[37];
    bordMat[11][2] = bord[38];
    bordMat[11][3] = bord[39];
    bordMat[11][4] = bord[40];
    bordMat[12][4] = bord[41];
    bordMat[13][4] = bord[42];
    bordMat[14][4] = bord[43];
    bordMat[14][5] = bord[44];
    bordMat[14][6] = bord[45];
    bordMat[14][7] = bord[46];
    bordMat[15][7] = bord[47];
    bordMat[16][7] = bord[48];
    bordMat[17][7] = bord[49];
    bordMat[18][7] = bord[50];
    bordMat[18][8] = bord[51];
    if (bord[52] != 0)
    bordMat[18][9] = bord[52];
    bordMat[18][10] = bord[53];
    if (bord[54] != 0)
    bordMat[18][11] = bord[54];
    bordMat[17][11] = bord[55];
    bordMat[16][11] = bord[56];
    bordMat[15][11] = bord[57];
    bordMat[14][11] = bord[58];
    bordMat[14][12] = bord[59];
    bordMat[14][13] = bord[60];
    bordMat[14][14] = bord[61];
    bordMat[13][14] = bord[62];
    bordMat[12][14] = bord[63];
    bordMat[11][14] = bord[64];
    bordMat[11][15] = bord[65];
    bordMat[11][16] = bord[66];
    bordMat[11][17] = bord[67];
    bordMat[11][18] = bord[68];
    bordMat[10][18] = bord[69];
    if (bord[70] != 0)
    bordMat[9][18] = bord[70];
    bordMat[8][18] = bord[71];

    if (bord[72] != 0)
    bordMat[9][17] = bord[72];
    if (bord[73] != 0)
    bordMat[9][16] = bord[73];
    if (bord[74] != 0)
    bordMat[9][15] = bord[74];
    if (bord[75] != 0)
    bordMat[9][14] = bord[75];

    if (bord[76] != 0)
    bordMat[1][9] = bord[76];
    if (bord[77] != 0)
    bordMat[2][9] = bord[77];
    if (bord[78] != 0)
    bordMat[3][9] = bord[78];
    if (bord[79] != 0)
    bordMat[4][9] = bord[79];

    if (bord[80] != 0)
    bordMat[9][1] = bord[80];
    if (bord[81] != 0)
    bordMat[9][2] = bord[81];
    if (bord[82] != 0)
    bordMat[9][3] = bord[82];
    if (bord[83] != 0)
    bordMat[9][4] = bord[83];

    if (bord[84] != 0)
    bordMat[17][9] = bord[84];
    if (bord[85] != 0)
    bordMat[16][9] = bord[85];
    if (bord[86] != 0)
    bordMat[15][9] = bord[86];
    if (bord[87] != 0)
    bordMat[14][9] = bord[87];



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

void drawCircleBorder(SDL_Renderer *renderer, int x, int y, int radius, SDL_Color colorOut, int width , SDL_Color colorIn) {
    drawCircle(renderer, x, y, radius, colorOut);
    drawCircle(renderer, x  , y, radius-width, colorIn);
}

void drawCircle(SDL_Renderer *renderer, int x, int y, int radius, SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    for (int w = 0; w < radius * 2; w++)
    {
        for (int h = 0; h < radius * 2; h++)
        {
            int dx = radius - w; // horizontal offset
            int dy = radius - h; // vertical offset
            if ((dx*dx + dy*dy) <= (radius * radius))
            {
                SDL_RenderDrawPoint(renderer, x + dx, y + dy);
            }
        }
    }
}


