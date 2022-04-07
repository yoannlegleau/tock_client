/**
 * \file PlayerBot.c
 * \brief Joueur de type Utilisateur reel (gestion des interactions)
 * \author LE GLEAU Yoann
 * \date 31/02/2022
 * \version 1
 */

/* ---------- Includes ---------- */
#include "../SDL/Drawable.h"

/* ---------- Sub Declaration ---------- */

/**
 * \brief permet a l'utilisateur de jouer son tour
 * \param p joueur
 * \param board plateau
 * \return true si le joueur a bien pue jouer
 */
bool playPlayer(Player *p, Board * board);


//---------- Constructor ----------

Player * playerRealFactory( int id){
    //appel le constructeur supérieure
    Player * player = playerFactory(id);
    player->play = &playPlayer;
    return player;
}


//---------- Utilities ----------

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