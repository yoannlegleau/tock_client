//
// Created by adzer on 31/03/2022.
//



#include "../Draw/Drawable.h"

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
    *defaultLocation = 0 - idPlayer;
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
                                                removeElem(p->cards, p->selectedCard);
                                                return true;
                                            }
                                        } else if(playCard(idPlayer,board,card,pawnLocation)){
                                            removeElem(p->cards, p->selectedCard);
                                            return true;
                                        }
                                    }
                                }
                                else if(playCard(idPlayer,board,cardPayed,pawnLocation)){
                                    removeElem(p->cards, p->selectedCard);
                                    return true;
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