//
// Created by adzer on 31/03/2022.
//



#include "../SDL/Drawable.h"

bool playPlayer(Player *p, Board * board);
void DrawCardMiddle(enum Card * card);


Player * playerRealFactory( int id){
    //appel le constructeur supérieure
    Player * player = playerFactory(id);
    player->play = &playPlayer;
    return player;
}


bool playPlayer(Player *p, Board * board) {

    bool running = true;
    bool update = false;
    bool ret = false;
    enum Card *cardPayed = NULL;
    Linkedlist *pawnsLocations;
    int highlightedPown = 0;
    int pawnLocation = -1;
    int idPlayer = p->idPlayer;
    //SELECTION DE LA CARTE

    if (isWin(board, p->idPlayer))
        idPlayer = getIdTeamMember(board, p->idPlayer);
    pawnsLocations = getPlayerPawnsLocation(board, idPlayer);
    int * defaultLocation = malloc(sizeof(int));
    *defaultLocation = 0 - p->idPlayer;
    addLast(pawnsLocations,defaultLocation);

    RenderAllDrawable();
    while (running) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_QUIT:
                    exit(EXIT_FAILURE);
                case SDL_KEYDOWN:
                    switch (e.key.keysym.sym) {
                        case SDLK_ESCAPE:
                            exit(EXIT_FAILURE);
                            break;
                        case SDLK_RIGHT:
                            if (cardPayed == NULL)
                                p->selectedCard = (p->selectedCard + 1) % length(p->cards);
                            else
                                highlightedPown--;
                            update = false;
                            break;
                        case SDLK_LEFT:
                            if (cardPayed == NULL)
                                p->selectedCard = (p->selectedCard - 1 + length(p->cards)) % length(p->cards);
                            else
                                highlightedPown++;
                            update = false;
                            break;

                        case SDLK_RETURN:
                            if (cardPayed == NULL) {
                                cardPayed = get(p->cards, p->selectedCard);
                                update = false;
                            } else {
                                //Jouer une carte
                                if ( isComposed(cardPayed)){
                                    Linkedlist *compose = getCardCompose(cardPayed);
                                    enum Card *card = NULL;
                                    for (int i = 0; i < length(compose); ++i) {
                                        card = get(compose,i);
                                        if (*card == out ) {
                                            if (pawnLocation == 0 - idPlayer && playCard(idPlayer, board, card, pawnLocation)) {
                                                running = false;
                                                ret = true;
                                                update = false;
                                            }
                                        } if(playCard(idPlayer,board,card,pawnLocation)){
                                            running = false;
                                            ret = true;
                                            update = false;
                                        }
                                    }
                                }
                                else if(playCard(idPlayer,board,cardPayed,pawnLocation)){
                                    running = false;
                                    ret = true;
                                    update = false;
                                }
                                if (ret) {
                                    removeElem(p->cards, p->selectedCard);
                                    return ret;
                                }
                            }

                            break;
                        case SDLK_BACKSPACE:
                            if (cardPayed != NULL){
                                cardPayed = NULL;
                                update = false;
                            }
                            break;
                        case SDLK_DELETE:
                            if (cardPayed == NULL && !playerCanPlay(p, board) ){
                                removeElem(p->cards,p->selectedCard);
                                running = false;
                                update = false;
                                return false;
                            }
                            break;
                    }
            }

            if (!update) {
                RenderAllDrawable();

                DrawCardMiddle(cardPayed);

                if (cardPayed != NULL){
                    pawnLocation = *((int *) get(pawnsLocations, highlightedPown));
                    highlightLocation(pawnLocation);
                }
                //FIXME affichage en retard
                //update = true;
            }
        }
    }
    return ret;
}

void DrawCardMiddle(enum Card * card){
    if(card == NULL)
        return;
    SDL_Texture *image_tex;
    SDL_Rect imgDestRect ;
    SDL_Surface *image=NULL;
    int cardx = 160;
    int cardy = 240;
    int idealCardy = SDLgetHeight(0.25);
    int idealCardx = ((float)cardx/(float)cardy)*idealCardy;

    imgDestRect.x = SDLgetWidth(0.5) - idealCardx/2;
    imgDestRect.y = SDLgetHeight(0.43) - idealCardy/2;
    imgDestRect.w = 10;

    SDL_RWops *rwop=SDL_RWFromFile(getAsset(card) , "rb");
    image=IMG_LoadPNG_RW(rwop);
    if(!image) {
        printf("IMG_LoadPNG_RW: %s\n", IMG_GetError());
    }

    image_tex = SDL_CreateTextureFromSurface(SDLgetRender(), image);
    if(!image_tex){
        fprintf(stderr, "Erreur a la creation du rendu de l'image : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }


    SDL_QueryTexture(image_tex, NULL, NULL, &(imgDestRect.w), &(imgDestRect.h));
    imgDestRect.w = idealCardx;
    imgDestRect.h = idealCardy;
    SDL_RenderCopy(SDLgetRender(), image_tex, NULL, &imgDestRect);
    SDL_FreeSurface(image);
    SDL_DestroyTexture(image_tex);

}


/*
 * bool playPlayer(Player *p, Board * board) {
    const int minint = -2147483648;
    int idPlayer = p->idPlayer, maxh = minint, cardPlayIndex, maxLocation, h = minint, pownLocation;
    enum Card * maxCard;
    if(isWin(board,p->idPlayer))
        idPlayer = getIdTeamMember(board,idPlayer);
    Linkedlist * pownsLocations = getPlayerPawnsLocation(board, idPlayer);
    Board *boardCopy;
    bool played = false;
    printf("\tnbPown:%i nbCard:%i\n",length(pownsLocations),length(p->cards));

    for (int i = length(pownsLocations) ; i >= 0 ; i--) {
        if (get(pownsLocations, i) != NULL)
            pownLocation = *((int*) get(pownsLocations, i));
        else
            pownLocation = -1;
        if(i == 0)
            pownLocation = -1;
        for (int j = 0; j < length(p->cards); j++) {
            boardCopy = boardClone(board);
            //gestion des cartes composé
            if (isComposed(get(p->cards, j))) {
                Linkedlist *compose = getCardCompose(get(p->cards, j));
                int compMaxh = minint,compMaxLocation;
                bool compplayed = false;
                enum Card * compmaxCard = NULL;
                for (int k = 0; k < length(compose); k++){
                    boardCopy = boardClone(board);
                    compplayed = playCard(idPlayer, boardCopy, get(compose, k), pownLocation);
                    if (compplayed) {
                        h = heuristic(boardCopy, idPlayer);
                        //TODO ferifier si onOUt ne casse pas le choi des autres cartes de la main (7.8.9)(les cartes normal)
                        printf("\t\th:%i location:%i carte:%s (%s)\n", h, pownLocation, cardToString((enum Card*)get(p->cards, j)), cardToString(get(compose, k)));
                        if (h > compMaxh) {
                            compMaxh = h;
                            compMaxLocation = pownLocation;
                            compmaxCard = get(compose, k);
                            compplayed = false;
                        }
                    }
                }
                printf("\th:%i location:%i carte:%s (%s)\n",compMaxh, pownLocation, cardToString((enum Card*)get(p->cards, j)), cardToString(compmaxCard));
                if (compMaxh > maxh) {
                    maxh = compMaxh;
                    maxLocation = compMaxLocation;
                    cardPlayIndex = j;
                    maxCard = compmaxCard;
                    played = false;
                }
            } else{
                played = playCard(idPlayer, boardCopy, get(p->cards, j), pownLocation);
                if (played) {
                    h = heuristic(boardCopy, idPlayer);
                    printf("\th:%i location:%i carte:", h, pownLocation);

                    drawCard(get(p->cards, j));
                    if (h > maxh) {
                        maxh = h;
                        maxLocation = pownLocation;
                        maxCard = get(p->cards, j);
                        cardPlayIndex = j;
                        played = false;
                    }
                }
            }
        }
    }

    if (h == minint && !isEmpty(p->cards)){
        printf("player %i a jeter ",p->idPlayer);
        drawCard(getFirst(p->cards));
        pollFirst(p->cards);
        played = false;
    } else {
        playCard(idPlayer, board, maxCard, maxLocation);
        printf("jouer h:%i location:%i carte:",maxh,maxLocation);
        drawCard(get(p->cards, cardPlayIndex));
        removeElem(p->cards, cardPlayIndex);
        played = true;
    }
    return played;
}
*/